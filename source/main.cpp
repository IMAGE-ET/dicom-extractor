#include "logxx/logxx.h"
#include "dicom/dicom.h"
#include "dirent.h"

static logxx::Log cLog("extractor");

int main(int argc, char **argv){
	S_LOG("main");
        logxx::GlobalLogLevel(logxx::warning);
        if (argc < 2){
                log(logxx::error) << "A path with dicom files should be specified" << logxx::endl;
                return 1;
        } else {
                std::string path(argv[1]);
                if (path[path.length()-1] != '/')
                        path += '/';
                DIR *dir;
                if ((dir = opendir (path.c_str())) != nullptr) {
                        dirent *ent;
                        while ((ent = readdir (dir)) != NULL) {
                                if (ent->d_type == DT_REG){
                                        std::string fName = ent->d_name;
                                        log(logxx::debug) << "{" << fName << "}" << logxx::endl;
                                        Dicom dicom(path + fName);
                                        if (dicom.Parse()){
                                                log(logxx::notice) << "{" << fName << "} Parsed" << logxx::endl;
                                        } else {
                                                log(logxx::notice) << "{" << fName << "} Not parsed" << logxx::endl;
                                        }
                                }
                        }
                        closedir (dir);
                } else {
                        log(logxx::error) << "Can't open path {" << path << "}" << logxx::endl;
                        return 1;
                }
                
                return 0;
        }
}
