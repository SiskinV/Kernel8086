/*
 * KerSem.cpp
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#include "KerSem.h"
#include "List.h"
#include "Schedule.h"
#include "System.h"
#include <iostream.h>

int KernelSem::idSem=0;

KernelSem::KernelSem(int init){
	lo;
	ck();
	val=init;
	id=++idSem;
	wq=new Queue;
	wl=new List;
	//gurni ga u niz semafora
	System::allSem->put(this);
	unlock();
}

int KernelSem::value(){
	return val;
}

//pregledaj ovaj wait jos jednom
//uradi -- i ako je val nakod dekrementa manji od 0 blokiraj me
int KernelSem::wait(Time maxTimeToWait){
	lo;
	ck();
//	Time t = maxTimeToWait;
	int povr=0;
//	if(t!=0) povr=1;

	if(--val < 0){
		System::running->state=PCB::BLOCKED;
		if(maxTimeToWait==0){
			wq->put((PCB*)System::running);
		}else{
			NodeL* pom = new NodeL;
			pom->setPCB((PCB*)System::running);
			pom->setTimeToWait(maxTimeToWait);
			wl->put(pom);
		}
		unlock();
		System::dispatch();
	}else{
		unlock();
	}


	//Treba da promenis tako da vraca tvoju vrednost
	return System::running->returnValue;
	//return 0;
}

int KernelSem::getId(){
	return id;
}


//++val i ako je >=0 unblock to
int KernelSem::signal(int n){
	lo;
	ck();
	int ret=0;
	PCB* pom;
	if(n<0) {unlock(); return n; }
	if(n==0){
			if(++val<=0){
				if(wq->size()!=0){
					pom=wq->get();
					pom->setRetValue(1);

				}else if(wl->size()!=0){
					pom=wl->getBasicSignal();
					pom->setRetValue(1);
				}
				pom->state=PCB::READY;
				Scheduler::put(pom);
				ret=1;
			}
		}else if(n>0){

			for(int i=0;i<n;i++){
				if(++val<=0){
					ret++;
					pom=wq->get();
					if(pom==0) pom=wl->getBasicSignal();
					pom->returnValue=1;
					pom->state=PCB::READY;
					Scheduler::put(pom);
				}
			}
		}
	unlock();
	//Vrati broj odblokiranih niti
	return ret;
}


//ispravi ovo majmuncino
KernelSem::~KernelSem(){
	/*PCB* pcb = wq->get();

	while(pcb != 0 ){
		pcb->state=PCB::READY;
		Scheduler::put(pcb);
		pcb = wq->get();
	}
	PCB* pcb1 = wl->getBasicSignal();
	while(pcb1 !=0 ){
		pcb1->state=PCB::READY;
		Scheduler::put(pcb);
		pcb1 = wl->getBasicSignal();
	}*/
	lo;
	ck();
	delete wq;
	delete wl;
	unlock();
}




