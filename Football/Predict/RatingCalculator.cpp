/*
 * RatingCalculator.cpp
 *
 *  Created on: 31/01/2015
 *      Author: Adriano
 */

#include "RatingCalculator.h"

GameRating::GameRating(FootballGame* game, double homeR, double awayR) :
		game(game), homeRating(homeR), awayRating(awayR) {

	calculateGamePercentages();

	if (homePerc >= awayPerc && homePerc >= drawPerc) {
		predcitedResult = HOME_WIN;
	} else if (drawPerc >= homePerc && drawPerc >= awayPerc) {
		predcitedResult = DRAW;
	} else
		predcitedResult = AWAY_WIN;
}

#define PERC_PRECISION 100
void GameRating::calculateGamePercentages() {
	vector<double> homeGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	vector<double> awayGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	homePerc = 0, drawPerc = 0, awayPerc = 0;

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		homeGoalsPerc[i] = RatingCalculator::poisson_pmf(homeRating, i);
		awayGoalsPerc[i] = RatingCalculator::poisson_pmf(awayRating, i);
	}

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		for (int j = 0; j <= MAX_NUMBER_GOALS_PREDICT; j++) {
			if (Utils::debugMathOn())
				printf("+ perc:(%d:%d) %f. %d\n", i, j,
						homeGoalsPerc[i] * awayGoalsPerc[j],
						(int) ((homeGoalsPerc[i] * awayGoalsPerc[j]
								* PERC_PRECISION * 100)));
			if (i > j) {
				homePerc += (int) (homeGoalsPerc[i] * awayGoalsPerc[j]
						* PERC_PRECISION * 100);
			} else if (i == j) {
				drawPerc += (int) (homeGoalsPerc[i] * awayGoalsPerc[j]
						* PERC_PRECISION * 100);
			} else {
				awayPerc += (int) (homeGoalsPerc[i] * awayGoalsPerc[j]
						* PERC_PRECISION * 100);
			}
		}
	}
	homePerc = homePerc / PERC_PRECISION;
	drawPerc = drawPerc / PERC_PRECISION;
	awayPerc = awayPerc / PERC_PRECISION;
}

int RatingCalculator::getPredictedGoals(double average) {
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
double RatingCalculator::poisson_pmf(const double mean, const int value) {
	return exp(value * log(mean) - lgamma(value + 1.0) - mean);
}

double GameRating::getHomeRating() {
	return homeRating;
}

double GameRating::getAwayRating() {
	return awayRating;
}

bool GameRating::isHomeWin() {
	return predcitedResult == HOME_WIN;
}
bool GameRating::isDraw() {
	return predcitedResult == DRAW;
}
bool GameRating::isAwayWin() {
	return predcitedResult == AWAY_WIN;
}

void GameRating::debugPrint() {
	if (!Utils::debugOn()) {
		return;
	}

	/*double homeAttack = homeTeam->getHomeScoreRating(), awayAttack =
	 awayTeam->getAwayScoreRating(), homeDefense =
	 homeTeam->getHomeDefenseRating(), awayDefense =
	 awayTeam->getAwayDefenseRating();*/
	printf("Home Team: %s, Away Team: %s\n",
			game->getHomeTeam()->getName().c_str(),
			game->getAwayTeam()->getName().c_str());

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

	printf("Pred Home Score: %f\tPred Away  Score:%f\n", homeRating,
			awayRating);

	printf("Home Win: %d\tDraw:%d\tAway Win:%d\t\n", homePerc, drawPerc,
			awayPerc);

}

RatingCalculator::RatingCalculator(FootballLeague* league) :
		league(league) {
	ratingsMap = map<FootballGame*, GameRating*>();
	ratings = new vector<GameRating*>();
}

void RatingCalculator::preditRatings() {
	vector<FootballGame*>::iterator i;
	for (i = league->getGames()->begin(); i != league->getGames()->end(); i++) {
		FootballGame* game = *i;

		FootballTeam* homeTeam = game->getHomeTeam();
		FootballTeam* awayTeam = game->getAwayTeam();
		double homeAttack = homeTeam->getHomeScoreRating(), awayAttack =
				awayTeam->getAwayScoreRating(), homeDefense =
				homeTeam->getHomeDefenseRating(), awayDefense =
				awayTeam->getAwayDefenseRating();

		double predictedHomeAverage = (homeAttack + awayDefense) / 2;
		double predictedAwayAverage = (awayAttack + homeDefense) / 2;
		GameRating * gameRating = new GameRating(game, predictedHomeAverage,
				predictedAwayAverage);
		ratingsMap[game] = gameRating;
		ratings->push_back(gameRating);
	}

}

vector<GameRating*>* RatingCalculator::getGameRatings() {
	return ratings;
}

GameRating * RatingCalculator::getRatings(FootballGame * game) {
	GameRating* gameRating = ratingsMap[game];

	if (gameRating == NULL) {
		printf("Game rating is null.%s - %s\n",
				game->getHomeTeam()->getName().c_str(),
				game->getAwayTeam()->getName().c_str());
	}

	return gameRating;
}

RatingCalculator* RatingFactory::createPoissonRating(FootballLeague* league) {
	return new RatingCalculator(league);
}

RatingCalculator::~RatingCalculator() {
}

