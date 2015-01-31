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
#include "Predict/PredictLeaguePoisson.h"
#include "Utils/Utils.h"

bool compareDouble(double num1, double num2) {
	double diff = num1 - num2;
	return fabs(num1 - num2) < 0.001;
}

#define ASSERT_BOOL(A) REQUIRE((bool)(A))

TEST_CASE("Debug ON") {
	Utils::configMap[string("debug")] = ("true");
	Utils::configMap[string("debugMath")] = ("true");
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
	vector<FootballGame*>* games = league.getGames();

	ASSERT_BOOL(games->size() == 0);

	teamA = league.getTeam("A");
	teamB = league.getTeam("B");

	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game2 = new FootballGame("date", teamB, teamA, 3, 2);

	REQUIRE(league.getTeam("A")->getID() == teamA->getID());

	league.addGame(game1);

	REQUIRE(league.getTeam("A")->getID() == teamA->getID());

	ASSERT_BOOL(games->size() == 1);

	FootballGame* firstGame = (*games)[0];
	REQUIRE(firstGame->getHomeTeam()->getID() == teamA->getID());
	REQUIRE(firstGame->getAwayTeam()->getID() == teamB->getID());

	league.addGame(game2);

	ASSERT_BOOL(games->size() == 2);
	FootballGame* secondGame = (*games)[1];
	REQUIRE(secondGame->getHomeTeam()->getID() == teamB->getID());
	REQUIRE(secondGame->getAwayTeam()->getID() == teamA->getID());

}

TEST_CASE( "Predict Game", "" ) {
	FootballTeam *teamA = new FootballTeam("A");
	FootballTeam *teamB = new FootballTeam("B");
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	PredictedGame* pred1 = new PredictedGame(game1, 5, 3, 50, 30, 20);

	REQUIRE(game1->getHomeScore() == 2);
	REQUIRE(game1->getAwayScore() == 1);
	REQUIRE(pred1->getHomeAv() == 5);
	REQUIRE(pred1->getAwayAv() == 3);
	REQUIRE(pred1->isHomeWin());
	REQUIRE(pred1->isDraw() == false);
	REQUIRE(pred1->isAwayWin() == false);

	PredictedGame* pred2 = new PredictedGame(game1, 1, 2, 20, 30, 50);
	REQUIRE(pred2->getHomeAv() == 1);
	REQUIRE(pred2->getAwayAv() == 2);
	REQUIRE(pred2->isHomeWin() == false);
	REQUIRE(pred2->isDraw() == false);
	REQUIRE(pred2->isAwayWin());

}
TEST_CASE( "Predict Possion", "" ) {
	FootballLeague league;
	FootballTeam* teamA = league.getTeam("A");
	FootballTeam* teamB = league.getTeam("B");
	FootballTeam* teamC = league.getTeam("C");
	FootballGame* game1 = new FootballGame("date", teamA, teamB, 2, 1);
	FootballGame* game2 = new FootballGame("date", teamB, teamA, 2, 3);
	FootballGame* game3 = new FootballGame("date", teamA, teamC, 2, 2);
	league.addGame(game1);
	league.addGame(game2);
	PredictLeaguePoisson plp = PredictLeaguePoisson(&league);
	plp.predict(0, 0);
	vector<PredictedGame*>* predictedGames = plp.getPredictedGames();
	ASSERT_BOOL(predictedGames->size() == 2);

	PredictedGame* firstGame = (*predictedGames)[0];

	REQUIRE(firstGame->getHomeAv() == 2);
	REQUIRE(firstGame->getAwayAv() == 1);
	REQUIRE(firstGame->isHomeWin());
	ASSERT_BOOL(firstGame->isDraw() == false);
	ASSERT_BOOL(firstGame->isAwayWin() == false);

	PredictedGame* secondGame = (*predictedGames)[1];
	secondGame->debugPrint();
	REQUIRE(secondGame->getHomeAv() == 2);
	REQUIRE(secondGame->getAwayAv() == 3);
	REQUIRE(secondGame->isAwayWin());
	ASSERT_BOOL(secondGame->isHomeWin() == false);
	ASSERT_BOOL(secondGame->isDraw() == false);

	league.addGame(game3);
	plp.predict(0, 0);
	predictedGames = plp.getPredictedGames();
	ASSERT_BOOL(predictedGames->size() == 3);

	PredictedGame* thirdGame = (*predictedGames)[2];
	REQUIRE(thirdGame->getHomeAv() == 2);
	REQUIRE(thirdGame->getAwayAv() == 1.75);
	ASSERT_BOOL(thirdGame->isDraw() == false);
	ASSERT_BOOL(thirdGame->isHomeWin());
	ASSERT_BOOL(thirdGame->isAwayWin() == false);
}
