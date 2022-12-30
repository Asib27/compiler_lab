#include"../ast.h"

AST::~AST(){}

void AST::addChild(std::vector<AST *> childs){
    for(auto i: childs){
        addChild(i);
    }
}

TokenAST::TokenAST(NodeType type, std::string info,  int startLineNo, int endLineNo)
    : nodeType(type), startLine(startLineNo), info(info)
{
    if(endLineNo == -1) endLineNo = startLine;
    endLine = endLineNo;
}

void TokenAST::addChild(AST * child){
    if(childs.size() == 0){
        startLine = child->getBeginLine();
    }
    childs.push_back(child);
    endLine = child->getEndLine();
}

TokenAST::~TokenAST()
{
    for(auto i: childs){
        delete i;
    }
}

std::ostream& TokenAST::print(std::ostream &os, int tab){
    os << std::string(tab, ' ') << getStringofNode(nodeType) << " : "<< info << "\t<Line:" << startLine << "-" 
        << endLine << ">" << std::endl;
        
    for(auto i: childs){
        i->print(os, tab+1);
    }

    return os;
}

// int main(){
//     TokenAST ast1(NodeType::EXP, "EXP", 1);
//     AST* ast2= new TokenAST(NodeType::VARIABLE, "VAR", 1);

//     auto t = new SymbolInfo("as", "sd");
//     AST* ast3= new SymbolAST(t, 2);
//     ast1.print(std::cout);

//     ast1.addChild(ast2);
//     ast1.print(std::cout);

//     ast1.addChild(ast3);
//     ast1.print(std::cout);

//     delete t;
// }