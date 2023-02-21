#ifndef __STNODE__H__
#define __STNODE__H__

#include<iostream>
#include<string>
#include<vector>
#include"symbolInfo.h"
#include"codeHelper.h"


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

class TerminalExpressionNode : public ExpressionNode
{
    std::string access;
public:
    TerminalExpressionNode(SymbolInfo* info, std::string access)
        : ExpressionNode(info, "", "terminal"), access(access)
        {}

    std::string getName(){ return getOperator();}
    std::string getAccess(){ return access;}

    std::string generate(std::vector<bool> &registerUse, CodeHelper &code) override{
        std::string reg = code.getEmptyRegister(registerUse);
        code.addToCode("MOV", reg, access, "");
        code.setRegister(reg, registerUse, true);
        return reg;
    }
};

class FunctionExpressionNode : public ExpressionNode
{
    std::vector<ExpressionNode *> args;
public:
    FunctionExpressionNode(SymbolInfo* info, std::vector<ExpressionNode *> args)
        : ExpressionNode(info, "", "function"), args(args)
    {
    }

    std::string generate(std::vector<bool> &registerUse, CodeHelper &code) override{
        if(code.isEmptyRegister("AX", registerUse))
            code.addToCode("PUSH", "AX", "");
        if(code.isEmptyRegister("BX", registerUse))
            code.addToCode("PUSH", "BX", "");
        if(code.isEmptyRegister("CX", registerUse))
            code.addToCode("PUSH", "CX", "");
        if(code.isEmptyRegister("DX", registerUse))
            code.addToCode("PUSH", "DX", "");
        
        int size  = args.size();
        for(auto i: args){
            std::vector<bool> registers(4, false);
            std::string res = i->generate(registerUse, code);
            code.addToCode("PUSH", res, "");
        }

        code.addToCode("CALL", getOperator(), "");

        code.addToCode("ADD", "SP", std::to_string(2*size), "");
        std::string res = code.getEmptyRegister(registerUse);
        code.addToCode("MOV", res, "AX", "");
        
        if(code.isEmptyRegister("DX", registerUse))
            code.addToCode("POP", "DX", "");
        if(code.isEmptyRegister("CX", registerUse))
            code.addToCode("POP", "CX", "");
        if(code.isEmptyRegister("BX", registerUse))
            code.addToCode("POP", "BX", "");
        if(code.isEmptyRegister("AX", registerUse))
            code.addToCode("POP", "AX", "");

        code.setRegister(res, registerUse, true);
        return res;
    }
};

class BinaryExpressionNode : public ExpressionNode
{
private:
    ExpressionNode *left;
    ExpressionNode *right;

    std::string getOperatorOpcode(){
        std::string s = getOperator();
        std::string type = getType();
        if(s == "+") return "ADD";
        else if(s == "-") return "SUB";
        else if(s == "*") return "MUL";
        else if(s == "/") return "DIV";
        else if(s == "%") return "DIV";
        else if(type == "RELOP"){
            if(s == "<") return "JL";
            else if(s == "<=") return "JLE";
            else if(s == ">") return "JG";
            else if(s == ">=") return "JGE";
            else if(s == "!=") return "JNZ";
            else if(s == "==") return "JZ";            
        }
        else if(type == "LOGICOP") return "CMPR";
        else if(s == "=") return "MOV";

        std::cerr << "INVALID OPERATOR " << s << __LINE__ << std::endl;
        return "BIN";
    }

    std::string getSymbolAccess(ExpressionNode* exp){
        auto term = dynamic_cast<TerminalExpressionNode *>(exp);
        if(!term) {
            std::cerr << "lhs does not contain reference" << std::endl;
            return "";
        }
        return term->getAccess();
    }
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
        std::string oprtr = getOperator();
        auto type = getType();

