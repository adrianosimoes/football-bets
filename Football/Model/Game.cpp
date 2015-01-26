/*
 * Game.cpp
 *
 *  Created on: 25/01/2015
 *      Author: Adriano
 */
#include "Game.h"
#include "../Utils/Utils.h"

FootballGame::FootballGame(string matchDate, string homeTeamName,
		string awayTeamName, int homeS, int awayS) :
		date(matchDate), homeTeam(homeTeamName), awayTeam(awayTeamName), homeScore(
				homeS), awayScore(awayS) {
}

void FootballGame::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}
	std::stringstream gamePrint;
	gamePrint << homeTeam << " " << homeScore << " - " << awayScore << " "
			<< awayTeam;
	Utils::print(gamePrint.str());
}

