/*
 * List.h
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include "Pcb.h"

class PCB;

class NodeL{
public:
	NodeL* next;
	PCB* pcb;
	//int value;
	int returnValue;
	int timeToWait;

	void setPCB(PCB* p){
		pcb=p;
	}

//	void setValue(int a){
//		value=a;
//	}
	void setTimeToWait(int a){
		timeToWait=a;
	}
	void setReturnValue(int a){
		returnValue=a;
	}
	int getTimeToWait(){
		return timeToWait;
	}
	int getRetValue(){
		return returnValue;
	}
};


class List{
private:
	NodeL *head;
	int len;
public:

	List();
	virtual ~List();

	void put(NodeL* node);
	PCB* getBasicSignal();
	PCB* getElById(int id);

//	int getBasicSignal();
//	int getElById(int id);


	int size() const;
	int numOfZer();
	void printList();
	void smanjiVrSvima();
	int izbaciSveNule();

	NodeL* last();

};

#endif /* LIST_H_ */
