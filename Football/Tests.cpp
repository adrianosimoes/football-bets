/*
 * Tests.cpp
 *
 *  Created on: 27/01/2015
 *      Author: Adriano
 */

#define CATCH_CONFIG_MAIN
#include "Tests.hpp"
#include "includes.h"
#include "Model/Model.h"
#include "Predict/PredictLeague.h"
#include "Predict/RatingCalculator.h"
#include "Utils/Utils.h"
#include "Predict/HDAStrategy.h"

bool compareDouble(double num1, double num2) {
	double diff = num1 - num2;
	return fabs(num1 - num2) < 0.001;
}

#define ASSERT_BOOL(A) REQUIRE((bool)(A))

TEST_CASE("Debug ON") {
	Utils::configMap[string("debug")] = ("true");
	//Utils::configMap[string("debugMath")] = ("true");
}

TEST_CASE( "Matches", "" ) {

	FootballTeam teamA("A");
	FootballTeam teamB("B");
	FootballGame game1("date", &teamA, &teamB, 2, 1);
	REQUIRE(game1.getHomeScore() == 2);
	REQUIRE(game1.getAwayScore() == 1);
	REQUIRE(game1.getHomeTeam() == &teamA);
	REQUIRE(game1.isHomeWin() == true);
	REQUIRE(game1.isAwayWin() == false);
	REQUIRE(game1.isDraw() == false);
}

TEST_CASE( "Goals", "" ) {
	FootballTeam teamA("A");
	FootballTeam teamB("B");
	FootballGame game1("date", &teamA, &teamB, 2, 1);
	FootballGame game2("date", &teamA, &teamB, 3, 2);

	REQUIRE(compareDouble(teamA.getHomeScoreRating(), 0.0));
	REQUIRE(compareDouble(teamA.getHomeDefenseRating(), 0.0));
	REQUIRE(compareDouble(teamA.getAwayScoreRating(), 0.0));
	REQUIRE(compareDouble(teamA.getAwayDefenseRating(), 0.0));

	teamA.addGame(&game1);
	teamB.addGame(&game1);

	REQUIRE(compareDouble(teamA.getHomeScoreRating(), 2));
	REQUIRE(compareDouble(teamA.getHomeDefenseRating(), 1));
	REQUIRE(compareDouble(teamA.getAwayScoreRating(), 0));
	REQUIRE(compareDouble(teamA.getAwayDefenseRating(), 0));

	REQUIRE(compareDouble(teamB.getHomeScoreRating(), 0));
	REQUIRE(compareDouble(teamB.getHomeDefenseRating(), 0));
	REQUIRE(compareDouble(teamB.getAwayScoreRating(), 1));
	REQUIRE(compareDouble(teamB.getAwayDefenseRating(), 2));

	teamA.addGame(&game2);
	teamB.addGame(&game2);

	REQUIRE(compareDouble(teamA.getHomeScoreRating(), 2.5));
	REQUIRE(compareDouble(teamA.getHomeDefenseRating(), 1.5));
	REQUIRE(compareDouble(teamA.getAwayScoreRating(), 0));
	REQUIRE(compareDouble(teamA.getAwayDefenseRating(), 0));

	REQUIRE(compareDouble(teamB.getHomeScoreRating(), 0));
	REQUIRE(compareDouble(teamB.getHomeDefenseRating(), 0));
	REQUIRE(compareDouble(teamB.getAwayScoreRating(), 1.5));
	REQUIRE(compareDouble(teamB.getAwayDefenseRating(), 2.5));
}

TEST_CASE( "League", "" ) {
	FootballLeague league;
	FootballTeam* teamA;
	FootballTeam* teamB;
	vector<FootballGame*>* games = league.getAllGames();

	ASSERT_BOOL(games->size() == 0);

	teamA = league.getTeam("A");
	teamB = league.getTeam("B");

	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game2 = new FootballGame("date", teamB, teamA, 3, 2);

	REQUIRE(league.getTeam("A")->getID() == teamA->getID());

	league.addGame(game1);
	games = league.getAllGames();

	REQUIRE(league.getTeam("A")->getID() == teamA->getID());

	ASSERT_BOOL(games->size() == 1);

	FootballGame* firstGame = (*games)[0];
	REQUIRE(firstGame->getHomeTeam()->getID() == teamA->getID());
	REQUIRE(firstGame->getAwayTeam()->getID() == teamB->getID());

	league.addGame(game2);
	games = league.getAllGames();

	ASSERT_BOOL(games->size() == 2);
	FootballGame* secondGame = (*games)[1];
	REQUIRE(secondGame->getHomeTeam()->getID() == teamB->getID());
	REQUIRE(secondGame->getAwayTeam()->getID() == teamA->getID());

}

