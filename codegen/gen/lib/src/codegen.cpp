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
            int param = 2 + params.size() * 2;

            symbolTable.enterScope();
            for(auto i: params){
                auto symbol = dynamic_cast<VariableSymbolInfo *> (i);
                symbol->setAccessBy("[BP+" + std::to_string(param) + "]");
                symbolTable.insert(symbol);
                param -= 2;
            }

            if(offset != 0)
                codeHelper.addToCode("SUB", "SP", std::to_string(offset), "");
            for(auto i: statement){
                codeHelper.addToCode("");
                codeHelper.addToCode( "line " + std::to_string(i->getBeginLine()));
                generateStatementCode(i, offset);
            }

            codeHelper.endFunction(funcName.getName(), offset);
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

    // var declaration
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

    // expression statment
    else if(treewalker.isNodeType(childs, {NodeType::EXPR_STMNT})){
        if(childs[0]->getChilds().size() == 1) return ;

        auto exp = childs[0]->getChilds()[0];
        generateExpressionCode(exp);
    }

    // For println
    else if(treewalker.isNodeType(childs, {NodeType::SYMBOL, NodeType::SYMBOL, NodeType::VARIABLE, NodeType::SYMBOL, NodeType::SYMBOL})){
        std::string id = treewalker.walkID(childs[2]->getChilds()[0]);

        // extracting symbol access string
        auto symbol = dynamic_cast<VariableSymbolInfo *> (symbolTable.lookup(id));
        std::string accessId = symbol->getAccessBy();

        codeHelper.addToCode("");
        codeHelper.addToCode("Line " + std::to_string(childs[0]->getBeginLine()));
        codeHelper.addToCode("MOV", "AX", accessId, "saving to register for printing");
        codeHelper.addToCode("CALL", "PRINT_OUTPUT", "");
        codeHelper.addToCode("CALL", "NEW_LINE", "");
    }

    // for compound statement
    else if(treewalker.isNodeType(childs, {NodeType::COMPOUND_STATEMENT})){
        generateCompoundStatementCode(childs[0], offset);
    }

    // for IF LPAREN expression RPAREN statement
    else if(
        treewalker.isNodeType(
            childs, 
            {NodeType::SYMBOL, NodeType::SYMBOL, NodeType::EXP, NodeType::SYMBOL, NodeType::STATEMENT}
        ) && treewalker.walkID(childs[0]) == "if"
        )
    {
        std::string reg = generateExpressionCode(childs[2]);
        std::string endLabel = codeHelper.getLabel() + "_if";

        codeHelper.addToCode("CMP", reg, "0", "");
        codeHelper.addToCode("JE", endLabel, "do not enter if");
        codeHelper.addToCode("IF starts");
        generateStatementCode(dynamic_cast<TokenAST *>(childs[4]), offset);
        codeHelper.addLabel(endLabel);
    }

    // if (expr) stmnt else stmnt
    else if(treewalker.isNodeType(
            childs, 
            {NodeType::SYMBOL, NodeType::SYMBOL, NodeType::EXP, NodeType::SYMBOL, NodeType::STATEMENT, NodeType::SYMBOL, NodeType::STATEMENT}
            ) &&
            treewalker.walkID(childs[0]) == "if"
    ){ 
        std::string reg = generateExpressionCode(childs[2]);
        std::string endLabel = codeHelper.getLabel() + "_if";

        codeHelper.addToCode("CMP", reg, "0", "");
        codeHelper.addToCode("JE", endLabel + "s", "do not enter if");
        codeHelper.addToCode("If starts");
        generateStatementCode(dynamic_cast<TokenAST *>(childs[4]), offset);
        codeHelper.addToCode("JMP", endLabel + "e", "");
        codeHelper.addLabel(endLabel + "s");
        codeHelper.addToCode("else block starts");
        generateStatementCode(dynamic_cast<TokenAST *>(childs[6]), offset);
        codeHelper.addLabel(endLabel + "e");
    }

    // while ( expr ) stmnt
    else if(treewalker.isNodeType(
        childs, 
        {NodeType::SYMBOL, NodeType::SYMBOL, NodeType::EXP, NodeType::SYMBOL, NodeType::STATEMENT}
        ) &&
        treewalker.walkID(childs[0]) == "while"
    ){
        std::string label = "line_" + std::to_string(childs[0]->getBeginLine()) + "_while_"; 
        codeHelper.addLabel(label + "s");
        std::string reg = generateExpressionCode(childs[2]);
        codeHelper.addToCode("CMP", reg, "0", "");
        codeHelper.addToCode("JZ", label+"e", ""); // if false go to end of while
        codeHelper.addToCode("While starts");
        generateStatementCode(dynamic_cast<TokenAST *>(childs[4]), offset);
        codeHelper.addToCode("JMP", label+"s", ""); //uncondition jump to go back to top of the loop
        codeHelper.addLabel(label+"e"); // end of while label
    }

    // for loop code
    else if(treewalker.isNodeType(
        childs,
        {
            NodeType::SYMBOL, NodeType::SYMBOL, NodeType::EXPR_STMNT,
            NodeType::EXPR_STMNT, NodeType::EXP, NodeType::SYMBOL, NodeType::STATEMENT
        }
    )){
        codeHelper.addToCode("FOR loop of line" + childs[0]->getBeginLine());

        // initialization
        generateExpressionStatementCode(childs[2]);

        // checking
        std::string label = "line_" + std::to_string(childs[0]->getBeginLine()) + "_for_";
        codeHelper.addLabel(label+"s"); // label to loopback
        std::string reg = generateExpressionStatementCode(childs[3]);
        codeHelper.addToCode("CMP", reg, "0", "");
        codeHelper.addToCode("JZ", label+"e", ""); // if condition false
        codeHelper.addToCode(" for loop body starts");
        generateStatementCode(dynamic_cast<TokenAST *>(childs[6]), offset);
        generateExpressionCode(childs[4]);
        codeHelper.addToCode("JMP", label+"s", ""); // go back to loop start
        codeHelper.addLabel(label+"e");
    }

    else if(treewalker.isNodeType(childs, {NodeType::SYMBOL, NodeType::EXP, NodeType::SYMBOL})){
        std::string res = generateExpressionCode(childs[1]);
        codeHelper.addToCode("MOV", "AX", res, "");
    }

}
    
void Codegen::generateCompoundStatementCode(AST* root, int &offset){
    symbolTable.enterScope();
    
    auto statements = treewalker.walkCompundStatements(root);
    for(auto i: statements){
        codeHelper.addToCode("");
        codeHelper.addToCode( "line " + std::to_string(i->getBeginLine()));
        generateStatementCode(i, offset);
    }

    symbolTable.exitScope();
}