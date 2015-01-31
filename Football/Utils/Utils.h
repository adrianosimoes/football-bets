/*
 * utils.h
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include "../includes.h"

class Utils {
public:
	static map<string, string> configMap;
	static bool debugOn();
	static bool debugMathOn();
	static void print(string print);
	static void debugprint(string print);
	static double poisson_pmf(const double mean, const int x);
};

#endif /* UTILS_UTILS_H_ */
