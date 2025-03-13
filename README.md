以下是整理后的 `README.md` 内容，严格遵循 Markdown 语法，并包含双语说明：

---

# MD5计算器 / MD5 Calculator

本工具是在跨平台MD5值一致性需求的背景下开发的统一工具，旨在消除Linux和Windows下计算结果的差异。  
*This tool is a unified tool developed against the background of the need for cross-platform MD5 value consistency, aiming to eliminate the difference in calculation results under Linux and Windows.*

这是一个跨平台的MD5计算工具，可以计算单个文件或目录下所有文件的MD5值。该工具由C++编写的动态链接库和Python命令行工具组成。  
*This is a cross-platform MD5 calculation tool that can compute the MD5 hash of a single file or all files in a directory. It consists of a C++ dynamic link library and a Python command-line tool.*

## 功能特点 / Features

• 支持计算单个文件的MD5值 / *Supports calculating the MD5 hash of a single file*  
• 支持递归计算目录下所有文件的MD5值 / *Supports recursively calculating the MD5 hashes of all files in a directory*  
• 跨平台支持（Windows和Linux） / *Cross-platform support (Windows and Linux)*  
• 使用OpenSSL库进行MD5计算 / *Uses the OpenSSL library for MD5 calculation*  
• 提供简单的命令行接口 / *Provides a simple command-line interface*

---

## 编译指南 / Compilation Guide

环境要求 / Environment Requirements
​Python 3.7 或更高版本 / Python 3.7 or higher
本工具依赖于 Python 3.7 及以上版本，请确保系统已安装正确版本的 Python。
This tool requires Python 3.7 or higher. Please ensure the correct version of Python is installed on your system.

### Windows 环境配置 / Windows Environment Setup

1. **安装 Visual Studio 2022 / Install Visual Studio 2022**  
   • 下载并安装 [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)  
   • 在安装程序中选择「使用 C++ 的桌面开发」工作负载 / *Select the "Desktop development with C++" workload in the installer*  
   • 确保安装以下组件 / *Ensure the following components are installed:*  
     ◦ MSVC v143 - VS 2022 C++ x64/x86 生成工具 / *MSVC v143 - VS 2022 C++ x64/x86 build tools*  
     ◦ Windows 10/11 SDK  
     ◦ C++ CMake 工具 / *C++ CMake tools*  

2. **安装 OpenSSL / Install OpenSSL**  
   • 下载 [OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html)  
   • 选择 Win64 OpenSSL v3.x.x 完整版（非 Light 版） / *Choose Win64 OpenSSL v3.x.x full version (not the Light version)*  
   • 安装到默认目录 `C:\Program Files\OpenSSL-Win64` / *Install to the default directory `C:\Program Files\OpenSSL-Win64`*  
   • 安装时选择「Copy OpenSSL DLLs to」并选择「The OpenSSL binaries (/bin) directory」 / *During installation, select "Copy OpenSSL DLLs to" and choose "The OpenSSL binaries (/bin) directory"*  

