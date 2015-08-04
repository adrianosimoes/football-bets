/*
 * FootballTeam.cpp
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#include "Team.h"

#include "../Utils/Utils.h"

int FootballTeam::idCounter = 1;

FootballTeam::FootballTeam(string name, int id) :
		id(id), name(name) {
	homeGoals = 0, awayGoals = 0, homeConceded = 0, awayConceded = 0, homeMatches =
			0, awayMatches = 0;
	games = vector<FootballGame*>();
}

FootballTeam::FootballTeam(string teamName) :
		name(teamName), homeGoals(0), awayGoals(0), homeConceded(0), awayConceded(
				0), homeMatches(0), awayMatches(0) {
	id = idCounter++;
	games = vector<FootballGame*>();
}

void FootballTeam::addGameStats(FootballGame* game, bool homeTeam) {
	if (homeTeam) {
		homeMatches++;
		homeGoals += game->getHomeScore();
		homeConceded += game->getAwayScore();
	} else {
		awayMatches++;
		awayGoals += game->getAwayScore();
		awayConceded += game->getHomeScore();
	}
}

void FootballTeam::addGame(FootballGame* game) {
	if (game->getHomeTeam()->getID() == getID()) {
		addGameStats(game, true);
	} else if (game->getAwayTeam()->getID() == getID()) {
		addGameStats(game, false);
	} else {
		//printf("team: %s\n", getName().c_str());
		//game->debugPrint();
		throw "Team not present in Add Game.";
	}
	games.push_back(game);
}

int FootballTeam::getID() {
	return id;
}

string FootballTeam::getName() {
	return name;
}

double divide(double a, double b) {
	return a ? b / a : 0.0;
}

double FootballTeam::getHomeScoreRating() {
	return divide(homeMatches, homeGoals);
}

double FootballTeam::getAwayScoreRating() {
	return divide(awayMatches, awayGoals);
}

double FootballTeam::getHomeDefenseRating() {
	return divide(homeMatches, homeConceded);
}

double FootballTeam::getAwayDefenseRating() {
	return divide(awayMatches, awayConceded);
}

double FootballTeam::getHomeScoreRatingRecent(int numberOfGames) {
	int matchesRecent = 0, homeGoalsRecent = 0;
	vector<FootballGame*>::reverse_iterator it = games.rbegin();
	for (int i = games.size(); i > 0; i--, it++) {
		if ((*it)->getHomeTeam()->getID() == this->getID()) {
			matchesRecent++;
			homeGoalsRecent += (*it)->getHomeScore();
			if (matchesRecent >= numberOfGames) {
				break;
			}
		}
	}
	return divide(matchesRecent, homeGoalsRecent);
}

double FootballTeam::getAwayScoreRatingRecent(int numberOfGames) {
	int matchesRecent = 0, awayGoalsRecent = 0;
	vector<FootballGame*>::reverse_iterator it = games.rbegin();
	for (int i = games.size(); i > 0; i--, it++) {
		if ((*it)->getAwayTeam()->getID() == this->getID()) {
			matchesRecent++;
			awayGoalsRecent += (*it)->getAwayScore();
			if (matchesRecent >= numberOfGames) {
				break;
			}
		}
	}
	return divide(matchesRecent, awayGoalsRecent);
}

double FootballTeam::getHomeDefenseRatingRecent(int numberOfGames) {
	int matchesRecent = 0, homeGoalsConcRecent = 0;
	vector<FootballGame*>::reverse_iterator it = games.rbegin();
	for (int i = games.size(); i > 0; i--, it++) {
		if ((*it)->getHomeTeam()->getID() == this->getID()) {
			matchesRecent++;
			homeGoalsConcRecent += (*it)->getAwayScore();
			if (matchesRecent >= numberOfGames) {
				break;
			}
		}
	}
	return divide(matchesRecent, homeGoalsConcRecent);
}

double FootballTeam::getAwayDefenseRatingRecent(int numberOfGames) {
	int matchesRecent = 0, awayGoalsConcRecent = 0;
	vector<FootballGame*>::reverse_iterator it = games.rbegin();
	for (int i = games.size(); i > 0; i--, it++) {
		if ((*it)->getAwayTeam()->getID() == this->getID()) {
			matchesRecent++;
			awayGoalsConcRecent += (*it)->getHomeScore();
			if (matchesRecent >= numberOfGames) {
				break;
			}
		}
	}
	return divide(matchesRecent, awayGoalsConcRecent);
}

void FootballTeam::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}

	std::stringstream teamPrint;
	teamPrint << "Team:" << id << ": " << name << "\tStats:"
			<< getHomeScoreRating() << ";" << getAwayScoreRating();
	Utils::print(teamPrint.str());
}

FootballTeam::~FootballTeam() {
}

