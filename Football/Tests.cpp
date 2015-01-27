/*
 * Tests.cpp
 *
 *  Created on: 27/01/2015
 *      Author: Adriano
 */

#include "Tests.hpp"
#define CATCH_CONFIG_MAIN
#include "includes.h"
#include "Model/Team.h"
#include "Model/Game.h"

TEST_CASE( "Test cases", "Matches" ) {

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

