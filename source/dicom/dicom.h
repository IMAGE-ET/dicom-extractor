#ifndef DICOM_H
#define	DICOM_H

#include <string>
#include "../logxx/logxx.h"
#include "encoding_converter.h"

class Dicom {
public:
        Dicom(const std::string &fileName);
        virtual ~Dicom();
        
        bool Parse(EncodingConverter &converter);
        
        std::string GetName() const;
        std::string GetPet() const;
        long long int GetId() const;
        std::string GetDate() const;
private:
        std::string fileName, userName, pet, date;
        long long int id = 0;
        
        static logxx::Log cLog;

};

#endif	/* DICOM_H */

