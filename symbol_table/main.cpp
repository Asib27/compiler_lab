#include<iostream>
#include<string>

using namespace std;

unsigned long long SDBMHash(string str) {
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
	SymbolInfo() : _next(nullptr) {}
	SymbolInfo(string name, string type, SymbolInfo* next=nullptr)
		: _name(name), _type(type), _next(next)
	{

	}

    SymbolInfo(SymbolInfo &s, SymbolInfo* next=nullptr)
		: _name(s._name), _type(s._type), _next(next)
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

    bool operator==(const SymbolInfo &s){
        return _name == s._name &&
                _type == s._type;
    }

    bool operator!=(const SymbolInfo &s){
        return !( *this == s);
    }

    bool operator==(const string &s){
        return _name == s;
    }

    bool operator!=(const string s){
        return !( *this == s);
    }
};

/**
* If any instance of ScopeTable is destroyed it will automatically free,
* all symbolInfo it contaims
*/
class ScopeTable
{
	SymbolInfo** _table;
	int _no_of_bucket;

    ScopeTable* _next;

	unsigned long long _getHash(string s){
        return SDBMHash(s) % _no_of_bucket;
    }
public:
	ScopeTable(int n, ScopeTable *next=nullptr)
     : _no_of_bucket(n), _next(next)
    {
		_table = new SymbolInfo*[n];
		for(int i = 0; i < n; i++) _table[i] = nullptr;
	} 

    bool insert(SymbolInfo s){
        if(lookup(s.getName()) != nullptr) return false;

        auto hash = _getHash(s.getName());
        auto sptr = new SymbolInfo(s, _table[hash]);
        _table[hash] = sptr;

        return true;
    }

    SymbolInfo* lookup(string s){
        auto hash = _getHash(s);

        for(SymbolInfo* cur = _table[hash]; cur != nullptr;cur = cur->getNext()){
            if(*cur == s) return cur;
        }

        return nullptr;
    }

    bool remove(string s){
        if(lookup(s) == nullptr) return false;

        auto hash = _getHash(s);
        auto head = _table[hash];
        
        if(*head == s){
            _table[hash] = head->getNext();
            delete head;
            return true;
        }
        else{
            auto prev = head; 
            for(head = head->getNext(); head != nullptr; prev = head, head = head->getNext()){
                if(*head == s){
                    prev->setNext(head->getNext());
                    delete head;
                    return true;
                }
            }

            return false;
        }

        return true;
    }

    void setNext(ScopeTable *next){
        _next = next;
    }
    ScopeTable* getNext(){
        return _next;
    }

	~ScopeTable(){
		for(int i = 0; i < _no_of_bucket; i++){
			for(auto head=_table[i]; head != nullptr; ){
                auto t = head->getNext();
                delete head;
                head = t;
            }
		}
		delete[] _table;
	}

    friend ostream& operator<<(ostream &os, const ScopeTable &s){
        for(int i = 0; i < s._no_of_bucket; i++){
            cout << i << " --> ";
            auto head = s._table[i];
            for(head = s._table[i];head != nullptr; head = head->getNext()){
                cout <<*head << " -> ";
            }
            
            cout << endl;
        }

        return os;
    }
};


class SymbolTable{
   ScopeTable* _curScope; 
   int _bucket_size;

public:
    SymbolTable(int bucket_size)
        : _bucket_size(bucket_size), _curScope(nullptr)
        {
            
        }

    void enterScope(){
        auto s =  new ScopeTable(_bucket_size, _curScope);
        _curScope = s;
    }

    void exitScope(){
        auto t = _curScope->getNext();
        delete _curScope;
        _curScope = t;
    }

    bool insert(SymbolInfo s){
        return _curScope->insert(s);
    }

    bool remove(string s){
        return _curScope->remove(s);
    }

    SymbolInfo* lookup(string s){
        for(auto head = _curScope; head != nullptr; head = head->getNext()){
            auto t = head->lookup(s);
            if(t != nullptr) return t;
        }

        return nullptr;
    }

    ostream& printCurrentScope(ostream &os){
        cout << *_curScope << endl;
        return os;
    }

    friend ostream& operator<<(ostream &os, const SymbolTable &s){
        for(auto head = s._curScope; head != nullptr; head = head->getNext()){
            cout << *head << endl;
        }
        return os;
    }

    ~SymbolTable(){
        for(auto head = _curScope; head != nullptr; ){
            auto t = head->getNext();
            delete head;
            head = t;
        }
    }
};

string RandomString(int len)
{
    const int ch_MAX = 26;
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    string result = "";
    for (int i = 0; i<len; i++)
        result = result + alpha[rand() % ch_MAX];

    return result;
}

class SymbolTableDriver{
    SymbolTable* s;
public:
    SymbolTableDriver(SymbolTable * s)
        : s(s) {}

    void run(){
        s->enterScope();

        
        while(true){
            int res = singleStep();
            if(res == 2) return ;
        }
    }

    int singleStep(){
        string input;
        cin >> input;

        if(input == "I"){
            string name, type;
            cin >> name >> type;

            SymbolInfo symbolInfo(name, type);
            auto res = s->insert(symbolInfo);

            return res;
        }
        
        if(input == "L"){
            string name; cin >> name;
            auto res = s->lookup(name);
            return res == nullptr;
        }
        else if(input == "D"){
            string name; cin >> name;
            auto res = s->remove(name);
            return res;
        }
        else if(input == "P"){
            string type; cin >> type;
            if(type == "A") cout << s << endl;
            else if(type == "C") s->printCurrentScope(cout);
            else cout << "Invalid Command";
        }

        else if(input == "S"){
            s->enterScope();
            return 1;
        }
        else if(input == "E"){
            s->exitScope();
            return 1;
        }
        else if(input == "Q"){
            return 2;
        }
        else{
            cout << "Invalid Command" << endl;
            return 0;
        }

        return 0;
    }
};

int main(){
    SymbolTable s(10);
    SymbolTableDriver driver(&s);

    driver.run();
}