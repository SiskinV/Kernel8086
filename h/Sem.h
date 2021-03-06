/*
 * Sem.h
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#ifndef SEM_H_
#define SEM_H_

typedef unsigned int Time;

class KernelSem;

class Semaphore {
public:
	 Semaphore (int init=1);
	 virtual ~Semaphore ();

	 virtual int wait (Time maxTimeToWait);
	 virtual int signal(int n=0);

	 int val () const; // Returns the current value of the semaphore

private:
 KernelSem* myImpl;
};
#endif /* SEM_H_ */
