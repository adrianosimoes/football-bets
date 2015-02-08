/*
 * HDAStrategy.h
 *
 *  Created on: 03/02/2015
 *      Author: Adriano
 */

#ifndef PREDICT_HDASTRATEGY_H_
#define PREDICT_HDASTRATEGY_H_

#include "../includes.h"
#include "../Model/Model.h"
#include "../Predict/PredictLeague.h"

class Bet;

class Strategy {
protected:
	vector<Bet*>* goodBets;
	PredictLeague* predictedLeague;
public:
	Strategy(PredictLeague* league);
	PredictLeague* getPredictLeague();
	virtual void printGoodBets()=0;
	/*void calculateBets();
	 Bet* calculateBet(GameRating * rating);
	 virtual void printGoodBets();*/
	 virtual ~Strategy();
};

class HDAStrategy:  Strategy {
protected:
	int profitMargin;
public:
	HDAStrategy(PredictLeague* league, int profitMargin);
	void calculateBets();
	Bet* calculateBet(GameRating * rating);
	void printGoodBets();
	virtual ~HDAStrategy();
};

enum BetType {
	HDA = 1, OVER_UNDER = 2
};

class Bet {
protected:
	BetType type;
	bool isHomeWin;
	bool isDraw;
	bool isAwayWin;
	bool isUnder25;
	bool isOver25;
	FootballGame* game;
	char betType;
public:
	Bet(bool isHomeWin, bool isDraw, bool isAwayWin, bool isOver25,
			bool isUnder25, FootballGame* game);
	FootballGame* getGame();
	bool isHomeBet();
	bool isDrawBet();
	bool isAwayBet();
	char getbetType();

};

#endif /* PREDICT_HDASTRATEGY_H_ */
