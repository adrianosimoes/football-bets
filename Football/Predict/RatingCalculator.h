/*
 * RatingCalculator.h
 *
 *  Created on: 31/01/2015
 *      Author: Adriano
 */

#ifndef PREDICT_RATINGCALCULATOR_H_
#define PREDICT_RATINGCALCULATOR_H_

#include "../includes.h"
#include "../Model/Model.h"
#include "../Utils/Utils.h"

enum FootballResult {
	HOME_WIN = 1, DRAW = 0, AWAY_WIN = 2,
};

class GameRating {
protected:
	FootballGame *game;
	double homeRating;
	double awayRating;
	int homePerc, drawPerc, awayPerc;
	FootballResult predcitedResult;
	vector<vector < double> >* goalsPerc;
public:
	GameRating(FootballGame* game, double homeRating, double awayRating);
	void calculateGamePercentages(bool debugPrint);
	double getHomeRating();
	double getAwayRating();
	bool isHomeWin();
	bool isDraw();
	bool isAwayWin();
	void debugPrint();
	vector<vector < double> >* getGoalsPerc();

};

class RatingCalculator {
protected:
	map<FootballGame*, GameRating*> ratingsMap;
	FootballLeague* league;
	vector<GameRating*>* ratings;
	GameRating* averageRating;
public:
	RatingCalculator(FootballLeague *league);
	virtual void preditRatings();
	GameRating* getRatings(FootballGame* game);
	vector<GameRating*>* getGameRatings();
	static int getPredictedGoals(double predictedAverage);
	static double poisson_pmf(const double mean, const int value);
	void printGamesGoalsPerc();
	virtual ~RatingCalculator();
};

class RatingFactory {
public:
	static RatingCalculator* createPoissonRating(FootballLeague* league);
};

#endif /* PREDICT_RATINGCALCULATOR_H_ */
