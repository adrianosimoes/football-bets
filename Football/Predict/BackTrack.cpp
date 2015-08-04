/*
 * BackTrack.cpp
 *
 *  Created on: 08/02/2015
 *      Author: Adriano
 */

#include "BackTrack.h"

BackTrack::BackTrack(Strategy* strategy, int startRound) :
		strategy(strategy), startRound(startRound) {
	totalWinMoney=0;
}

void BackTrack::run() {
	PredictLeague* pLeague = strategy->getPredictLeague();
	FootballLeague* league = pLeague->getLeague();
	double gamesWin = 0, sumOdds = 0;
	int betsMade = 0;

	for (int i = startRound; i < league->getLastRound(); i++) {
		pLeague->predict(i, i+1);
		//pLeague->debugPrint();
		strategy->calculateBets();
		totalWinMoney += strategy->getWinMoney();
		gamesWin += strategy->getSuccBets();
		sumOdds += strategy->getSumOdds();
		betsMade += strategy->getTotalBetsMade();
		//strategy->printBets();
	}
	printf(
			"Winnings: %f Perc Wins: %f. Average Odd: %f. Win per Bet: %f. Bets: %d\n",
			totalWinMoney, betsMade > 0 ? gamesWin / betsMade : 0,
			gamesWin > 0 ? sumOdds / gamesWin : 0,
			betsMade > 0 ? totalWinMoney / betsMade : 0, betsMade);

}
BackTrack::~BackTrack() {
// TODO Auto-generated destructor stub
}

