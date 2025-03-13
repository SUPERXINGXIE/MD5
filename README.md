# MD5计算器 / MD5 Calculator
本工具是在跨平台MD5值一致性需求的背景下开发的统一工具，旨在消除Linux和Windows下计算结果的差异。/This tool is a unified tool developed against the background of the need for cross-platform MD5 value consistency, and aims to eliminate the difference in calculation results under Linux and Windows. 

这是一个跨平台的MD5计算工具，可以计算单个文件或目录下所有文件的MD5值。该工具由C++编写的动态链接库和Python命令行工具组成。/This is a cross-platform MD5 calculation tool that can compute the MD5 hash of a single file or all files in a directory. It consists of a C++ dynamic link library and a Python command-line tool. 




## 功能特点 / Features

- 支持计算单个文件的MD5值 / Supports calculating the MD5 hash of a single file  
- 支持递归计算目录下所有文件的MD5值 / Supports recursively calculating the MD5 hashes of all files in a directory  
- 跨平台支持（Windows和Linux） / Cross-platform support (Windows and Linux)  
- 使用OpenSSL库进行MD5计算 / Uses the OpenSSL library for MD5 calculation  
- 提供简单的命令行接口 / Provides a simple command-line interface  

---

## 编译指南 / Compilation Guide

### Windows 环境配置 / Windows Environment Setup

1. **安装 Visual Studio 2022 / Install Visual Studio 2022**  
   - 下载并安装 [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) / Download and install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)  
   - 在安装程序中选择「使用 C++ 的桌面开发」工作负载 / Select the "Desktop development with C++" workload in the installer  
   - 确保安装以下组件 / Ensure the following components are installed:  
     - MSVC v143 - VS 2022 C++ x64/x86 生成工具 / MSVC v143 - VS 2022 C++ x64/x86 build tools  
     - Windows 10/11 SDK  
     - C++ CMake 工具 / C++ CMake tools  

