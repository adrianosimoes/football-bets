/*
 * utils.cpp
 *
 *  Created on: 26/01/2015
 *      Author: Adriano
 */

#include "Utils.h"
using namespace std;

map<string, string> Utils::configMap = map<string, string>();

void Utils::debugprint(string print) {
	if (!Utils::configMap[string("debug")].compare("true")) {
		printf("%s\n", print.c_str());
	}
}

double Utils::getPercFromDecOdds(double decimalOdds) {
	return 100 / decimalOdds;
}

void Utils::print(string print) {
	printf("%s\n", print.c_str());
}

bool Utils::debugOn() {
	return !Utils::configMap[string("debug")].compare("true");
}

bool Utils::debugMathOn() {
	return !Utils::configMap[string("debugMath")].compare("true");
}

