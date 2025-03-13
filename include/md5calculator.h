#ifndef MD5CALCULATOR_H
#define MD5CALCULATOR_H

#ifdef _WIN32
#ifdef MD5CALCULATOR_EXPORTS
#define MD5CALCULATOR_API __declspec(dllexport)
#else
#define MD5CALCULATOR_API __declspec(dllimport)
#endif
#else
#define MD5CALCULATOR_API
#endif

#include <string>

struct MD5Result {
    std::string filePath;
    std::string md5Hash;
};

extern "C" {
    MD5CALCULATOR_API const char* calculateFileMD5(const char* filePath);
    MD5CALCULATOR_API void calculateDirectoryMD5(const char* dirPath, MD5Result** results, int* count);
    MD5CALCULATOR_API void freeResults(MD5Result* results);
}

#endif // MD5CALCULATOR_H