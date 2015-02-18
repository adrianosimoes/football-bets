/*
 * UOStrategy.h
 *
 *  Created on: 17/02/2015
 *      Author: Adriano
 */

#ifndef PREDICT_UOSTRATEGY_H_
#define PREDICT_UOSTRATEGY_H_

#include "HDAStrategy.h"

class UOStrategy: public Strategy {
public:
	UOStrategy(PredictLeague* league, int profitMargin);
	void calculateBets();
	Bet* calculateBet(GameRating * rating);
	virtual ~UOStrategy();
};

#endif /* PREDICT_UOSTRATEGY_H_ */
