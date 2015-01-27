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

void Utils::print(string print) {
	printf("%s\n", print.c_str());
}

bool Utils::debugOn() {
	return !Utils::configMap[string("debug")].compare("true");
}

//Impl. from: http://www.masaers.com/2013/10/08/Implementing-Poisson-pmf.html
double Utils::poisson_pmf(const double mean, const int value) {
	return exp(value * log(mean) - lgamma(value + 1.0) - mean);
}

