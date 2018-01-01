#include "stdafx.h"
#include "JavaList.h"

JavaList::JavaList(UDP * udp, jobject list) : AbstractClass::AbstractClass(udp, "java/util/List")
{
	mdGet = getMethodID("get", "(I)Ljava/lang/Object;", false);
	mdSize = getMethodID("size", "()I", false);
	mdToArray = getMethodID("toArray", "()[Ljava/lang/Object;", false);

	this->list = list;
}

jobject JavaList::get(jint index) {
	return getObject(list, mdGet, index);
}

int JavaList::size() {
	return getInt(list, mdSize);
}

jobjectArray JavaList::toArray() {
	return (jobjectArray) getObject(list, mdToArray);
}