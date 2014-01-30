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
        intValue = std::stoi(value);
}

int IntegerField::GetIntValue() const {
        return intValue;
}
