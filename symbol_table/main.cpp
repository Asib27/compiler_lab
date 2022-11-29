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

	unsigned int _getHash(string s){
        return SDBMHash(s) % _no_of_bucket;
    }
public:
	ScopeTable(int n) : _no_of_bucket(n){
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

int main(){
    SymbolInfo s1("abc", "type"), s2("abc", "jhsad"),
                s3("ahks", "type");
    
    ScopeTable s(10);

    s.insert(s1);
    cout << s << endl;
    s.insert(s2);

    s.insert(s3);
    cout << s << endl;
    s.remove(s2.getName());
    // while(true){
    //     char a;
    //     cin >> a;
    //     if(a == 'q') break;

    //     auto str1 = RandomString(2);
    //     auto str2 = RandomString(2);
    //     s.insert(SymbolInfo(str1, str2));
    //     cout << str1 << " " << str2 << endl;
    // }
    //s.insert(s3);
    //s.insert(s2);
    cout << s << endl;
    
}