#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include<iostream>
#include<vector>
#include "ast.h"
#include "tokenHelper.h"
#include "treeWalker.h"
#include "symbolTable.h"
#include "codeHelper.h"
#include "stnode.h"

using namespace std;


class Codegen
{
private:
    TreeWalker treewalker;
    SymbolTable symbolTable;
    AST* root;
    CodeHelper codeHelper;

    void showError(int line){
        std::cerr << "Code gen error " << line << std::endl;
    }
public:
    Codegen(AST* root): symbolTable(11), root(root) {}

    void generateCode();
    void generateGlobalVariableCode(std::vector<SymbolAST*> vars);
    void generateStatementCode(TokenAST *token, int &offset);

    
    std::string generateThreeAdressExpressionCode(ExpressionNode * exp, int start = 1);
    std::string generateExpressionCode(AST *exp){
        std::vector<bool> registers(4, false);
        codeHelper.setCurLabel("Line" + std::to_string(exp->getBeginLine()) + "_");
        
        auto expSt = treewalker.processExpression(exp, symbolTable);
        std::string reg = expSt->generate(registers, codeHelper);
        return reg;
    }
    void printCode(std::ostream &os){
        codeHelper.print(os);
    }

    void generateCompoundStatementCode(AST* root, int &offset);
    std::string generateExpressionStatementCode(AST* root){
        auto child = root->getChilds();
        if(child.size() == 1) return "";
        if(child.size() == 2){
            return generateExpressionCode(child[0]);
        }

        return "";
    }

    ~Codegen() {}
};

#endif