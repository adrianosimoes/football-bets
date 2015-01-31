/*
 * MyApp.h
 *
 *  Created on: 17/Mar/2009
 *      Author: Adriano
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "includes.h"
#include "Model/Game.h"
#include "Utils/Utils.h"
#include "Utils/DataLoad.h"
#include "Predict/PredictLeaguePoisson.h"


void predictLeagues(map<unsigned int, FootballLeague*> leagues);



#endif /* MAIN_H_ */
