/*
 * HDAStrategy.cpp
 *
 *  Created on: 03/02/2015
 *      Author: Adriano
 */

#include "HDAStrategy.h"

Strategy::Strategy(PredictLeague* pLeague) :
		predictedLeague(pLeague) {
}

Strategy::~Strategy() {
}

PredictLeague* Strategy::getPredictLeague() {
	return predictedLeague;
}

HDAStrategy::HDAStrategy(PredictLeague* pleague, int profitMargin) :
		Strategy(pleague), profitMargin(profitMargin) {
	goodBets = new vector<Bet*>();
	calculateBets();
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

void HDAStrategy::calculateBets() {
	vector<GameRating*>::iterator i;
	for (i = predictedLeague->getGameRatings()->begin();
			i != predictedLeague->getGameRatings()->end(); i++) {
		Bet* bet = calculateBet(*i);
		if (bet != NULL) {
			goodBets->push_back(bet);
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

void HDAStrategy::printGoodBets() {
	vector<Bet*>::iterator i;
	double money = 0, gamesWin = 0, sumOdds = 0;
	printf("Good Bets(%d)  \n", profitMargin);
	for (i = goodBets->begin(); i != goodBets->end(); i++) {
		FootballGame* game = (*i)->getGame();
		double odd = 0, result = 0;
		money = money - 1;
		if ((*i)->isHomeBet()) {
			odd = game->getHomeWinOdds();
			if (game->isHomeWin()) {
				result = odd;
			}
		}
		if ((*i)->isDrawBet()) {
			odd = game->getDrawOdds();
			if (game->isDraw()) {
				result = odd;
			}
		}
		if ((*i)->isAwayBet()) {
			odd = game->getAwayWinOdds();
			if (game->isAwayWin()) {
				result = odd;
			}
		}
		money = money + result;
		if (result > 0) {
			gamesWin++;
			sumOdds += result;
		}
		/*printf("Match: %s - %s. Bet: %c Odd: %f Result: %f\n",
		 game->getHomeTeam()->getName().c_str(),
		 game->getAwayTeam()->getName().c_str(), (*i)->getbetType(), odd,
		 result);*/
	}
	printf(
			"Winnings: %f Perc Wins: %f. Average Odd: %f. Win per Bet: %f. Bets: %ld\n",
			money, gamesWin / goodBets->size(), sumOdds / gamesWin,
			money / goodBets->size(), goodBets->size());
}

HDAStrategy::~HDAStrategy() {
}

