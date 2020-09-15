/*
 * KerSemKerSemQueue.cpp
 *
 *  Created on: Apr 26, 2020
 *      Author: OS1
 */

#include <stdlib.h>
#include <iostream.h>
#include <dos.h>


#include "System.h"
#include "SemQueue.h"
#include "KerSem.h"


SemQueue::SemQueue() {

	head=0;
	len=0;
	//cout<<"USAO U KONSTRUKTOR ZA QUEUE"<<endl;

};

SemQueue::~SemQueue() {
	//lock()
	lo;
	ck();
	NodeS* temp = new NodeS;

	while(head != 0)
	{
		temp=head;
		head=head->next;
		delete temp;
		len--;
	}
	unlock();
}

int SemQueue::size() const{
	//cout<<"size:"<<endl;
	return len;

}

KernelSem* SemQueue::getSem(){
	return this->head->sem;
}

void SemQueue::put(KernelSem *s){
	//lock()
	lo;
	ck();
	//pomocna prom tail u koju smo ubacili vrednosti
	NodeS *tail = new NodeS;
	//tail->x=i;
	tail->sem=s;
	tail->next=0;

	//ako je prazna lista samo stavi na pocetak i vezi head i tail
	if(head==0)
	{
		head=tail;

	}else{

		//napravi jos jednu pomocnu kojom ces doci do kraja liste i ubaciti vr
		NodeS *temp = new NodeS;
		temp=head;
		while(temp->next != 0)
			temp=temp->next;
		temp->next=tail;
	}
	//povecaj za 1 duzinu liste
	len++;

	unlock()
}

KernelSem* SemQueue::get(){
	if(head==0) return 0;

	//lock()
	lo;
	ck();
	//uzmi vrednost prvog elementa
	//int vel = head->x;
	KernelSem* vel=head->sem;
	//napravi pomocni koji ce se brisati
	NodeS *temp = head;
	//prebaci prvi na sledeci
	head=head->next;
	//obrisi pomocni i smanji velicinu liste
	delete temp;
	len--;
	unlock();
	return vel;
}

int SemQueue::isEmpty(){
	if(size()==0)
		return 1;
	return 0;
}

NodeS* SemQueue::first(){
	if(size()==0){
		return 0;
	}
	return head;
}


void SemQueue::printList(){
	//lock()
	if(size() == 0 ) cout<<"Lista je prazna unesiti prvo neke elemente"<<'\n';
	else{
	NodeS* temp=head;
	int help=0;
	while(help!=size()){
		cout<<temp->sem->value()<<endl;
		temp=temp->next;
		help++;
	}
	cout<<'\n'<<"End of list ";
	}
	//unlock()
}

KernelSem* SemQueue::getElemById(int id){
	if(id<0 || id>size()) return 0;
	NodeS* temp=new NodeS;
	KernelSem* pom;


	if(id==0) {
		temp=head;
		head=temp->next;
		pom=temp->sem;
		//pom=temp->value;
		temp->next=0;
		len--;
		delete temp;
		return pom;
	}else if(id==size()-1){
		temp=head;
		NodeS* pom1;
		while(temp->next!=0){
			pom1=temp;
			temp=temp->next;
		}
		pom1->next=0;
		pom = temp->sem;
		//pom=temp->value;
		len--;
		delete temp;
		return pom;
	}else{
		int pok=0;
		NodeS* temp=head;
		NodeS* pom1=head;
		while(pok!=id-1){
			//cout<<"Usao ovde";
			pok++;
			pom1=pom1->next;
		}
		temp=pom1->next;
		//pom=temp->value;
		pom=temp->sem;
		pom1->next=temp->next;

		len--;
		delete temp;
		return pom;
	}
}



