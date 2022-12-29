#include"../scopeTable.h"


unsigned long long ScopeTable::SDBMHash(std::string str) {
	unsigned long long hash = 0;
	unsigned long long i = 0;
	unsigned long long len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
};

unsigned long long ScopeTable::_getHash(std::string s){
    return SDBMHash(s) % _no_of_bucket;
}

void ScopeTable::printHelper(std::string s, int pos1, int pos2){
    if(printer != nullptr && printer->isPrint()){
        auto &os = printer->getOutputStream();
        os << "\t";
        os << "'" << s << "'" << " found in ScopeTable# " << _scopeId
            << " at position " << pos1 << ", " << pos2 << std::endl;

    }        
}

void ScopeTable::printDeleteHelper(std::string s, int pos1, int pos2){
    if(printer != nullptr && printer->isPrint()){
        auto &os = printer->getOutputStream();
        os << "\t";
        os << "Deleted '" << s << "' from ScopeTable# " << _scopeId
            << " at position " << pos1 << ", " << pos2 << std::endl;
    }
}

void ScopeTable::printInsertHelper(int pos1, int pos2){
    if(printer != nullptr && printer->isPrint()){
        auto &os = printer->getOutputStream();
        os << "\t";
        os << "Inserted in ScopeTable# " << _scopeId << " at position "
            << pos1 << ", " << pos2 << std::endl;
    }
}

void ScopeTable::printInsertHelper(std::string s){
    if(printer != nullptr && printer->isPrint()){
        auto &os = printer->getOutputStream();
        os << "\t";
        os << s << " already exists in the current ScopeTable" << std::endl;
    }
}

void ScopeTable::printHelper(std::string s){
    if(printer != nullptr && printer->isPrint()){
        auto &os = printer->getOutputStream();
        os << "\t";
        os << s << std::endl;
    }
}

ScopeTable::ScopeTable(int n, int scopeId, ScopeTable *next, Printer *printer)
    : _no_of_bucket(n), _next(next), _scopeId(scopeId), printer(printer)
{
    _table = new SymbolInfo*[n];
    for(int i = 0; i < n; i++) _table[i] = nullptr;

    if(printer != nullptr && printer->isPrint()){
        auto &os = printer->getOutputStream();
        // os << "\t";
        // os << "ScopeTable# " << _scopeId << " created" << std::endl;
    }
} 

SymbolInfo* ScopeTable::insert(SymbolInfo s){
    auto hash = _getHash(s.getName());

    if(_table[hash] == nullptr){
        auto sptr = new SymbolInfo(s, _table[hash]);
        _table[hash] = sptr;
        // printInsertHelper(hash+1, 1);
        return sptr;
    }
    else{
        auto toInsertAt = _table[hash];
        int i = 1;
        for(auto head = _table[hash]; head != nullptr; head = head->getNext(), i++){
            if(*head == s.getName()){
                printInsertHelper(s.getName());
                return nullptr;
            }
            toInsertAt = head;
        }

        auto sptr = new SymbolInfo(s);
        toInsertAt->setNext(sptr);
        return sptr;
        // printInsertHelper(hash+1, i);
    }

    // return true;
}

SymbolInfo* ScopeTable::lookup(std::string s){
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

bool ScopeTable::remove(std::string s){
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

void ScopeTable::setNext(ScopeTable *next){
    _next = next;
}
ScopeTable* ScopeTable::getNext(){
    return _next;
}

int ScopeTable::getScopeId(){
    return _scopeId;
}

ScopeTable::~ScopeTable(){
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
        // os << "\t";
        // os << "ScopeTable# " << _scopeId << " removed" << std::endl;
    }
}

std::ostream& operator<<(std::ostream &os, const ScopeTable &s){
    os << "\t";
    os << "ScopeTable# " << s._scopeId << std::endl;
    for(int i = 0; i < s._no_of_bucket; i++){
        if(s._table[i] == nullptr) continue; 

        os << "\t";
        os << i+1 << "--> ";
        auto head = s._table[i];
        for(head = s._table[i];head != nullptr; head = head->getNext()){
            os <<*head << " "; //(head->getNext() == nullptr? "" : " ");
        }
        
        os << std::endl;
    }

    return os;
}
