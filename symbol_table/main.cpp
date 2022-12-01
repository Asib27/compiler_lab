#include<iostream>
#include<string>

using namespace std;

class Printer{
    bool _print;
    ostream &_os;
public:
    Printer(ostream &os, bool print=false)
        : _print(print), _os(os)
    {

    }

    ostream &getOutputStream(){
        return _os;
    }

    bool isPrint(){
        return _print;
    }
};

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
    int _scopeId;

    Printer *printer;
    ScopeTable* _next;

	unsigned long long _getHash(string s){
        return SDBMHash(s) % _no_of_bucket;
    }
public:
	ScopeTable(int n, int scopeId, ScopeTable *next=nullptr, Printer *printer=nullptr)
     : _no_of_bucket(n), _next(next), _scopeId(scopeId), printer(printer)
    {
		_table = new SymbolInfo*[n];
		for(int i = 0; i < n; i++) _table[i] = nullptr;

        if(printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "ScopeTable #" << _scopeId << " created" << endl;
        }
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

    int getScopeId(){
        return _scopeId;
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

        if(printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "ScopeTable# " << _scopeId << " removed" << endl;
        }
	}

    friend ostream& operator<<(ostream &os, const ScopeTable &s){
        os << "ScopeTable# " << s._scopeId << endl;
        for(int i = 0; i < s._no_of_bucket; i++){
            os << i << " --> ";
            auto head = s._table[i];
            for(head = s._table[i];head != nullptr; head = head->getNext()){
                os <<*head << (head->getNext() == nullptr? "" : " ");
            }
            
            os << endl;
        }

        return os;
    }
};


class SymbolTable{
    ScopeTable* _curScope; 
    int _bucket_size;

    int nextScopeId;
    Printer *printer;
public:
    SymbolTable(int bucket_size, Printer *printer=nullptr)
        : _bucket_size(bucket_size), _curScope(nullptr), nextScopeId(1)
          , printer(printer)
        {
            
        }

    void enterScope(){
        auto s =  new ScopeTable(_bucket_size, nextScopeId++, _curScope, printer);
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
            cout << *head ;
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
    string msg;
public:
    SymbolTableDriver(SymbolTable * s)
        : s(s) {}


    /* returns is there any remaining input in the line*/
    bool inputString(istream &is, string &p1, string &p2, string &p3){
        is >> p1;

        if (is.peek() != EOF && is.peek() != '\n' ){
            is >> p2;
        }
        if (is.peek() != EOF && is.peek() != '\n' ){
            is >> p3;
        }

        if(is.peek() != EOF && is.peek() != '\n'){
            return true;
        }
        return false;
    }

    bool isNoArgumentValid(string param1, string param2, string param3){
        if(param1 == "I"){
            if(param2 == "" || param3 == "")
               return false;
        }

        else if(param1 == "L" || param1 == "D" || param1 == "P"){
            if(param2 == "" || param3 != "")
                return false;
        }

        else if(param1 == "S" || param1 == "E" || param1 == "Q"){
            if(param2 != "" || param3 != "")
                return false;
        }

        return true;
    }

    void run(istream &is, ostream &os){
        s->enterScope();
        string param1, param2, param3;

        while(true){
            param1 = param2 = param3 = "";
            bool remaining = inputString(is, param1, param2, param3);

            os << param1 << "/" << param2 << "/" << param3 << "/" << endl;
            if(remaining){
                os << "Number of parameters mismatch for the command " << param1 << endl;
                continue;
            }
            
            if(!isNoArgumentValid(param1, param2, param3)){
                os << "Number of parameters mismatch for the command " << param1 << endl;
                continue;
            }

            // checking invalid command existance
            if(param1 != "I" && param1 != "L" && param1 != "D" && param1 != "P" 
                && param1 != "S" && param1 != "E"  && param1 != "Q"
            ){
                os << "Invalid Command" << endl;
                continue;
            }

            if(param1 == "Q") return ;
            cout << "here " << endl;
            singleStep(param1, param2, param3);
            
        }
    }

    int singleStep(string param1, string param2, string param3){
        if(param1 == "I"){
            SymbolInfo symbolInfo(param2, param3);
            auto res = s->insert(symbolInfo);

            return res;
        }
        
        if(param1 == "L"){
            auto res = s->lookup(param2);
            return res == nullptr;
        }
        else if(param1 == "D"){
            auto res = s->remove(param2);
            return res;
        }
        else if(param1 == "P"){
            if(param2 == "A") cout << *s << endl;
            else if(param2 == "C") s->printCurrentScope(cout);
            else cout << "Invalid Command";
        }

        else if(param1 == "S"){
            s->enterScope();
            return 1;
        }
        else if(param1 == "E"){
            s->exitScope();
            return 1;
        }
        else if(param1 == "Q"){
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
    Printer printer(cout, true);

    int no_of_bucket;
    cin >> no_of_bucket;
    SymbolTable s(no_of_bucket, &printer);
    SymbolTableDriver driver(&s);

    driver.run(cin, cout);
}