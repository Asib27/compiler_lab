#ifndef __CODE_HELPER_H__
#define __CODE_HELPER_H__

#include<iostream>
#include<vector>
#include<string>

class CodeHelper
{
private:
    std::vector<std::string> data;
    std::vector<std::string> code;

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
    }

    ~CodeHelper(){}
};

#endif