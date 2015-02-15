/*
 * HDAStrategy.cpp
 *
 *  Created on: 03/02/2015
 *      Author: Adriano
 */

#include "HDAStrategy.h"

Strategy::Strategy(PredictLeague* pLeague) :
		predictedLeague(pLeague) {
	goodBets = new vector<Bet*>();
	winMoney = 0, succBets = 0, sumOdds = 0;
}

Strategy::~Strategy() {
}

PredictLeague* Strategy::getPredictLeague() {
	return predictedLeague;
}

double Strategy::getWinMoney() {
	return winMoney;
}
double Strategy::getSuccBets() {
	return succBets;
}
double Strategy::getSumOdds() {
	return sumOdds;
}
int Strategy::getTotalBetsMade() {
	return goodBets->size();
}

HDAStrategy::HDAStrategy(PredictLeague* pleague, int profitMargin) :
		Strategy(pleague), profitMargin(profitMargin) {
}

Bet::Bet(bool homeWin, bool draw, bool awayWin, bool over25, bool under25,
		FootballGame* game) :
		isHomeWin(homeWin), isDraw(draw), isAwayWin(awayWin), isUnder25(
				under25), isOver25(over25), game(game) {
	if (isHomeWin || isDraw || isAwayWin) {
		type = HDA;
		if (isHomeWin) {
			betType = 'H';
		} else if (isDraw) {
			betType = 'D';
		} else if (isAwayWin) {
			betType = 'A';
		}
	} else if (isUnder25 || isOver25) {
		type = OVER_UNDER;
	} else {
		throw "Bet with no type";
	}
}

FootballGame* Bet::getGame() {
	return game;
}

bool Bet::isHomeBet() {
	return isHomeWin;
}

bool Bet::isDrawBet() {
	return isDraw;
}

bool Bet::isAwayBet() {
	return isAwayWin;
}

char Bet::getbetType() {
	return betType;
}

void HDAStrategy::cleanBets() {
	winMoney = 0, succBets = 0, sumOdds = 0;
	vector<Bet*>::iterator i;
	for (i = goodBets->begin(); i != goodBets->end(); i++) {
		delete *i;
	}
	goodBets->clear();
}

void HDAStrategy::calculateBets() {
	cleanBets();
	vector<GameRating*>::iterator i;
	for (i = predictedLeague->getGameRatings()->begin();
			i != predictedLeague->getGameRatings()->end(); i++) {
		Bet* bet = calculateBet(*i);
		if (bet != NULL) {
			goodBets->push_back(bet);
			FootballGame* game = (*i)->getOriginalGame();
			double odd = 0, result = 0;
			winMoney = winMoney - 1;
			if (bet->isHomeBet()) {
				odd = game->getHomeWinOdds();
				if (game->isHomeWin()) {
					result = odd;
				}
			}
			if (bet->isDrawBet()) {
				odd = game->getDrawOdds();
				if (game->isDraw()) {
					result = odd;
				}
			}
			if (bet->isAwayBet()) {
				odd = game->getAwayWinOdds();
				if (game->isAwayWin()) {
					result = odd;
				}
			}
			winMoney = winMoney + result;
			if (result > 0) {
				succBets++;
				sumOdds += result;
			}
		}
	}
}

Bet* HDAStrategy::calculateBet(GameRating * rating) {
	if (rating->getHomeWinPerc()
			> Utils::getPercFromDecOdds(
					rating->getOriginalGame()->getHomeWinOdds())
					+ profitMargin) {
		return new Bet(true, false, false, false, false,
				rating->getOriginalGame());
	}

	if (rating->getDrawPerc()
			> Utils::getPercFromDecOdds(
					rating->getOriginalGame()->getDrawOdds()) + profitMargin) {
		return new Bet(false, true, false, false, false,
				rating->getOriginalGame());
	}

	if (rating->getAwayWinPerc()
			> Utils::getPercFromDecOdds(
					rating->getOriginalGame()->getAwayWinOdds())
					+ profitMargin) {
		return new Bet(false, false, true, false, false,
				rating->getOriginalGame());
	}

	return NULL;
}

void HDAStrategy::printBets() {
	vector<Bet*>::iterator i;
	printf("Good Bets(%ld)  \n", goodBets->size());
	for (i = goodBets->begin(); i != goodBets->end(); i++) {
		FootballGame* game = (*i)->getGame();
		printf("Match: %s - %s. Bet: %c\n",
				game->getHomeTeam()->getName().c_str(),
				game->getAwayTeam()->getName().c_str(), (*i)->getbetType());
	}
	/*printf(
	 "Winnings: %f Perc Wins: %f. Average Odd: %f. Win per Bet: %f. Bets: %ld\n",
	 winMoney, goodBets->size() > 0 ? succBets / goodBets->size() : 0,
	 succBets > 0 ? sumOdds / succBets : 0,
	 goodBets->size() > 0 ? winMoney / goodBets->size() : 0,
	 goodBets->size());*/
}

HDAStrategy::~HDAStrategy() {
}

