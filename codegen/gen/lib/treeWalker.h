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
    void showError(int line){
        std::cerr << line << "," << __FILE__ << " : ast process error" << std::endl;
    }


    SymbolAST* createDeclarationChild(AST* child, bool flag);
    SymbolAST* declarationListChild(std::vector<AST*> childs, AST** rootptr);

    std::string parameterListChild(std::vector<AST *> childs, AST** rootptr);

    std::string argumentListChild(std::vector<AST *> childs, AST **rootptr);
public:

    bool isNodeType(AST* root, NodeType n){
        // std::cerr << root->getTokenType() << std::endl;
        // std::cerr << getStringofNode(n) << std::endl;

        return root->getTokenType() == getStringofNode(n);
    }

    bool isNodeType(std::vector<AST*> roots, std::vector<NodeType> nodes){
        if(roots.size() != nodes.size()) return false;

        for(int i = 0; i < nodes.size(); i++){
            if(!isNodeType(roots[i], nodes[i])) return false;
        }
        return true;
    }
    TreeWalker();
    
    std::string getDataType(AST *expressionNode);
    std::string walkTypeSpecifier(AST* root);
    std::string walkID(AST* root);
    std::vector<SymbolAST *> walkDeclarationList(AST* root);
    std::vector<std::string> walkParameterList(AST* root);
    std::vector<SymbolInfo *> walkParameterListFindIds(AST* root);
    std::vector<std::string> walkArgumentList(AST *root);
    int walkUnaryExpressionValue(AST *root);

    std::vector<SymbolAST *> processVarDeclaration(AST *root);
    std::vector<AST *> processProgram(AST *);
    AST* processStart(AST * root);
    AST * processUnit(AST *);
    ~TreeWalker();
};

#endif