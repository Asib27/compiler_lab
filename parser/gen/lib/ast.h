#ifndef __AST_H__
#define __AST_H__

#include<vector>
#include"symbolInfo.h"
#include"tokenHelper.h"

class AST
{
private:
    NodeType nodeType;
    int startLine;
    int endLine;
    SymbolInfo* symbolInfo;
    std::vector<AST *> childs;
public:
    AST(NodeType type, int startLineNo, int endLineNo=-1);
    AST(NodeType type, SymbolInfo* symbolInfo, int startLineNo, int endLineNo=-1);
    ~AST();

    void addChild(AST * child);
    std::ostream& print(std::ostream &os, int tab=0);
};

#endif