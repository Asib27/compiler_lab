#ifndef __FUNCTION_SYMBOL_INFO_H__
#define __FUNCTION_SYMBOL_INFO_H__

#include<iostream>
#include<string>
#include<vector>
#include"symbolInfo.h"

class FunctionSymbolInfo : public SymbolInfo
{
private:
    std::string _returnType;
    std::vector<std::string> _params;

    void printHelper(std::ostream &os) override ;
public:
    FunctionSymbolInfo(std::string name, std::string returnType, std::vector<std::string> params);
    ~FunctionSymbolInfo();

    std::string getReturnType(){ return _returnType;}
    int getNoParam(){ return _params.size();}
    std::vector<std::string> getParameter() { return _params;}
    bool matchParam(std::vector<std::string> v);
};


#endif