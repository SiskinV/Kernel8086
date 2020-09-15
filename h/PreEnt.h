/*
 * PreEnt.h
 *
 *  Created on: Apr 29, 2020
 *      Author: OS1
 */

#ifndef PREENT_H_
#define PREENT_H_

#include "IVTEntry.h"
#include "System.h"

#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...); \
IVTEntry ent##ivtno(ivtno,routine##ivtno); \
void interrupt routine##ivtno(...) { \
	ent##ivtno.signal(); \
	if (old) ent##ivtno.oldRoutine(); \
	System::dispatch(); \
}\


#endif /* PREENT_H_ */
