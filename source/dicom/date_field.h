#ifndef DATE_FIELD_H
#define	DATE_FIELD_H

#include "field.h"

class DateField : public Field {
public:
        DateField();
        virtual ~DateField();
        
        std::string GetDate() const;
        
protected:
        virtual void ProcessValue();
        static logxx::Log cLog;
        
        bool CheckValue() const;

private:
        std::string date;
        

};

#endif	/* DATE_FIELD_H */

