import os
import sys
import ctypes
from ctypes import c_char_p, c_int, POINTER, Structure

class MD5Result(Structure):
    _fields_ = [
        ("filePath", c_char_p),
        ("md5Hash", c_char_p)
    ]

def load_library():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    if sys.platform == "win32":
        lib_name = "md5calculator.dll"
    else:
        lib_name = "libmd5calculator.so"
    
    lib_path = os.path.join(script_dir, lib_name)
    if not os.path.exists(lib_path):
        raise FileNotFoundError(f"无法找到库文件: {lib_path}")
    
    return ctypes.CDLL(lib_path)

def calculate_file_md5(lib, file_path):
    if not os.path.isfile(file_path):
        print(f"错误：文件 '{file_path}' 不存在")
        return

    lib.calculateFileMD5.restype = c_char_p
    lib.calculateFileMD5.argtypes = [c_char_p]
    
    result = lib.calculateFileMD5(file_path.encode('utf-8'))
    if result:
        print(f"{file_path}: {result.decode('utf-8')}")
    else:
        print(f"错误：无法计算文件 '{file_path}' 的MD5值")

def calculate_directory_md5(lib, dir_path):
    if not os.path.isdir(dir_path):
        print(f"错误：目录 '{dir_path}' 不存在")
        return

    results_ptr = POINTER(MD5Result)()
    count = c_int(0)

    lib.calculateDirectoryMD5.argtypes = [c_char_p, POINTER(POINTER(MD5Result)), POINTER(c_int)]
    lib.calculateDirectoryMD5.restype = None
    lib.calculateDirectoryMD5(dir_path.encode('utf-8'), ctypes.byref(results_ptr), ctypes.byref(count))

    if count.value > 0:
        for i in range(count.value):
            result = results_ptr[i]
            print(f"{result.filePath.decode('utf-8')}: {result.md5Hash.decode('utf-8')}")
        
        lib.freeResults.argtypes = [POINTER(MD5Result)]
        lib.freeResults(results_ptr)
    else:
        print(f"目录 '{dir_path}' 中没有找到文件")

def print_usage():
    print("使用方法：")
    print("计算单个文件：python md5_cli.py -f <文件路径>")
    print("计算目录下所有文件：python md5_cli.py -d <目录路径>")

def main():
    if len(sys.argv) != 3 or sys.argv[1] not in ["-f", "-d"]:
        print_usage()
        return

    try:
        lib = load_library()
    except Exception as e:
        print(f"错误：无法加载MD5计算器库：{str(e)}")
        return

    path = sys.argv[2]
    if sys.argv[1] == "-f":
        calculate_file_md5(lib, path)
    else:
        calculate_directory_md5(lib, path)

if __name__ == "__main__":
    main()