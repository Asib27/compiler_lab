#include"../codegen.h"

void Codegen::generateCode(){
    auto program = treewalker.processStart(root);
    auto units = treewalker.processProgram(program);
    for(auto unit: units){
        unit->print(std::cout);
        std::cout << std::endl;
    }
}

vector<string> Codegen::generateGlobalVariableCode(vector<AST*> vars){
    vector<string> v;
    return v;
}
