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
	double homeOdds, drawOdds, awayOdds;
	double underOdds, overOdds;
public:
	FootballGame(string date, FootballTeam* homeTeam, FootballTeam* awayTeam,
			int homeScore, int awayScore);
	void setOdds(double homeOdds, double drawOdds, double awayOdds,
			double underOdds, double overOdds);
	FootballTeam* getHomeTeam();
	FootballTeam* getAwayTeam();
	double getHomeWinOdds();
	double getDrawOdds();
	double getAwayWinOdds();
	double getUnderOdds();
	double getOverOdds();
	virtual int getHomeScore();
	virtual int getAwayScore();
	virtual bool isHomeWin();
	virtual bool isDraw();
	virtual bool isAwayWin();
	virtual bool isUnderScore();
	virtual bool isOverScore();
	virtual void debugPrint();
	virtual ~FootballGame() {
	}
	;
};

#endif /* MODEL_GAME_H_ */
