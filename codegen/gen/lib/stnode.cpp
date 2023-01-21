#include<iostream>

class Stnode
{
private:
protected:
    int startLineNo;
    int endLineNo;

    virtual void print() = 0;
public:
    Stnode(int start, int end) 
        : startLineNo(start), endLineNo(end)
    {}
    ~Stnode(){}
    int getStartLine(){ return startLineNo;}
    int getEndLine(){ return endLineNo;}

    friend std::ostream& operator<<(std::ostream &os, Stnode &st){
        st.print();        
        return os;
    }
};


class FuncDefine : public Stnode
{

protected:
    void print(){

    }
};

class StmntNode : public Stnode
{

protected:
    void print(){

    }
};


class CompStmnt : public StmntNode
{

protected:
    void print(){

    }
};

class VarDecl : public StmntNode
{

protected:
    void print(){

    }
};

class ControlFlow : public StmntNode
{

protected:
    void print(){

    }
};

class ExpNode : public StmntNode
{

protected:
    void print(){

    }
};

class UnaryExp : public ExpNode
{

};

class BinaryExp : public ExpNode
{

};

class TermExp : public ExpNode
{

};