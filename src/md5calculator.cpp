#include "md5calculator.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

std::string calculateMD5(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }

    EVP_MD_CTX* mdContext = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdContext, EVP_md5(), nullptr);

    constexpr size_t bufferSize = 4096;
    char buffer[bufferSize];
    while (file.read(buffer, bufferSize) || file.gcount()) {
        EVP_DigestUpdate(mdContext, buffer, file.gcount());
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    EVP_DigestFinal_ex(mdContext, hash, &hashLen);
    EVP_MD_CTX_free(mdContext);
    file.close();

    std::stringstream ss;
    for (unsigned int i = 0; i < hashLen; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

#ifdef _WIN32
std::vector<std::string> getAllFiles(const std::string& dirPath) {
    std::vector<std::string> files;
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    std::string searchPath = dirPath + "\\*";

    hFind = FindFirstFile(searchPath.c_str(), &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return files;
    }

    do {
        if (findData.cFileName[0] == '.') {
            continue;
        }
        std::string fullPath = dirPath + "\\" + findData.cFileName;
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            auto subFiles = getAllFiles(fullPath);
            files.insert(files.end(), subFiles.begin(), subFiles.end());
        } else {
            files.push_back(fullPath);
        }
    } while (FindNextFile(hFind, &findData) != 0);

    FindClose(hFind);
    return files;
}
#else
std::vector<std::string> getAllFiles(const std::string& dirPath) {
    std::vector<std::string> files;
    DIR* dir = opendir(dirPath.c_str());
    if (!dir) {
        return files;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        std::string fullPath = dirPath + "/" + entry->d_name;
        struct stat statBuf;
        if (stat(fullPath.c_str(), &statBuf) == -1) {
            continue;
        }
        if (S_ISDIR(statBuf.st_mode)) {
            auto subFiles = getAllFiles(fullPath);
            files.insert(files.end(), subFiles.begin(), subFiles.end());
        } else if (S_ISREG(statBuf.st_mode)) {
            files.push_back(fullPath);
        }
    }
    closedir(dir);
    return files;
}
#endif

extern "C" MD5CALCULATOR_API char* calculateFileMD5(const char* filePath) {
    std::string md5 = calculateMD5(filePath);
    if (md5.empty()) {
        return nullptr;
    }
    char* result = (char*)malloc(md5.length() + 1);
    strcpy(result, md5.c_str());
    return result;
}

extern "C" MD5CALCULATOR_API void calculateDirectoryMD5(const char* dirPath, MD5Result** results, int* count) {
    std::vector<std::string> files = getAllFiles(dirPath);
    *count = static_cast<int>(files.size());
    *results = (MD5Result*)malloc(*count * sizeof(MD5Result));

    for (int i = 0; i < *count; ++i) {
        std::string md5 = calculateMD5(files[i]);
        (*results)[i].filePath = (char*)malloc(files[i].length() + 1);
        (*results)[i].md5 = (char*)malloc(md5.length() + 1);
        strcpy((*results)[i].filePath, files[i].c_str());
        strcpy((*results)[i].md5, md5.c_str());
    }
}

extern "C" MD5CALCULATOR_API void freeMD5Results(MD5Result* results, int count) {
    for (int i = 0; i < count; ++i) {
        free(results[i].filePath);
        free(results[i].md5);
    }
    free(results);
}