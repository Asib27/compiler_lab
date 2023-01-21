#ifndef __TREE_WALKER_H__
#define __TREE_WALKER_H__


#include<iostream>
#include<vector>
#include<algorithm>
#include"symbolInfo.h"
#include"functionSymbolInfo.h"
#include"variableSymbolInfo.h"
#include"ast.h"

class TreeWalker
{
private:
    SymbolAST* createDeclarationChild(AST* child, bool flag);
    SymbolAST* declarationListChild(std::vector<AST*> childs, AST** rootptr);

    std::string parameterListChild(std::vector<AST *> childs, AST** rootptr);

    std::string argumentListChild(std::vector<AST *> childs, AST **rootptr);
public:
    TreeWalker();
    
    std::string getDataType(AST *expressionNode);
    std::string walkTypeSpecifier(AST* root);
    std::string walkID(AST* root);
    std::vector<SymbolAST *> walkDeclarationList(AST* root);
    std::vector<std::string> walkParameterList(AST* root);
    std::vector<SymbolInfo *> walkParameterListFindIds(AST* root);
    std::vector<std::string> walkArgumentList(AST *root);
    int walkUnaryExpressionValue(AST *root);

    ~TreeWalker();
};

#endif