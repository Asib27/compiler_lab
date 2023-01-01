#include"../treeWalker.h"

SymbolAST* TreeWalker::createDeclarationChild(AST* child, bool flag){
    auto symbolAst = dynamic_cast<SymbolAST *> (child);
    auto symbol = symbolAst->getSymbol();

    SymbolInfo * t = nullptr;
    if(flag){
        t = new SymbolInfo(symbol->getName(), "");
    }
    else{
        t = new SymbolInfo(symbol->getName(), "array");
    }

    return new SymbolAST(t, symbolAst->getBeginLine());
}

SymbolAST* TreeWalker::declarationListChild(std::vector<AST*> childs, AST** rootptr){
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


SymbolAST* TreeWalker::parameterListChild(std::vector<AST *> childs, AST** rootptr){
    if(childs.size() == 0){
        *rootptr = nullptr;
        return nullptr;
    }

    // if first node is not type specifier, then it is parameter list
    // so rootptr points to there and typespecifier node is kept in idx
    int idx = 0;
    *rootptr = nullptr;
    if(childs[0]->getTokenType() != "type_specifier"){
        *rootptr = childs[0];
        idx = 2;
    }

    // type specifier is found
    std::string type = walkTypeSpecifier(childs[idx]);

    // optional ID part is found
    std::string id = "";
    if(childs.size() > idx+1){
        auto symbolAST = dynamic_cast<SymbolAST *> (childs[idx+1]);
        id = symbolAST->getSymbol()->getName();
    }

    // new SymbolAST is created and returned 
    auto newSymbol = new SymbolInfo(id, type);
    return new SymbolAST(newSymbol, childs[0]->getBeginLine());
}

std::vector<SymbolAST *> TreeWalker::walkDeclarationList(AST* root){
    std::vector<SymbolAST *> ans;

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();

        if(root->getTokenType() == "declaration_list"){
            auto t = declarationListChild(childs, &root);
            ans.push_back(t);
        }
        else if(root->getTokenType() == "parameter_list"){
            auto t = parameterListChild(childs, &root);
            ans.push_back(t);
        }

        // std::cout << t << " " << root << std::endl;
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

std::string TreeWalker::walkID(AST* root){
    if(root == nullptr) return "";
    if(root->getTokenType() != "symbol") return "";

    auto symbolAST = dynamic_cast<SymbolAST *> (root);
    if(symbolAST == nullptr || symbolAST->getSymbol() == nullptr) return "";
    return symbolAST->getSymbol()->getName();
}

TreeWalker::TreeWalker(/* args */)
{
}

TreeWalker::~TreeWalker()
{
}
