/*
 * FootballTeam.cpp
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#include "Team.h"

#include "../Utils/Utils.h"

int FootballTeam::idCounter = 1;

FootballTeam::FootballTeam(string teamName) :
		name(teamName) {
	id = idCounter++;
	games = vector<FootballGame*>();
}

void FootballTeam::addGame(FootballGame* game) {
	games.push_back(game);
}

int FootballTeam::getID() {
	return id;
}

string FootballTeam::getName() {
	return name;
}

void FootballTeam::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}

	std::stringstream teamPrint;
	teamPrint << id << ": " << name;
	Utils::print(teamPrint.str());
}

FootballTeam::~FootballTeam() {
	// TODO Auto-generated destructor stub
}

