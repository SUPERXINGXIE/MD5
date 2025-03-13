cmake_minimum_required(VERSION 3.10)
project(MD5Calculator)

# 设置 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 查找 OpenSSL
find_package(OpenSSL REQUIRED)

# 添加共享库目标
add_library(md5calculator SHARED
    src/md5calculator.cpp
)

# Windows 下禁用 C++17 弃用警告
if(MSVC)
    target_compile_definitions(md5calculator PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
endif()

# 定义导出宏
target_compile_definitions(md5calculator PRIVATE MD5CALCULATOR_EXPORTS)

# 设置头文件路径
target_include_directories(md5calculator PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OPENSSL_INCLUDE_DIR}
)

# 链接 OpenSSL
target_link_libraries(md5calculator PRIVATE OpenSSL::Crypto)

# GCC 7.x 下链接 stdc++fs 并定义 USE_EXPERIMENTAL_FS
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.0")
        target_link_libraries(md5calculator PRIVATE stdc++fs)
        target_compile_definitions(md5calculator PRIVATE USE_EXPERIMENTAL_FS)
    endif()
endif()

# 构建后复制库文件到项目根目录
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

# 安装目标
install(TARGETS md5calculator
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(FILES include/md5calculator.h DESTINATION include)