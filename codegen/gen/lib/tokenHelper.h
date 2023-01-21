#ifndef __TOKEN_HELPER__
#define __TOKEN_HELPER__

#include<iostream>
#include<string>

enum class NodeType{
    VARIABLE, EXP, LOGIC_EXP, REL_EXP, SIMPLE_EXP,
    TERM, UNARY_EXP, FACTOR, ARG_LIST, ARGS, TOKEN,
    VAR_DECL, TYPE_SPECIFIER, DECL_LIST, STATEMENTS, STATEMENT,
    EXPR_STMNT, COMPOUND_STATEMENT, FUNC_DECL, FUNC_DEF,
    START, PROGRAM, UNIT, PARAM_LIST
};

std::string getStringofNode(NodeType n);

#endif