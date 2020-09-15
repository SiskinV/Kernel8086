/*
 * List.cpp
 *
 *  Created on: Apr 25, 2020
 *      Author: OS1
 */


#include <stdlib.h>
#include <iostream.h>
#include <dos.h>

#include "List.h"
#include "System.h"
#include "schedule.h"

List::List() {
//	lo;
//	ck;
	head=0;
	len=0;
//	unlock();
}

List::~List() {
//	lo;
//	ck;
	NodeL* temp = new NodeL;

	while(head != 0)
	{
		temp=head;
		head=head->next;
		delete temp;
		len--;
	}
//	unlock();

}

int List::size()const{
	return len;
}

void List::put(NodeL* node){

//	lo;
//	ck;
	NodeL *tail = node;
	tail->next=0;


	//ako je prazna lista samo stavi na pocetak i vezi head i tail
	if(head==0)
	{
		head=tail;

	}else{

		//napravi jos jednu pomocnu kojom ces doci do kraja liste i ubaciti vr
		NodeL *temp = new NodeL;
		temp=head;
		while(temp->next != 0)
			temp=temp->next;
		temp->next=tail;
	}
	//povecaj za 1 duzinu liste
	len++;
//	unlock();

}

PCB* List::getBasicSignal(){
//	lo;
//	ck;
	if(head==0) return 0;

	//cout<<len<<"\n\n";

	//int vel=head->value;
	PCB* p = head->pcb;
	//int p = head->value;
	NodeL *temp = head;

	head=head->next;

	delete temp;
	len--;
//	unlock();
	return p;
}


int List::numOfZer(){
	int pom=0;
	NodeL* temp=head;
	while(temp!=0){
		if(temp->getTimeToWait()==0){
			pom++;
		}
		temp=temp->next;
	}
	return pom;
}

void List::printList(){
	//lock()
//	lo;
//	ck;
	if(size() == 0 ) cout<<"Lista je prazna unesiti prvo neke elemente"<<'\n';
	else{
	NodeL* temp=head;
	int help=0;
	while(help!=size()){
		cout<<temp->timeToWait<<temp->pcb->myThread->getId();
		//cout<<temp->value<<" "<<temp->timeToWait<<endl;
		temp=temp->next;
		help++;
		}
	cout<<'\n'<<"End of list "<<endl;
	}
//	unlock();
}

NodeL* List::last(){
	NodeL* temp=head;
	while(temp->next!=0){
		temp=temp->next;
	}
	return temp;
}

PCB* List::getElById(int id){
	if(id<0 || id>size()) return 0;
	//cout<<len<<"\n\n";
	NodeL* temp=new NodeL;
	PCB* pom;
	//int pom;

	if(id==0) {
		temp=head;
		head=temp->next;
		pom=temp->pcb;
		//pom=temp->value;
		temp->next=0;
		len--;
		delete temp;
		return pom;
	}else if(id==size()-1){
		temp=head;
		NodeL* pom1;
		while(temp->next!=0){
			pom1=temp;
			temp=temp->next;
		}
		pom1->next=0;
		pom = temp->pcb;
		//pom=temp->value;
		len--;
		delete temp;
		return pom;
	}else{
		int pok=0;
		NodeL* temp=head;
		NodeL* pom1=head;
		while(pok!=id-1){
			//cout<<"Usao ovde";
			pok++;
			pom1=pom1->next;
		}
		temp=pom1->next;
		//pom=temp->value;
		pom=temp->pcb;
		pom1->next=temp->next;

		len--;
		delete temp;
		return pom;
	}
}

void List::smanjiVrSvima(){
	NodeL* temp=head;
	while(temp!=0){
		temp->timeToWait--;
		temp=temp->next;
	}
}

int List::izbaciSveNule(){
	NodeL* temp=head;
	int izb=0;
	int brojIzbacenih=0;
	while(temp!=0){
		if(temp->getTimeToWait()==0){
			temp=temp->next;
			brojIzbacenih++;
			PCB* p=getElById(izb);
			p->returnValue=0;
			p->state=PCB::READY;
			//dodaj u scheduler sve koje izbacis
			Scheduler::put(p);
		}else{
			izb++;
			temp=temp->next;
		}
	}
	return brojIzbacenih;
}









