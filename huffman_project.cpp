#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 256;

class huffType
{
	private:
		
		struct nodeType
		{
			char ch;
			int weight;
			nodeType *next, *zero, *one;
			
			nodeType()
			{
				ch = '*';
				weight = 0;
				next = zero = one = NULL;
			}
		};
		
		nodeType *root, **arr;
		
		void alt_printHuffTree(nodeType *p, int lvl)
		{
			if(p)
			{
				cout << p->ch << ' ' << p->weight << ' ' << lvl << '\n';
				alt_printHuffTree(p->zero, lvl + 1);
				alt_printHuffTree(p->one, lvl +1);
			}
		}
		void put(nodeType* p)
		{
			nodeType** dp;
			dp = &root;
			while(*dp && (*dp) ->weight <= p->weight)
			{
				dp = &(*dp)->next;
			}
			p->next = *dp;
			*dp = p;
		}
		
		bool isThere(nodeType *p, char myCh)
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
		
		huffType()
		{
			root = NULL;
			arr = new nodeType*[MAX];
			
			for(int i=0; i<MAX; i++)
			{
				arr[i] = NULL;
			}
		}
		
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
					arr[j] = new nodeType;
					arr[j]->ch = myCh;
				}
				arr[j]->weight++;
			}
			inFile.close();
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
			nodeType* p;
			p = root;
			while(p)
			{
				cout << p->ch << '\t' << p->weight << '\n';
				p = p->next;
			}
		}
		
		void buildHuffTree()
		{
			nodeType *p;
			while(root->next)
			{
				p = new nodeType;
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
		nodeType *p=root;
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

	char decode(char *s)
	{
		int i=0;
		char digit;
		
		nodeType *p=root;
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
	
		