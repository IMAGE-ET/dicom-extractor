#include "logxx/logxx.h"
#include "dicom/field.h"
#include "config.h"

int main(){
	logxx::Log log("main");
	log(logxx::info) << DATA_DIR << logxx::endl;
	return 0;
}
