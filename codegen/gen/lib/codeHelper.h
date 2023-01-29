#ifndef __CODE_HELPER_H__
#define __CODE_HELPER_H__

#include<iostream>
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
        
public:
    CodeHelper(/* args */){}

    void addToData(std::string code, std::string comment){
        data.push_back(code + "\t; " + comment);
    }
    
    void addToData(std::string comment){
        data.push_back("; " + comment);
    }

    void addToCode(std::string code, std::string comment){
        this->code.push_back(code + "\t; " + comment);
    }

    void addToCode(std::string comment){
        this->code.push_back("; " + comment);
    }

    void addToThreeAdressCode(ThreeAdressCode t){
        threeCode.push_back(t);
    }

    void print(std::ostream &os){
        os << ".MODEL SMALL" << std::endl;
        os << ".STACK 1000H" << std::endl;
        os << ".DATA" << std::endl;

        for(auto i : data){
            os << i << std::endl;
        }

        os << ".CODE" << std::endl;
        for(auto i: code){
            os << i << std::endl;
        }

        for(auto i: threeCode){
            os << i << std::endl;
        }
    }

    ~CodeHelper(){}
};

#endif