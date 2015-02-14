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
	double winMoney = 0, gamesWin = 0, sumOdds = 0;
	int betsMade = 0;

	for (int i = 5; i < league->getLastRound(); i++) {
		pLeague->predict(i, i+1);
		//pLeague->debugPrint();
		strategy->calculateBets();
		winMoney += strategy->getWinMoney();
		gamesWin += strategy->getSuccBets();
		sumOdds += strategy->getSumOdds();
		betsMade += strategy->getTotalBetsMade();
		//strategy->printBets();
	}
	printf(
			"Winnings: %f Perc Wins: %f. Average Odd: %f. Win per Bet: %f. Bets: %d\n",
			winMoney, betsMade > 0 ? gamesWin / betsMade : 0,
			gamesWin > 0 ? sumOdds / gamesWin : 0,
			betsMade > 0 ? winMoney / betsMade : 0, betsMade);

}
BackTrack::~BackTrack() {
// TODO Auto-generated destructor stub
}

