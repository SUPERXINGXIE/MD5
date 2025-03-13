以下是整理后的Markdown文件内容：

---

# MD5计算器

这是一个跨平台的MD5计算工具，可以计算单个文件或目录下所有文件的MD5值。该工具由C++编写的动态链接库和Python命令行工具组成。

## 功能特点

• 支持计算单个文件的MD5值  
• 支持递归计算目录下所有文件的MD5值  
• 跨平台支持（Windows和Linux）  
• 使用OpenSSL库进行MD5计算  
• 提供简单的命令行接口  

---

## 编译指南

### Windows 环境配置

1. **安装 Visual Studio 2022**  
   • 下载并安装 [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)  
   • 在安装程序中选择「使用 C++ 的桌面开发」工作负载  
   • 确保安装以下组件：  
     ◦ MSVC v143 - VS 2022 C++ x64/x86 生成工具  
     ◦ Windows 10/11 SDK  
     ◦ C++ CMake 工具  

2. **安装 OpenSSL**  
   • 下载 [OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html)  
   • 选择 Win64 OpenSSL v3.x.x 完整版（非 Light 版）  
   • 安装到默认目录 `C:\Program Files\OpenSSL-Win64`  
   • 安装时选择「Copy OpenSSL DLLs to」并选择「The OpenSSL binaries (/bin) directory」  

3. **安装 CMake**  
   • 下载并安装 [CMake](https://cmake.org/download/)  
   • 安装时选择「Add CMake to the system PATH for all users」  

---

### Linux 环境配置

1. **更新系统包**  
   • 打开终端，执行：  
     ```bash
     sudo apt-get update
     ```

2. **安装编译工具和依赖库**  
   • 安装GCC、CMake、OpenSSL开发库和Python3：  
     ```bash
     sudo apt-get install build-essential cmake libssl-dev python3
     ```

---

## 编译步骤

### Windows 编译步骤

1. 打开 `Developer PowerShell for VS 2022`  
2. 执行以下命令：  
   ```bash
   mkdir build
   cd build
   cmake -G "Visual Studio 17 2022" -A x64 ..
   cmake --build . --config Release
   ```  
3. 构建完成后，`md5calculator.dll` 将自动复制到项目根目录。  

---

### Linux 编译步骤

1. 打开终端，进入项目目录  
2. 执行以下命令：  
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```  
3. 构建完成后，`libmd5calculator.so` 将自动复制到项目根目录。  

---

## 使用说明

编译完成后，可以使用Python脚本来计算MD5值：

### 计算单个文件的MD5值
```bash
python3 md5_cli.py -f <文件路径>
```

### 计算目录下所有文件的MD5值
```bash
python3 md5_cli.py -d <目录路径>
```

---

## 常见问题

### Q: Linux下CMake报错“Unknown CMake command 'add_compile_definitions'”怎么办？  
**A**: 已修复。现在的CMakeLists.txt使用CMake 3.10兼容的命令，适用于大多数Linux系统上的默认CMake版本。  

### Q: Python脚本找不到库文件怎么办？  
**A**: 确保构建完成后库文件（`md5calculator.dll`或`libmd5calculator.so`）位于Python脚本同一目录。新的构建过程会自动复制这些文件到项目根目录。  

---

通过以上内容，可以快速了解、编译和使用MD5计算器工具。