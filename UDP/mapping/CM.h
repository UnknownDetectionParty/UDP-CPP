#pragma once
#include <map>
#include "Mem.h"

struct CM {
	char* name;
	std::map<char*, Mem> fields;
	std::map<char*, Mem> methods;
	CM(char* clsName) : name(clsName) {}
};