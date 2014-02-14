#include "../source/logxx/logxx.h"
#include "config.h"
#include "../source/dicom/dicom.h"

static logxx::Log cLog("Testing");

template<class T>
bool Compare(const std::string& label, const T& etalon, const T& testing){
        S_LOG("CompareStr");
        if (etalon == testing)
                return true;
        else {
                log(logxx::info) << "Faild comaring " << label << ": should be {" << etalon << "}, got {" << testing << "}" << logxx::endl;
                return false;
        }
}

bool TestFile(EncodingConverter& converter, const std::string& filename, const std::string &surname,
        const std::string &pet, long long int id, const std::string& date){
        S_LOG("TestFile");
        Dicom dicomFile(filename);
        if (dicomFile.Parse(converter)){
                if (Compare("surname", surname, dicomFile.GetName()) &&
                        Compare("pet", pet, dicomFile.GetPet()) &&
                        Compare("id", id, dicomFile.GetId()) &&
                        Compare("date", date, dicomFile.GetDate()))
                        return true;
                else {
                        log(logxx::error) << "Test failed for {" << filename << "}" << logxx::endl;
                        return false;
                }
        } else {
                log(logxx::error) << "Can't parse {" << filename << "}" << logxx::endl;
                return false;
        }
}

int main(){
        logxx::GlobalLogLevel(logxx::notice);
	S_LOG("main");
        EncodingConverter converter;
        return (
                TestFile(converter, DATA_DIR "8_13_10_55_1-cut.dcm", "Басова", "Умка", 21211, "2011-04-08") &&
                TestFile(converter, DATA_DIR "10_21_16_57_1-cut.dcm", "егорова", "альгамбра", 31559, "1998-09-30") &&
                TestFile(converter, DATA_DIR "28_10_14_45_1-cut.dcm", "Герасимчук", "Шейла", 39020, "2013-05-28") &&
                TestFile(converter, DATA_DIR "31_16_16_31_1-cut.dcm", "искандерова", "матильда", 38742, "2013-05-02") &&
                TestFile(converter, DATA_DIR "21_20_15_27_2-cut.dcm", "селецкий", "бонита", 28776, "2009-11-21")
                ) ? 0 : 1;
        
}
