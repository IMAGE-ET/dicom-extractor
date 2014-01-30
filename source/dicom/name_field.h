#ifndef NAME_FIELD_H
#define	NAME_FIELD_H

#include "field.h"

class NameField : public Field {
public:
        NameField();
        virtual ~NameField();
        
        std::string GetUserName() const;
        std::string GetPet() const;
protected:
        virtual void ProcessValue();
        
        std::string userName, pet;
        static logxx::Log cLog;

};

#endif	/* NAME_FIELD_H */

