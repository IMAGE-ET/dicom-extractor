/* 
 * File:   dir.cpp
 * Author: mexus
 * 
 * Created on February 3, 2014, 1:17 PM
 */

#include "dir.h"

Dir::Dir(const std::string& path, bool onlyFiles, const std::string& extension) :
dir(opendir(path.c_str())), onlyFiles(onlyFiles), ext(extension) {
}

Dir::~Dir() {
        Close();
}

void Dir::Close() {
        if (dir) {
                closedir(dir);
                dir = nullptr;
        }
}

bool Dir::Ok() const {
        return dir;
}

std::string Dir::Read() {
        std::string fName;
        if (Ok()) {
                dirent* entry = readdir(dir);
                if (entry) {
                        fName = entry->d_name;
                        if (onlyFiles && entry->d_type != DT_REG)
                                return Read();
                        else if (!CompareExtention(fName))
                                return Read();
                } else
                        Close();
        }
        return fName;
}

bool Dir::CompareExtention(const std::string& original) {
        if (ext.empty())
                return true;
        else {
                size_t origSize = original.size();
                size_t extSize = ext.size();
                if (origSize < extSize)
                        return false;
                else
                        return original.compare(origSize - extSize, extSize, ext) == 0;
        }
}
