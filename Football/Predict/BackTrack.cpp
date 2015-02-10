/*
 * BackTrack.cpp
 *
 *  Created on: 08/02/2015
 *      Author: Adriano
 */

#include "BackTrack.h"

BackTrack::BackTrack(Strategy* strategy) :
		strategy(strategy) {
}

void BackTrack::run() {
	PredictLeague* pLeague = strategy->getPredictLeague();
	FootballLeague* league = pLeague->getLeague();
	for (int i = 5; i < league->getLastRound(); i++) {
		pLeague->predict(i, i+1);
		strategy->calculateBets();
		strategy->printGoodBets();
	}

}
BackTrack::~BackTrack() {
// TODO Auto-generated destructor stub
}

