#ifndef __TOKEN_HELPER__
#define __TOKEN_HELPER__

#include<iostream>
#include<string>

enum class NodeType{
    VARIABLE, EXP, LOGIC_EXP, REL_EXP, SIMPLE_EXP,
    TERM, UNARY_EXP, FACTOR, ARG_LIST, ARGS

};

std::string getStringofNode(NodeType n);

#endif