/*
 * StatisticsPrint.h
 *
 *  Created on: 08/02/2015
 *      Author: Adriano
 */

#ifndef STATISTICS_PRINT_H_
#define STATISTICS_PRINT_H_


#include "../Model/Model.h"
#include "RatingCalculator.h"

class StatisticsPrint {
protected:
public:
	static void printMatchStatisticsForPrediction(FootballGame* game, GameRating* gameRating);
};

#endif /* STATISTICS_PRINT_H_ */
