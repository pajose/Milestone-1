/*
 * Server.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: Jon
 */

#include "Server.h"
#include "..\objects\PlayerEntity.h"
#include "..\objects\FoodEntity.h"

Server* Server::instance;

Server::Server() {
	admin = new EntityAdministrator();

	
	/*
	// Delete after. Test cases
	admin->addEntity(*new PlayerEntity("Jon", std::make_pair(0, 0)));
	admin->addEntity(*new PlayerEntity("Wesley", std::make_pair(0, 500)));
	admin->addEntity(*new FoodEntity());

	for (GameEntity* entity : admin->getEntities()) {
		std::cout << "This is the object's name " << entity->getName().c_str() << " and type " << entity->getType();
		std::cout << " and position ";
		std::cout << entity->getPosition().first << ", " << entity->getPosition().second << std::endl;
	}

	std::string name = "Jon";
	std::cout << "Retrieved entity with name " << name.c_str() << " " << admin->getEntity(name) << std::endl;

	admin->removeEntity(name);
	*/
	
}

Server::~Server() {
	delete admin;
	delete Server::instance;
}

Server* Server::getInstance() {
	if (!Server::instance)
		Server::instance = new Server();
	return Server::instance;
}

EntityAdministrator* Server::getAdministrator() {
	return admin;
}

void Server::printState()
{
	std::cout << "Current game state" << std::endl;
	std::cout << "Player count: " << admin->getPlayers().size() << std::endl;
	for (GameEntity* entity : admin->getEntities())
		std::cout << entity->getName().c_str() << " at location " << entity->getPosition().first << ", " << entity->getPosition().second << std::endl;
	std::cout <<  std::endl;
}

void Server::start()
{
	SYSTEMTIME st;
	int prev_time = -60;
	return;
	while (true) {
		GetSystemTime(&st);
		if (st.wMilliseconds - prev_time >= 60 || st.wMilliseconds - prev_time < 0) {
			prev_time = st.wMilliseconds;
		}
	}
}

// Restarts the game and sets scores to players to respective areas.
void Server::restart()
{
	// Sets players at respective beginning locations
	for (int player_number = 0; player_number < admin->getPlayers().size() && player_number < 2; player_number++)
		admin->getPlayers().at(player_number)->setPosition(std::make_pair(0, 0 + (500 * player_number)));

	// Respawns food at a random location
	admin->getFood()->respawn();
}
