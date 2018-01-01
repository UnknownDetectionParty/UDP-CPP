#include "stdafx.h"
#include "Minecraft.h"
#include "Entity.h"

Entity::Entity(UDP * udp, Minecraft * mc, jobject entity) : AbstractClass::AbstractClass(udp, "ve")
{
	this->mc = mc;
	this->entity = entity;

	//Get all the field and method IDs for Entity that we want (mappings are for 1.12)
	fdPosX = getFieldID("p", "D", false);
	fdPosY = getFieldID("q", "D", false);
	fdPosZ = getFieldID("r", "D", false);
	mdGetId = getMethodID("S", "()I", false);
	mdGetName = getMethodID("h_", "()Ljava/lang/String;", false);
}

jdouble Entity::getPosX() {
	return getDouble(entity, fdPosX);
}

jdouble Entity::getPosY() {
	return getDouble(entity, fdPosY);
}

jdouble Entity::getPosZ() {
	return getDouble(entity, fdPosZ);
}

jint Entity::getId() {
	return getInt(entity, mdGetId);
}

const char * Entity::getName() {
	//Needs to get the name as a jstring, then convert that to something usable
	jstring str = (jstring)getObject(entity, mdGetName);
	return udp->getEnv()->GetStringUTFChars(str, false);
}
