// RAII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdexcpt>

void CopyFile(FILE* source, FILE* destination) {
    while (!feof(source)) {
        char ch = fgetc(source);
        fputc(ch, destination);
    }
}

void without_raii() {
    FILE* sampleFile = NULL;
    FILE* resultFile = NULL;
    auto err = fopen_s(&sampleFile, "sample.txt", "r");
    if (err != 0) {
        return;
    }

    err = fopen_s(&resultFile, "without_raii.txt", "w");
    if (err != 0) {
        fclose(sampleFile);
        return;
    }

    CopyFile(sampleFile, resultFile);
    fclose(sampleFile);
    fclose(resultFile);
}

class FileWrapper {
private:
    FILE* fp;

public:
    FileWrapper(const std::string& fileName, const std::string& mode) {
        auto err = fopen_s(&fp, fileName.c_str(), mode.c_str());
        if (err != 0) {
            throw std::runtime_error("Failed to open file");
        }
    }

    ~FileWrapper() noexcept {
        if (fp) {
            fclose(fp);
            fp = NULL;
        }
    }

    operator FILE* () { return fp; }
};

void with_raii() {
    FileWrapper source("sample.txt", "r");
    FileWrapper destination("with_raii.txt", "w");

    CopyFile(source, destination);
}

template<typename FunctionType> struct scope_guard
{
    FunctionType _fn;
    scope_guard(FunctionType fn) : _fn{ fn } {}
    ~scope_guard() { _fn(); }
};

template<typename FunctionType> auto CreateScopeGuard(FunctionType fn)
{
    return scope_guard<FunctionType>(fn);
}

void with_scopeguard() {
    FILE* sampleFile;
    FILE* resultFile;

    auto guard = CreateScopeGuard(
        [&]() {
            if (sampleFile != NULL) {
                fclose(sampleFile);
                sampleFile = NULL;
            }
            if (resultFile != NULL) {
                fclose(resultFile);
                resultFile = NULL;
            }
        });

    auto err = fopen_s(&sampleFile, "sample.txt", "r");
    if (err != 0) {
        return;
    }

    err = fopen_s(&resultFile, "without_raii.txt", "w");
    if (err != 0) {
        return;
    }

    CopyFile(sampleFile, resultFile);

}


int main() {
    with_scopeguard();
}