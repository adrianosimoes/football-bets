/*
 * Game.cpp
 *
 *  Created on: 25/01/2015
 *      Author: Adriano
 */
#include "Game.h"
#include "Team.h"
#include "../Utils/Utils.h"

FootballGame::FootballGame() {
}
FootballGame::FootballGame(string matchDate, FootballTeam* homeTeam,
		FootballTeam* awayTeam, int homeS, int awayS) :
		date(matchDate), homeTeam(homeTeam), awayTeam(awayTeam), homeScore(
				homeS), awayScore(awayS) {
}

FootballTeam* FootballGame::getHomeTeam() {
	return homeTeam;
}
FootballTeam* FootballGame::getAwayTeam() {
	return awayTeam;
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
			<< " " << awayTeam->getName();

	Utils::print(gamePrint.str());
}

