/*
 * RatingCalculator.h
 *
 *  Created on: 28/07/2015
 *      Author: Adriano
 */
#include "StatisticsPrint.h"

void StatisticsPrint::printMatchStatisticsForPrediction(FootballGame* game, GameRating* gameRating ) {
	FootballTeam* homeTeam = game->getHomeTeam();
	FootballTeam* awayTeam = game->getAwayTeam();

	//H Av. Goals S, H Av. Goals C., H Av.Goals A, H Av. Goals C. A,
	printf("%f,%f,%f,%f,",homeTeam->getHomeScoreRating(), homeTeam->getHomeDefenseRating(), homeTeam->getAwayScoreRating(), homeTeam->getAwayDefenseRating());

	//A Av. Goals S, A Av. Goals C, A Av. Goals S H, A aV. Goals C H
	printf("%f,%f,%f,%f,",awayTeam->getHomeScoreRating(), awayTeam->getHomeDefenseRating(), awayTeam->getAwayScoreRating(), awayTeam->getAwayDefenseRating());

	//Result
	printf("%d,%d,%c,%d\n", game->getHomeScore(), game->getAwayScore(), *game->getResult(),game->getHomeScore()-game->getAwayScore());
}

