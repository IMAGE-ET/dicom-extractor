#ifndef NAME_FIELD_H
#define	NAME_FIELD_H

#include "field.h"
#include "encoding_converter.h"

class NameField : public Field {
public:
        NameField(EncodingConverter &converter);
        virtual ~NameField();
        
        std::string GetUserName() const;
        std::string GetPet() const;
protected:
        virtual void ProcessValue();
        
        EncodingConverter &converter;
        std::string userName, pet;
        static logxx::Log cLog;

};

#endif	/* NAME_FIELD_H */

