/*
 * FootballTeam.h
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_TEAM_H_
#define MODEL_TEAM_H_

#include "../includes.h"
#include "Game.h"

class FootballTeam {
protected:
	static int idCounter;
	int id;
	string name;
	vector<FootballGame*> games;
	int homeGoals,awayGoals,homeConceded,awayConceded, homeMatches,awayMatches;
public:
	FootballTeam(string name);
	string getName();
	void addGame(FootballGame* game);
	int getID();
	void debugPrint();
	double getHomeScoreRating();
	double getAwayScoreRating();
	double getHomeDefenseRating();
	double getAwayDefenseRating();
	virtual ~FootballTeam();
};

#endif /* MODEL_TEAM_H_ */
