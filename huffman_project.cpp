//Edwin Smith: EdwinSmith@my.unt.edu
//Varun Gelli: VarunGelli@my.unt.edu
//Hector Barrios: hectorbarrios@my.unt.edu
#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 256;

class huffType
{
	private:
		
	// creating the character node within the class
		struct charNode 
		{
			char ch;
			int weight;
			charNode *next, *zero, *one;
			
			//setting default constructor
			charNode()
			{
				ch = '*';
				weight = 0;
				next = zero = one = NULL;
			}
		};
		
		charNode *root, **arr;
		
		void alt_printHuffTree(charNode *p, int lvl)
		{
			if(p)
			{
				cout << p->ch << ' ' << p->weight << ' ' << lvl << '\n';
				alt_printHuffTree(p->zero, lvl + 1);
				alt_printHuffTree(p->one, lvl +1);
			}
		}
	
	        // insert node while preserving priority 
		void put(charNode* p)
		{
			charNode** dp;
			dp = &root;
			while(*dp && (*dp) ->weight <= p->weight)
			{
				dp = &(*dp)->next;
			}
			p->next = *dp;
			*dp = p;
		}
		
	        //set *p to myCh
		bool isThere(charNode *p, char myCh)
		{
			if(!p)
			{
				return false;
			}
			else
			{
				if(p->ch == myCh)
				{
					return true;
				}
				else
				{
					return isThere(p->zero, myCh) || isThere(p->one, myCh);
				}
			}
		}
		
	public:
		//creating a constructor for the class
		huffType()
		{
			root = NULL;
			arr = new charNode*[MAX];
			
			for(int i=0; i<MAX; i++)
			{
				arr[i] = NULL;
			}
		}
		
                //read input file and store in array of structs
		void loadArray()
		{
			ifstream inFile;
			inFile.open("input.txt");
			
			char myCh;
			while(true)
			{
				myCh = inFile.get();
				if(inFile.eof())
				{
					break;
				}
				cout.put(myCh);
				int j = (int)myCh;
				if(!arr[j])
				{
					arr[j] = new charNode; //create a new character node
					arr[j]->ch = myCh; //add the charcter to the node
				}
				arr[j]->weight++; // add weight once a new node is assigned a character
			}
			inFile.close(); //close file
			cout.put('\n');
		}
		
		void printArray()
		{
			cout << "\nPrint The array:\n";
			for(int i=0; i<MAX; i++)
			{
				if(arr[i])
				{
					cout << arr[i]->ch << '\t' << arr[i]->weight << '\n';
				}
			}
		}
		
		void buildLinkedList()
		{
			for(int i=0; i<MAX; i++)
			{
				if(arr[i])
				{
					put(arr[i]);
				}
			}
		}
		
		void printLinkedList()
		{
			cout << "\n\nPrint the linked list: \n";
			charNode* p;
			p = root;
			while(p)
			{
				cout << p->ch << '\t' << p->weight << '\n';
				p = p->next;
			}
		}
		
		void buildHuffTree()
		{
			charNode *p;
			while(root->next)
			{
				p = new charNode;
				p->zero = root;
				p->one = root->next;
				p->weight = p->zero->weight + p->one->weight;
				root = root->next->next;
				put(p);
			}
		}
		
		void printHuffTree()
		{
			cout << "\n\nPrint the Huffman Tree:\n";
			alt_printHuffTree(root, 0);
		}
	void encode(char ch)
	{
		charNode *p=root;
		while(p->zero)
		{
			if(isThere(p->zero, ch))
			{
				cout.put('0');
				p=p->zero;
			}
			else
			{
				cout.put('1');
				p=p->one;
			}
		}
		cout << "\n\nDone\n\n";
	}
	
	//printEncoding code???
	
	/*
	void printEncoding(char ch){
		cout << ch << "     " << myHuffman.encode(ch) << endl;
	}
	*/

	char decode(char *s)
	{
		int i=0;
		char digit;
		
		charNode *p=root;
		while(p->zero)
		{
			digit = s[i++];
			cout.put(digit);
			
			if(digit == '0')
			{
				p=p->zero;
			}
			else
			{
				p=p->one;
			}
		}
		cout.put('\t');
		return p->ch;
	}
};


int main()
{
	huffType myHuffman; 
	
	myHuffman.loadArray();
	myHuffman.printArray(); 
	
	myHuffman.buildLinkedList();
	myHuffman.printLinkedList();
	
	myHuffman.buildHuffTree();
	myHuffman.printHuffTree();
	
	char ch;
	while(true)
	{
		cout << "\n\nInput Character: ";
		cin >> ch;
		if(ch == '~')
		{
			break;
		}
		cout << "\n\n";
		myHuffman.encode(ch);
		//myHuffman.printEncoding(ch);
	}
	
	char* s;
	s = new char[8];
	
	while(true)
	{
		cin.ignore(255, '\n');
		cout << "Enter string to decode: ";
		cin.getline(s,8);
		if(!s[0])
		{
			break;
		}
		cout << myHuffman.decode(s) << "\n\n";
	}
	
	return 0;
}
	
		
