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
	double winMoney,succBets,sumOdds;
	vector<Bet*>* goodBets;
	PredictLeague* predictedLeague;
	int profitMargin;
public:
	Strategy(PredictLeague* league, int profitMargin);
	PredictLeague* getPredictLeague();
	virtual void printBets();
	virtual void calculateBets()=0;
	double getWinMoney();
	double getSuccBets();
	double getSumOdds();
	int getTotalBetsMade();
	virtual void cleanBets();
	virtual ~Strategy()=0;
};

class HDAStrategy: public Strategy {
public:
	HDAStrategy(PredictLeague* league, int profitMargin);
	void calculateBets();
	Bet* calculateBet(GameRating * rating);
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
	bool isUnderBet();
	bool isOverBet();
	char getbetType();

};

#endif /* PREDICT_HDASTRATEGY_H_ */
