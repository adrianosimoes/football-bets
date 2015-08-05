/*
 * RatingCalculator.cpp
 *
 *  Created on: 31/01/2015
 *      Author: Adriano
 */

#include "RatingCalculator.h"
#include "StatisticsPrint.h"

TeamRating::TeamRating(FootballTeam* team) :
		FootballTeam(team->getName(), team->getID()) {
	homeScoreRating = 0;
	awayScoreRating = 0;
	homeDefenseRating = 0;
	awayDefenseRating = 0;
	homeScoreRatingRecent = 0;
	awayScoreRatingRecent = 0;
	homeDefenseRatingRecent = 0;
	awayDefenseRatingRecent = 0;
}

void TeamRating::setRatingsFromStats(int numberOFRecentGames) {
	homeScoreRating = FootballTeam::getHomeScoreRating();
	awayScoreRating = FootballTeam::getAwayScoreRating();
	homeDefenseRating = FootballTeam::getHomeDefenseRating();
	awayDefenseRating = FootballTeam::getAwayDefenseRating();

	/*homeScoreRatingRecent = getHomeScoreRatingRecent(numberOFRecentGames);
	awayScoreRatingRecent = getAwayScoreRatingRecent(numberOFRecentGames);
	homeDefenseRatingRecent = getHomeDefenseRatingRecent(numberOFRecentGames);
	awayDefenseRatingRecent = getAwayDefenseRatingRecent(numberOFRecentGames);*/
}

double TeamRating::getHomeScoreRating(TeamRating* awayRating,
		TeamRating* avgRating) {
	return (this->homeScoreRating + awayRating->getAwayDefenseRating()) / 2;
}
double TeamRating::getAwayScoreRating(TeamRating* homeRating,
		TeamRating* avgRating) {
	return (this->awayScoreRating + homeRating->getHomeDefenseRating()) / 2;
}

/*void TeamRating::setRatings(double homeScoreRating, double awayScoreRating,
		double homeDefenseRating, double awayDefenseRating) {
	this->homeScoreRating = homeScoreRating;
	this->awayScoreRating = awayScoreRating;
	this->homeDefenseRating = homeDefenseRating;
	this->awayDefenseRating = awayDefenseRating;
}*/

void TeamRating::setRatingsToAverage(double leagueHome, double leagueAway) {
	this->homeScoreRating = (homeMatches ? (homeGoals / homeMatches) : 30)
			/ leagueHome;
	this->awayScoreRating = (awayMatches ? (awayGoals / awayMatches) : 30)
			/ leagueAway;
	this->homeDefenseRating = (homeMatches ? (homeConceded / homeMatches) : 30)
			/ leagueAway;
	this->awayDefenseRating = (awayMatches ? (awayConceded / awayMatches) : 30)
			/ leagueHome;
}

double TeamRating::getHomeScoreRating() {
	return homeScoreRating;
}
double TeamRating::getAwayScoreRating() {
	return awayScoreRating;
}
double TeamRating::getHomeDefenseRating() {
	return homeDefenseRating;
}
double TeamRating::getAwayDefenseRating() {
	return awayDefenseRating;
}

