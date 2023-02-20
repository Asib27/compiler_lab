#ifndef __CODE_HELPER_H__
#define __CODE_HELPER_H__

#include<iostream>
#include<fstream>
#include<vector>
#include<string>



class ThreeAdressCode
{
    std::string op;
    std::string first;
    std::string second;
    std::string result;
    std::string comment;
public:
    ThreeAdressCode(std::string res, std::string f, std::string op, std::string s, std::string comment)
        : op(op), result(res), first(f), second(s), comment(comment)
    {

    }

    friend std::ostream &operator<<(std::ostream &os, ThreeAdressCode t){
       os << t.result << "=" << t.first << t.op << t.second << "\t; " << t.comment;
       return os;
    }
};

class CodeHelper
{
private:
    std::vector<std::string> data;
    std::vector<std::string> code;
    std::vector<ThreeAdressCode> threeCode;

    std::string curLabel;
    int curLabelNo;

    std::string print_output;
    std::string new_line;

    std::string getComment(std::string cmnt){
        return cmnt == ""? "" : "\t; " + cmnt; 
    }   
public:
    CodeHelper(/* args */){
        curLabel = "generic";

        new_line = std::string("NEW_LINE proc\n") + std::string("\tpush ax\n") +
                        "\tpush dx\n" + "\tmov ah,2\n" + "\tmov dl,cr\n" + "\tint 21h\n" +
                        "\tmov ah,2\n" + "\tmov dl,lf\n" + "\tint 21h\n" + "\tpop dx\n" +
                        "\tpop ax\n" + "\tret\n" + "new_line endp\n";
        print_output =  std::string("PRINT_OUTPUT proc  ;print what is in ax\n") + "\tpush ax\n" +
                        "\tpush bx\n" + "\tpush cx\n" + "\tpush dx\n" + "\tpush si\n" +
                        "\tlea si,number\n" + "\tmov bx,10\n" + "\tadd si,4\n" +
                        "\tcmp ax,0\n" + "\tjnge negate\n" + "print:\n" + "\txor dx,dx\n" +
                        "\tdiv bx\n" + "\tmov [si],dl\n" + "\tadd [si],'0'\n" + "\tdec si\n" +
                        "\tcmp ax,0\n" + "\tjne print\n" + "\tinc si\n" + "\tlea dx,si\n" +
                        "\tmov ah,9\n" + "\tint 21h\n" + "\tpop si\n" + "\tpop dx\n" + "\tpop cx\n" +
                        "\tpop bx\n" + "\tpop ax\n" + "\tret\n" + "negate:\n" + "\tpush ax\n" +
                        "\tmov ah,2\n" + "\tmov dl,'-'\n" + "\tint 21h\n" + "\tpop ax\n" +"\tneg ax\n" +
                        "\tjmp print\n"+ "print_output endp\n";

    }

    void addToData(std::string code, std::string comment){
        data.push_back("\t" + code + getComment(comment));
    }
    
    void addToData(std::string comment){
        data.push_back( getComment(comment));
    }

    void addToCode(std::string code, std::string comment){
        this->code.push_back("\t" + code + getComment(comment));
    }
    
    void addToCode(std::string opcode, std::string op1, std::string op2, std::string comment){
        this->code.push_back("\t" + opcode + " " + op1 + "," + op2 + getComment(comment));
    }

    void addToCode(std::string opcode, std::string op1, std::string comment){
        this->code.push_back("\t" + opcode + " " + op1 + getComment(comment));
    }

    void addToCode(std::string comment){
        this->code.push_back( getComment(comment));
    }

    void addLabel(std::string label){
        this->code.push_back(label + ":");
    }

    void addToThreeAdressCode(ThreeAdressCode t){
        threeCode.push_back(t);
    }

    void startFunction(std::string funcname){
        this->code.push_back(funcname + " PROC");

        if(funcname == "main"){
            addToCode("MOV", "AX", "@DATA", "");
            addToCode("MOV", "DX", "AX", "");
            addToCode("PUSH", "BP", "");
            addToCode("MOV", "BP", "SP", "");
        }
    }

    void endFunction(std::string funcname){
        this->code.push_back(funcname + " ENDP");
    }

    std::string getEmptyRegister(std::vector<bool> &registerUse){
        if(!registerUse[1]) return "BX";
        else if(!registerUse[2]) return "CX";
        else if(!registerUse[3]) return "DX";
        else if(!registerUse[0]) return "AX";
        else return "";
    }

    bool isEmptyRegister(std::string regName, std::vector<bool> &registerUse){
        if(regName == "BX") return registerUse[1];
        else if(regName == "CX") return registerUse[2];
        else if(regName == "AX") return registerUse[0];
        else if(regName == "DX") return registerUse[3];
        else return false;
    }

    void setRegister(std::string regName, std::vector<bool> &registerUse, bool val){
        if(regName == "BX") registerUse[1] = val;
        else if(regName == "CX") registerUse[2] = val;
        else if(regName == "AX") registerUse[0] = val;
        else if(regName == "DX") registerUse[3] = val;
    }

    void print(std::ostream &os){
        os << ".MODEL SMALL" << std::endl;
        os << ".STACK 1000H" << std::endl;
        os << ".DATA" << std::endl;

        os << "\tCR EQU 0DH" << std::endl;
        os << "\tLF EQU 0AH" << std::endl;
        os << "\tnumber DB \"00000$\"" << std::endl;
        os << "" << std::endl;

        for(auto i : data){
            os << i << std::endl;
        }

        os << ".CODE" << std::endl;
        for(auto i: code){
            os << i << std::endl;
        }

        os << new_line << std::endl;
        os << print_output << std::endl;

        os << "END MAIN" << std::endl;
    }

    void setCurLabel(std::string label){
        this->curLabel = label;
        this->curLabelNo = 0;
    }

    std::string getLabel(){
        return this->curLabel + std::to_string(this->curLabelNo++);
    }

    ~CodeHelper(){}
};

#endif