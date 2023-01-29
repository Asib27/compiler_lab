#ifndef __STNODE__H__
#define __STNODE__H__

#include<iostream>
#include<string>
#include"symbolInfo.h"

class ExpressionNode{
    const std::string op;
    const std::string type;
    const std::string childOp;
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
    ~UnaryExpressionNode() {}
};

class TerminalExpressionNode : public ExpressionNode
{
public:
    TerminalExpressionNode(SymbolInfo* info)
        : ExpressionNode(info, "", "terminal")
        {}

    std::string getName(){ return getOperator();}
};

#endif