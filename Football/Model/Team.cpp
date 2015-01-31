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
		name(teamName), homeGoals(0), awayGoals(0), homeConceded(0), awayConceded(
				0), homeMatches(0), awayMatches(0) {
	id = idCounter++;
	games = vector<FootballGame*>();
}

void FootballTeam::addGame(FootballGame* game) {
	if (game->getHomeTeam()->getID() == getID()) {
		homeMatches++;
		homeGoals += game->getHomeScore();
		homeConceded += game->getAwayScore();
	} else {
		awayMatches++;
		awayGoals += game->getAwayScore();
		awayConceded += game->getHomeScore();
	}
	games.push_back(game);
}

int FootballTeam::getID() {
	return id;
}

string FootballTeam::getName() {
	return name;
}

double FootballTeam::getHomeScoreRating() {
	return homeMatches ? (double) homeGoals / homeMatches : 0.0;
}

double FootballTeam::getAwayScoreRating() {
	return awayMatches ? (double) awayGoals / awayMatches : 0.0;
}

double FootballTeam::getHomeDefenseRating() {
	return homeMatches ? (double) homeConceded / homeMatches : 0.0;
}

double FootballTeam::getAwayDefenseRating() {
	return awayMatches ? (double) awayConceded / awayMatches : 0.0;
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
}

