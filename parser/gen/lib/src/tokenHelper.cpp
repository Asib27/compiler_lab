#include"../tokenHelper.h"

std::string NodeTypeToString[] = {
    "variable", "expression", "logic_expression", "rel_expression",
    "simple_expression", "term", "unary_expression", "factor",
    "arg_list", "args", "", "variable_declaration", "type_specifier", "declaration_list",
    "statements", "statement", "expression_statement"
};

std::string getStringofNode(NodeType n){
    return NodeTypeToString[static_cast<int>(n)];
}