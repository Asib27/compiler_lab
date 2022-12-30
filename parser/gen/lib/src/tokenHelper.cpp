#include"../tokenHelper.h"

std::string NodeTypeToString[] = {
    "variable", "expression", "logic_expression", "rel_expression",
    "simple_expression", "term", "unary_expression", "factor",
    "argument_list", "arguments", "", "var_declaration", "type_specifier", "declaration_list",
    "statements", "statement", "expression_statement", "compound_statement", 
    "func_declaration", "func_defination", "start", "program", "unit", "parameter_list"
};

std::string getStringofNode(NodeType n){
    return NodeTypeToString[static_cast<int>(n)];
}