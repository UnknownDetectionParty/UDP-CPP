#include "stdafx.h"
#include "UDP.h"
#include "Minecraft.h"
#include "EntityPlayerSP.h"
#include "WorldClient.h"

Minecraft::Minecraft(UDP * udp) : AbstractClass::AbstractClass(udp, "bhz")
{
	smdGetMinecraft = getMethodID("z", "()Lbhz;", true);
	fdPlayer = getFieldID("h", "Lbub;", false);
	fdWorld = getFieldID("f", "Lbrz;", false);
}

jobject Minecraft::getMinecraft() {
	return getObject(smdGetMinecraft);
}

jobject Minecraft::getPlayer() {
	return getObject(getMinecraft(), fdPlayer);
}

jobject Minecraft::getWorld() {
	return getObject(getMinecraft(), fdWorld);
}

EntityPlayerSP * Minecraft::getPlayerContainer() {
	//If the player container doesn't exist, make it, why am I even commenting this?
	if (!playerContainer)
		playerContainer = new EntityPlayerSP(udp, this);
	return playerContainer;
}

WorldClient * Minecraft::getWorldContainer() {
	if (!worldContainer)
		worldContainer = new WorldClient(udp, this);
	return worldContainer;
}