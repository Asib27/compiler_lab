#ifndef __AST_H__
#define __AST_H__

#include<vector>
#include"symbolInfo.h"
#include"tokenHelper.h"
#include<string>

class AST
{
private:
    NodeType nodeType;
    std::string info;
    int startLine;
    int endLine;
    SymbolInfo* symbolInfo;
    std::vector<AST *> childs;
public:
    AST(NodeType type, std::string info, int startLineNo, int endLineNo=-1);
    AST(SymbolInfo* symbolInfo, int startLineNo, int endLineNo=-1);
    ~AST();

    void addChild(AST * child);
    std::ostream& print(std::ostream &os, int tab=0);
};


#endif