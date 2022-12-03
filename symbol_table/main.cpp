#include<iostream>
#include<string>
#include<sstream>

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
	unsigned long long hash = 0;
	unsigned long long i = 0;
	unsigned long long len = str.length();

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

    void printHelper(string s, int pos1, int pos2){
        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "'" << s << "'" << " found in ScopeTable# " << _scopeId
                << " at position " << pos1 << ", " << pos2 << endl;

        }        
    }

    void printDeleteHelper(string s, int pos1, int pos2){
        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "Deleted '" << s << "' from ScopeTable# " << _scopeId
                << " at position " << pos1 << ", " << pos2 << endl;
        }
    }

    void printInsertHelper(int pos1, int pos2){
        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "Inserted in ScopeTable# " << _scopeId << " at position "
                << pos1 << ", " << pos2 << endl;
        }
    }

    void printInsertHelper(string s){
        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "'" << s << "'" << " already exists in the current ScopeTable" << endl;
        }
    }

    void printHelper(string s){
        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << s << endl;
        }
    }
public:
	ScopeTable(int n, int scopeId, ScopeTable *next=nullptr, Printer *printer=nullptr)
     : _no_of_bucket(n), _next(next), _scopeId(scopeId), printer(printer)
    {
		_table = new SymbolInfo*[n];
		for(int i = 0; i < n; i++) _table[i] = nullptr;

        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "ScopeTable# " << _scopeId << " created" << endl;
        }
	} 

    bool insert(SymbolInfo s){
        auto hash = _getHash(s.getName());

        if(_table[hash] == nullptr){
            auto sptr = new SymbolInfo(s, _table[hash]);
            _table[hash] = sptr;
            printInsertHelper(hash+1, 1);
        }
        else{
            auto toInsertAt = _table[hash];
            int i = 1;
            for(auto head = _table[hash]; head != nullptr; head = head->getNext(), i++){
                if(*head == s.getName()){
                    printInsertHelper(s.getName());
                    return false;
                }
                toInsertAt = head;
            }

            auto sptr = new SymbolInfo(s);
            toInsertAt->setNext(sptr);
            printInsertHelper(hash+1, i);
        }

        return true;
    }

    SymbolInfo* lookup(string s){
        auto hash = _getHash(s);

        int i = 1;
        for(SymbolInfo* cur = _table[hash]; cur != nullptr;cur = cur->getNext(), i++){
            if(*cur == s) {
                printHelper(s, hash+1, i);
                return cur;
            }
        }

        return nullptr;
    }

    bool remove(string s){
        auto hash = _getHash(s);
        auto head = _table[hash];
        
        if(head == nullptr){
            printHelper("Not found in the current ScopeTable");
            return false;
        }

        if(*head == s){
            _table[hash] = head->getNext();
            delete head;
            printDeleteHelper(s, hash+1, 1);

            return true;
        }
        else{
            auto prev = head; 
            int i = 2;
            for(head = head->getNext(); head != nullptr; prev = head, head = head->getNext(), i++){
                if(*head == s){
                    prev->setNext(head->getNext());
                    delete head;
                    printDeleteHelper(s, hash+1, i);
                    return true;
                }
            }
        }

        printHelper("Not found in the current ScopeTable");
        return false;
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

        if(printer != nullptr && printer->isPrint()){
            auto &os = printer->getOutputStream() ;
            os << "\t";
            os << "ScopeTable# " << _scopeId << " removed" << endl;
        }
	}

    friend ostream& operator<<(ostream &os, const ScopeTable &s){
        os << "\t";
        os << "ScopeTable# " << s._scopeId << endl;
        for(int i = 0; i < s._no_of_bucket; i++){
            os << "\t";
            os << i+1 << "--> ";
            auto head = s._table[i];
            for(head = s._table[i];head != nullptr; head = head->getNext()){
                os <<*head << " "; //(head->getNext() == nullptr? "" : " ");
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
            enterScope();
        }

    void enterScope(){
        auto s =  new ScopeTable(_bucket_size, nextScopeId++, _curScope, printer);
        _curScope = s;
    }

    void exitScope(){
        auto t = _curScope->getNext();
        if(t == nullptr){
            if(printer != nullptr && printer->isPrint()){
                auto &os = printer->getOutputStream();
                os << "\t";
	            os << "ScopeTable# " << _curScope->getScopeId() <<" cannot be removed" << endl;
            }
            return ;
        }
                                          
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

        if(printer->isPrint()){
            auto &os = printer->getOutputStream();
            os << "\t";
            os << "'" << s << "'" << " not found in any of the ScopeTables" << endl;
        }
        return nullptr;
    }

    ostream& printCurrentScope(ostream &os){
        cout << *_curScope;
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
        string line;
        getline(is, line);

        stringstream ss(line);
        ss >> p1;
        if(!(ss >> p2)){
            return false;
        }
        if(!(ss >> p3)){
            return false;
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
        string param1, param2, param3;

        for(int i = 1; ; i++){
            param1 = param2 = param3 = "";
            bool remaining = inputString(is, param1, param2, param3);

            //os << param1 << "/" << param2 << "/" << param3 << "/" << endl;
            os << "Cmd " << i << ": " << param1 
                << (param2==""?"":" ") << param2 
                << (param3==""?"":" ") << param3 << endl;

            if(remaining){
                os << "\t";
                os << "Number of parameters mismatch for the command " << param1 << endl;
                continue;
            }
            
            if(!isNoArgumentValid(param1, param2, param3)){
                os << "\t";
                os << "Number of parameters mismatch for the command " << param1 << endl;
                continue;
            }

            // checking invalid command existance
            if(param1 != "I" && param1 != "L" && param1 != "D" && param1 != "P" 
                && param1 != "S" && param1 != "E"  && param1 != "Q"
            ){
                os << "\t";
                os << "Invalid Command" << endl;
                continue;
            }

            if(param1 == "P" && (param2 != "C" && param2 != "A")){
                os << "\t";
                os << "Invalid Command" << endl;
                continue;
            }

            if(param1 == "Q") return ;
            // cout << "here " << endl;
            singleStep(param1, param2, param3, os);
            
        }
    }

    int singleStep(string param1, string param2, string param3, ostream &os){
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
            if(param2 == "A") os << *s;
            else if(param2 == "C") s->printCurrentScope(os);
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

        return 0;
    }
};

int main(){
    Printer printer(cout, true);

    int no_of_bucket;
    cin >> no_of_bucket;
    cin.ignore(100, '\n');
    SymbolTable s(no_of_bucket, &printer);
    SymbolTableDriver driver(&s);

    driver.run(cin, cout);
}