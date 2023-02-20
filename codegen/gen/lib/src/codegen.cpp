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
            int offset = 0;

            symbolTable.enterScope();
            for(auto i: params){
                auto symbol = dynamic_cast<VariableSymbolInfo *> (i);
                symbol->setAccessBy("[BP-" + std::to_string(offset+2) + "]");
                symbolTable.insert(symbol);
                offset += 2;
            }

            if(offset != 0)
                codeHelper.addToCode("SUB", "SP", std::to_string(offset), "");
            for(auto i: statement){
                codeHelper.addToCode("");
                codeHelper.addToCode( "line " + std::to_string(i->getBeginLine()));
                generateStatementCode(i, offset);
            }
            codeHelper.endFunction(funcName.getName(), offset);
            std::cout << symbolTable << std::endl;
            symbolTable.exitScope();
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


void Codegen::generateStatementCode(TokenAST *token, int &offset){
    if(treewalker.isNodeType(token, NodeType::EXPR_STMNT)){
        showError(__LINE__);
    }

    auto childs = token->getChilds();
    if(treewalker.isNodeType(childs, {NodeType::VAR_DECL})){
        auto vars = treewalker.processVarDeclaration(childs[0]);

        int prev = offset;
        for(auto i: vars){
            auto symbol = dynamic_cast<VariableSymbolInfo*> (i->getSymbol());
            i->setSymbol(nullptr);
            
            symbol->setAccessBy("[BP-" + std::to_string(offset+2) + "]");
            symbolTable.insert(symbol);
            offset += 2;
        }
            
        if(offset != prev)
            codeHelper.addToCode("SUB", "SP", std::to_string(offset), "initializing local variables");
    }
    else if(treewalker.isNodeType(childs, {NodeType::EXPR_STMNT})){
        if(childs[0]->getChilds().size() == 1) return ;

        auto exp = childs[0]->getChilds()[0];
        auto expSt = treewalker.processExpression(exp, symbolTable);

        vector<bool> registers(4, false);
        expSt->generate(registers, codeHelper);  
    }

    // For println
    else if(treewalker.isNodeType(childs, {NodeType::SYMBOL, NodeType::SYMBOL, NodeType::VARIABLE, NodeType::SYMBOL, NodeType::SYMBOL})){
        std::string id = treewalker.walkID(childs[2]->getChilds()[0]);

        // extracting symbol access string
        auto symbol = dynamic_cast<VariableSymbolInfo *> (symbolTable.lookup(id));
        std::string accessId = symbol->getAccessBy();

        codeHelper.addToCode("");
        codeHelper.addToCode(std::to_string(root->getBeginLine()));
        codeHelper.addToCode("MOV", "AX", accessId, "saving to register for printing");
        codeHelper.addToCode("CALL", "PRINT_OUTPUT", "");
        codeHelper.addToCode("CALL", "NEW_LINE", "");
    }
}