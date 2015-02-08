/*
 * BackTrack.h
 *
 *  Created on: 08/02/2015
 *      Author: Adriano
 */

#ifndef PREDICT_BACKTRACK_H_
#define PREDICT_BACKTRACK_H_

#include "HDAStrategy.h"

class BackTrack {
protected:
	Strategy* strategy;
public:
	BackTrack(Strategy* strategy);
	void run();
	virtual ~BackTrack();
};

#endif /* PREDICT_BACKTRACK_H_ */
