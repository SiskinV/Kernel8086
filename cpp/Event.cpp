/*
 * Event.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"
#include "System.h"

Event::Event(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	lo;
	ck();
	myImpl = new KernelEv(ivtNo);
	unlock();
}

Event::~Event() {
	// TODO Auto-generated destructor stub
	lo;
	ck();
	delete myImpl;
	unlock();
}

void Event::wait(){
	lo;
	ck();
	myImpl->wait();
	unlock();
}

void Event::signal(){
	lo;
	ck();
	myImpl->signal();
	unlock();
}
