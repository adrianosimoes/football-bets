/*
 * utils.h
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include "../includes.h"
#include "../Model/League.h"
#include "../Main.h"

//File processing Constants:
//Number of Fields
#define CSV_FIELDS 10
#define CSV_DATE 1
#define CSV_HOME_TEAM_NAME 2
#define CSV_AWAY_TEAM_NAME 3
#define CSV_HOME_TEAM_SCORE 4
#define CSV_AWAY_TEAM_SCORE 5

class Utils {
public:
	static map<unsigned int, FootballLeague> analyseFolder(string dirName,
			bool reverse);
	static bool debugOn();
	static void print(string print);
	static void debugprint(string print);
	static void readMatchesToLeague(char* filename, FootballLeague* league);
};

#endif /* UTILS_UTILS_H_ */
