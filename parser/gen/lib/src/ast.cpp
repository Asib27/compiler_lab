#include"../ast.h"

AST::AST(NodeType type, int startLineNo, int endLineNo)
    : nodeType(type), startLine(startLineNo)
{
    if(endLineNo == -1) endLineNo = startLine;
    endLine = endLineNo;

    symbolInfo = nullptr;
}

AST::AST(NodeType type, SymbolInfo* symbolInfo, int startLineNo, int endLineNo)
    : AST(type, startLineNo, endLineNo)
{
    this->symbolInfo = symbolInfo;
}

void AST::addChild(AST * child){
    childs.push_back(child);
    endLine = child->endLine;
}

AST::~AST()
{
    for(auto i: childs){
        i->~AST();
    }
}



std::ostream& AST::print(std::ostream &os, int tab){
    os << std::string(tab, '\t') << getStringofNode(nodeType) << " :  <Line:" << startLine << "-" 
        << endLine << ">" << std::endl;
    
    for(auto i: childs){
        i->print(os, tab+1);
    }

    return os;
}

// int main(){
//     AST ast1(NodeType::EXP, 1), ast2(NodeType::VARIABLE, 1), ast3(NodeType::FACTOR, 2);
//     ast1.print(std::cout);

//     ast1.addChild(&ast2);
//     ast1.print(std::cout);

//     ast1.addChild(&ast3);
//     ast1.print(std::cout);
// }