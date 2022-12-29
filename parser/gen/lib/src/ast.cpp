#include"../ast.h"

AST::AST(NodeType type, std::string info,  int startLineNo, int endLineNo)
    : nodeType(type), startLine(startLineNo), info(info)
{
    if(endLineNo == -1) endLineNo = startLine;
    endLine = endLineNo;

    symbolInfo = nullptr;
}

AST::AST(SymbolInfo* symbolInfo, int startLineNo, int endLineNo)
    : AST(NodeType::TOKEN, "",startLineNo, endLineNo)
{
    this->symbolInfo = symbolInfo;
}

void AST::addChild(AST * child){
    if(childs.size() == 0){
        startLine = child->startLine;
    }
    childs.push_back(child);
    endLine = child->endLine;
}

AST::~AST()
{
    if(nodeType == NodeType::TOKEN){
        delete symbolInfo;
    }
    for(auto i: childs){
        i->~AST();
    }
}



std::ostream& AST::print(std::ostream &os, int tab){
    if(nodeType != NodeType::TOKEN){
        os << std::string(tab, '\t') << getStringofNode(nodeType) << " : "<< info << "  <Line:" << startLine << "-" 
            << endLine << ">" << std::endl;
    }
    else{
        os << std::string(tab, '\t') << symbolInfo->getType() << " : " << symbolInfo->getName() << "  <Line:" << startLine << "-" 
            << endLine << ">" << std::endl;
    }
    
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