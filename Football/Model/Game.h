/*
 * Game.h
 *
 *  Created on: 25/01/2015
 *      Author: Adriano
 */

#ifndef MODEL_GAME_H_
#define MODEL_GAME_H_

#include "../includes.h"
class FootballTeam;

class FootballGame {
protected:
	string date;
	FootballTeam* homeTeam, *awayTeam;
	int homeScore, awayScore;
public:
	FootballGame();
	FootballGame(string date, FootballTeam* homeTeam, FootballTeam* awayTeam,
			int homeScore, int awayScore);
	FootballTeam* getHomeTeam();
	FootballTeam* getAwayTeam();
	virtual int getHomeScore();
	virtual int getAwayScore();
	virtual bool isHomeWin();
	virtual bool isDraw();
	virtual bool isAwayWin();
	virtual void debugPrint();
	virtual ~FootballGame() {
	}
	;
};

#endif /* MODEL_GAME_H_ */
