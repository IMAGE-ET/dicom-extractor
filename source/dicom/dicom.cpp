#include "dicom.h"
#include "name_field.h"
#include "integer_field.h"
#include "date_field.h"
#include <fstream>

logxx::Log Dicom::cLog("Dicom");

Dicom::Dicom(const std::string& fileName) : fileName(fileName) {
}

Dicom::~Dicom() {
}

std::string Dicom::GetDate() const {
        return date;
}

int Dicom::GetId() const {
        return id;
}

std::string Dicom::GetName() const {
        return userName;
}

std::string Dicom::GetPet() const {
        return pet;
}

bool LookupString(std::ifstream& f, const std::string& str){
        size_t strLen = str.length();
        std::string tempStr;
        while (f.good()){
                char c = f.get();
                if (tempStr.size() == strLen)
                        tempStr.erase(0, 1);
                tempStr +=c ;
                if (tempStr == str)
                        return true;
        }
        return false;
}

bool Dicom::Parse() {
        S_LOG("Parse");
        std::ifstream in(fileName, std::ios_base::binary);
        if (in.good()){
                static const std::string kodakString("Kodak Point-of-Care CR 120 140 System");
                if (LookupString(in, kodakString)){
                        NameField nameField;
                        IntegerField idField;
                        DateField dateField;
                        if (nameField.Load(in, 17) && idField.Load(in, 4) && dateField.Load(in, 4)){
                                userName = nameField.GetUserName();
                                pet = nameField.GetPet();
                                id = idField.GetIntValue();
                                date = dateField.GetDate();
                                return true;
                        } else {
                                log(logxx::error) << "Can't parse a file {" << fileName << "}" << logxx::endl;
                                return false;
                        }
                } else {
                        log(logxx::error) << "Can't find kodak string in a file {" << fileName << "}" << logxx::endl;
                        return false;
                }
        } else {
                log(logxx::error) << "Can't read file {" << fileName << "}" << logxx::endl;
                return false;
        }
}
