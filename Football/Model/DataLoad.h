/*
 * IO.h
 *
 *  Created on: 27/01/2015
 *      Author: Adriano
 */

#ifndef UTILS_DATALOAD_H_
#define UTILS_DATALOAD_H_

#include "../includes.h"
#include "../Model/League.h"
#include "../Model/Game.h"
#include "../Utils/Utils.h"

//File processing Constants:
//Number of Fields
#define CSV_FIELDS 70
#define CSV_DATE 1
#define CSV_HOME_TEAM_NAME 2
#define CSV_AWAY_TEAM_NAME 3
#define CSV_HOME_TEAM_SCORE 4
#define CSV_AWAY_TEAM_SCORE 5
#define CSV_HOME_TEAM_ODDS_HEADER "B365H"
/*#define CSV_HOME_TEAM_ODDS 23
#define CSV_DRAW_ODDS CSV_HOME_TEAM_ODDS+1
#define CSV_AWAY_ODDS CSV_HOME_TEAM_ODDS+2*/

class DataLoad {
public:
	static map<unsigned int, FootballLeague*> analyseFolder(string dirName);
	static void readMatchesToLeague(char* filename, FootballLeague* league);
	virtual ~DataLoad();
};

#endif /* UTILS_DATALOAD_H_ */
