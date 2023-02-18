#include"../codegen.h"

void Codegen::generateCode(){
    auto program = treewalker.processStart(root);
    auto units = treewalker.processProgram(program);

    
    codeHelper.addToData("; global variable declaration");
    for(auto unit: units){
        if(treewalker.isNodeType(unit, NodeType::VAR_DECL)){
            auto vars = treewalker.processVarDeclaration(unit);
            generateGlobalVariableCode(vars);
        }
        else if(treewalker.isNodeType(unit, NodeType::FUNC_DEF)){
            auto func = treewalker.processFunction(unit);
            auto funcName = get<0>(func);
            auto params = get<1>(func);
            auto statement = get<2>(func);

            codeHelper.startFunction(funcName.getName());
            std::cout<< funcName << std::endl;
            for(auto i: params){
                std::cout << *i << std::endl;
            }
            for(auto i: statement){
                i->print(std::cout);
            }
            codeHelper.endFunction(funcName.getName());
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


std::string Codegen::generateThreeAdressExpressionCode(ExpressionNode * exp, int start){
        if(exp == nullptr){
            showError(__LINE__);
            return "";
        }
        else if(exp->getNodeType() == "terminal"){
            auto node = dynamic_cast<TerminalExpressionNode *>(exp);
            if(node == nullptr ){ showError(__LINE__); return "";}

            auto varName = node->getName();

            if(node->getType() == "INT" || node->getType() == "FLOAT"){
                auto symbol = symbolTable.lookup(varName);

                auto varSymbol = dynamic_cast<VariableSymbolInfo *>(symbol);
                if(varSymbol == nullptr ){ showError(__LINE__); return "";}

                varName = varSymbol->getAccessBy();
            }

            ThreeAdressCode code("t" + to_string(start), varName, "", "", "");
            codeHelper.addToThreeAdressCode(code);
            
            return "t" + to_string(start);
        }       
        else if(exp->getNodeType() == "unary"){
            auto node = dynamic_cast<UnaryExpressionNode *>(exp);
            if(node == nullptr ){ showError(__LINE__); return "";}

            auto nodeVal = generateThreeAdressExpressionCode(node->getChild(), start);
            ThreeAdressCode code(nodeVal, "", node->getOperator(), nodeVal, "");
            codeHelper.addToThreeAdressCode(code);
            return nodeVal;
        }
        else if(exp->getNodeType() == "binary"){
            auto node = dynamic_cast<BinaryExpressionNode *>(exp);
            if(node == nullptr ){ showError(__LINE__); return "";}
            auto lhs = generateThreeAdressExpressionCode(node->getLeft(), start);

            auto backup = lhs;
            lhs.erase(lhs.begin());

            auto rhs = generateThreeAdressExpressionCode(node->getRight(), stoi(lhs) + 1);
            ThreeAdressCode code(backup, backup, node->getOperator(), rhs, "");
            codeHelper.addToThreeAdressCode(code);
            return backup;
        }
        else{
            showError(__LINE__);
            return "";
        }
    }


void Codegen::generateFunctionCode(TokenAST *token){

}