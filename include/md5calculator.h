#ifndef MD5CALCULATOR_H
#define MD5CALCULATOR_H

#ifdef _WIN32
    #ifdef MD5CALCULATOR_EXPORTS
        #define MD5CALCULATOR_API __declspec(dllexport)
    #else
        #define MD5CALCULATOR_API __declspec(dllimport)
    #endif
#else
    #define MD5CALCULATOR_API __attribute__((visibility("default")))
#endif

extern "C" {
    MD5CALCULATOR_API char* calculateFileMD5(const char* filePath);
    typedef struct {
        char* filePath;
        char* md5;
    } MD5Result;
    MD5CALCULATOR_API void calculateDirectoryMD5(const char* dirPath, MD5Result** results, int* count);
    MD5CALCULATOR_API void freeMD5Results(MD5Result* results, int count);
}

#endif // MD5CALCULATOR_H