#include "encoding_converter.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

logxx::Log TempFile::cLog("TempFile");
logxx::Log EncodingConverter::cLog("EncodingConverter");

TempFile::TempFile(const std::string& fileName) : name(fileName) {
        std::ofstream o(fileName, std::ios_base::trunc);
        o.flush();
}

TempFile::~TempFile() {
        S_LOG("~TempFile");
        int retCode = std::remove(name.c_str());
        if (retCode != 0)
                log(logxx::warning) << "Can't remove file {" << name << "}, error code " << retCode << logxx::endl;
        else
                log(logxx::debug) << "Removed file {" << name << "}" << logxx::endl;
}


EncodingConverter::EncodingConverter(const std::string& path) : tempFile(path + "/encoding-converter.txt" ),
        encodings({"CP1251", "ISO-8859-5"}) {
}

EncodingConverter::~EncodingConverter() {
}

void EncodingConverter::WriteString(const std::string& s) {
        std::ofstream tmp(tempFile.name, std::ios_base::binary);
        S_LOG("WriteString");
        if (tmp.good()){
                tmp.write(s.c_str(), s.length());
        } else {
                log(logxx::error) << "Can't open file {" << tempFile.name << "} for writing" << logxx::endl;
                throw std::runtime_error("File open failed");
        }
}

std::string EncodingConverter::ReadString(const std::string &fileName) {
        std::string fName = fileName.empty() ? tempFile.name : fileName;
        std::ifstream readingTempFile(fName, std::ios_base::binary);
        S_LOG("ReadString");
        if (readingTempFile.good()){
                static const std::streamsize maxLength = 1024;
                std::unique_ptr<char[]> cValue(new char[maxLength]);
                auto length = readingTempFile.readsome(cValue.get(), maxLength);
                if (length != 0){
                        return std::string(cValue.get(), length);
                } else
                        return std::string();
        } else {
                log(logxx::error) << "Can't open {" << fName << "} for reading" << logxx::endl;
                return std::string();
        }
}

bool EncodingConverter::RunCommand(const std::string& cmd) {
        int res = std::system(cmd.c_str());
        if (res == -1)
                return false;
        else {
                return WEXITSTATUS(res) == 0;
        }
}

std::string EncodingConverter::AutoConvertString(const std::string& string, bool interactive) {
        S_LOG("AutoConvertString");
        std::string res;
        WriteString(string);
        
        std::string cmd = "enconv -Lru -xUTF8 \"" + tempFile.name + "\"";
        if (interactive)
                cmd += " 2>/dev/null";
        
        bool convert = RunCommand(cmd);
        if (convert){
                res = ReadString();
        } else{
                if (interactive)
                        res = InteractiveConvert(string);
                else
                        log(logxx::warning) << "running enconv failed" << logxx::endl;
        }
        return res;
}

std::string EncodingConverter::ConvertString(const std::string& string, const std::string &from, bool hideErrors) {
        S_LOG("ConvertString");
        encodings.insert(from);
        std::string res;
        WriteString(string);
        TempFile temp2(tempFile.name + "2");
        std::string cmd = "iconv -f" + from + " -tUTF8 \"" + tempFile.name + "\" > \"" + temp2.name + "\"";
        bool convert = RunCommand(cmd);
        if (convert){
                res = ReadString(temp2.name);
        } else{
                log(hideErrors ? logxx::debug : logxx::warning) << "running iconv failed" << logxx::endl;
        }
        return res;
}

std::string EncodingConverter::InteractiveConvert(const std::string& val) {
        S_LOG("InteractiveConvert");
        if (val.empty())
                return val;
        else {
                auto known = knownConversions.find(val);
                if (known != knownConversions.end()){
                        return known->second;
                } else {
                        std::vector<std::string> conversions;
                        int i(0);
                        for (auto &enc : encodings){
                                std::string res = ConvertString(val, enc);
                                log(logxx::info, i++, enc) << "{" << res << "}" << logxx::endl;
                                conversions.push_back(res);
                        }
                        log(logxx::info) << "Select conversion: " << logxx::endl;
                        std::cin >> i;
                        knownConversions[val] = conversions[i];
                        return conversions[i];
                }
        }
        
}
