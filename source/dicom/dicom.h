#ifndef DICOM_H
#define	DICOM_H

#include <string>
#include "../logxx/logxx.h"

class Dicom {
public:
        Dicom(const std::string &fileName);
        virtual ~Dicom();
        
        bool Parse();
        
        std::string GetName() const;
        std::string GetPet() const;
        int GetId() const;
        std::string GetDate() const;
private:
        std::string fileName, userName, pet, date;
        int id = 0;
        
        static logxx::Log cLog;

};

#endif	/* DICOM_H */