TEST_CASE( "Predict Game", "" ) {
	FootballTeam *teamA = new FootballTeam("A");
	FootballTeam *teamB = new FootballTeam("B");
	TeamRating* ra = new TeamRating(teamA);
	TeamRating* rb = new TeamRating(teamB);
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game2 = new FootballGame("date", teamA, teamB, 5, 3);
	ra->addGame(game2);
	rb->addGame(game2);
	ra->setRatingsFromStats();
	rb->setRatingsFromStats();

	GameRating* pred1 = new GameRating(game1, ra, rb, NULL);

	REQUIRE(game1->getHomeScore() == 2);
	REQUIRE(game1->getAwayScore() == 1);
	REQUIRE(pred1->getHomeRatingScore() == 5);
	REQUIRE(pred1->getAwayRatingScore() == 3);
	REQUIRE(pred1->isHomeWin());
	REQUIRE(pred1->isDraw() == false);
	REQUIRE(pred1->isAwayWin() == false);

	FootballGame* game3 = new FootballGame("date", teamA, teamB, 1, 2);
	TeamRating* ra2 = new TeamRating(teamA);
	TeamRating* rb2 = new TeamRating(teamB);
	ra2->addGame(game3);
	rb2->addGame(game3);
	ra2->setRatingsFromStats();
	rb2->setRatingsFromStats();
	GameRating* pred3 = new GameRating(game2, ra2, rb2, NULL);
	REQUIRE(pred3->getHomeRatingScore() == 1);
	REQUIRE(pred3->getAwayRatingScore() == 2);
	REQUIRE(pred3->isHomeWin() == false);
	REQUIRE(pred3->isDraw() == false);
	REQUIRE(pred3->isAwayWin());
}

TEST_CASE( "Game Rating", "" ) {
	FootballTeam *teamA = new FootballTeam("A");
	FootballTeam *teamB = new FootballTeam("B");
	TeamRating* ra = new TeamRating(teamA);
	TeamRating* rb = new TeamRating(teamB);
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 3, 4);
	ra->addGame(game1);
	rb->addGame(game1);
	ra->setRatingsFromStats();
	rb->setRatingsFromStats();
	GameRating *gr = new GameRating(game1, ra, rb, NULL);
	REQUIRE(gr->getHomeRatingScore() == 3);
	REQUIRE(gr->getAwayRatingScore() == 4);
}

TEST_CASE( "Rating Calculator", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamB = league.getTeam("B");
	FootballTeam* teamC = league.getTeam("C");
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game1b = new FootballGame("date", teamA, teamB, 5, 3);
	league.addGame(game1);
	league.addGame(game1b);
	RatingCalculator rc = RatingCalculator(&league);
	rc.preditRatings(2, league.getLastRound() + 1);

	GameRating* firstGame = rc.getRatings(game1b);

	REQUIRE(firstGame!=NULL);
	REQUIRE(firstGame->getHomeRatingScore() == 2);
	REQUIRE(firstGame->getAwayRatingScore() == 1);
}

TEST_CASE( "Predict Possion", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamB = league.getTeam("B");
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game2 = new FootballGame("date", teamA, teamB, 5, 5);
	league.addGame(game1);
	league.addGame(game2);
	PredictLeague pl = PredictLeague(&league,
			RatingFactory::createPoissonRating(&league));
	pl.predict(2, league.getLastRound() + 1);
	vector<GameRating*>* predictedGames = pl.getGameRatings();
	ASSERT_BOOL(predictedGames->size() == 1);

	GameRating* firstGame = (*predictedGames)[0];
	GameRating* r = pl.getGameRating(game2);

	REQUIRE(firstGame->getHomeRatingScore() == 2);
	REQUIRE(firstGame->getAwayRatingScore() == 1);
	REQUIRE(firstGame->isHomeWin());
	ASSERT_BOOL(firstGame->isDraw() == false);
	ASSERT_BOOL(firstGame->isAwayWin() == false);
}

