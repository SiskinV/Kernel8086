/*
 * IdleT.cpp
 *
 *  Created on: Apr 15, 2020
 *      Author: OS1
 */

#include "IdleT.h"
#include "system.h"
#include "pcb.h"
#include <iostream.h>

IdleThread::IdleThread():Thread(512,1) {
	//cout<<"Created idle thread\n";
	//new Thread(256,1);
}

// samo se vrti u krug i ceka da se pojavi neka koja je ready
void IdleThread::run(){
	//cout<<"Idle nit radi trenutno"<<"\n";
	while(1);
}


//idle nijad ne sme da se stavi u scheduler nikad i zato mora novi start da se napise
//nikad se nece sistem zavrsiti ona se rucno aktivira i deaktivira jer ce projekat zabosti jer je while(1) u runu

void IdleThread::start(){
	//idle nit se nikad ne stavlja u scheduler jer ako bi se pozvala nikad se ne bi zavrsila
	lo;
	ck();
	makePcbReady();
	unlock();
}
