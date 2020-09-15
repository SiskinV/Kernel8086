/*
 * System.h
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "idleT.h"
#include "queue.h"
#include "thread.h"
#include "pcb.h"
#include "SemQueue.h";

#define lo {asm{pushf}}
#define ck(){asm{cli}}
//sranje nece da radi sa ovim ispod lock nego kad ga stavim odvojeno radi
#define lock{asm{pushf; cli;}}

#define unlock() {asm{popf}}

//class pa nesto mora da stoji kada zelim da koristim kao * ili kao & na taj objekat
class Queue;
class Thread;
class PCB;
class IdleT;

class System {
public:

	static void load();
	static void dispatch();
	static void unload();
	static volatile PCB* running;
	static SemQueue* allSem;

private:
	friend class Thread;
	friend class PCB;


	static Queue* allThreads;
	static Thread* starting;
	static IdleThread* idle;


	static volatile int dispatched;


	static void smanjujSve();

	static void interrupt(*oldRoutine)(...);
	static void interrupt timerInterrupt(...);
	static void wrapper();

};

#endif /* SYSTEM_H_ */
