/*
 * KernelEv.h
 *
 *  Created on: Apr 28, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "System.h"
#include "PCB.h"
#include "KerSem.h"

typedef unsigned char IVTNo;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	virtual ~KernelEv();

	void wait();
	void signal();

private:
	friend class Event;
	friend class IVTEntry;

	int val;
	KernelSem *mySemaphore;
	PCB *myPCB;
	IVTNo entry;
};

#endif /* KERNELEV_H_ */
