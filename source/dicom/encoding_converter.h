#ifndef ENCODING_CONVERTER_H
#define	ENCODING_CONVERTER_H

#include <fstream>
#include <set>
#include "../logxx/logxx.h"

struct TempFile {
public:
        TempFile(const std::string& fileName);
        ~TempFile();
        const std::string name;
private:
        static logxx::Log cLog;
};

class EncodingConverter {
private:
        static logxx::Log cLog;
        
public:
        EncodingConverter(const std::string & path = "/var/tmp/");
        virtual ~EncodingConverter();
        
        std::string InteractiveConvert(const std::string &string);
        
        std::string AutoConvertString(const std::string &string, bool interactive = false);
        std::string ConvertString(const std::string &string, const std::string &from, bool hideErrors = false);
private:
        TempFile tempFile;
        std::set<std::string> encodings;
        std::map<std::string, std::string> knownConversions;

        void WriteString(const std::string&);
        std::string ReadString(const std::string &fileName = std::string());
        bool RunCommand(const std::string & cmd);
};

#endif	/* ENCODING_CONVERTER_H */

