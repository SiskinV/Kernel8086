#include "system.h"

//void main()
//{
//	Queue* mojRed = new Queue();


//	for(int i =0; i<5;i++)
//	{
//
//		int x;
//		cout<<"Unesite vrednost x: ";
//		cin>>x;
//		cout<<"\n";
//		pPCB* pomocni = new pPCB(x);
//		mojRed->put(pomocni);
//		mojRed->printList();
//		int vel = mojRed->size();
//		cout<<vel<<'\n';
//	}
//
//	pPCB* pom = mojRed->get();
//	int x1 = pom->getX();
//	cout<<x1<<"\n";
//	mojRed->printList();
	//mojRed->printList();
//	pPCB *pcb1 = mojRed->get();
//
//	int x2 =mojRed->get();
//	int vel = mojRed->size();
//	cout<<vel<<'\n';
//	mojRed->printList();
//	int x3 =mojRed->get();
//	int x4=mojRed->get();

//	mojRed->~Queue();
//	mojRed->printList();


	//cout<<x1<<' '<<x2<<' '<<x3<<' '<<x4;
//}
extern int userMain(int argc,char* argv[]);

int main(int argc,char* argv[]){
	System::load();
	int value = userMain(argc,argv);
	System::unload();
	return value;
}
