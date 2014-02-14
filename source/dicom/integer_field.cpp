/* 
 * File:   integer_field.cpp
 * Author: mexus
 * 
 * Created on January 30, 2014, 3:36 PM
 */

#include "integer_field.h"

IntegerField::IntegerField() : Field() {
}

IntegerField::~IntegerField() {
}

void IntegerField::ProcessValue() {
        Field::ProcessValue();
        try {
                intValue = std::stoll(value);
        } catch (const std::exception &e) {
                intValue = 0;
                throw std::runtime_error("IntegerField::ProcessValue: Can't convert {" + value + "} to integer: " + e.what());
        }
}

long long int IntegerField::GetIntValue() const {
        return intValue;
}
