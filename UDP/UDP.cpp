#include "stdafx.h"
#include "UDP.h"
#include "util/MathHelper.h"
#include "mapping/impl/JavaList.h"
#include "mapping/impl/Minecraft.h"
#include "mapping/impl/EntityPlayerSP.h"
#include "mapping/impl/WorldClient.h"
#include "mapping/impl/Entity.h"

UDP::UDP()
{
	//Get the JVM and JNI environment
	jsize count;
	if (JNI_GetCreatedJavaVMs(&jvm, 1, &count) != JNI_OK || count == 0) {
		std::cout << "Failed to get the JVM" << std::endl;
		return;
	}
	jint res = jvm->GetEnv((void **)&env, JNI_VERSION_1_8); //for java 8
	if (res == JNI_EDETACHED)
		res = jvm->AttachCurrentThread((void **)&env, nullptr);
	if (res != JNI_OK) {
		std::cout << "Failed to attach to thread" << std::endl;
		return;
	}
	std::cout << "Attached to JVM" << std::endl;

	//Get the Minecraft instance
	Minecraft * mc = new Minecraft(this);

	// Infininte loop, very error-prone but good enough for the purpose of showiing that it works.
	//
	// In this case there is no null checking, so this will crash if the world is null,
	// so inject while in-game. This will crash if you leave.
	//
	while (true) {
		// This is in the loop so that the instances are current. IE, joining a new world not trying to reference the old one.
		EntityPlayerSP * player = mc->getPlayerContainer();
		WorldClient * world = mc->getWorldContainer();
		// Ensure the player an world are not null (IE, check if in-game)
		if (player == nullptr || world == nullptr) {
			Sleep(1000);
		}
		//Get all the entities, calculate the closest one
		JavaSet * entities = world->getEntities();
		double dist = 6;
		Entity * closest = nullptr;
		for (int i = 0; i < entities->size(); i++) {
			Entity * entity = new Entity(this, mc, entities->get(i));
			if (entity->getId() != player->getId()) {
				double newDist = MathHelper::distance(entity->getPosX(), entity->getPosY(), entity->getPosZ(), player->getPosX(), player->getPosY(), player->getPosZ());
				if (newDist < dist) {
					dist = newDist;
					closest = entity;
				}
			}
		}

		//If there is an entity in range, look at it
		if (closest != nullptr) {
			double * rotation = MathHelper::direction(player->getPosX(), player->getPosY(), player->getPosZ(), closest->getPosX(), closest->getPosY(), closest->getPosZ());
			player->setRotationYaw(rotation[0]);
			player->setRotationPitch(rotation[1]);
		}

		//Sleep cause I'm tired
		Sleep(1000 / 60);
	}
}

JavaVM * UDP::getJvm() {
	return jvm;
}

JNIEnv * UDP::getEnv() {
	return env;
}
