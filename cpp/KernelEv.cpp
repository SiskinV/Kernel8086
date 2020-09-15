/*
 * KernelEv.cpp
 *
 *  Created on: Apr 28, 2020
 *      Author: OS1
 */
#include "KernelEv.h"
#include "System.h"
#include "Schedule.h"
#include "IVTEntry.h"
#include "KerSem.h"

KernelEv::KernelEv(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	lo;
	ck();
	entry=ivtNo;
	//val=0;
	mySemaphore = new KernelSem(0);
	if(IVTEntry::IVTEN[entry]!=0){
		myPCB=(PCB*)System::running;
		IVTEntry::IVTEN[entry]->myKernelEv=this;
	}
	unlock();
}

KernelEv::~KernelEv() {
	lo;
	ck();
	// TODO Auto-generated destructor stub
	if(IVTEntry::IVTEN[entry]!=0){
		IVTEntry::IVTEN[entry]->myKernelEv=0;
	}
	delete mySemaphore;
	unlock();
}



//ovde vidi za taj lock i unlock da li moze ovako da se radi
void KernelEv::signal(){
	lo;
	ck();
	if (mySemaphore->value()==1) {
		unlock();
		return;
	}
	mySemaphore->signal(0);
	/*if(val==-1){
		val=0;
		myPCB->state=PCB::READY;
		Scheduler::put(myPCB);
	}*/
	unlock();
}

void KernelEv::wait(){
	lo;
	ck();
	if(System::running==myPCB)
		mySemaphore->wait(0);
	/*	if(val==0){
			val=-1;
			myPCB->state=PCB::BLOCKED;
			unlock();
			System::dispatch();
		}else{
			unlock();
			return;
		}*/
	unlock();
	return;

}










