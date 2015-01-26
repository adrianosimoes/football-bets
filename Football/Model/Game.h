/*
 * Game.h
 *
 *  Created on: 25/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_GAME_H_
#define MODEL_GAME_H_

#include "../includes.h"

class FootballGame{
protected:
	string date, homeTeam,  awayTeam;
	int  homeScore,  awayScore;
public:
	FootballGame(string date, string homeTeam, string awayTeam, int homeScore, int awayScore );
	void debugPrint();
};



#endif /* MODEL_GAME_H_ */
