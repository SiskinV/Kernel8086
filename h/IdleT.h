/*
 * IdleT.h
 *
 *  Created on: Apr 15, 2020
 *      Author: OS1
 */

#ifndef IDLET_H_
#define IDLET_H_

#include "thread.h"

class Thread;

class IdleThread : public Thread {
public:
	IdleThread();
	virtual void run();
	void start();
};

#endif /* IDLET_H_ */
