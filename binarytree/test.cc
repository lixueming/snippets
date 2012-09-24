// test.cc - test program

#include <iostream.h>
#include "bintree.h"

int main(void)
{
    BinTree apple;
    int size = 30;
    DataType key;
    int i;

    cout << "Enter numbers(" << size << ") : ";
    for (i = 0; i < size; i++)
    {
        cin >> key;
        apple.Insert(key);
        apple.Print();
        cout << "Min = " << apple.Minimum() << ", Max = " << apple.Maximum() << endl;
    }
    apple.Print();

    cout << "Enter search keys(10): ";
    for (i = 0; i < 10; i++)
    {
        cin >> key;
        if (!apple.Search(key))
            cout << "There is no such element with the key, " << key << endl;
    }

    cout << "Enter delete keys(10): ";
    for (i = 0; i < 10; i++)
    {
        cin >> key;
        if (apple.Delete(key))
        {
            cout << key << " is deleted. " << endl;
            apple.Print();
        }
        else
            cout << "There is no such element with the key, " << key << endl;
    }
   
    cout << "Last:" << endl; 
    apple.Print();

    return 0;
}
