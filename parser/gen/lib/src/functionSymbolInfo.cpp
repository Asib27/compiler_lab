#include"../functionSymbolInfo.h"

FunctionSymbolInfo::FunctionSymbolInfo(std::string name, std::string returnType, std::vector<std::string> params)
    : SymbolInfo(name, "FUNCTION"), _returnType(returnType), _params(params)
{

}
FunctionSymbolInfo::~FunctionSymbolInfo()
{
}

void FunctionSymbolInfo::printHelper(std::ostream &os) {
    os << "<" << getName() << ", " << getType() << ", " << _returnType << ">";
}

bool FunctionSymbolInfo::matchParam(std::vector<std::string> v){
    if(_params.size() != v.size()) return false;
    
    for(int i = 0; i < _params.size();i++){
        if(_params[i] != v[i]) {return false;}
    }

    return true;
}

bool FunctionSymbolInfo::matchParam(std::vector<std::string> v, std::vector<int> &errors){
    if(_params.size() != v.size()) return false;
    
    for(int i = _params.size()-1; i >= 0;i--){
        if(_params[i] != v[i]) {
            errors.push_back(v.size()-i);
        }
    }

    return errors.size() == 0;
}

// int main(){
//     FunctionSymbolInfo f1("foo", "INT", {"INT", "INT"});

//     std::cout << (f1 == "foo") << " " << (f1 == "bar") << std::endl;
//     std::cout << (f1 != "foo") << " " << (f1 != "bar") << std::endl;
//     std::cout << f1.getType() << std::endl;
//     std::cout << f1.matchParam({"INT", "INT"}) << " " << f1.matchParam({"INT", "FLOAT"})
//                 << " " << f1.matchParam({"INT", "INT", "INT"}) << f1.matchParam({}) << std::endl;
    
//     SymbolInfo *f2 = new FunctionSymbolInfo("bar", "INT", {"INT", "INT"});
//     SymbolInfo *s1 = new SymbolInfo("bar", "INT");

//     std::cout << ((*s1) == "bar") << std::endl;
//     std::cout << f2->getName() << f2->getType() << std::endl;
// }