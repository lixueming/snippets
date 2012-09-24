#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include "fibheap.h"

int main(void)
{

int slnum;
int RandomTest(void);
int UserInput(void);
int sig(void);

sig();

cin >> slnum;


while (slnum != 3)  {    // While start
 
switch (slnum) {  // switch start
   case  1:
              RandomTest();  
              break; 

   case 2:  
              UserInput();
              break;
 
   default:
              cout << "Wrong Number.    Input the number\n" ;
 

}  // switch end

sig();

cin >> slnum;

}  // while end
return 0;
}  // main end


int UserInput(void) {

    int i,j;
    int A[15] = { 54,39,692,93,75,38,69,437,957,37,73,94,298,836,274};
    int B[15] = { 839,594,503,384,31,40,384,924,359,90,23,143,36,742,384};
    FHNode  *A1[15];
    FHNode  *B1[15];
    FHNode *pNode;
    FibHeap   Aheap;
    FibHeap   *Bheap = new FibHeap; 

for (i = 0; i < 15 ; i++)      {
        pNode = new FHNode(A[i]);
        A1[i] = pNode;
        Aheap.Insert(pNode);   
      }
for (j = 0 ; j < 15 ; j++)        {
        pNode = new FHNode(B[j]);
        B1[j] = pNode;       
        Bheap->Insert(pNode);
    }

pNode  =  Aheap.ExtractMin();
cout << "Aheap minimum " <<*pNode << endl<< "\n";

pNode = Bheap->ExtractMin();
cout << "Bheap minimum " <<*pNode << endl<<"\n";

Aheap.Union(Bheap);
pNode = Aheap.ExtractMin();
cout << "Union Aheap minimum "<<*pNode << endl<<"\n";


Aheap.DecreaseKey(A1[14],10);
pNode = Aheap.Minimum();
cout << *pNode << endl<< "\n";

pNode = new FHNode(3);
Aheap.Insert(pNode);
pNode=Aheap.Minimum();
cout << *pNode << endl;

if (Aheap.Delete(A1[14])) {
    while ((pNode = Aheap.ExtractMin()) != NULL)
        cout << *pNode << endl;
      }
         else cout << "Delete failed..." << endl;
   

pNode = Aheap.Minimum();
if (pNode != NULL)
cout << "\n" << *pNode << endl;
else  cout << "Aheap is empty" << endl;

pNode = new FHNode(3);
Aheap.Insert(pNode);
pNode=Aheap.Minimum();
cout << *pNode << endl;


return 0; 
}



int RandomTest(void)   {   // RandomTest start

FHNode *pNode;
FibHeap fheap;
int i;
time_t t;
	srand(time(&t));

	for (i = 0; i < 30; i++)
	{
		pNode = new FHNode(rand() % 10000);
		fheap.Insert(pNode);
	}

	pNode = fheap.ExtractMin();

	cout << "------------------------------------------------" << endl;

	

      while ((pNode = fheap.ExtractMin()) != NULL) 
		cout << *pNode << endl;
	cout << endl;
        return 0;

}  //Random test end

int sig(void) 
{                                  //sig start
cout << "*********************************************\n";
cout << "         FIBONACCI HEAP PROGRAM\n";
cout << "*********************************************\n\n";
cout << "  @ TEST PROGRAM @\n";
cout << "      1 . Random test ( input data ) \n";
cout << "      2 . User data input test \n";
cout << "      3 . Exit\n\n"; 
cout << "        Select test program :  ";  
return 0;
}  // sig end
