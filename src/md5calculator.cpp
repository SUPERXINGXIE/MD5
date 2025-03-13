#include "md5calculator.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>

#ifdef USE_EXPERIMENTAL_FS
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#ifdef _WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

static std::string calculateMD5(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }

    EVP_MD_CTX* md5Context = EVP_MD_CTX_new();
    if (!md5Context || EVP_DigestInit_ex(md5Context, EVP_md5(), nullptr) != 1) {
        EVP_MD_CTX_free(md5Context);
        return "";
    }

    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        if (EVP_DigestUpdate(md5Context, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(md5Context);
            return "";
        }
    }
    if (file.gcount() > 0) {
        if (EVP_DigestUpdate(md5Context, buffer, file.gcount()) != 1) {
            EVP_MD_CTX_free(md5Context);
            return "";
        }
    }

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLen = 0;
    if (EVP_DigestFinal_ex(md5Context, digest, &digestLen) != 1) {
        EVP_MD_CTX_free(md5Context);
        return "";
    }
    EVP_MD_CTX_free(md5Context);

    std::stringstream ss;
    for (unsigned int i = 0; i < digestLen; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(digest[i]);
    }

    return ss.str();
}

static std::vector<std::string> getAllFiles(const std::string& dirPath) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
#ifdef USE_EXPERIMENTAL_FS
            // GCC 7.x: 使用 status() 获取文件类型
            if (fs::is_regular_file(entry.status())) {
                files.push_back(entry.path().string());
            }
#else
            // GCC 8.0+ 或 MSVC: 直接使用 is_regular_file()
            if (entry.is_regular_file()) {
                files.push_back(entry.path().string());
            }
#endif
        }
    } catch (const std::exception&) {
        // 忽略目录访问错误
    }
    return files;
}

extern "C" {
    static thread_local std::string lastResult;

    MD5CALCULATOR_API const char* calculateFileMD5(const char* filePath) {
        lastResult = calculateMD5(filePath);
        return lastResult.c_str();
    }

    MD5CALCULATOR_API void calculateDirectoryMD5(const char* dirPath, MD5Result** results, int* count) {
        std::vector<std::string> files = getAllFiles(dirPath);
        *count = static_cast<int>(files.size());

        if (*count == 0) {
            *results = nullptr;
            return;
        }

        *results = new MD5Result[*count];
        for (int i = 0; i < *count; i++) {
            (*results)[i].filePath = files[i];
            (*results)[i].md5Hash = calculateMD5(files[i]);
        }
    }

    MD5CALCULATOR_API void freeResults(MD5Result* results) {
        delete[] results;
    }
}