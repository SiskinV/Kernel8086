/*
 * Thread.h
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

class PCB;

typedef unsigned long StackSize;
typedef unsigned int Time;
typedef int ID;

const StackSize defaultStackSize = 4096;
const Time defaultTimeSlice = 2;
static ID id=0;


class Thread {
public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread* getThreadById(ID id);

	Thread* isThisThread(Thread* t);
	int threadIsOverOrNew();
	void threadIsOn();
	void makePcbReady();

protected:
	friend class PCB;
	friend class IdleThread;
	friend class System;

	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:

	int p;
	ID _id;
	PCB* myPCB;

};

//void dispatch();

#endif /* THREAD_H_ */
