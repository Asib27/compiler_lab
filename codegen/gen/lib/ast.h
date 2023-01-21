#ifndef __AST_H__
#define __AST_H__

#include<vector>
#include"symbolInfo.h"
#include"tokenHelper.h"
#include<string>

class AST
{
public:
    AST() = default;
    virtual void addChild(AST * child) = 0;
    virtual void addChild(std::vector<AST *> childs);
    virtual void removeAllChild() = 0;
    virtual std::ostream& print(std::ostream &os, int tab=0) = 0;
    virtual int getBeginLine() = 0;
    virtual int getEndLine() = 0;
    virtual std::vector<AST *> getChilds() = 0;
    virtual std::string getTokenType() = 0;
    virtual ~AST();
};


class TokenAST : public AST
{
    NodeType nodeType;
    std::string info;
    int startLine;
    int endLine;
    std::vector<AST *> childs;
public:
    TokenAST(NodeType nodeType, std::string info, int startLineNo, int endLineNo = -1);
    void addChild(AST * child) override;
    std::vector<AST *> getChilds() override { return childs;}
    void removeAllChild() override { childs = std::vector<AST * >();}
    std::ostream& print(std::ostream &os, int tab=0) override;
    int getBeginLine() override { return startLine; }
    int getEndLine() override { return endLine;}
    std::string getTokenType() override ;
    ~TokenAST();
};

class ExpressionAST : public TokenAST
{
    std::string dataType;
public:
    ExpressionAST(TokenAST *token, std::string dataType)
        : TokenAST(*token), dataType(dataType)
    {}
    
    ExpressionAST(NodeType nodeType, std::string info, std::string dataType ,int startLineNo, int endLineNo = -1)
        : TokenAST(nodeType, info, startLineNo, endLineNo) , dataType(dataType)
    {}

    std::string getDataType(){ return dataType; }
};


class SymbolAST : public AST
{
    SymbolInfo *symbolInfo;
    int lineNo;
public:
    SymbolAST(SymbolInfo *symbolInfo, int lineNo);

    void addChild(AST * child) override {}
    std::vector<AST *> getChilds() override { return std::vector<AST *> ();}
    void removeAllChild() override {}

    std::ostream& print(std::ostream &os, int tab=0) override;

    int getBeginLine() override{ return lineNo; }
    int getEndLine() override{ return lineNo; }
    std::string getTokenType() override {return "symbol";}

    SymbolInfo* getSymbol(){ return symbolInfo;}
    void setSymbol(SymbolInfo *symbolInfo){ this->symbolInfo = symbolInfo;}

    ~SymbolAST();
};

#endif