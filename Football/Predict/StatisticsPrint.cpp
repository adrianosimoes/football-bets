/*
 * RatingCalculator.h
 *
 *  Created on: 28/07/2015
 *      Author: Adriano
 */
#include "StatisticsPrint.h"

void StatisticsPrint::printMatchStatisticsForPrediction(FootballGame* game, GameRating* gameRating ) {
	TeamRating* homeTeam = gameRating->getHomeRating();
	TeamRating* awayTeam = gameRating->getAwayRating();

	if (!Utils::debugOn(string("printMatchStatisticsForPrediction"))) {
			return;
	}

	//H Av. Goals S, H Av. Goals C., H Av.Goals A, H Av. Goals C. A,
	printf("%f,%f,%f,%f,",homeTeam->getHomeScoreRating(), homeTeam->getHomeDefenseRating(), awayTeam->getAwayScoreRating(), awayTeam->getAwayDefenseRating());

	//A Av. Goals S, A Av. Goals C, A Av. Goals S H, A aV. Goals C H
	printf("%f,%f,%f,%f,",homeTeam->getHomeScoreRatingRecent(5), homeTeam->getHomeDefenseRatingRecent(5), awayTeam->getAwayScoreRatingRecent(5), awayTeam->getAwayDefenseRatingRecent(5));

	//Result
	printf("%d,%d,%c,%d\n", game->getHomeScore(), game->getAwayScore(), *game->getResult(),game->getHomeScore()-game->getAwayScore());
}

