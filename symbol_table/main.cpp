#include<iostream>
#include<string>

using namespace std;

unsigned int SDBMHash(string str) {
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
};

class SymbolInfo
{
	string _name;
	string _type;
	SymbolInfo* _next;
public:
	SymbolInfo() : _next(nullptr) {};
	SymbolInfo(string name, string type, SymbolInfo* next=nullptr)
		: _name(name), _type(type), _next(next)
	{

	}

	string getName(){ return _name;}
	string getType(){ return _type;}
	SymbolInfo* getNext(){ return _next;}
	void setName(string name){ _name = name;}
	void setType(string type){ _type = type;} 
	void setNext(SymbolInfo* next){
		_next = next;
	}

    friend ostream& operator<<(ostream &os, SymbolInfo s){
        os << "<" << s._name << "," << s._type << ">";

        return os;
    }
};

/**
* If any instance of ScopeTable is destroyed it will automatically free,
* all symbolInfo it contaims
*/
// class ScopeTable
// {
// 	SymbolInfo* _table;
// 	int _no_of_bucket;

	
// public:
// 	ScopeTable(int n) : _no_of_bucket(n){
// 		table = new SymbolInfo[n];
// 		for(int i = 0; i < n; i++) table[i] = nullptr;
// 	}

// 	~ScopeTable(){
// 		for(int i = 0; i < _no_of_bucket; i++){
// 			if(table[i]) delete table[i];
// 		}
// 		delete[] table;
// 	}
// }

int main(){
    SymbolInfo s1("10", "int");
    SymbolInfo s3("15", "float");

    s3.setNext(&s1);
    cout << s3 << " " << *s3.getNext();
}