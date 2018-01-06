#pragma once
struct Mem {
	char* name;
	char* desc;
	bool isStatic;
	Mem(char* memName, char* memDesc, bool stat) : name(memName), desc(memDesc), isStatic(stat) {}
};