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
#include "Predict/PredictLeague.h"
#include "Utils/Utils.h"
#include "Model/DataLoad.h"
#include "Predict/RatingCalculator.h"
#include "Predict/HDAStrategy.h"


void predictLeagues(map<unsigned int, FootballLeague*> leagues);



#endif /* MAIN_H_ */
