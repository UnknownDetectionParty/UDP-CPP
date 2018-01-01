#include "stdafx.h"
#include "Minecraft.h"
#include "WorldClient.h"

WorldClient::WorldClient(UDP * udp, Minecraft * mc) : AbstractClass::AbstractClass(udp, "brz")
{
	this->mc = mc;
	fdEntityList = getFieldID("K", "Ljava/util/Set;", false);
	mdSetWorldTime = getMethodID("b", "(J)V", false);
}

jobject WorldClient::getEntityList() {
	return getObject(mc->getWorld(), fdEntityList);
}

void WorldClient::setWorldTime(jlong time) {
	callMethod(mc->getWorld(), mdSetWorldTime, time);
}

JavaSet * WorldClient::getEntities() {
	JavaSet * set = new JavaSet(udp, getEntityList());
	return set;
}
