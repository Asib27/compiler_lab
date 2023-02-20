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

        new_line = std::string("NEW_LINE PROC\n\
    PUSH AX\n\
    PUSH DX\n\
    \n\
    MOV AH, 2       ; output a char\n\
    MOV DL, 0DH     \n\
    INT 21H         ; print CR\n\
    MOV DL, 0AH     \n\
    INT 21H         ; print LF\n\
    \n\
    POP DX                    \n\
    POP AX                    \n\
    RET\n\
NEW_LINE ENDP\n");

        // indentation is not maintained to keep good indentation in output asm code
        print_output =  std::string("\
PRINT_OUTPUT PROC\n\
    PUSH AX\n\
    PUSH BX\n\
    PUSH CX\n\
    PUSH DX\n\
\n\
    ; if AX < 0\n\
    OR AX, AX\n\
    JGE @END_IF1\n\
\n\
    ; then\n\
    PUSH AX         ; save number\n\
    MOV DL, '-'     ; get '-'\n\
    MOV AH, 2       ; print char function\n\
    INT 21H         \n\
    POP AX          ; get AX back\n\
    NEG AX          ; AX = - AX\n\
@END_IF1:\n\
    \n\
    ; get decimal digits                   \n\
    XOR CX, CX      ; CX counts digits\n\
    MOV BX, 10D     ; BX has divisor\n\
                                \n\
DEC_OUTPUT_WHILE:\n\
    XOR DX, DX      ; prepare high word of dividend\n\
    DIV BX          ; AX = quotient, DX = remainder\n\
    PUSH DX         ; save remainder on stack\n\
    INC CX          ; count = count + 1\n\
    \n\
    ; until\n\
    OR AX,  AX      ; quotient = 0?\n\
    JNE DEC_OUTPUT_WHILE      \n\
    \n\
    ; convert digit to char and print\n\
    MOV AH, 2       ; print char function\n\
DEC_PRINT_LOOP:\n\
    POP DX          ; digit in DL\n\
    OR DL, 30H      ; convert to char\n\
    INT 21H         ; print digit\n\
    LOOP DEC_PRINT_LOOP\n\
    \n\
    ; end for\n\
    \n\
    POP DX  \n\
    POP CX     \n\
    POP BX\n\
    POP AX       \n\
    RET\n\
PRINT_OUTPUT ENDP\n"
);

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

    void endFunction(std::string funcname, int offset){
        addToCode("ADD", "SP", std::to_string(offset), "");
        if(funcname == "main"){
            addToCode("MOV", "AX", "4CH", "");
            addToCode("INT", "21H", "");
        }
        else{
            this->code.push_back("\tRET");
        }
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