#ifndef __TREE_WALKER_H__
#define __TREE_WALKER_H__


#include<iostream>
#include<vector>
#include"symbolInfo.h"
#include"functionSymbolInfo.h"
#include"ast.h"

class TreeWalker
{
private:
    SymbolInfo* createDeclarationChild(AST* child, bool flag);
    SymbolInfo* declarationListChild(std::vector<AST*> childs, AST** rootptr);
public:
    TreeWalker();

    std::vector<SymbolInfo *> walkDeclarationList(AST* root);
    std::string walkTypeSpecifier(AST* root);

    ~TreeWalker();
};

#endif