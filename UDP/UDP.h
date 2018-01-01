#pragma once

#include "stdafx.h"

class UDP
{
public:
	UDP();
	JavaVM * getJvm();
	JNIEnv * getEnv();
private:
	JavaVM * jvm;
	JNIEnv * env;
};

