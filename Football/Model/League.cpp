/*
 * League.cpp
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#include "League.h"

#include "../Utils/Utils.h"

FootballLeague::FootballLeague() {
	games = new vector<FootballGame*>();
	teams = map<string, FootballTeam*>();
}

string FootballLeague::getName() {
	return name;
}

void FootballLeague::setName(string leagueName) {
	name = leagueName;
}

FootballTeam* FootballLeague::addTeam(string teamName) {
	FootballTeam* team = new FootballTeam(teamName);
	teams[teamName] = team;
	return team;
}

FootballTeam* FootballLeague::getTeam(string teamName) {
	std::map<string, FootballTeam*>::iterator it;
	it = teams.find(teamName);

	if (it != teams.end()) {
		return it->second;
	} else
		return addTeam(teamName);
}

vector<FootballGame*>* FootballLeague::getGames() {
	return games;
}

void FootballLeague::addGame(FootballGame* game) {
	game->getHomeTeam()->addGame(game);
	game->getAwayTeam()->addGame(game);
	games->push_back(game);
}

void FootballLeague::printStats(bool debugPrint) {
	if (Utils::debugMathOn() || debugPrint) {
		printf("League Data (games %ld):\n", games->size());
	}

	double goals[MAX_NUMBER_GOALS_PREDICT + 1][MAX_NUMBER_GOALS_PREDICT + 1] { 0 };

	vector<double> homeGoals(MAX_NUMBER_GOALS_PREDICT + 1);
	vector<double> awayGoals(MAX_NUMBER_GOALS_PREDICT + 1);
	vector<FootballGame*>::iterator g;
	for (g = games->begin(); g != games->end(); g++) {
		goals[(*g)->getHomeScore()][(*g)->getAwayScore()]++;
	}

	for (int k = 0; k <= MAX_NUMBER_GOALS_PREDICT; k++) {
		for (int m = 0; m <= MAX_NUMBER_GOALS_PREDICT; m++) {
			goals[k][m] = goals[k][m] / games->size();
		}
	}

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		for (int j = 0; j <= MAX_NUMBER_GOALS_PREDICT; j++) {
			if (Utils::debugMathOn() || debugPrint) {
				printf("%d\t", (int) (goals[i][j] *
				PERC_PRECISION * 100));
			}
		}
		if (Utils::debugMathOn() || debugPrint) {
			printf("\n");
		}
	}
}

void FootballLeague::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}
	Utils::print("Printing League:");
	Utils::print("Teams:");
	printf("Size: %ld\n", teams.size());
	map<string, FootballTeam*>::iterator i;
	for (i = teams.begin(); i != teams.end(); i++) {
		i->second->debugPrint();
	}
	Utils::print("Games:");
	vector<FootballGame*>::iterator j;
	for (j = games->begin(); j != games->end(); j++) {
		(*j)->debugPrint();
	}
}

FootballLeague::~FootballLeague() {
	vector<FootballGame*>::iterator i;
	for (i = games->begin(); i != games->end(); i++) {
		delete *i;
	}
}

