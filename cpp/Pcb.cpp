/*
 * Pcb.cpp
 *
 *  Created on: Apr 10, 2020
 *      Author: OS1
 */

#include "Pcb.h"
#include <dos.h>
#include <stdlib.h>
#include <iostream.h>
#include "System.h"



PCB::PCB(Thread* myT,StackSize stackSize,LongTime timeSlice) {
	lo;
	ck();
	checkStackSize(stackSize);
	initPCB(myT,timeSlice);
	unlock();
}

void PCB::initPCB(Thread* T,LongTime time){
	this->myThread=T;
	this->state = PCB::NEW;
	this->pcbSP=0;
	this->pcbTimeSlice=time;
	this->returnValue=0;
	this->timePassedCounter = 0.;
	this->wq = new Queue();
}

void PCB::checkStackSize(StackSize s){
	if(s > 65535) this->pcbStackSize = 65535;
		else this->pcbStackSize = s;
}

PCB::~PCB() {
	// TODO Auto-generated destructor stub
	lo;
	ck()
	delete wq;
	delete pcbSP;
	unlock()
}


//12 registara po 2b cini pocetni kontekst
//slicno kao na labu na C-u
//nebitno je sta cini tih 12 registara

// to su:
// prvo psw,pc koji se sastoji od: code segmenta cs i instruction pointera ip
// i onda ide ax,bx,cx,dx.... 9 registara opste namene
// nas samo prva 3 zanimaju
// alociram stek i posto je vel u bajtovima a svi su dvobajtni onda zato delim sa 2
// 2 je sizeof(unsigned int)
// stek raste na dole i na posl zauzetu pokazuje
// na dno idu flags i bitno je da bit i bude setovan da bi poceo u unlocokovanom modu da se kreira nit
// u dokumentaciji je 9 flag i zapravo
// seg i off su cs i ip
// ide adr wrappera i za jos 9 reg se ssamo jos ostavi prostor i n-12 je posl zauzeta
// ove ostale ostavim prazne i pareko njih ce se pisati kasije kad se bude cuvao konteskst
// wrapper sluzi da pozove polimorfno run tokom izvrsavanja
// run je virtuelan i ne mogu da zadam adresu run-a jer ce se uvek zvati run od osnovne klase koji je prazan

// a nama treba izvedene klase i onda mora da se zove uz pokazivac ili referencu i mi mu prilikom pravljenja
// niti zadajemo adresu i ona se polimorfno preko pokazivaca na nit zove run izvedene klase
// ovo je veoma bitno

// FPSEG i FPOFF su makrio i koji vraca segmentni i offsetni deo
int n;
unsigned* st1;
void PCB::createStack(){
	lo;
	ck();
	n = this->pcbStackSize/2;
	st1 = new unsigned[n];

	this->pcbSP = (unsigned *)st1;

	st1[n-1] = 0x200;
	st1[n-2] = FP_SEG(&(System::wrapper));
	st1[n-3] = FP_OFF(&(System::wrapper));

	this->sp = FP_OFF(st1+n-12);
	this->ss = FP_SEG(st1+n-12);

	unlock();

}

Thread* PCB::getMyThread(){
	return myThread;
}

int PCB::getID(){
	return getMyThread()->getId();
}

Queue* PCB::getWaitQueue(){
	return wq;
}

unsigned int PCB::getSP(){
	return sp;
}
unsigned int PCB::getSS(){
	return ss;
}
void PCB::setRetValue(int a){
	returnValue=a;
}

//void tick(){};
