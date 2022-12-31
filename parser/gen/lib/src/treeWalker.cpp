#include"../treeWalker.h"

SymbolInfo* TreeWalker::createDeclarationChild(AST* child, bool flag){
    auto symbolAst = dynamic_cast<SymbolAST *> (child);
    auto symbol = symbolAst->getSymbol();

    if(flag){
        return new SymbolInfo(symbol->getName(), "");
    }
    else{
        return new SymbolInfo(symbol->getName(), "array");
    }
}

SymbolInfo* TreeWalker::declarationListChild(std::vector<AST*> childs, AST** rootptr){
    if(childs.size() == 0){
        *rootptr = nullptr;
        return nullptr;
    }

    if(childs[0]->getTokenType() == "symbol"){
        *rootptr = nullptr;
        return createDeclarationChild(childs[0], childs.size() == 1);
    }
    else{
        *rootptr = childs[0];
        return createDeclarationChild(childs[2], childs.size() == 3);
    }
}
std::vector<SymbolInfo *> TreeWalker::walkDeclarationList(AST* root){
    std::vector<SymbolInfo *> ans;

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();
        auto t = declarationListChild(childs, &root);
        ans.push_back(t);

        // std::cout << t << " " << root << std::endl;
    }

    for(auto i: ans){
        std::cout << *i << std::endl;
    }
    return ans;
}


std::string TreeWalker::walkTypeSpecifier(AST* root){
    if(root == nullptr) return "";
    if(root->getTokenType() != "type_specifier") return "";
    
    auto t = root->getChilds();
    if(t.size() != 1) return "";

    auto symbolAST = dynamic_cast<SymbolAST *>  (t[0]);
    if(symbolAST == nullptr || symbolAST->getSymbol() == nullptr) return "";
    return symbolAST->getSymbol()->getName();
}

TreeWalker::TreeWalker(/* args */)
{
}

TreeWalker::~TreeWalker()
{
}
