#include "name_field.h"

logxx::Log NameField::cLog(Field::cLog, "NameField");

NameField::NameField() : Field() {
}

NameField::~NameField() {
}

std::string NameField::GetPet() const {
        return pet;
}

std::string NameField::GetUserName() const {
        return userName;
}

class Pipe {
public:
        Pipe(const std::string& command, const char* modes = "r"){
                pipe = popen(command.c_str(), modes);
        }
        ~Pipe(){
                if (pipe)
                        pclose(pipe);
        }
        std::string Get() {
                std::string result;
                if (pipe){
                        static const size_t bufSize = 10;
                        char buffer[bufSize];
                        while(!feof(pipe)) {
                                if(fgets(buffer, bufSize, pipe) != nullptr)
                                        result += buffer;
                        }
                }
                return result;
        }
        bool Ok() const {return pipe;}
private:
        FILE *pipe = nullptr;
};

void NameField::ProcessValue() {
        S_LOG("ProcessValue");
        static const char delimiter = '^';
        auto delim_pos = value.find(delimiter);
        if (delim_pos == std::string::npos)
                log(logxx::error) << "Can't find a dilimiter charecter [" << delimiter << "]" << logxx::endl;
        else {
                Pipe enconvPipe("echo \"" + value +  "\" | enconv -Lru -xUTF8");
                if (enconvPipe.Ok()){
                        std::string encoded = enconvPipe.Get();
                        delim_pos = encoded.find(delimiter);
                        
                        userName = encoded.substr(0, delim_pos);
                        pet = encoded.substr(delim_pos + 1);
                } else
                        log(logxx::error) << "Can't open pipe" << logxx::endl;
        }
}

