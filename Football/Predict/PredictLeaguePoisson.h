/*
 * PredictLeague.h
 *
 *  Created on: 28/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_PREDICTLEAGUEPOISSON_H_
#define MODEL_PREDICTLEAGUEPOISSON_H_

#include "../Model/Model.h"
#include "PredictedGame.h"

#define MAX_NUMBER_GOALS_PREDICT 10

class PredictLeague {
protected:
	FootballLeague* league;
	vector<PredictedGame*>* predictedGames;
public:
	PredictLeague(FootballLeague* league);
	virtual void predict(int startRound, int roundBeforeEnd)=0;
	virtual void printPredictions()=0;
	virtual vector<PredictedGame*>* getPredictedGames();
	virtual void clearPredictedGames();
	void printResultsHDL();
	virtual void debugPrint();
	virtual ~PredictLeague() {
	}
	;
};

class PredictLeaguePoisson: public PredictLeague {
public:
	PredictLeaguePoisson(FootballLeague* league);
	virtual void predict(int startRound, int roundBeforeEnd);
	virtual void printPredictions();
	static int getPredictedGoals(double predictedAverage);
	void getGamePercentages(double predictedHomeAverage,
			double predictedAwayAverage, int* homePerc, int* awayPerc,
			int* drawPerc);
	PredictedGame* predictGame(FootballGame* game);
	static double poisson_pmf(const double mean, const int value);

};

#endif /* MODEL_PREDICTLEAGUEPOISSON_H_ */
