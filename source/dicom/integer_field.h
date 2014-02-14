#ifndef INTEGER_FIELD_H
#define	INTEGER_FIELD_H

#include "field.h"

class IntegerField : public Field {
public:
        IntegerField();
        virtual ~IntegerField();
        
        long long int GetIntValue() const;
protected:
        virtual void ProcessValue();

private:
        long long int intValue = 0;

};

#endif	/* INTEGER_FIELD_H */

