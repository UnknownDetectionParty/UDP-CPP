#include "stdafx.h"
#include "MathHelper.h"
#include "UDP.h"
#include "JavaList.h"
#include "Minecraft.h"
#include "EntityPlayerSP.h"
#include "WorldClient.h"
#include "Entity.h"

UDP::UDP()
{
	//Get the jvm and jni environment
	jsize count;
	if (JNI_GetCreatedJavaVMs(&jvm, 1, &count) != JNI_OK || count == 0) {
		std::cout << "Failed to get the JVM" << std::endl;
		return;
	}
	jint res = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
		res = jvm->AttachCurrentThread((void **)&env, nullptr);
	if (res != JNI_OK) {
		std::cout << "Failed to attach to thread" << std::endl;
		return;
	}
	std::cout << "Attached to JVM" << std::endl;

	//Get the mineman instance, and the player and world
	Minecraft * mc = new Minecraft(this);
	EntityPlayerSP * player = mc->getPlayerContainer();
	WorldClient * world = mc->getWorldContainer();

	//Loop forever cause im lazy and like errors
	while (true) {
		//Get all the entities
		JavaSet * entities = world->getEntities();

		//Figure out the closest
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