/*
 * PredictLeague.cpp
 *
 *  Created on: 28/01/2015
 *      Author: Adriano
 */

#include "PredictLeaguePoisson.h"

PredictLeaguePoisson::PredictLeaguePoisson(FootballLeague* league) :
		PredictLeague(league) {
}

void PredictLeaguePoisson::predict(int startRound, int roundBeforeEnd) {
	vector<FootballGame*>* games = league->getGames();
	PredictLeague::clearPredictedGames();

	vector<FootballGame*>::iterator i;
	for (i = games->begin(); i != games->end(); i++) {
		predictedGames->push_back(predictGame(*i));
	}
}

void PredictLeague::clearPredictedGames() {
	vector<PredictedGame*>::iterator i;
	for (i = predictedGames->begin(); i != predictedGames->end(); i++) {
		delete *i;
	}
	predictedGames->clear();
}

PredictedGame* PredictLeaguePoisson::predictGame(FootballGame* game) {
	FootballTeam* homeTeam = game->getHomeTeam();
	FootballTeam* awayTeam = game->getAwayTeam();
	double homeAttack = homeTeam->getHomeScoreRating(), awayAttack =
			awayTeam->getAwayScoreRating(), homeDefense =
			homeTeam->getHomeDefenseRating(), awayDefense =
			awayTeam->getAwayDefenseRating();

	double predictedHomeAverage = (homeAttack + awayDefense) / 2;
	double predictedAwayAverage = (awayAttack + homeDefense) / 2;

	//double predictedHomeTeamScore = getPredictedGoals(predictedHomeAverage);
	//double predictedAwayTeamScore = getPredictedGoals(predictedAwayAverage);
	int homePerc, drawPerc, awayPerc;
	getGamePercentages(predictedHomeAverage, predictedAwayAverage, &homePerc,
			&drawPerc, &awayPerc);

	return new PredictedGame(game, predictedHomeAverage, predictedAwayAverage,
			homePerc, drawPerc, awayPerc);
}

void PredictLeaguePoisson::getGamePercentages(double predictedHomeAverage,
		double predictedAwayAverage, int* homePerc, int* drawPerc,
		int* awayPerc) {
	vector<double> homeGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	vector<double> awayGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	*homePerc = 0, *drawPerc = 0, *awayPerc = 0;

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		homeGoalsPerc[i] = poisson_pmf(predictedHomeAverage, i);
		awayGoalsPerc[i] = poisson_pmf(predictedAwayAverage, i);
	}

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		for (int j = 0; j <= MAX_NUMBER_GOALS_PREDICT; j++) {
			if (Utils::debugMathOn())
				printf("+ perc:(%d:%d) %f. %d\n", i, j,
										homeGoalsPerc[i] * awayGoalsPerc[j],
										(int) ((homeGoalsPerc[i] * awayGoalsPerc[j] * 1000)));
			if (i > j) {
				*homePerc += (int)(homeGoalsPerc[i] * awayGoalsPerc[j] * 1000) ;
			} else if (i == j) {
				*drawPerc += (int)(homeGoalsPerc[i] * awayGoalsPerc[j] * 1000) ;
			} else {
				*awayPerc += (int)(homeGoalsPerc[i] * awayGoalsPerc[j] * 1000) ;
			}
		}
	}
	*homePerc=*homePerc/10;
	*drawPerc=*drawPerc/10;
	*awayPerc=*awayPerc/10;
}

int PredictLeaguePoisson::getPredictedGoals(double average) {
	int preditedGoals = 0;
	double predictedGoalPerc = 0;

//Only predict results until 6 goals
	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		double thisGoalsPerc = poisson_pmf(average, i);
		if (Utils::debugMathOn())
			printf("average: %f goals: %d  perc: %f\n", average, i,
					thisGoalsPerc);
		if (thisGoalsPerc >= predictedGoalPerc) {
			preditedGoals = i;
			predictedGoalPerc = thisGoalsPerc;
		}
	}
	return preditedGoals;
}

//Impl. from: http://www.masaers.com/2013/10/08/Implementing-Poisson-pmf.html
double PredictLeaguePoisson::poisson_pmf(const double mean, const int value) {
	return exp(value * log(mean) - lgamma(value + 1.0) - mean);
}

void PredictLeaguePoisson::printPredictions() {

}

std::vector<PredictedGame*>* PredictLeague::getPredictedGames() {
	return predictedGames;
}

void printStats(vector<FootballGame*>* games) {
	int home = 0, draw = 0, away = 0, allMatches = 0;
	vector<FootballGame*>::iterator i;
	for (i = games->begin(); i != games->end(); i++) {
		if ((*i)->isHomeWin()) {
			home++;
		} else if ((*i)->isDraw()) {
			draw++;
		} else {
			away++;
		}
		allMatches++;
	}
	printf("Results:\t%d%%\t%d%%\t%d%%\n", (home * 100) / allMatches,
			(draw * 100) / allMatches, (away * 100) / allMatches);
}

void PredictLeague::printResultsHDL() {
	printStats(league->getGames());
	printStats((vector<FootballGame*>*) predictedGames);
}

void PredictLeague::debugPrint() {
	vector<PredictedGame*>::iterator i;
	for (i = predictedGames->begin(); i != predictedGames->end(); i++) {
		(*i)->debugPrint();
	}
}

PredictLeague::PredictLeague(FootballLeague* league) :
		league(league) {
	predictedGames = new vector<PredictedGame*>();
}

