cmake_minimum_required(VERSION 3.10)
project(UniMD5)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 强制静态链接运行时
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options(/MT)
endif()

# 指定 OpenSSL 静态链接
set(OPENSSL_USE_STATIC_LIBS TRUE)
if(WIN32)
    set(OPENSSL_MSVC_STATIC_RT TRUE)
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
endif()
# Linux 下不指定 OPENSSL_ROOT_DIR，使用系统默认路径（如 /usr/lib/x86_64-linux-gnu）
find_package(OpenSSL REQUIRED)
if(NOT OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL not found. Please ensure static libraries are installed.")
endif()

# 添加共享库目标
add_library(md5calculator SHARED
    src/md5calculator.cpp
)

# 跨平台宏定义
if(WIN32)
    target_compile_definitions(md5calculator PRIVATE 
        _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
        _CRT_SECURE_NO_WARNINGS
        MD5CALCULATOR_EXPORTS
    )
else()
    target_compile_definitions(md5calculator PRIVATE MD5CALCULATOR_EXPORTS)
endif()

# 设置头文件路径
target_include_directories(md5calculator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
)

# 链接库
if(WIN32)
    target_link_libraries(md5calculator PRIVATE 
        ${OPENSSL_CRYPTO_LIBRARY}
        Ws2_32.lib
        Crypt32.lib
    )
else()
    target_link_libraries(md5calculator PRIVATE 
        ${OPENSSL_CRYPTO_LIBRARY}
        -static-libstdc++  # 静态链接 libstdc++
        -static-libgcc     # 静态链接 libgcc
    )
endif()

# 构建后复制库文件
if(WIN32)
    add_custom_command(TARGET md5calculator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/md5calculator.dll
            ${CMAKE_SOURCE_DIR}/md5calculator.dll
    )
else()
    add_custom_command(TARGET md5calculator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_BINARY_DIR}/bin/libmd5calculator.so
            ${CMAKE_SOURCE_DIR}/libmd5calculator.so
    )
endif()

# 安装目标（可选）
install(TARGETS md5calculator
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(FILES include/md5calculator.h DESTINATION include)