        auto opcode = getOperatorOpcode();
        if(type == "ADDOP"){
            std::string reg1 = left->generate(registerUse, code);
            std::string reg2 = right->generate(registerUse, code);
            code.addToCode(opcode , reg1, reg2, "");
            code.setRegister(reg2, registerUse, false);
            return reg1;
        }
        else if(type == "MULOP"){
            std::string reg1 = left->generate(registerUse, code);
            std::string reg2 = right->generate(registerUse, code);

            // pushing register
            // bool AxPushed = code.isEmptyRegister("AX", registerUse) && (reg1 != "AX") && (reg2 != "AX");
            // bool DxPushed = code.isEmptyRegister("DX", registerUse) && (reg1 != "AX") && (reg2 != "DX");
            // if(AxPushed){
            //     code.addToCode("PUSH", "AX", "");
            // }
            // if(DxPushed){
            //     code.addToCode("PUSH", "DX", "");
            // }

            if(reg1 != "AX"){
                code.addToCode("MOV", "AX", reg1, "");
                code.setRegister(reg1, registerUse, false);
            }

            if(oprtr == "*"){
                code.addToCode("MUL", reg2, "");
                code.setRegister(reg2, registerUse, false);

                code.setRegister(reg1, registerUse, true);
                return "AX";
            }
            else if(oprtr == "/" || oprtr == "%"){
                code.addToCode("CWD", "");
                
                code.addToCode("DIV", reg2, "");
                code.setRegister(reg2, registerUse, false);
                
                if(oprtr == "/"){
                    code.setRegister("AX", registerUse, true);
                    return "AX";
                }else if (oprtr == "%"){
                    code.setRegister("DX", registerUse, true);
                    return "DX";                   
                }
            }

            // if(DxPushed){
            //     code.addToCode("POP", "DX", "");
            //     code.setRegister("DX", registerUse, true);
            // }
            // if(AxPushed){
            //     code.addToCode("POP", "AX", "");
            //     code.setRegister("AX", registerUse, true);
            // }
        }
        else if(type == "ASSIGNOP"){
            std::string reg = right->generate(registerUse, code);
            std::string leftAccess = getSymbolAccess(left);
            code.addToCode(opcode, leftAccess, reg, "");
            return reg;
        }
        else if(type == "RELOP"){
            std::string reg1 = left->generate(registerUse, code);
            std::string reg2 = right->generate(registerUse, code);
            code.addToCode("CMP", reg1, reg2, "");
            std::string label = code.getLabel();
            code.addToCode(opcode, label + "s", "");
            code.addToCode("MOV", reg1, "0", "");
            code.addToCode("JMP", label + "e", "");

            code.addLabel(label + "s");
            code.addToCode("MOV", reg1, "1", "");
            code.addLabel(label + "e");

            code.setRegister(reg2, registerUse, false);
            return reg1;
        }
        else if(type == "LOGICOP"){
            if(oprtr == "&&"){
                std::string reg1 = left->generate(registerUse, code);
                std::string label = code.getLabel();
                code.addToCode("CMP", reg1, "0", "");
                code.addToCode("JZ", label + "s", "");

                std::string reg2 = right->generate(registerUse, code);
                code.addToCode("CMP", reg2, "0", "");
                code.addToCode("JZ", label + "s", "");

                code.addToCode("MOV", reg1, "1", "");
                code.addToCode("JMP", label + "e", "");
                code.addLabel(label + "s");
                code.addToCode("MOV", reg1, "0", "");
                code.addLabel(label + "e");

                code.setRegister(reg2, registerUse, false);
                return reg1;
            }
            else if(oprtr == "||"){
                std::string reg1 = left->generate(registerUse, code);
                std::string label = code.getLabel();
                code.addToCode("JNZ", label + "s", "");

                std::string reg2 = right->generate(registerUse, code);
                code.addToCode("JNZ", label + "s", "");

                code.addToCode("MOV", reg1, "0", "");
                code.addToCode("JMP", label + "e", "");
                code.addLabel(label + "s");
                code.addToCode("MOV", reg1, "1", "");
                code.addLabel(label + "e");

                code.setRegister(reg2, registerUse, false);
                return reg1;
            }

        }

        std::cerr << type << " " << oprtr << " " << "doent match " << __LINE__ << std::endl;

        return "AX";
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
            auto acess = dynamic_cast<TerminalExpressionNode*>(child)->getAccess();
            code.addToCode("INC", acess, "");
            // code.addToCode("MOV", acess, reg, "");
        }
        else if(getOperator() == "--"){
            auto acess = dynamic_cast<TerminalExpressionNode*>(child)->getAccess();
            code.addToCode("DEC", acess, "");
            // code.addToCode("MOV", acess, reg, "");
        }
        else if(getOperator() == "-"){
            code.addToCode("NEG", reg, "");
        }
        else if(getOperator() == "+"){
            
        }
        else{
            std::cerr << __LINE__ << " : INVALID OPERAND " << getOperator() << " " << std::endl;
        }
        return reg;
    }
    
    ~UnaryExpressionNode() {}
};

#endif