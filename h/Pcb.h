/*
 * Pcb.h
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "queue.h"

typedef unsigned int LongTime;

class Thread;
class Queue;

class PCB {
public:

	PCB(Thread *myT,StackSize stackSize,LongTime timeSlice);
	~PCB();

	Thread *myThread;

	enum stanje {NEW=0,READY,BLOCKED,OVER};
	volatile stanje state;

	//brojacka promenljiva oja nam govori koliko je vremeena proslo
	volatile LongTime timePassedCounter;
	LongTime pcbTimeSlice;

	StackSize pcbStackSize;

	unsigned* pcbSP;

	//stack segment i stack offset ss:sp
	unsigned int sp,ss;

	int returnValue;

	void createStack();
	Thread* getMyThread();
	int getID();
	void initPCB(Thread* T,LongTime time);
	void checkStackSize(StackSize s);
	unsigned int getSP();
	unsigned int getSS();
	Queue* getWaitQueue();
	void setRetValue(int a);

private:
	//red niti koje cekaju na ovu
	Queue* wq;

};

extern void tick();

#endif /* PCB_H_ */
