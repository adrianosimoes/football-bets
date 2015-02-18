/*
 * UOStrategy.cpp
 *
 *  Created on: 17/02/2015
 *      Author: Adriano
 */

#include "UOStrategy.h"

UOStrategy::UOStrategy(PredictLeague* league, int margin) :
		Strategy(league, margin) {
}

UOStrategy::~UOStrategy() {
	// TODO Auto-generated destructor stub
}

void UOStrategy::calculateBets() {
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
			if (bet->isUnderBet()) {
				odd = game->getUnderOdds();
				if (game->isUnderScore()) {
					result = odd;
				}
			}
			if (bet->isOverBet()) {
				odd = game->getOverOdds();
				if (game->isOverScore()) {
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

Bet* UOStrategy::calculateBet(GameRating * rating) {
	if (rating->getUnderPerc()
			> Utils::getPercFromDecOdds(
					rating->getOriginalGame()->getUnderOdds()) + profitMargin) {
		return new Bet(false, false, false, false, true,
				rating->getOriginalGame());
	}

	if (rating->getOverPerc()
			> Utils::getPercFromDecOdds(
					rating->getOriginalGame()->getOverOdds()) + profitMargin) {
		return new Bet(false, false, false, true, false,
				rating->getOriginalGame());
	}

	return NULL;
}
