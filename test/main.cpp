#include "../source/logxx/logxx.h"
#include "config.h"
#include "../source/dicom/dicom.h"

int main(){
        logxx::GlobalLogLevel(logxx::debug);
	logxx::Log log("main");
        Dicom dicomFile(DATA_DIR "1_16_37_40_1.dcm");
        if (dicomFile.Parse()){
                log(logxx::info) << "Surname: " << dicomFile.GetName() << "\n" <<
                        "Pet: " << dicomFile.GetPet() << "\n" <<
                        "Id: " << dicomFile.GetId() << "\n" << 
                        "Date: " << dicomFile.GetDate() << logxx::endl;
                return 0;
        } else
                return 1;
}
