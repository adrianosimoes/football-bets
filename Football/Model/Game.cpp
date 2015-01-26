/*
 * Game.cpp
 *
 *  Created on: 25/01/2015
 *      Author: Adriano
 */
#include "Game.h"
#include "../Utils/Utils.h"

FootballGame::FootballGame(string matchDate, FootballTeam* homeTeam,
		FootballTeam* awayTeam, int homeS, int awayS) :
		date(matchDate), homeTeam(homeTeam), awayTeam(awayTeam), homeScore(
				homeS), awayScore(awayS) {
}

void FootballGame::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}
	std::stringstream gamePrint;
	gamePrint << homeTeam->getName() << " " << homeScore << " - " << awayScore << " "
			<< awayTeam->getName();
	Utils::print(gamePrint.str());
}

