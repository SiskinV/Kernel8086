/*
 * KerSemQueue.h
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#ifndef KerSemQUEUE_H_
#define KerSemQUEUE_H_

#include "KerSem.h";

class KerSem;

class NodeS {
public:
	NodeS* next;
	KernelSem *sem;

	NodeS(){
		next=0;
		sem=0;
	}
};

class SemQueue {
private:
	//NodeS *head;


public:

	NodeS *head;

	SemQueue();
	virtual ~SemQueue();
	int len;
	void put(KernelSem* sem);
	KernelSem* get();

	KernelSem* getSem();
	int size() const;
	int isEmpty();
	void printList();
	NodeS* first();
	KernelSem* getElemById(int i);
};
#endif /* KerSemQUEUE_H_ */
