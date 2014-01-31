/* 
 * File:   date_field.cpp
 * Author: mexus
 * 
 * Created on January 30, 2014, 3:39 PM
 */

#include "date_field.h"

logxx::Log DateField::cLog(Field::cLog, "DateField");


DateField::DateField() : Field() {
}

DateField::~DateField() {
}

bool DateField::CheckValue() const {
        S_LOG("CheckValue");
        if (value.size() != 8){
                log(logxx::error) << "Date should constists of 8 symbols, but in contains " << value.size() << logxx::endl;
                return false;
        }
        for (size_t i = 0; i < 8; ++i){
                if (value[i] < '0' || value[0] > '9'){
                        log(logxx::error) << "Detected non-numeric value at " << i + 1 << ": [" << value[i] << "]" << logxx::endl;
                        return false;
                }
        }
        return true;
}

void DateField::ProcessValue() {
        Field::ProcessValue();
        if (CheckValue())
                date = value.substr(0, 4) + "-" + value.substr(4, 2) + "-" + value.substr(6, 2);
        else
                value.clear();
}


