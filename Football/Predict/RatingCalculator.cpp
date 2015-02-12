/*
 * RatingCalculator.cpp
 *
 *  Created on: 31/01/2015
 *      Author: Adriano
 */

#include "RatingCalculator.h"

GameRating::GameRating(FootballGame* game, double homeR, double awayR) :
		game(game), homeRating(homeR), awayRating(awayR) {

	goalsPerc = new vector<vector<double> >(MAX_NUMBER_GOALS_PREDICT + 1,
			vector<double>(MAX_NUMBER_GOALS_PREDICT + 1, 0));

	calculateGamePercentages(false);

	if (homePerc >= awayPerc && homePerc >= drawPerc) {
		predcitedResult = HOME_WIN;
	} else if (drawPerc >= homePerc && drawPerc >= awayPerc) {
		predcitedResult = DRAW;
	} else
		predcitedResult = AWAY_WIN;
}

int GameRating::getHomeWinPerc() {
	return homePerc;
}

int GameRating::getDrawPerc() {
	return drawPerc;
}

int GameRating::getAwayWinPerc() {
	return awayPerc;
}

void GameRating::calculateGamePercentages(bool debugPrint) {
	vector<double> homeGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	vector<double> awayGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	homePerc = 0, drawPerc = 0, awayPerc = 0;

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		homeGoalsPerc[i] = RatingCalculator::poisson_pmf(homeRating, i);
		awayGoalsPerc[i] = RatingCalculator::poisson_pmf(awayRating, i);
	}

	if (Utils::debugMathOn() || debugPrint) {
		printf("Game Percentage Data:\t%f\t%f\n", homeRating, awayRating);
	}

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		for (int j = 0; j <= MAX_NUMBER_GOALS_PREDICT; j++) {
			(*goalsPerc)[i][j] = homeGoalsPerc[i] * awayGoalsPerc[j] * 100;
			if (Utils::debugMathOn() || debugPrint)
				printf("%d\t", /*i, j,*/
						(int) ((homeGoalsPerc[i] * awayGoalsPerc[j]
								* PERC_PRECISION * 1000)));
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
		if (Utils::debugMathOn() || debugPrint) {
			printf("\n");
		}
	}

	if (Utils::debugMathOn() || debugPrint) {
		printf("Home:\t%d\tDraw:\t%d\tAway:\t%d\n",
				(int) homePerc / PERC_PRECISION,
				(int) drawPerc / PERC_PRECISION,
				(int) awayPerc / PERC_PRECISION);
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

vector<vector<double> >* GameRating::getGoalsPerc() {
	return goalsPerc;
}

FootballGame* GameRating::getOriginalGame() {
	return game;
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
	averageRating = NULL;
}

void RatingCalculator::clearRatings() {
	vector<GameRating*>::iterator i;
	for (i = ratings->begin(); i != ratings->end(); i++) {
		delete *i;
	}
	ratingsMap.clear();
	delete ratings;
	delete averageRating;
	ratings = new vector<GameRating*>();
	averageRating = NULL;
}

void RatingCalculator::preditRatings(int startRound, int endRound) {
	clearRatings();
	vector<FootballGame*>* games = league->getGames(startRound, endRound);
	vector<FootballGame*>::iterator i;

	for (i = games->begin(); i != games->end(); i++) {
		FootballGame* game = *i;

		FootballTeam* homeTeam = game->getHomeTeam();
		FootballTeam* awayTeam = game->getAwayTeam();
		double homeAttack = homeTeam->getHomeScoreRating(), awayAttack =
				awayTeam->getAwayScoreRating(), homeDefense =
				homeTeam->getHomeDefenseRating(), awayDefense =
				awayTeam->getAwayDefenseRating();

		double predictedHomeAverage = (homeAttack + awayDefense) / 2;
		double predictedAwayAverage = (awayAttack + homeDefense) / 2;
		//averageLeagueHome += homeTeam->getHomeScoreRating();
		//averageLeagueAway += awayTeam->getAwayScoreRating();
		GameRating * gameRating = new GameRating(game, predictedHomeAverage,
				predictedAwayAverage);
		ratingsMap[game] = gameRating;
		ratings->push_back(gameRating);
	}
	printGamesGoalsPerc();
	delete games;
}

void RatingCalculator::printGamesGoalsPerc() {
	vector<vector<long double>> allGoals = vector<vector<long double> >(
	MAX_NUMBER_GOALS_PREDICT + 1,
			vector<long double>(MAX_NUMBER_GOALS_PREDICT + 1, 0));
	vector<GameRating*>::iterator i;
	for (i = ratings->begin(); i != ratings->end(); i++) {
		vector<vector<double> >* gameGoals = (*i)->getGoalsPerc();
		for (int j = 0; j <= MAX_NUMBER_GOALS_PREDICT; j++) {
			for (int k = 0; k <= MAX_NUMBER_GOALS_PREDICT; k++) {
				allGoals[j][k] += (*gameGoals)[j][k];
			}
		}
	}
	if (!Utils::debugOn()) {
		return;
	}
	printf("Predicted Games Stats:\n");

	for (int n = 0; n <= MAX_NUMBER_GOALS_PREDICT; n++) {
		for (int m = 0; m <= MAX_NUMBER_GOALS_PREDICT; m++) {
			printf("%Lf\t",
					(allGoals[n][m] * PERC_PRECISION) / ratings->size());
		}
		printf("\n");
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

