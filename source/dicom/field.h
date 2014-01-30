#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <fstream>
#include "../logxx/logxx.h"

class Field {
public:
	virtual ~Field();

	std::string GetValue() const;

	virtual bool Load(std::ifstream&, int shift = 4);
protected:
	std::string value;
	virtual void ProcessValue();

	static logxx::Log cLog;
};

#endif //FIELD_H

