/*
 * League.h
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_LEAGUE_H_
#define MODEL_LEAGUE_H_

#include "../includes.h"
#include "Game.h"
#include "Team.h"

#define MAX_NUMBER_GOALS_PREDICT 10
#define PERC_PRECISION 100

class FootballLeague {
protected:
	string name;
	vector<FootballGame*>* games;
	map<string, FootballTeam*> teams;
	FootballTeam* addTeam(string name);
public:
	FootballLeague();
	void setName(string name);
	string getName();
	void printStats(bool debugPrint);
	FootballTeam* getTeam(string name);
	vector<FootballGame*>* getGames(int startRound, int lastRoundFromEnd);
	void addGame(FootballGame* game);
	void debugPrint();
	virtual ~FootballLeague();
};

#endif /* MODEL_LEAGUE_H_ */
