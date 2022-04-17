#include<iostream>
#include<fstream>

using namespace std;

const int MAX = 256;

class huffmanType {

    private:

        struct charNode 
        {// creating the character node within the class
            char ch;
            int weight;
            charNode* next;

        charNode()//setting default constructor
        {
            ch = '~';
            weight = 0;
            next = NULL;
        };

charNode *root, **array;

    public:
        
        huffmanType() //creating a constructor for the class
        {
            root = NULL;
            array = new charNode* [MAX]; //creates a dynamic array of pointers
            for(int i = 0; i < MAX; i++)
                    arr[i] = NULL;// sets all pointers to NULL

        }

void loadArray()
{
    ifstream inFile;
    inFile.open("input.txt");

    char myChar;
    while(true)
    {
        myChar = inFile.get();
        if (inFile.eof())
            break;

        int j = (int)myChar;
        if( !arr[j] )
        {
            arr[j] = new charNode;//create a new character node
            arr[j]->char = myChar;//add the charcter to the node
        }

        arr[j]->weight++;// add weight once a new node is assigned a character
    }
    inFile.close();//close file
}
void printArray()
{
    cout << "\tPrinting out the array\t" << endl;
    for(int i = 0; i < MAX; i++)
            if(arr[i])
                cout << arr[i]->char << \t << arr[i]->weight << endl;
}

void put(charNode* p)
{
    charNode **dp;
    dp = &root;
        while(*dp && (*dp)->weight<=p->weight)
            dp = &(*dp)->next;
            p->next = *dp;
            *dp = p;
}

void createLinkedList()
{
    for(int i = 0; i < MAX; i++)
        if(arr[i])
            put(arr[i]);
}

void printList()
{
    coout << "\tPrinting List\t" << endl;
    charNode *p;
    p = root;
    while(p)
		{
        cout << p->char << "\t" << p->weight << endl;
        p = p->next;
		}

}

};