TEST_CASE( "Predict Possion Bigger League", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamB = league.getTeam("B");
	FootballTeam* teamC = league.getTeam("C");
	FootballTeam* teamD = league.getTeam("D");
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 0, 2);
	FootballGame* game2 = new FootballGame("date", teamD, teamC, 2, 1);
	FootballGame* game3 = new FootballGame("date", teamC, teamA, 4, 0);
	FootballGame* game4 = new FootballGame("date", teamB, teamD, 1, 3);
	FootballGame* game5 = new FootballGame("date", teamB, teamA, 0, 0);
	FootballGame* game6 = new FootballGame("date", teamC, teamB, 7, 8);
	FootballGame* game7 = new FootballGame("date", teamA, teamC, 9, 10);
	FootballGame* game8 = new FootballGame("date", teamD, teamB, 11, 12);

	league.addGame(game1);
	league.addGame(game2);
	league.addGame(game3);
	league.addGame(game4);
	league.addGame(game5);
	league.addGame(game6);
	league.addGame(game7);
	league.addGame(game8);

	PredictLeague pl = PredictLeague(&league,
			RatingFactory::createPoissonRating(&league));

	pl.predict(3, league.getLastRound() + 1);
	vector<GameRating*>* predictedGames = pl.getGameRatings();
	ASSERT_BOOL(predictedGames->size() == 4);

	GameRating* fifth = (*predictedGames)[0];

	REQUIRE(fifth->getHomeRatingScore() == 2.5);
	REQUIRE(fifth->getAwayRatingScore() == 1.5);
	REQUIRE(fifth->isHomeWin());
	ASSERT_BOOL(fifth->isDraw() == false);
	ASSERT_BOOL(fifth->isAwayWin() == false);

	GameRating* sixth = (*predictedGames)[1];
	REQUIRE(sixth->getHomeRatingScore() == 2);
	REQUIRE(sixth->getAwayRatingScore() == 1);
	ASSERT_BOOL(sixth->isDraw() == false);
	ASSERT_BOOL(sixth->isHomeWin());
	ASSERT_BOOL(sixth->isAwayWin() == false);
}

TEST_CASE( "Test Odds", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamB = league.getTeam("B");
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game2 = new FootballGame("date", teamB, teamA, 2, 3);
	league.addGame(game1);
	league.addGame(game2);
	game1->setOdds(2.0, 3.0, 4.0);
	game2->setOdds(7.0, 6.0, 5.0);

	REQUIRE(compareDouble(game1->getHomeWinOdds(), 2.0));
	REQUIRE(compareDouble(game1->getDrawOdds(), 3.0));
	REQUIRE(compareDouble(game1->getAwayWinOdds(), 4.0));

	REQUIRE(compareDouble(game2->getHomeWinOdds(), 7.0));
	REQUIRE(compareDouble(game2->getDrawOdds(), 6.0));
	REQUIRE(compareDouble(game2->getAwayWinOdds(), 5.0));
}

TEST_CASE( "Odds Conv", "" ) {
	REQUIRE(compareDouble(Utils::getPercFromDecOdds(2), 50));
	REQUIRE(compareDouble(Utils::getPercFromDecOdds(3), 33.333));
	REQUIRE(compareDouble(Utils::getPercFromDecOdds(1.25), 80));
	REQUIRE(compareDouble(Utils::getPercFromDecOdds(1.333), 75.019));
	REQUIRE(compareDouble(Utils::getPercFromDecOdds(1.1), 90.91));
}

TEST_CASE( "Test Bet", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamC = league.getTeam("C");
	FootballGame* game3 = new FootballGame("date", teamA, teamC, 2, 2);

	Bet* homeBet = new Bet(true, false, false, false, false, game3);
	Bet* drawBet = new Bet(false, true, false, false, false, game3);
	Bet* awayBet = new Bet(false, false, true, false, false, game3);

	REQUIRE(homeBet->isHomeBet() == true);
	REQUIRE(homeBet->isDrawBet() == false);
	REQUIRE(homeBet->isAwayBet() == false);
	REQUIRE(homeBet->getbetType() == 'H');

	REQUIRE(drawBet->isHomeBet() == false);
	REQUIRE(drawBet->isDrawBet() == true);
	REQUIRE(drawBet->isAwayBet() == false);
	REQUIRE(drawBet->getbetType() == 'D');

	REQUIRE(awayBet->isHomeBet() == false);
	REQUIRE(awayBet->isDrawBet() == false);
	REQUIRE(awayBet->isAwayBet() == true);
	REQUIRE(awayBet->getbetType() == 'A');
}

TEST_CASE( "Test Bet and Rating", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamC = league.getTeam("C");
	FootballGame* game3 = new FootballGame("date", teamA, teamC, 2, 2);

	Bet* homeBet = new Bet(true, false, false, false, false, game3);
	Bet* drawBet = new Bet(false, true, false, false, false, game3);
	Bet* awayBet = new Bet(false, false, true, false, false, game3);

	REQUIRE(homeBet->isHomeBet() == true);
	REQUIRE(homeBet->isDrawBet() == false);
	REQUIRE(homeBet->isAwayBet() == false);

	REQUIRE(drawBet->isHomeBet() == false);
	REQUIRE(drawBet->isDrawBet() == true);
	REQUIRE(drawBet->isAwayBet() == false);

	REQUIRE(awayBet->isHomeBet() == false);
	REQUIRE(awayBet->isDrawBet() == false);
	REQUIRE(awayBet->isAwayBet() == true);
}
