/*
 * League.cpp
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#include "League.h"

#include "../Utils/Utils.h"

FootballLeague::FootballLeague() {
	games = vector<FootballGame*>();
}

string FootballLeague::getName() {
	return name;
}

void FootballLeague::setName(string leagueName) {
	name = leagueName;
}

void FootballLeague::addTeam(string teamName) {
	teams.insert(teamName);
}

void FootballLeague::addGame(FootballGame* game) {
	games.push_back(game);
}

void FootballLeague::debugPrint() {
	if(!Utils::debugOn()){
		return;
	}
	Utils::print("Printing League:");
	Utils::print("Games:");
	vector<FootballGame*>::iterator i;
	for (i = games.begin(); i != games.end(); i++) {
		(*i)->debugPrint();
	}
}

FootballLeague::~FootballLeague() {
	vector<FootballGame*>::iterator i;
	for (i = games.begin(); i != games.end(); i++) {
		delete *i;
	}
}

