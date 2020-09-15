/*
 * Sem.cpp
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */

#include "Sem.h"
#include "KerSem.h"
#include "System.h"

Semaphore::Semaphore(int init){
	lo;
	ck();
	myImpl = new KernelSem(init);
	unlock();
}

Semaphore::~Semaphore(){
	lo;
	ck();
	delete myImpl;
	unlock();
}

int Semaphore::signal(int n){
	int pom;
	lo;
	ck();
	pom= myImpl->signal(n);
	unlock();
	return pom;
}

int Semaphore::wait(Time MaxTimeToWait){
	int pom;
	lo;
	ck();
	pom = myImpl->wait(MaxTimeToWait);
	unlock();
	return pom;
}

int Semaphore::val()const{

	return myImpl->value();

}
