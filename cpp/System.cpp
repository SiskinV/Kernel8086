/*
 * System.cpp
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#include "System.h"
#include "Queue.h"
#include "PCB.h";
#include "SemQueue.h";
#include "Schedule.h";
#include<dos.h>
#include<stdlib.h>
#include "idleT.h"
#include <iostream.h>
#include "List.h"


//DODAJ UNFINISHEDTHREADS KAO OBICAN INTIGER KAD OVO PRORADI

volatile PCB* System::running=0;
Thread* System::starting = 0;
IdleThread* System::idle=0;
Queue* System::allThreads = new Queue();
SemQueue* System::allSem=new SemQueue();
void interrupt(*System::oldRoutine)(...)=0;
volatile int System::dispatched = 0;



void System::load(){
	lo;
	ck();

	//dohvata staru prekidnu rutinu onu na ulazu 8..... na ulazu 8 je sistemski brojac od hardvera
	//koji ce svakih 55ms da okida maskirajuci prekid ali mi zelimo nas kod da se zove na svkaih 55ms
	oldRoutine = getvect(0x08);
	//postavlja novu moju prekidnu rutinu na taj odredjeni ulaz
	setvect(0x08,timerInterrupt);


	//nit od maina ima sve ali ona nije nit koja se zahteva u tekstu projekta
	//nit mora da bude izvedena iz klase thread i da se pokrece sa start sto znaci da je to ova nasa starting nit
	//ima stek ima kontekst
	//fali joj objekat thread
	//prvi param velicina steka a drugi je timeSlice
	starting = new Thread(1000,1);

	starting->myPCB->state=PCB::READY;
	running=(volatile PCB*)starting->myPCB;

	idle = new IdleThread();

	idle->start();
	unlock();

}
void System::dispatch(){
	lo;
	ck();
	dispatched=1;
	timerInterrupt();
	dispatched =0;
	unlock();
}


//objasnjenje kod pcb-a
// po definiciji nit je zavrsila naakon runa
// sad moram da vidim da li ima blokiranih i sve koje su cekali na nju stavljam da su ready
// sve niti koje su cekale na ovo stavljam na ready
// mora promena konteksta jer se nikad necu vracati ovde
// puklo bi da nema dispatch
// jer krece da izvrsava wrapper na praznom steku pa bi viticasta ne moze da se vrati i onda mora da postoji dispatch da ne bi puklo
// vestaccki ulazim u wrapper i mora da se izadje
void System::wrapper(){

	running->myThread->run();
	lo;
	ck();
	running->state = PCB::OVER;
	PCB* temp;
	while(running->getWaitQueue()->size()>0){
		temp = running->getWaitQueue()->get();
		temp->state = PCB::READY;
		Scheduler::put(temp);
	}
	unlock();
	dispatch();
}

void System::unload(){
	if((PCB*)running!=starting->myPCB) return;

	lo;
	ck();
	setvect(0x08,oldRoutine);

	//pitaj za ovo zasto se prvo brise starting pa idle


		delete starting;
		delete idle;
		delete allThreads;
		delete allSem;
		unlock();
}

//mora biti u ovom formatu a ... znace da je promenljiv format funkcije i ovaj format
//zahtevaju setvect i getvect.ako se asemblerski radi ne gleda potpis i onda moze bez... ali sa set i getvect sve moraju ovako
//interrupt znaci da ce automatski pushovati kontekst i na kraju restorovati
static volatile PCB *newThread;
static volatile unsigned int tsp,tss;

void interrupt System::timerInterrupt(...){
	//ovde dodaj svim semaforima smanjiVrSvima,izbaciSveNule
	if(!dispatched){
		tick();
		(*oldRoutine)();


		if(allSem!= 0){
			//cout<<"usao u DISPATCH->allSem!=0\n"<<endl;
			System::smanjujSve();
	}
}
	//asm{cli};
	//cout<<"Drugi if\n";
	if(dispatched==0 && running->pcbTimeSlice!=0)
		running->timePassedCounter+=(LongTime) 1;
	//cout<<"Treci if\n";
	if(!dispatched && (running->timePassedCounter < running->pcbTimeSlice || running->pcbTimeSlice==0 )) return;

	dispatched=0;
	//cout<<"Cetvrti if\n";
	if(running->state==PCB::READY && running!=idle->myPCB)
		Scheduler::put((PCB*)running);

	 	 //cout<<"Uzmi iz schedulera if\n";
		newThread=Scheduler::get();
		//ako nema niti onda vracamo na idle
		if(newThread==0) {
			//cout<<"SADA RADI IDLE THREAD\n";
			newThread=idle->myPCB;
			}
		//cout<<"Uzeo iz sch i proverio idle\n";
		asm{
			mov tsp,sp
			mov tss,ss
		}
		running->sp=tsp;
		running->ss=tss;

		running = newThread;

		tsp=running->sp;
		tss=running->ss;

		asm{
			mov sp,tsp
			mov ss,tss
		}

		//nakon zamene konteksta vrati vreme koje je proslo na 0;
		running->timePassedCounter=0.;

	return;
}

void System::smanjujSve(){
	NodeS* pom =allSem->head;

	for(int i=0;i<allSem->size();i++)
	{
		int pov=0;
		pom->sem->wl->smanjiVrSvima();
		pov=pom->sem->wl->izbaciSveNule();
		pom->sem->val+=pov;
		pom=pom->next;
	}
}













