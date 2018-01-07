#pragma once
#include <map>
#include <string>
#include "Mem.h"

struct CM {
	char* name;
	std::map<std::string, Mem> fields;
	std::map<std::string, Mem> methods;
	CM(char* clsName) : name(clsName) {}
};