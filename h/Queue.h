/*
 * Queue.h
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_

class PCB;

#include "pcb.h"

class Node {
public:
	//za sad probaj sa najobicnijim int-om a posle ubaci PCB
	//int x;
	Node* next;
	PCB *pcb;
};

class Queue {
private:
	Node *head;
	int len;

public:
	Queue();
	virtual ~Queue();

	void put(PCB* pcb);
	PCB* get();

	int size() const;
	int isEmpty();
	void printList();
	Node* first();
	Node* getElemById(int i);
};

#endif /* QUEUE_H_ */
