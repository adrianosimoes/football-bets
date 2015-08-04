/*
 * BackTrack.h
 *
 *  Created on: 08/02/2015
 *      Author: Adriano
 */

#ifndef PREDICT_BACKTRACK_H_
#define PREDICT_BACKTRACK_H_

#include "HDAStrategy.h"

class BackTrack {
protected:
	int startRound;
	Strategy* strategy;
	double totalWinMoney;
public:
	BackTrack(Strategy* strategy, int startRound);
	void run();
	double getTotalWinMoney(){return totalWinMoney;}
	virtual ~BackTrack();
};

#endif /* PREDICT_BACKTRACK_H_ */
