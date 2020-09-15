/*
 * Thread.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "SCHEDULE.h"
#include "system.h"
#include "Queue.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>

class System;


Thread::Thread(StackSize stackSize,Time timeSlice){
	lo;
	ck();
	_id = ++id;
	myPCB = new PCB(this,stackSize,(LongTime)timeSlice);
	System::allThreads->put(myPCB);
	p=0;
	unlock();
}

Thread::~Thread() {
	//zakljucaj, zavrsi prvo sve niti koje su na cekanju i na kraju obrisi PCB
	lo;
	ck();
	p=0;
	waitToComplete();
	delete myPCB;
	unlock();
}

void Thread::start(){
	lo;
	ck();
	//pcb::ready and makeStack()
	makePcbReady();
	Scheduler::put(myPCB);
	unlock()
}


//zasto se ovde pravi pocetni kontekst?
//napravim stack ali mora i pocetni kontekst da se doda da bi ovo moglo da radi
//pocetni kontekst se pravi tako da imitira realan kontekst i on se svlaci kada nit dodje prvi put na procesor

void Thread::makePcbReady(){
	this->myPCB->state=PCB::READY;
	this->myPCB->createStack();
}

ID Thread::getId(){
	//ako ova nit nepostoji koju vracam moram da vratim 0 kao njen ID
	if(this==0) return 0;
	return _id;
}

ID Thread::getRunningId(){
	Thread *pom;
	//ovde si cast uradio proveri ovo sranje
	PCB *pom1 =(PCB*) System::running;
	pom = pom1->getMyThread();
	int PomId = pom->getId();
	return PomId;
}

Thread* Thread::getThreadById(ID id){

	int counter = 0;
	int max = System::allThreads->size();
	Node *temp = System::allThreads->first();
	//cout<<max<<"\n";
	if(id>max) return 0;

	while(counter!=max){
		if(temp->pcb->myThread->getId() == id){
			return temp->pcb->getMyThread();
		}
		counter++;
		temp = temp->next;
	}
	return 0;
}


// pod kojim uslovima ne blokiram???
// ako je zavrsilo ili dete nije pokrenuto nije mi bezbedno da se blokiram
// ne sme sam na sebi da pozove waitToComplete to je sve deadlock
// ne smem na main-u da zovem i ne smem za idle

void Thread::waitToComplete(){
	lo;
	ck();
	//nece da ceka na gotovoj ili nepokrenutoj niti
	if(threadIsOverOrNew()){unlock(); return;}
	if (myPCB == (PCB*)System::running) { unlock(); return; }
	if(isThisThread(System::starting)) {unlock();return;}
	if(isThisThread(System::idle)) {unlock();return;}

	//podesi stanje na blokirano
	threadIsOn();
	//?????????????????????????
	System::running->state = PCB::BLOCKED;
	myPCB->getWaitQueue()->put((PCB*)System::running); //prijavi running za cekanje

	//????????????????? DA LI OVDE MOZE DA SE POZOVE FJA DISPATCH

	System::dispatch();
	unlock();
}

int Thread::threadIsOverOrNew(){
	if(this->myPCB->state==PCB::OVER || this->myPCB->state==PCB::NEW)
		{
		threadIsOn();
		return 1;
		}
	return 0;
}

Thread* Thread::isThisThread(Thread* t){
	if(this==t)
		return t;
	return 0;
}

void Thread::threadIsOn(){
	p+=2;
	p--;
	if(p%2==1){
		p++;
	}else{
		p--;
	}
}


//void dispatch(){
//	lo;
//	ck();
//	System::dispatch();
//	unlock()
//}



