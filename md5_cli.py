import sys
import os
import ctypes
from ctypes import c_char_p, POINTER, Structure, c_int

class MD5Result(Structure):
    _fields_ = [("filePath", c_char_p), ("md5", c_char_p)]

# 调试加载路径
script_dir = os.path.dirname(os.path.abspath(__file__))
#print(f"当前脚本目录: {script_dir}")
#print(f"当前工作目录: {os.getcwd()}")

if sys.platform == "win32":
    dll_path = os.path.join(script_dir, "md5calculator.dll")
    #print(f"尝试加载 Windows DLL: {dll_path}")
    try:
        md5_lib = ctypes.CDLL(dll_path)
    except OSError as e:
        print(f"错误：无法加载MD5计算器库：{e}")
        sys.exit(1)
else:
    so_path = os.path.join(script_dir, "libmd5calculator.so")
    #print(f"尝试加载 Linux SO: {so_path}")
    if not os.path.exists(so_path):
        print(f"文件不存在: {so_path}")
    try:
        md5_lib = ctypes.CDLL(so_path)
        #print("加载成功")
    except OSError as e:
        print(f"错误：无法加载MD5计算器库：{e}")
        sys.exit(1)

md5_lib.calculateFileMD5.argtypes = [c_char_p]
md5_lib.calculateFileMD5.restype = c_char_p

md5_lib.calculateDirectoryMD5.argtypes = [c_char_p, POINTER(POINTER(MD5Result)), POINTER(c_int)]
md5_lib.calculateDirectoryMD5.restype = None

md5_lib.freeMD5Results.argtypes = [POINTER(MD5Result), c_int]
md5_lib.freeMD5Results.restype = None

def calculate_file_md5(file_path):
    result = md5_lib.calculateFileMD5(file_path.encode('utf-8'))
    if result:
        return result.decode('utf-8')
    else:
        return None

def calculate_directory_md5(dir_path):
    results = POINTER(MD5Result)()
    count = c_int()
    md5_lib.calculateDirectoryMD5(dir_path.encode('utf-8'), ctypes.byref(results), ctypes.byref(count))
    md5_list = []
    for i in range(count.value):
        md5_list.append((results[i].filePath.decode('utf-8'), results[i].md5.decode('utf-8')))
    md5_lib.freeMD5Results(results, count)
    return md5_list

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("用法: python md5_cli.py [-f 文件路径 | -d 目录路径]")
        sys.exit(1)

    option = sys.argv[1]
    path = sys.argv[2]

    if option == "-f":
        md5 = calculate_file_md5(path)
        if md5:
            print(f"{path}: {md5}")
        else:
            print(f"错误：无法计算文件 {path} 的MD5值")
    elif option == "-d":
        md5_list = calculate_directory_md5(path)
        for file_path, md5 in md5_list:
            print(f"{file_path}: {md5}")
    else:
        print("无效选项。使用 -f 计算单个文件，或 -d 计算目录")