GameRating::GameRating(FootballGame* game, TeamRating* homeR, TeamRating* awayR,
		TeamRating* avgRating) :
		game(game), homeRating(homeR), awayRating(awayR), avgRating(avgRating) {

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

int GameRating::getUnderPerc() {
	return underPerc;
}

int GameRating::getOverPerc() {
	return overPerc;
}

void GameRating::calculateGamePercentages(bool debugPrint) {
	vector<double> homeGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	vector<double> awayGoalsPerc(MAX_NUMBER_GOALS_PREDICT + 1);
	homePerc = 0, drawPerc = 0, awayPerc = 0, underPerc = 0, overPerc = 0;

	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		homeGoalsPerc[i] = RatingCalculator::poisson_pmf(getHomeRatingScore(),
				i);
		awayGoalsPerc[i] = RatingCalculator::poisson_pmf(getAwayRatingScore(),
				i);
	}

	if (Utils::debugMathOn() || debugPrint) {
		printf("Game Rating Score Data:\t%f\t%f\n", getHomeRatingScore(),
				getAwayRatingScore());
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

	// Under/Over Calc:
	for (int i = 0; i <= MAX_NUMBER_GOALS_PREDICT; i++) {
		for (int j = 0; j <= MAX_NUMBER_GOALS_PREDICT; j++) {
			if (i + j <= 2) {
				underPerc += (int) (homeGoalsPerc[i] * awayGoalsPerc[j]
						* PERC_PRECISION * 100);
			} else {
				overPerc += (int) (homeGoalsPerc[i] * awayGoalsPerc[j]
						* PERC_PRECISION * 100);
			}
		}
	}

	if (Utils::debugMathOn() || debugPrint) {
		printf("Home:\t%d\tDraw:\t%d\tAway:\t%d\n Under:\t%d\tOver:%d\n",
				(int) homePerc / PERC_PRECISION,
				(int) drawPerc / PERC_PRECISION,
				(int) awayPerc / PERC_PRECISION,
				(int) underPerc / PERC_PRECISION,
				(int) overPerc / PERC_PRECISION);
	}
	homePerc = homePerc / PERC_PRECISION;
	drawPerc = drawPerc / PERC_PRECISION;
	awayPerc = awayPerc / PERC_PRECISION;
	underPerc = underPerc / PERC_PRECISION;
	overPerc = overPerc / PERC_PRECISION;
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

double GameRating::getHomeRatingScore() {
	return homeRating->getHomeScoreRating(awayRating, avgRating);
}

double GameRating::getAwayRatingScore() {
	return awayRating->getAwayScoreRating(homeRating, avgRating);
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
	 awayTeam->getAwayDefenseRating();
	printf("Home Team: %s, Away Team: %s\n",
			game->getHomeTeam()->getName().c_str(),
			game->getAwayTeam()->getName().c_str());

	printf(
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

	printf("Pred Home Score: %f\tPred Away  Score:%f\n", getHomeRatingScore(),
			getAwayRatingScore());

	printf("Home Win: %d\tDraw:%d\tAway Win:%d\t\n", homePerc, drawPerc,
			awayPerc);

}

RatingCalculator::RatingCalculator(FootballLeague* league, RatingFactory* rf) :
		league(league), factory(rf) {
	ratingsMap = map<FootballGame*, GameRating*>();
	ratings = new vector<GameRating*>();
	averageTeamRating = NULL;
	teamRatings = map<FootballTeam*, TeamRating*>();
}

void RatingCalculator::clearRatings() {
	vector<GameRating*>::iterator i;
	map<FootballTeam*, TeamRating*>::iterator j;
	for (i = ratings->begin(); i != ratings->end(); i++) {
		delete *i;
	}
	for (j = teamRatings.begin(); j != teamRatings.end(); j++) {
		delete (*j).second;
	}
	teamRatings.clear();
	ratingsMap.clear();
	ratings->clear();
	delete averageTeamRating;
	averageTeamRating = NULL;
}

TeamRating* RatingCalculator::getTeamRating(FootballTeam* team) {

	std::map<FootballTeam*, TeamRating*>::iterator i = teamRatings.find(team);
	if (i == teamRatings.end()) {
		TeamRating* rating = factory->createTeamRating(team);
		teamRatings[team] = rating;
		return rating;
	}
	return (*i).second;
}

void printGames(vector<FootballGame*> gamesList) {
	vector<FootballGame*>::iterator i;
	printf("Games analised: %ld\n", gamesList.size());
	for (i = gamesList.begin(); i != gamesList.end(); i++) {
		(*i)->debugPrint();
	}
}

void RatingCalculator::calculateTeamRatings(int startRound, int endRound) {
	vector<FootballGame*>* games = league->getGames(startRound, endRound);
	//printGames(*games);

	FootballTeam* avg = new FootballTeam("Avg");
	averageTeamRating = factory->createTeamRating(avg);

	vector<FootballGame*>::iterator i;
	for (i = games->begin(); i != games->end(); i++) {
		TeamRating* homeRating = getTeamRating((*i)->getHomeTeam());
		TeamRating* awayRating = getTeamRating((*i)->getAwayTeam());
		homeRating->addGame(*i);
		awayRating->addGame(*i);
		averageTeamRating->addGameStats(*i, true);
		averageTeamRating->addGameStats(*i, false);
	}

	//averageTeamRating->setRatingsFromStats(0);
	//averageTeamRating->debugPrint();
	std::map<FootballTeam*, TeamRating*>::iterator j;
	for (j = teamRatings.begin(); j != teamRatings.end(); j++) {
		TeamRating* rating = (*j).second;
		//rating->setRatingsToAverage(averageTeamRating->getHomeScoreRating(),
		//		averageTeamRating->getAwayScoreRating());
		rating->setRatingsFromStats(10);
	}

	delete games;
}

void RatingCalculator::preditRatings(int startRound, int endRound) {
	clearRatings();
	calculateTeamRatings(1, startRound);
	vector<FootballGame*>* games = league->getGames(startRound, endRound);
	vector<FootballGame*>::iterator i;
	for (i = games->begin(); i != games->end(); i++) {
		FootballGame* game = *i;

		TeamRating* homeRating = getTeamRating(game->getHomeTeam());
		TeamRating* awayRating = getTeamRating(game->getAwayTeam());
		//homeRating->debugPrint();
		//awayRating->debugPrint();

		GameRating * gameRating = new GameRating(game, homeRating, awayRating,
				averageTeamRating);
		//gameRating->debugPrint();
		StatisticsPrint::printMatchStatisticsForPrediction(game, gameRating);

		ratingsMap[game] = gameRating;
		ratings->push_back(gameRating);
	}
	//printGamesGoalsPerc();
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
	if (!Utils::debugOn(string("debugPrintGamesGoalsPerc"))) {
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
	map<FootballGame*, GameRating*>::iterator i = ratingsMap.find(game);

	if (i == ratingsMap.end()) {
		printf("Game rating is null.%s - %s\n",
				game->getHomeTeam()->getName().c_str(),
				game->getAwayTeam()->getName().c_str());
		return NULL;
	}

	return (*i).second;
}

RatingCalculator* RatingFactory::createRatingCalculator(
		FootballLeague* league) {
	return new RatingCalculator(league, this);
}

TeamRating* RatingFactory::createTeamRating(FootballTeam* team) {
	return new TeamRating(team);
}

RatingCalculator::~RatingCalculator() {
}

