#include"../codegen.h"

void Codegen::generateCode(){
    auto program = treewalker.processStart(root);
    auto units = treewalker.processProgram(program);

    
    codeHelper.addToData("; global variable declaration");
    for(auto unit: units){
        // unit->print(std::cout);
        // std::cout << std::endl;

        if(treewalker.isNodeType(unit, NodeType::VAR_DECL)){
            auto vars = treewalker.processVarDeclaration(unit);
            generateGlobalVariableCode(vars);
        }
    }
}

void Codegen::generateGlobalVariableCode(vector<SymbolAST*> vars){
    for(auto var: vars){
        auto symbol = dynamic_cast<VariableSymbolInfo*>( var->getSymbol());
        var->setSymbol(nullptr);

        symbol->setAccessBy(symbol->getName());
        symbolTable.insert(symbol);
        codeHelper.addToData(symbol->getName() + " DW 1 DUP (0000H)", "declared at line " + to_string(var->getBeginLine()) );
        delete var;
    }
}
