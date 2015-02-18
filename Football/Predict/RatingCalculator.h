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

class RatingCalculator;

enum FootballResult {
	HOME_WIN = 1, DRAW = 0, AWAY_WIN = 2,
};

class TeamRating: public FootballTeam {
protected:
	double homeScoreRating, awayScoreRating, homeDefenseRating,
			awayDefenseRating;
public:
	TeamRating(FootballTeam* team);
	double getHomeScoreRating();
	double getAwayScoreRating();
	double getHomeDefenseRating();
	double getAwayDefenseRating();
	double getHomeScoreRating(TeamRating* awayRating, TeamRating*  avgRating);
	double getAwayScoreRating(TeamRating* homeRating, TeamRating*  avgRating);
	void setRatingsFromStats();
	void setRatings(double homeScoreRating, double awayScoreRating,
			double homeDefenseRating, double awayDefenseRating);
	void setRatingsToAverage(double leagueHome, double leagueAway);
};

class GameRating {
protected:
	FootballGame *game;
	TeamRating* homeRating;
	TeamRating* awayRating;
	TeamRating* avgRating;
	int homePerc, drawPerc, awayPerc, underPerc,overPerc;
	FootballResult predcitedResult;
	vector<vector<double> >* goalsPerc;
public:
	GameRating(FootballGame* game, TeamRating* homeRating, TeamRating* awayRating, TeamRating* averageRating);
	int getHomeWinPerc();
	int getDrawPerc();
	int getAwayWinPerc();
	int getUnderPerc();
	int getOverPerc();
	void calculateGamePercentages(bool debugPrint);
	double  getHomeRatingScore();
	double  getAwayRatingScore();
	bool isHomeWin();
	bool isDraw();
	bool isAwayWin();
	void debugPrint();
	FootballGame* getOriginalGame();
	vector<vector<double> >* getGoalsPerc();

};

class RatingFactory {
public:
	RatingCalculator* createRatingCalculator(FootballLeague* league);
	TeamRating* createTeamRating(FootballTeam* team);
};

class RatingCalculator {
protected:
	map<FootballGame*, GameRating*> ratingsMap;
	map<FootballTeam*, TeamRating*> teamRatings;
	FootballLeague* league;
	vector<GameRating*>* ratings;
	TeamRating* averageTeamRating;
	RatingFactory* factory;
public:
	RatingCalculator(FootballLeague *league, RatingFactory* rf);
	virtual void preditRatings(int startRound, int endRound);
	void calculateTeamRatings(int startRound, int endRound);
	TeamRating* getTeamRating(FootballTeam* team);
	GameRating* getRatings(FootballGame* game);
	vector<GameRating*>* getGameRatings();
	static int getPredictedGoals(double predictedAverage);
	static double poisson_pmf(const double mean, const int value);
	void clearRatings();
	void printGamesGoalsPerc();
	virtual ~RatingCalculator();
};



#endif /* PREDICT_RATINGCALCULATOR_H_ */
