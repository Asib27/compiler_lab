#include"../treeWalker.h"

SymbolAST* TreeWalker::createDeclarationChild(AST* child, bool flag){
    auto symbolAst = dynamic_cast<SymbolAST *> (child);
    auto symbol = symbolAst->getSymbol();

    SymbolInfo * t = nullptr;
    if(flag){
        t = new SymbolInfo(symbol->getName(), "");
    }
    else{
        t = new VariableSymbolInfo(symbol->getName(), "", "ARRAY");
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


std::string TreeWalker::parameterListChild(std::vector<AST *> childs, AST** rootptr){
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

    // new SymbolAST is created and returned 
    return type;
}


std::vector<std::string> TreeWalker::walkParameterList(AST* root){
    std::vector<std::string> ans;

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();
        auto t = parameterListChild(childs, &root);
        ans.push_back(t);

        // std::cout << t << " " << root << std::endl;
    }

    return ans;
}

std::vector<SymbolAST *> TreeWalker::walkDeclarationList(AST* root){
    std::vector<SymbolAST *> ans;

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();
        auto t = declarationListChild(childs, &root);
        ans.push_back(t);

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

    auto type = symbolAST->getSymbol()->getName();
    transform(type.begin(), type.end(), type.begin(), ::toupper);
    return type;
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
