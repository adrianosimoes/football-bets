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


class Utils {
public:
	static map<unsigned int, FootballLeague> analyseFolder(string dirName,
			bool reverse);
	static bool debugOn();
	static void print(string print);
	static void debugprint(string print);
	static double poisson_pmf(const double mean, const int x);
};

#endif /* UTILS_UTILS_H_ */
