#ifndef __STNODE__H__
#define __STNODE__H__

#include<iostream>
#include<string>
#include<vector>
#include"symbolInfo.h"
#include"codeHelper.h"

/*
c = a && b
MOV AX, a   ; generating first block
CMP.0
AX, 0
JE first_block
MOV BX, b  ; FOR generating second block 
CMP BX, 0
JE first_block
MOV AX, 1
JMP END
first_block:
MOV AX, 0
END:
*/

/*
c = a || b
MOV AX, a   ; first block
CMP AX, 0 
JNE first_block
MOV BX, b   ; second block 
CMP BX, 0
JNE first_block
MOV AX, 0
JMP END
first_block:
MOV AX, 1
END:
*/

class ExpressionNode{
    const std::string op;
    const std::string type;
    std::string childOp;
    const std::string nodeType;

public:
    ExpressionNode(SymbolInfo *s, std::string childOp, std::string nodeType)
        : op(s->getName()), type(s->getType()), childOp(childOp), nodeType(nodeType)
    {

    }

    std::string getOperator(){
        return op;
    }
    std::string getType(){
        return type;
    }
    std::string getChildOperator(){
        return childOp;
    }

    std::string getNodeType(){
        return nodeType;
    }

    virtual void print(std::ostream &os, int tab=0){
        os << std::string(tab, ' ') << op << " " << type << " " << std::endl;
    } 

    friend std::ostream &operator<<(std::ostream &os, ExpressionNode &e){
        e.print(os);
        return os;
    }

    virtual std::string generate(std::vector<bool> &registerUse, CodeHelper &code) = 0;
};

class BinaryExpressionNode : public ExpressionNode
{
private:
    ExpressionNode *left;
    ExpressionNode *right;

public:
    void print(std::ostream &os, int tab=0){
        ExpressionNode::print(os, tab);
        left->print(os, tab+1);
        right->print(os, tab+1);
    }

    BinaryExpressionNode(ExpressionNode *l, ExpressionNode *r, SymbolInfo *s, std::string childOp)
        : left(l), right(r), ExpressionNode(s, childOp, "binary")
     {}
    
    ExpressionNode* getLeft(){
        return left;
    }

    ExpressionNode* getRight(){
        return right;
    }
    
    std::string generate(std::vector<bool> &registerUse, CodeHelper &code) override{
        std::string reg1 = left->generate(registerUse, code);
        std::string reg2 = right->generate(registerUse, code);
        code.addToCode("BIN" , reg1, reg2, "");
        return reg1;
    }

    ~BinaryExpressionNode() {}
};

class UnaryExpressionNode : public ExpressionNode
{
private:
    ExpressionNode *child;

public:
    UnaryExpressionNode(ExpressionNode *child, SymbolInfo *s, std::string childOp)
        : child(child), ExpressionNode(s, childOp, "unary")
     {}

    ExpressionNode* getChild(){
        return child;
    }

    void print(std::ostream &os, int tab=0){
        ExpressionNode::print(os, tab);
        child->print(os, tab+1);
    }
    
    std::string generate(std::vector<bool> &registerUse, CodeHelper &code) override{
        std::string reg = child->generate(registerUse, code);
        if(getOperator() == "++"){
            code.addToCode("INC", reg, "");
        }
        else if(getOperator() == "--"){
            code.addToCode("DEC", reg, "");
        }
        else if(getOperator() == "!"){
            code.addToCode("NEG", reg, "");
        }
        else{
            std::cerr << __LINE__ << " : INVALID OPERAND " << getOperator() << " " << std::endl;
        }
        return reg;
    }
    
    ~UnaryExpressionNode() {}
};

class TerminalExpressionNode : public ExpressionNode
{
    std::string access;
public:
    TerminalExpressionNode(SymbolInfo* info, std::string access)
        : ExpressionNode(info, "", "terminal"), access(access)
        {}

    std::string getName(){ return getOperator();}

    std::string generate(std::vector<bool> &registerUse, CodeHelper &code) override{
        std::string reg = code.getEmptyRegister(registerUse);
        code.addToCode("MOV", reg, access, "");
        return reg;
    }
};

#endif