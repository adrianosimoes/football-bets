/*
 * PredictedGame.h
 *
 *  Created on: 28/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_PREDICTEDGAME_H_
#define MODEL_PREDICTEDGAME_H_

#include "../includes.h"
#include "../Model/Model.h"
#include "../Utils/Utils.h"

enum FootballResult {
	HOME_WIN = 1, DRAW = 0, AWAY_WIN = 2,
};

class PredictedGame: FootballGame {
protected:
	FootballGame* game;
	double predictedHomeAv, predictedAwayAv;
	int homePerc, drawPerc, awayPerc;
	FootballResult predcitedResult;
public:
	PredictedGame(FootballGame* game, double predHomeAv, double predAwayAv,
			int predictedHomePerc, int predictedDrawPerc,
			int predictedAwayPerc);
	void setHomeTeamScore(int homeScore);
	void setAwayTeamScore(int awayScore);
	double getHomeAv();
	double getAwayAv();
	bool isHomeWin();
	bool isDraw();
	bool isAwayWin();
	void debugPrint();
	FootballGame* getOriginalGame();
	~PredictedGame();
};

#endif /* MODEL_PREDICTEDGAME_H_ */
