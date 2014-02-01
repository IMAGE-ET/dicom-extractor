#include <cstdint>
#include <cstring>
#include <algorithm>
#include "field.h"

logxx::Log Field::cLog("Field");

Field::~Field(){
}

std::string Field::GetValue() const{
	return value;
}

#define check_error(val) \
	if (!f.good()){\
		log(logxx::error) << "Can't extract value " #val << logxx::endl;\
		return false;\
	}
#define fread(val) \
		f.read(reinterpret_cast<char*>(&val), sizeof(val));\
		check_error(val);

bool Field::Load(std::ifstream& f, int shift){
	S_LOG("Load");
	auto current = std::ios_base::cur;
	if (f.good()){
		f.seekg(shift, current);
                log(logxx::debug) << "Current position: 0x" << std::hex << f.tellg() << std::dec << logxx::endl;
                uint32_t fieldLength(0);
                char optionalField[2];
                f.read(optionalField, 2);
                check_error(optionalField);
                if (
                        std::strncmp(optionalField, "PN", 2) == 0 ||
                        std::strncmp(optionalField, "LO", 2) == 0 ||
                        std::strncmp(optionalField, "DA", 2) == 0
                        ){
                        uint16_t shortFieldLength(0);
                        fread(shortFieldLength);
                        fieldLength = shortFieldLength;
                } else{
                        f.seekg(-2, std::ios_base::cur);
                        fread(fieldLength);
                }
                
                if (fieldLength == 0){
                        log(logxx::warning) << "Field length is zero, nothing to read!" << logxx::endl;
                        return false;
                }
		std::unique_ptr<char[]> cValue(new char[fieldLength]);
		f.read(cValue.get(), fieldLength);
		check_error(cValue);
		try {
			value.assign(cValue.get(), fieldLength);
			ProcessValue();
			return true;
		} catch (const std::exception& e){
			log(logxx::error) << "Can't copy value to std::string: " << e.what() << logxx::endl;
			return false;
		}
	} else {
		log(logxx::error) << "Can't read file" << logxx::endl;
		return false;
	}
}

void Field::ProcessValue(){
        auto lastNonSpace = std::find_if(value.rbegin(), value.rend(),
                [](char c)->bool{
                        return c != ' ';
                });
        value.erase(lastNonSpace.base(), value.end());
}

#undef read

