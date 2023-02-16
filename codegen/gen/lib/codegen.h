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
    void generateFunctionCode(TokenAST *token);

    
    std::string generateThreeAdressExpressionCode(ExpressionNode * exp, int start = 1);
    std::string generateExpressionCode(ExpressionNode *exp, int lineno){
        std::vector<bool> registers(4, false);
        codeHelper.setCurLabel("Line" + std::to_string(lineno) + "_");
        std::string reg = exp->generate(registers, codeHelper);
        return reg;
    }
    void printCode(std::ostream &os){
        codeHelper.print(os);
    }

    ~Codegen() {}
};

#endif