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
	//FootballLeague* league = pLeague->getLeague();
	pLeague->predict(5, 0);
	strategy->printGoodBets();

}
BackTrack::~BackTrack() {
	// TODO Auto-generated destructor stub
}

