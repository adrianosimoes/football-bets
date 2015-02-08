/*
 * PredictLeague.cpp
 *
 *  Created on: 28/01/2015
 *      Author: Adriano
 */

#include "PredictLeague.h"

void PredictLeague::predict(int startRound, int roundBeforeEnd) {
	delete ratingCalc;
	setRating(new RatingCalculator(this->league));
	ratingCalc->preditRatings(startRound, roundBeforeEnd);
}

GameRating* PredictLeague::getGameRating(FootballGame* game) {
	return ratingCalc->getRatings(game);
}

std::vector<GameRating*>* PredictLeague::getGameRatings() {
	return ratingCalc->getGameRatings();
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
	printf("Real Results:\t%d%%\t%d%%\t%d%%\n", (home * 100) / allMatches,
			(draw * 100) / allMatches, (away * 100) / allMatches);
	printf("Number of games:\t%d\t%d\t%d\n", home, draw, away);
}

void printPredictedStats(vector<GameRating*>* games) {
	int home = 0, draw = 0, away = 0, allMatches = 0;
	vector<GameRating*>::iterator i;
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
	printf("Model Results:\t%d%%\t%d%%\t%d%%\n", (home * 100) / allMatches,
			(draw * 100) / allMatches, (away * 100) / allMatches);
}

void PredictLeague::printResultsHDL() {
	printStats(league->getGames(0,0));
	//printPredictedStats(getGameRatings());
}

void PredictLeague::debugPrint() {
	vector<GameRating*>::iterator i;
	for (i = getGameRatings()->begin(); i != getGameRatings()->end(); i++) {
		(*i)->debugPrint();
	}
}

void PredictLeague::setRating(RatingCalculator* ratingCalc) {
	this->ratingCalc = ratingCalc;
}

PredictLeague::PredictLeague(FootballLeague* league, RatingCalculator* rc) :
		league(league), ratingCalc(rc) {
}

PredictLeague::~PredictLeague() {
}
