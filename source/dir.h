#ifndef DIR_H
#define	DIR_H

#include <dirent.h>
#include <string>

class Dir {
public:
        Dir(const std::string &path, bool onlyFiles, const std::string &extension);
        ~Dir();
        void Close();
        bool Ok() const;
        std::string Read();
private:
        DIR *dir;
        bool onlyFiles;
        const std::string ext;
        
        bool CompareExtention(const std::string &original);
};

#endif	/* DIR_H */

