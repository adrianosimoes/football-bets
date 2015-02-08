/*
 * Game.cpp
 *
 *  Created on: 25/01/2015
 *      Author: Adriano
 */
#include "Game.h"
#include "Team.h"
#include "../Utils/Utils.h"

FootballGame::FootballGame(string matchDate, FootballTeam* homeTeam,
		FootballTeam* awayTeam, int homeS, int awayS) :
		date(matchDate), homeTeam(homeTeam), awayTeam(awayTeam), homeScore(
				homeS), awayScore(awayS) {
	homeOdds = 0;
	drawOdds = 0;
	awayOdds = 0;
}

void FootballGame::setOdds(double homeOdds, double drawOdds, double awayOdds) {
	this->homeOdds = homeOdds;
	this->drawOdds = drawOdds;
	this->awayOdds = awayOdds;
}

FootballTeam* FootballGame::getHomeTeam() {
	return homeTeam;
}
FootballTeam* FootballGame::getAwayTeam() {
	return awayTeam;
}

double FootballGame::getHomeWinOdds() {
	return homeOdds;
}

double FootballGame::getDrawOdds() {
	return drawOdds;
}

double FootballGame::getAwayWinOdds() {
	return awayOdds;
}

int FootballGame::getHomeScore() {
	return homeScore;
}
int FootballGame::getAwayScore() {
	return awayScore;
}
bool FootballGame::isHomeWin() {
	return homeScore > awayScore;
}
bool FootballGame::isDraw() {
	return homeScore == awayScore;
}
bool FootballGame::isAwayWin() {
	return awayScore > homeScore;
}

void FootballGame::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}
	std::stringstream gamePrint;
	gamePrint << homeTeam->getName() << " " << homeScore << " - " << awayScore
			<< " " << awayTeam->getName() << "\tHome odds:" << homeOdds
			<< " Draw odds:" << drawOdds << " Away Odds:" << awayOdds;

	Utils::print(gamePrint.str());
}

