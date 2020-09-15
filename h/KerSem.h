/*
 * KerSem.h
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

class Queue;
class List;
class System;

typedef unsigned int Time;

class KernelSem {
public:

	KernelSem(int init);
	virtual ~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n);
	int value();
	int getId();

	static int idSem;

	Queue *wq;
	List *wl;

private:

	friend class PCB;
	friend class Sem;
	friend class Thread;
	friend class System;

	int id;
	int val;

};

#endif /* KERSEM_H_ */
