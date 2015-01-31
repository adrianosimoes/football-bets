/*
 * PredictedGame.cpp
 *
 *  Created on: 28/01/2015
 *      Author: Adriano
 */

#include "PredictedGame.h"
#include "PredictLeaguePoisson.h"

PredictedGame::PredictedGame(FootballGame* footGame, double predHomeAv,
		double predAwayAv, int predictedHomePerc, int predictedDrawPerc,
		int predictedAwayPerc) :
		predictedHomeAv(predHomeAv), predictedAwayAv(predAwayAv), homePerc(
				predictedHomePerc), drawPerc(predictedDrawPerc), awayPerc(
				predictedAwayPerc) {
	game = footGame;
	homeTeam = footGame->getHomeTeam();
	awayTeam = footGame->getAwayTeam();

	if (homePerc >= awayPerc && homePerc >= drawPerc) {
		predcitedResult = HOME_WIN;
	} else if (drawPerc >= homePerc && drawPerc >= awayPerc) {
		predcitedResult = DRAW;
	} else
		predcitedResult = AWAY_WIN;
}

double PredictedGame::getHomeAv() {
	return predictedHomeAv;
}
double PredictedGame::getAwayAv() {
	return predictedAwayAv;
}

bool PredictedGame::isHomeWin() {
	return predcitedResult == HOME_WIN;
}
bool PredictedGame::isDraw() {
	return predcitedResult == DRAW;
}
bool PredictedGame::isAwayWin() {
	return predcitedResult == AWAY_WIN;
}

FootballGame* PredictedGame::getOriginalGame() {
	return game;
}

void PredictedGame::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}

	/*double homeAttack = homeTeam->getHomeScoreRating(), awayAttack =
	 awayTeam->getAwayScoreRating(), homeDefense =
	 homeTeam->getHomeDefenseRating(), awayDefense =
	 awayTeam->getAwayDefenseRating();*/
	printf("Home Team: %s, Away Team: %s\n", homeTeam->getName().c_str(),
			awayTeam->getName().c_str());

	/*printf(
	 "Home attack: %f\tHome  Defense: %f\tAway Atack: %f\t,Away Defense:%f\n",
	 homeAttack, homeDefense, awayAttack, awayDefense);

	 double predictedHomeAverage = (homeAttack + awayDefense) / 2;
	 double predictedAwayAverage = (awayAttack + homeDefense) / 2;

	 printf("Home average: %f\tAway  Average:%f\n", predictedHomeAverage,
	 predictedAwayAverage);

	 double predictedHomeTeamScore = PredictLeaguePoisson::getPredictedGoals(
	 predictedHomeAverage);
	 double predictedAwayTeamScore = PredictLeaguePoisson::getPredictedGoals(
	 predictedAwayAverage);*/

	printf("Pred Home Score: %f\tPred Away  Score:%f\n", predictedHomeAv,
			predictedAwayAv);

	printf("Home Win: %d\tDraw:%d\tAway Win:%d\t\n", homePerc, drawPerc,
			awayPerc);

}

PredictedGame::~PredictedGame() {
}
