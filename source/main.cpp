#include "logxx/logxx.h"
#include "dicom/dicom.h"
#include "dir.h"
#include <fstream>

static logxx::Log cLog("extractor");

std::ostream& operator<<(std::ostream& s, const Dicom & d){
        s << d.GetId() << "," << d.GetDate() << "," << d.GetName() << "," << d.GetPet();
        return s;
}

void PrintProgress(){
        S_LOG("PrintProgress");
        static time_t start = time(nullptr);
        static const time_t interval = 10;
        static int counter = 0;
        
        time_t now = time(nullptr);
        ++counter;
        if (now > start + interval){
                start = now;
                log(logxx::info) << counter << logxx::endl;
        }
}

int main(int argc, char **argv){
	S_LOG("main");
        logxx::GlobalLogLevel(logxx::warning);
        EncodingConverter converter;
        if (argc < 2){
                log(logxx::error) << "A path with dicom files should be specified" << logxx::endl;
                return 1;
        } else {
                std::string path(argv[1]);                
                if (path[path.length()-1] != '/')
                        path += '/';
                
                std::string csvFile = path + "out.csv";
                std::ofstream out(csvFile);
                if (out.good()){
                        Dir dir(path, true, ".dcm");
                        if (dir.Ok()) {
                                std::string fName;
                                while ((fName = dir.Read()).empty() == false) {
                                        log(logxx::debug) << "{" << fName << "}" << logxx::endl;
                                        Dicom dicom(path + fName);
                                        if (dicom.Parse(converter)){
                                                // cppcheck-suppress constStatement
                                                log(logxx::notice) << "{" << fName << "} Parsed" << logxx::endl;
                                                out << fName << "," << dicom << std::endl;

                                        } else {
                                                // cppcheck-suppress constStatement
                                                log(logxx::notice) << "{" << fName << "} Not parsed" << logxx::endl;
                                        }
                                        PrintProgress();
                                }
                                return 0;
                        } else {
                                log(logxx::error) << "Can't open path {" << path << "}" << logxx::endl;
                                return 1;
                        }
                } else {
                        log(logxx::error) << "Can't open file {" << csvFile <<  "} for writing"  << logxx::endl;
                        return 1;
                }
        }
}