3. **安装 CMake / Install CMake**  
   • 下载并安装 [CMake](https://cmake.org/download/)  
   • 安装时选择「Add CMake to the system PATH for all users」 / *During installation, select "Add CMake to the system PATH for all users"*  

### Linux 环境配置 / Linux Environment Setup

1. **更新系统包 / Update System Packages**  
   • 打开终端，执行 / *Open a terminal and execute:*  
     ```bash
     sudo apt-get update
     ```

2. **安装编译工具和依赖库 / Install Compilation Tools and Dependencies**  
   • 安装GCC、CMake、OpenSSL开发库和Python3 / *Install GCC, CMake, OpenSSL development libraries, and Python3:*  
     ```bash
     sudo apt-get install build-essential cmake libssl-dev python3
     ```

---

## 编译步骤 / Compilation Steps

### Windows 编译步骤 / Windows Compilation Steps

1. 打开 `Developer PowerShell for VS 2022` / *Open `Developer PowerShell for VS 2022`*  
2. 执行以下命令 / *Execute the following commands:*  
   ```powershell
   mkdir build
   cd build
   cmake -G "Visual Studio 17 2022" -A x64 -DOPENSSL_ROOT_DIR="C:/Program Files/OpenSSL-Win64" -DOPENSSL_USE_STATIC_LIBS=TRUE -DOPENSSL_MSVC_STATIC_RT=TRUE ..
   cmake --build . --config Release
   ```  
3. 构建完成后，`md5calculator.dll` 将自动复制到项目根目录 / *After the build is complete, `md5calculator.dll` will be automatically copied to the project root directory.*  
4. 检查依赖 / *Check dependencies:*  
   ```powershell
   dumpbin /dependents .\md5calculator.dll
   ```

### Linux 编译步骤 / Linux Compilation Steps

1. 打开终端，进入项目目录 / *Open a terminal and navigate to the project directory*  
2. 执行以下命令 / *Execute the following commands:*  
   ```bash
   mkdir build
   cd build
   cmake -DOPENSSL_USE_STATIC_LIBS=TRUE ..
   make
   ```  
3. 构建完成后，`libmd5calculator.so` 将自动复制到项目根目录 / *After the build is complete, `libmd5calculator.so` will be automatically copied to the project root directory.*  
4. 检查依赖 / *Check dependencies:*  
   ```bash
   ldd ./libmd5calculator.so
   ```

---

## 使用说明 / Usage Instructions

编译完成后，可以使用Python脚本来计算MD5值 / *After compilation, you can use the Python script to calculate MD5 hashes:*

### 计算单个文件的MD5值 / Calculate the MD5 Hash of a Single File
```bash
python3 md5_cli.py -f <文件路径> / python3 md5_cli.py -f <file_path>
```
*输出示例 / Output example:*
```
README.md: 349fd0f557b23323a82195b22976c20d
```

### 计算目录下所有文件的MD5值 / Calculate the MD5 Hashes of All Files in a Directory
```bash
python3 md5_cli.py -d <目录路径> / python3 md5_cli.py -d <directory_path>
```
*输出示例 / Output example:*
```
/path/to/dir/file1.txt: <md5_hash>
/path/to/dir/file2.txt: <md5_hash>
```

---

## 验证结果 / Verification Results

以下是在Linux和Windows上对同一个文件（`README.md`）进行MD5校验的验证结果 / *Below are the verification results of calculating the MD5 hash of the same file (`README.md`) on Linux and Windows:*

### Linux 验证结果 / Linux Verification Results
```bash
liushenshen@sh-48-149:~/MD5$ python3 md5_cli.py -f README.md
README.md: 349fd0f557b23323a82195b22976c20d

liushenshen@sh-48-149:~/MD5$ md5sum README.md 
349fd0f557b23323a82195b22976c20d  README.md
```

### Windows 验证结果 / Windows Verification Results
```powershell
D:\MD5> openssl dgst -md5 .\README.md
MD5(.\README.md)= 349fd0f557b23323a82195b22976c20d

D:\MD5> python md5_cli.py -f .\README.md
.\README.md: 349fd0f557b23323a82195b22976c20d
```

### 验证结论 / Verification Conclusion
• 无论是使用 `python3 md5_cli.py`、`md5sum` 还是 `openssl dgst -md5`，计算结果均为 `349fd0f557b23323a82195b22976c20d` / *Whether using `python3 md5_cli.py`, `md5sum`, or `openssl dgst -md5`, the result is consistently `349fd0f557b23323a82195b22976c20d`.*  
• 验证通过，工具在Linux和Windows上的计算结果一致 / *Verification passed; the tool produces consistent results on Linux and Windows.*

---

## 代码结构 / Code Structure

项目目录结构如下 / *The project directory structure is as follows:*

```
项目根目录 / Project Root Directory/
├── CMakeLists.txt
├── include/
│   └── md5calculator.h
├── src/
│   └── md5calculator.cpp
└── md5_cli.py
```

• **CMakeLists.txt**：CMake配置文件，用于跨平台编译 / *CMake configuration file for cross-platform compilation.*  
• **include/md5calculator.h**：头文件，定义了库的接口和结构体 / *Header file defining the library's interface and structures.*  
• **src/md5calculator.cpp**：源文件，实现了MD5计算和文件遍历逻辑 / *Source file implementing MD5 calculation and file traversal logic.*  
• **md5_cli.py**：Python脚本，用于调用动态链接库并提供命令行接口 / *Python script for calling the dynamic link library and providing a command-line interface.*

---

## 核心逻辑讲解 / Core Logic Explanation

### C++动态链接库（md5calculator.dll / libmd5calculator.so） / C++ Dynamic Link Library (md5calculator.dll / libmd5calculator.so)

#### 1. MD5计算逻辑 / MD5 Calculation Logic
• 使用OpenSSL的EVP接口进行MD5哈希计算 / *Uses OpenSSL's EVP interface for MD5 hash calculation.*  
• 核心函数：`calculateMD5(const std::string& filePath)` / *Core function: `calculateMD5(const std::string& filePath)`*  
  • 打开文件并以二进制模式读取 / *Opens the file and reads it in binary mode.*  
  • 初始化EVP_MD_CTX上下文并使用EVP_md5()算法 / *Initializes an EVP_MD_CTX context and uses the EVP_md5() algorithm.*  
  • 分块读取文件内容并更新哈希 / *Reads file contents in chunks and updates the hash.*  
  • 最终生成MD5哈希值并返回 / *Generates and returns the final MD5 hash value.*

#### 2. 文件遍历逻辑 / File Traversal Logic
• 使用平台特定的目录遍历方法 / *Uses platform-specific directory traversal methods:*  
  • Windows：`WIN32_FIND_DATA` 和 `FindFirstFile` / *Windows: `WIN32_FIND_DATA` and `FindFirstFile`.*  
  • Linux：`dirent.h` 和 `opendir` / *Linux: `dirent.h` and `opendir`.*  
• 核心函数：`getAllFiles(const std::string& dirPath)` / *Core function: `getAllFiles(const std::string& dirPath)`*  
  • 递归遍历目录，收集所有常规文件的路径 / *Recursively traverses the directory and collects paths of all regular files.*

#### 3. 对外接口 / External Interface
• 提供两个C风格的函数接口，供Python调用 / *Provides two C-style function interfaces for Python to call:*  
  • `calculateFileMD5(const char* filePath)`：计算单个文件的MD5 / *Calculates the MD5 of a single file.*  
  • `calculateDirectoryMD5(const char* dirPath, MD5Result** results, int* count)`：计算目录下所有文件的MD5 / *Calculates the MD5 of all files in a directory.*

### Python命令行工具（md5_cli.py） / Python Command-Line Tool (md5_cli.py)

#### 1. 加载动态链接库 / Load Dynamic Link Library
• 根据操作系统加载对应的库文件（`md5calculator.dll` 或 `libmd5calculator.so`） / *Loads the appropriate library file based on the operating system (`md5calculator.dll` or `libmd5calculator.so`).*

#### 2. 调用C函数 / Call C Functions
• 使用`ctypes`模块调用C函数，处理文件路径和MD5结果 / *Uses the `ctypes` module to call C functions, handling file paths and MD5 results.*  
• 支持命令行参数`-f`（文件）和`-d`（目录） / *Supports command-line arguments `-f` (file) and `-d` (directory).*

#### 3. 输出结果 / Output Results
• 默认仅输出文件路径和MD5值，报错时显示调试信息 / *By default, outputs only the file path and MD5 value; displays debug information on errors.*

---

## 跨平台兼容性核心逻辑 / Core Logic for Cross-Platform Compatibility

### 1. CMake配置 / CMake Configuration
• 使用CMake管理编译过程，确保跨平台兼容 / *Uses CMake to manage the compilation process, ensuring cross-platform compatibility.*  
• Windows：指定OpenSSL路径并静态链接 / *Windows: Specifies OpenSSL path and links statically.*  
• Linux：使用系统OpenSSL静态库（`/usr/lib/x86_64-linux-gnu/libcrypto.a`） / *Linux: Uses system OpenSSL static library (`/usr/lib/x86_64-linux-gnu/libcrypto.a`).*

### 2. 文件系统适配 / File System Adaptation
• Windows使用`FindFirstFile`，Linux使用`opendir` / *Windows uses `FindFirstFile`, Linux uses `opendir`.*  
• 通过预处理宏区分平台实现 / *Distinguishes platform implementations via preprocessor macros.*

### 3. 路径分隔符 / Path Separator
• Windows使用`\`，Linux使用`/`，在代码中动态适配 / *Windows uses `\`, Linux uses `/`, dynamically adapted in the code.*

### 4. 库文件命名 / Library File Naming
• Windows生成`md5calculator.dll`，Linux生成`libmd5calculator.so` / *Windows generates `md5calculator.dll`, Linux generates `libmd5calculator.so`.*  
• Python脚本根据操作系统加载对应库 / *The Python script loads the appropriate library based on the operating system.*

---

## 新方案对比市面现有方案的优点 / Advantages Over Existing Solutions

与市面上的常见MD5计算工具（如`md5sum`、`CertUtil`、`openssl dgst -md5`、Python `hashlib`）相比，本方案具有以下优点 / *Compared to common MD5 calculation tools on the market (e.g., `md5sum`, `CertUtil`, `openssl dgst -md5`, Python `hashlib`), this solution offers the following advantages:*

1. **跨平台一致性 / Cross-Platform Consistency**  
   • 优点：支持Windows和Linux，结果一致 / *Advantage: Supports Windows and Linux with consistent results.*  
   • 对比：`md5sum`仅限Linux，`CertUtil`仅限Windows / *Comparison: `md5sum` is Linux-only, `CertUtil` is Windows-only.*

2. **目录递归计算 / Directory Recursive Calculation**  
   • 优点：内置支持递归计算目录下所有文件的MD5 / *Advantage: Built-in support for recursively calculating MD5 hashes of all files in a directory.*  
   • 对比：`md5sum`和`openssl dgst`需额外脚本 / *Comparison: `md5sum` and `openssl dgst` require additional scripting.*

3. **高性能与模块化 / High Performance and Modularity**  
   • 优点：基于C++和OpenSSL实现，可作为库集成 / *Advantage: Based on C++ and OpenSSL, can be integrated as a library.*  
   • 对比：`hashlib`性能较低 / *Comparison: `hashlib` has lower performance.*

4. **简单易用的命令行接口 / Simple and User-Friendly Command-Line Interface**  
   • 优点：直观命令（`-f`和`-d`），输出简洁 / *Advantage: Intuitive commands (`-f` and `-d`) with concise output.*  
   • 对比：`openssl dgst`命令复杂 / *Comparison: `openssl dgst` has complex commands.*

5. **扩展性 / Extensibility**  
   • 优点：提供C++接口，可扩展到其他算法 / *Advantage: Offers C++ interfaces, extensible to other algorithms.*  
   • 对比：内置工具功能固定 / *Comparison: Built-in tools have fixed functionality.*

---
