/*
 * IVTEntry.cpp
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "System.h"
#include "KernelEv.h"
#include <dos.h>

IVTEntry* IVTEntry::IVTEN[256];

IVTEntry::IVTEntry(IVTNo ivtn,void interrupt(*newRoutine)(...)){
	// TODO Auto-generated constructor stub
	lo;
	ck();
	myKernelEv = 0;
	ivtNo=ivtn;
	IVTEN[ivtn]=this;


	oldRoutine = getvect(ivtNo);
	setvect(ivtNo,newRoutine);
	unlock();
}

IVTEntry::~IVTEntry() {
	// TODO Auto-generated destructor stub
	lo;
	ck();
	oldRoutine();
	setvect(ivtNo,oldRoutine);
	unlock();
}

void IVTEntry::signal(){
	if(myKernelEv!=0){
		myKernelEv->signal();
	}

}

