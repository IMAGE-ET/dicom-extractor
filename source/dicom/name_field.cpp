#include "name_field.h"
#include <algorithm>

logxx::Log NameField::cLog(Field::cLog, "NameField");

NameField::NameField(EncodingConverter &converter) : Field(), converter(converter) {
}

NameField::~NameField() {
}

std::string NameField::GetPet() const {
        return pet;
}

std::string NameField::GetUserName() const {
        return userName;
}

void NameField::ProcessValue() {
        Field::ProcessValue();
        S_LOG("ProcessValue");
        static const char delimiter = '^';
        auto delim_pos = value.find(delimiter);
        if (delim_pos == std::string::npos)
                log(logxx::error) << "Can't find a delimiter charecter [" << delimiter << "]" << logxx::endl;
        else {
                value = converter.AutoConvertString(value, true);
                if (!value.empty()){
                        delim_pos = value.find(delimiter);
                        if (delim_pos == std::string::npos){
                                log(logxx::error) << "Can't find a delimiter after encoding conversion" << logxx::endl;
                        } else {
                                userName = value.substr(0, delim_pos);
                                pet = value.substr(delim_pos + 1);
                        }
                } else {
                        userName = pet = value = "[NOT ENCODED]";
                }
        }
}

