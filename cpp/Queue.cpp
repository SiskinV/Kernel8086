/*
 * Queue.cpp
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#include <stdlib.h>
#include <iostream.h>
#include <dos.h>
#include "Queue.h"
#include "System.h"
//#include "pPCB.h"
#include "PCB.h"

//#define lock() {asm{pushf; cli;}} //zasto cli ne prepoznaje
//#define unlock() {asm{popf;}}


Queue::Queue() {

	lo;
	ck();
	head=0;
	len=0;
	unlock();
};

Queue::~Queue() {
	//lock()
	lo;
	ck();
	Node* temp = new Node;

	while(head != 0)
	{
		temp=head;
		head=head->next;
		delete temp;
		len--;
	}
	unlock();
}

int Queue::size() const{
	return len;
}

void Queue::put(PCB *pcb){
	//lock()
	lo;
	ck();
	//pomocna prom tail u koju smo ubacili vrednosti
	Node *tail = new Node;
	//tail->x=i;
	tail->pcb=pcb;
	tail->next=0;

	//ako je prazna lista samo stavi na pocetak i vezi head i tail
	if(head==0)
	{
		head=tail;

	}else{

		//napravi jos jednu pomocnu kojom ces doci do kraja liste i ubaciti vr
		Node *temp = new Node;
		temp=head;
		while(temp->next != 0)
			temp=temp->next;
		temp->next=tail;
	}
	//povecaj za 1 duzinu liste
	len++;

	unlock();
}

PCB* Queue::get(){
	if(head==0) return 0;

	//lock()
	lo;
	ck();
	//uzmi vrednost prvog elementa
	//int vel = head->x;
	PCB* vel=head->pcb;
	//napravi pomocni koji ce se brisati
	Node *temp = head;
	//prebaci prvi na sledeci
	head=head->next;
	//obrisi pomocni i smanji velicinu liste
	delete temp;
	len--;
	unlock();
	return vel;
}

int Queue::isEmpty(){
	if(size()==0)
		return 1;
	return 0;
}

Node* Queue::first(){
	return head;
}

Node* Queue:: getElemById(int i){
	if(i<0 || i>size()) return 0;

	int j=0;
	Node* temp=head;
	while(j!=i){
		temp=temp->next;
		j++;
	}
	return temp;
}

void Queue::printList(){
	//lock()
	if(size() == 0 ) cout<<"Lista je prazna unesiti prvo neke elemente"<<'\n';
	else{
	Node* temp=head;
	int help=0;
	while(help!=size()){
		cout<<temp->pcb->getID()<<" ";
		temp=temp->next;
		help++;
	}
	cout<<'\n'<<"End of list ";
	}
	//unlock()
}






