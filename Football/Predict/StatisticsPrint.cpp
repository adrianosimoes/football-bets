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
	int recentGames =8;

	if (!Utils::debugOn(string("printMatchStatisticsForPrediction"))) {
			return;
	}

	//H Av. Goals S, H Av. Goals C., H Av.Goals A, H Av. Goals C. A,
	printf("%f,%f,%f,%f,",homeTeam->getHomeScoreRating(), homeTeam->getHomeDefenseRating(), awayTeam->getAwayScoreRating(), awayTeam->getAwayDefenseRating());

	//A Av. Goals S, A Av. Goals C, A Av. Goals S H, A aV. Goals C H
	printf("%f,%f,%f,%f,",homeTeam->getHomeScoreRatingRecent(recentGames), homeTeam->getHomeDefenseRatingRecent(recentGames), awayTeam->getAwayScoreRatingRecent(recentGames), awayTeam->getAwayDefenseRatingRecent(recentGames));

	//Result
	printf("%d,%d,%c,%d\n", game->getHomeScore(), game->getAwayScore(), *game->getResult(),game->getHomeScore()-game->getAwayScore());
}