2. **安装 OpenSSL / Install OpenSSL**  
   - 下载 [OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html) / Download [OpenSSL for Windows](https://slproweb.com/products/Win32OpenSSL.html)  
   - 选择 Win64 OpenSSL v3.x.x 完整版（非 Light 版） / Choose Win64 OpenSSL v3.x.x full version (not the Light version)  
   - 安装到默认目录 `C:\Program Files\OpenSSL-Win64` / Install to the default directory `C:\Program Files\OpenSSL-Win64`  
   - 安装时选择「Copy OpenSSL DLLs to」并选择「The OpenSSL binaries (/bin) directory」 / During installation, select "Copy OpenSSL DLLs to" and choose "The OpenSSL binaries (/bin) directory"  

3. **安装 CMake / Install CMake**  
   - 下载并安装 [CMake](https://cmake.org/download/) / Download and install [CMake](https://cmake.org/download/)  
   - 安装时选择「Add CMake to the system PATH for all users」 / During installation, select "Add CMake to the system PATH for all users"  

---

### Linux 环境配置 / Linux Environment Setup

1. **更新系统包 / Update System Packages**  
   - 打开终端，执行 / Open a terminal and execute:  
     ```bash
     sudo apt-get update
     ```

2. **安装编译工具和依赖库 / Install Compilation Tools and Dependencies**  
   - 安装GCC、CMake、OpenSSL开发库和Python3 / Install GCC, CMake, OpenSSL development libraries, and Python3:  
     ```bash
     sudo apt-get install build-essential cmake libssl-dev python3
     ```

---

## 编译步骤 / Compilation Steps

### Windows 编译步骤 / Windows Compilation Steps

1. 打开 `Developer PowerShell for VS 2022` / Open `Developer PowerShell for VS 2022`  
2. 执行以下命令 / Execute the following commands:  
   ```bash
   mkdir build
   cd build
   cmake -G "Visual Studio 17 2022" -A x64 ..
   cmake --build . --config Release
   ```  
3. 构建完成后，`md5calculator.dll` 将自动复制到项目根目录 / After the build is complete, `md5calculator.dll` will be automatically copied to the project root directory.  

---

### Linux 编译步骤 / Linux Compilation Steps

1. 打开终端，进入项目目录 / Open a terminal and navigate to the project directory  
2. 执行以下命令 / Execute the following commands:  
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```  
3. 构建完成后，`libmd5calculator.so` 将自动复制到项目根目录 / After the build is complete, `libmd5calculator.so` will be automatically copied to the project root directory.  

---

## 使用说明 / Usage Instructions

编译完成后，可以使用Python脚本来计算MD5值 / After compilation, you can use the Python script to calculate MD5 hashes:

### 计算单个文件的MD5值 / Calculate the MD5 Hash of a Single File
```bash
python3 md5_cli.py -f <文件路径> / python3 md5_cli.py -f <file_path>
```

### 计算目录下所有文件的MD5值 / Calculate the MD5 Hashes of All Files in a Directory
```bash
python3 md5_cli.py -d <目录路径> / python3 md5_cli.py -d <directory_path>
```

---

## 验证结果 / Verification Results

以下是在Linux和Windows上对同一个文件（`README.md`）进行MD5校验的验证结果 / Below are the verification results of calculating the MD5 hash of the same file (`README.md`) on Linux and Windows:

### Linux 验证结果 / Linux Verification Results
```bash
ubuntu@sh-48-149:~/MD5$ python3 md5_cli.py -f README.md
README.md: 349fd0f557b23323a82195b22976c20d

ubuntu@sh-48-149:~/MD5$ md5sum README.md 
349fd0f557b23323a82195b22976c20d  README.md
```

### Windows 验证结果 / Windows Verification Results
```bash
D:\MD5> openssl dgst -md5 .\README.md
MD5(.\README.md)= 349fd0f557b23323a82195b22976c20d

D:\MD5> python md5_cli.py -f .\README.md
.\README.md: 349fd0f557b23323a82195b22976c20d
```

### 验证结论 / Verification Conclusion
- 无论是使用 `python3 md5_cli.py`、`md5sum` 还是 `openssl dgst -md5`，计算结果均为 `349fd0f557b23323a82195b22976c20d` / Whether using `python3 md5_cli.py`, `md5sum`, or `openssl dgst -md5`, the result is consistently `349fd0f557b23323a82195b22976c20d`.  
- 验证通过，工具在Linux和Windows上的计算结果一致 / Verification passed; the tool produces consistent results on Linux and Windows.  

---

## 代码结构 / Code Structure

项目目录结构如下 / The project directory structure is as follows:

```
项目根目录 / Project Root Directory/
├── CMakeLists.txt
├── include/
│   └── md5calculator.h
├── src/
│   └── md5calculator.cpp
└── md5_cli.py
```

- **CMakeLists.txt**：CMake配置文件，用于跨平台编译 / CMake configuration file for cross-platform compilation.  
- **include/md5calculator.h**：头文件，定义了库的接口和结构体 / Header file defining the library's interface and structures.  
- **src/md5calculator.cpp**：源文件，实现了MD5计算和文件遍历逻辑 / Source file implementing MD5 calculation and file traversal logic.  
- **md5_cli.py**：Python脚本，用于调用动态链接库并提供命令行接口 / Python script for calling the dynamic link library and providing a command-line interface.  

---

## 核心逻辑讲解 / Core Logic Explanation

### C++动态链接库（md5calculator.dll / libmd5calculator.so） / C++ Dynamic Link Library (md5calculator.dll / libmd5calculator.so)

#### 1. MD5计算逻辑 / MD5 Calculation Logic
- 使用OpenSSL的EVP接口进行MD5哈希计算 / Uses OpenSSL's EVP interface for MD5 hash calculation.  
- 核心函数：`calculateMD5(const std::string& filePath)` / Core function: `calculateMD5(const std::string& filePath)`  
  - 打开文件并以二进制模式读取 / Opens the file and reads it in binary mode.  
  - 初始化EVP_MD_CTX上下文并使用EVP_md5()算法 / Initializes an EVP_MD_CTX context and uses the EVP_md5() algorithm.  
  - 分块读取文件内容并更新哈希 / Reads file contents in chunks and updates the hash.  
  - 最终生成MD5哈希值并返回 / Generates and returns the final MD5 hash value.  

#### 2. 文件遍历逻辑 / File Traversal Logic
- 使用C++17的`<filesystem>`（或GCC 7.x的`<experimental/filesystem>`）进行目录递归遍历 / Uses C++17's `<filesystem>` (or `<experimental/filesystem>` for GCC 7.x) for recursive directory traversal.  
- 核心函数：`getAllFiles(const std::string& dirPath)` / Core function: `getAllFiles(const std::string& dirPath)`  
  - 递归遍历目录，收集所有常规文件的路径 / Recursively traverses the directory and collects paths of all regular files.  
  - 根据编译器版本，适配文件类型判断逻辑 / Adapts file type checking logic based on the compiler version.  

#### 3. 对外接口 / External Interface
- 提供两个C风格的函数接口，供Python调用 / Provides two C-style function interfaces for Python to call:  
  - `calculateFileMD5(const char* filePath)`：计算单个文件的MD5 / Calculates the MD5 of a single file.  
  - `calculateDirectoryMD5(const char* dirPath, MD5Result** results, int* count)`：计算目录下所有文件的MD5 / Calculates the MD5 of all files in a directory.  

---

### Python命令行工具（md5_cli.py） / Python Command-Line Tool (md5_cli.py)

#### 1. 加载动态链接库 / Load Dynamic Link Library
- 根据操作系统加载对应的库文件（`md5calculator.dll`或`libmd5calculator.so`） / Loads the appropriate library file based on the operating system (`md5calculator.dll` or `libmd5calculator.so`).  

#### 2. 调用C函数 / Call C Functions
- 使用`ctypes`模块调用C函数，处理文件路径和MD5结果 / Uses the `ctypes` module to call C functions, handling file paths and MD5 results.  
- 支持命令行参数`-f`（文件）和`-d`（目录） / Supports command-line arguments `-f` (file) and `-d` (directory).  

#### 3. 输出结果 / Output Results
- 打印文件路径和对应的MD5哈希值 / Prints file paths and their corresponding MD5 hash values.  

---

## 跨平台兼容性核心逻辑 / Core Logic for Cross-Platform Compatibility

### 1. CMake配置 / CMake Configuration
- 使用CMake管理编译过程，确保跨平台兼容 / Uses CMake to manage the compilation process, ensuring cross-platform compatibility.  
- 检测编译器版本，针对GCC 7.x链接`stdc++fs`并定义`USE_EXPERIMENTAL_FS` / Detects compiler version, linking `stdc++fs` and defining `USE_EXPERIMENTAL_FS` for GCC 7.x.  
- 自动复制生成的库文件到项目根目录，方便Python脚本调用 / Automatically copies the generated library files to the project root directory for easy Python script access.  

### 2. 文件系统适配 / File System Adaptation
- 在C++代码中，通过预处理宏`USE_EXPERIMENTAL_FS` / In C++ code, via the preprocessor macro `USE_EXPERIMENTAL_FS`:  
  - GCC 7.x：使用`<experimental/filesystem>`和`fs::is_regular_file(entry.status())` / GCC 7.x: Uses `<experimental/filesystem>` and `fs::is_regular_file(entry.status())`.  
  - GCC 8.0+ / MSVC：使用`<filesystem>`和`entry.is_regular_file()` / GCC 8.0+ / MSVC: Uses `<filesystem>` and `entry.is_regular_file()`.  

### 3. 路径分隔符 / Path Separator
- 定义`PATH_SEPARATOR`宏，根据操作系统选择路径分隔符（Windows: `\`, Linux: `/`） / Defines the `PATH_SEPARATOR` macro, selecting the path separator based on the OS (Windows: `\`, Linux: `/`).  

### 4. 库文件命名 / Library File Naming
- Windows下生成`md5calculator.dll`，Linux下生成`libmd5calculator.so` / Generates `md5calculator.dll` on Windows and `libmd5calculator.so` on Linux.  
- Python脚本根据操作系统加载对应的库文件 / The Python script loads the appropriate library file based on the operating system.  

---

## 新方案对比市面现有方案的优点 / Advantages Over Existing Solutions

与市面上的常见MD5计算工具（如`md5sum`、`CertUtil`、`openssl dgst -md5`、Python `hashlib`）相比，本方案具有以下优点 / Compared to common MD5 calculation tools on the market (e.g., `md5sum`, `CertUtil`, `openssl dgst -md5`, Python `hashlib`), this solution offers the following advantages:

1. **跨平台一致性 / Cross-Platform Consistency**  
   - 优点：支持Windows和Linux，结果一致（MD5值均为`349fd0f557b23323a82195b22976c20d`） / Advantage: Supports Windows and Linux with consistent results (MD5 value is always `349fd0f557b23323a82195b22976c20d`).  
   - 对比：`md5sum`仅限Linux，`CertUtil`仅限Windows，而本方案通过CMake和条件编译实现无缝跨平台支持 / Comparison: `md5sum` is Linux-only, `CertUtil` is Windows-only, while this solution achieves seamless cross-platform support via CMake and conditional compilation.

2. **目录递归计算 / Directory Recursive Calculation**  
   - 优点：内置支持递归计算目录下所有文件的MD5，无需手动遍历 / Advantage: Built-in support for recursively calculating MD5 hashes of all files in a directory, no manual traversal required.  
   - 对比：`md5sum`和`openssl dgst`需脚本支持，`hashlib`需额外代码，本方案通过`getAllFiles`函数实现开箱即用 / Comparison: `md5sum` and `openssl dgst` require scripting, `hashlib` needs extra code, while this solution offers out-of-the-box functionality via the `getAllFiles` function.

3. **高性能与模块化 / High Performance and Modularity**  
   - 优点：基于C++和OpenSSL实现，性能优于Python脚本，可作为动态链接库集成到其他项目 / Advantage: Based on C++ and OpenSSL, outperforms Python scripts and can be integrated into other projects as a dynamic link library.  
   - 对比：`hashlib`性能较低，图形化工具不可扩展，本方案分块读取文件（4KB缓冲区）优化性能 / Comparison: `hashlib` has lower performance, graphical tools lack extensibility, while this solution optimizes performance with 4KB chunked file reading.

4. **简单易用的命令行接口 / Simple and User-Friendly Command-Line Interface**  
   - 优点：通过Python脚本提供直观命令（`-f`和`-d`），输出格式统一 / Advantage: Provides intuitive commands (`-f` and `-d`) via a Python script with consistent output formatting.  
   - 对比：`openssl dgst`和`CertUtil`命令复杂，本方案更易上手 / Comparison: `openssl dgst` and `CertUtil` have complex commands, while this solution is more user-friendly.

5. **兼容老旧环境 / Compatibility with Older Environments**  
   - 优点：支持CMake 3.10和GCC 7.x，适配老旧Linux系统 / Advantage: Supports CMake 3.10 and GCC 7.x, compatible with older Linux systems.  
   - 对比：许多工具依赖最新环境，本方案通过条件编译和CMake配置降低部署要求 / Comparison: Many tools rely on modern environments, while this solution reduces deployment requirements via conditional compilation and CMake configuration.

6. **扩展性 / Extensibility**  
   - 优点：提供C++接口和Python封装，可扩展到其他哈希算法或功能 / Advantage: Offers C++ interfaces and Python encapsulation, extensible to other hash algorithms or features.  
   - 对比：内置工具功能固定，本方案的动态链接库设计更灵活 / Comparison: Built-in tools have fixed functionality, while this solution’s dynamic link library design is more flexible.

---

## 常见问题 / FAQ

### Q: Linux下CMake报错“Unknown CMake command 'add_compile_definitions'”怎么办？ / What to do if CMake reports "Unknown CMake command 'add_compile_definitions'" on Linux?  
**A**: 已修复。现在的CMakeLists.txt使用CMake 3.10兼容的命令，适用于大多数Linux系统上的默认CMake版本 / Fixed. The current CMakeLists.txt uses CMake 3.10-compatible commands, suitable for most default CMake versions on Linux systems.  

### Q: Python脚本找不到库文件怎么办？ / What to do if the Python script cannot find the library file?  
**A**: 确保构建完成后库文件（`md5calculator.dll`或`libmd5calculator.so`）位于Python脚本同一目录。新的构建过程会自动复制这些文件到项目根目录 / Ensure that after building, the library file (`md5calculator.dll` or `libmd5calculator.so`) is in the same directory as the Python script. The new build process automatically copies these files to the project root directory.  

---
