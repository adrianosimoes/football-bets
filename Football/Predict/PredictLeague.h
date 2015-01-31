/*
 * PredictLeague.h
 *
 *  Created on: 28/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_PREDICTLEAGUEPOISSON_H_
#define MODEL_PREDICTLEAGUEPOISSON_H_

#include "../Model/Model.h"
#include "RatingCalculator.h"

class PredictLeague {
protected:
	FootballLeague* league;
	RatingCalculator* ratingCalc;
public:
	PredictLeague(FootballLeague* league, RatingCalculator *rc);
	void setRating(RatingCalculator* ratingCalc);
	virtual void predict(int startRound, int roundBeforeEnd);
	//virtual void printPredictions();
	vector<GameRating*>* getGameRatings();
	GameRating* getGameRating(FootballGame* game);
	void printResultsHDL();
	virtual void debugPrint();
	virtual ~PredictLeague();
};

#endif /* MODEL_PREDICTLEAGUEPOISSON_H_ */
