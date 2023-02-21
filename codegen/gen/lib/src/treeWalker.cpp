#include"../treeWalker.h"


std::string TreeWalker::getDataType(AST *node){
	auto t = dynamic_cast<ExpressionAST *> (node);
	if(t != nullptr) return t->getDataType();
	
	return "";
}

SymbolAST* TreeWalker::createDeclarationChild(AST* child, bool flag){
    auto symbolAst = dynamic_cast<SymbolAST *> (child);
    auto symbol = symbolAst->getSymbol();

    SymbolInfo * t = nullptr;
    if(flag){
        t = new VariableSymbolInfo(symbol->getName(), "", "NORMAL");
    }
    else{
        t = new VariableSymbolInfo(symbol->getName(), "", "ARRAY");
    }

    return new SymbolAST(t, symbolAst->getBeginLine());
}

SymbolAST* TreeWalker::declarationListChild(std::vector<AST*> childs, AST** rootptr){
    if(childs.size() == 0){
        *rootptr = nullptr;
        return nullptr;
    }

    if(childs[0]->getTokenType() == "symbol"){
        *rootptr = nullptr;
        return createDeclarationChild(childs[0], childs.size() == 1);
    }
    else{
        *rootptr = childs[0];
        return createDeclarationChild(childs[2], childs.size() == 3);
    }
}

std::string TreeWalker::parameterListChild(std::vector<AST *> childs, AST** rootptr){
    if(childs.size() == 0){
        *rootptr = nullptr;
        return "";
    }

    // if first node is not type specifier, then it is parameter list
    // so rootptr points to there and typespecifier node is kept in idx
    int idx = 0;
    *rootptr = nullptr;
    if(childs[0]->getTokenType() != "type_specifier"){
        *rootptr = childs[0];
        idx = 2;
    }

    // type specifier is found
    std::string type = idx < childs.size() ? walkTypeSpecifier(childs[idx]) : "error";

    // new SymbolAST is created and returned 
    return type;
}

std::vector<std::string> TreeWalker::walkParameterList(AST* root){
    std::vector<std::string> ans;

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();
        auto t = parameterListChild(childs, &root);
        ans.push_back(t);

        // std::cout << t << " " << root << std::endgetChildsl;
    }

    
    return ans;
}

std::vector<SymbolAST *> TreeWalker::walkDeclarationList(AST* root){
    std::vector<SymbolAST *> ans;

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();
        auto t = declarationListChild(childs, &root);

        if(t == nullptr) {
            for(auto i: ans) delete i;
            return std::vector<SymbolAST *> ();
        }
        ans.push_back(t);

        // std::cout << t << " " << root << std::endl;
    }

    return ans;
}


std::string TreeWalker::walkTypeSpecifier(AST* root){
    if(root == nullptr) return "";
    if(root->getTokenType() != "type_specifier") return "";
    
    auto t = root->getChilds();
    if(t.size() != 1) return "";

    auto symbolAST = dynamic_cast<SymbolAST *>  (t[0]);
    if(symbolAST == nullptr || symbolAST->getSymbol() == nullptr) return "";

    auto type = symbolAST->getSymbol()->getName();
    transform(type.begin(), type.end(), type.begin(), ::toupper);
    return type;
}

std::string TreeWalker::walkID(AST* root){
    if(root == nullptr) return "";
    if(root->getTokenType() != "symbol") return "";

    auto symbolAST = dynamic_cast<SymbolAST *> (root);
    if(symbolAST == nullptr || symbolAST->getSymbol() == nullptr) return "";
    return symbolAST->getSymbol()->getName();
}

std::vector<SymbolInfo *> TreeWalker::walkParameterListFindIds(AST* root){
    std::vector<SymbolInfo *> ids;

    if(root == nullptr) return ids; // if nullptr return empty child list
    auto childs = root->getChilds();

    if(childs.size() == 4){
        ids = walkParameterListFindIds(childs[0]);
        auto type = walkTypeSpecifier(childs[2]);
        auto id = walkID(childs[3]);
        ids.push_back(new VariableSymbolInfo(id, type, "normal"));
    }
    else if(childs.size() == 2 && childs[0]->getTokenType() != "parameter_list"){
        auto type = walkTypeSpecifier(childs[0]);
        auto id = walkID(childs[1]);
        ids.push_back(new VariableSymbolInfo(id, type, "normal"));
    }
    
    return ids;
}

std::string TreeWalker::argumentListChild(std::vector<AST *> childs, AST **rootptr){
    if(childs.size() == 0){
        *rootptr = nullptr;
        return nullptr;
    }

    // if first node is not type specifier, then it is parameter list
    // so rootptr points to there and typespecifier node is kept in idx
    int idx = 0;
    *rootptr = nullptr;
    if(childs[0]->getTokenType() != "logic_expression"){
        *rootptr = childs[0];
        idx = 2;
    }

    // type specifier is found
    std::string type = getDataType(childs[idx]);

    // new SymbolAST is created and returned 
    return type;
}

std::vector<std::string> TreeWalker::walkArgumentList(AST *root){
    std::vector<std::string> ans;

    if(root->getChilds().size() != 1) return ans;

    root = root->getChilds()[0];

    if(root->getTokenType() != "arguments"){
        return ans;
    }

    while(root){
        // root->print(std::cout);

        auto childs = root->getChilds();
        auto t = argumentListChild(childs, &root);
        ans.push_back(t);

        // std::cout << t << " " << root << std::endl;
    }

    // reverse(ans.begin(), ans.end());
    return ans;
}

int TreeWalker::walkUnaryExpressionValue(AST* root){
    if(root->getTokenType() != "unary_expression") return 1;
    if(root->getChilds().size() != 1) return 2;

    auto factor = root->getChilds()[0];
    if(factor->getTokenType() != "factor") return 3;
    if(factor->getChilds().size() != 1) return 4;

    auto value = factor->getChilds()[0];
    if(value->getTokenType() != "symbol") return 5;
    auto symbol = dynamic_cast<SymbolAST*>(value);

    if(symbol == nullptr) return 6;
    auto text = symbol->getSymbol()->getName();
    int con_value = 7;
    if(symbol->getSymbol()->getType() == "CONST_INT"){
        con_value = std::stoi(text);
    }
    else if(symbol->getSymbol()->getType() == "CONST_FLOAT"){
        con_value = (int)std::stof(text);
    }
    return con_value;
}

std::vector<AST*> TreeWalker::processProgram(AST* root){
    if(!isNodeType(root, NodeType::PROGRAM)){
        showError(__LINE__);
        return std::vector<AST *>();
    }

    std::vector<AST *> ans;

    auto childs = root->getChilds();
    if(isNodeType(childs, {NodeType::PROGRAM, NodeType::UNIT})){
        ans = processProgram(childs[0]);
        auto childAst = processUnit(childs[1]);

        if(childAst != nullptr){
            ans.push_back(childAst);
        }
    }
    else if(isNodeType(childs, {NodeType::UNIT})){
        auto childAst = processUnit(childs[0]);

        if(childAst != nullptr){
            ans.push_back(childAst);
        }
    }
    else{
        showError(__LINE__);
    }

    return ans;
}

AST* TreeWalker::processUnit(AST* root){
    if(!isNodeType(root, NodeType::UNIT)){
        showError(__LINE__);
        return nullptr;
    }

    auto childs = root->getChilds();
    if(!isNodeType(childs, {NodeType::FUNC_DECL})){
        return childs[0];
    }else{
        return nullptr;
    }
}

AST* TreeWalker::processStart(AST * root){
    if(isNodeType(root, NodeType::START)){
        if(isNodeType(root->getChilds(), {NodeType::PROGRAM})){
            return root->getChilds()[0];
        }
    }

    showError(__LINE__);
    return nullptr;
}

std::vector<SymbolAST *> TreeWalker::processVarDeclaration(AST *root){
    if(!isNodeType(root, NodeType::VAR_DECL)){
        showError(__LINE__);
        return std::vector<SymbolAST *>();
    }

    auto childs = root->getChilds();
    if(isNodeType(childs, {NodeType::TYPE_SPECIFIER, NodeType::DECL_LIST, NodeType::SYMBOL})){
        std::string type = walkTypeSpecifier(childs[0]);
        auto symbols = walkDeclarationList(childs[1]);
        for(auto i: symbols){
            i->getSymbol()->setType(type);
        }
        return symbols;
    }
    else{
        showError(__LINE__);
        return std::vector<SymbolAST *>();
    }
}

ExpressionNode* TreeWalker::processUnaryExpression(AST * expression,  SymbolTable &symbolTable){
    auto childs = expression->getChilds();
    if(childs.size() == 2){
        auto symbol = dynamic_cast<SymbolAST *>(childs[0])->getSymbol();
        auto child = processExpression(childs[1], symbolTable);
        return new UnaryExpressionNode(child, symbol, "");       
    }
    else if(childs.size() == 1){
        return processExpression(childs[0], symbolTable);
    }
    else{
        showError(__LINE__);
        return nullptr;
    }
}

ExpressionNode* TreeWalker::processFactor(AST * expression, SymbolTable &symbolTable){
    auto childs = expression->getChilds();
    if(childs.size() == 1){ // factor -> variable | CONST_INT | CONST_FLOAT
        if(isNodeType(childs[0], NodeType::VARIABLE)){
            return processExpression(childs[0], symbolTable);
        }
        else{
            auto symbol = dynamic_cast<SymbolAST *>(childs[0])->getSymbol();
            return new TerminalExpressionNode(symbol, symbol->getName());
        }
    }
    else if(childs.size() == 2){ // factor -> variable INCOP | variable DECOP   
        auto child = processExpression(childs[0], symbolTable);
        auto symbol = dynamic_cast<SymbolAST *>(childs[1])->getSymbol();
        return new UnaryExpressionNode(child, symbol, "");
    }
    else if(childs.size() == 3){  // factor -> LPAREN expression RPAREN
        return processExpression(childs[1], symbolTable);
    }
    else if(childs.size() == 4){ // factor -> ID LPAREN argument_list RPAREN
        auto argumentList = dynamic_cast<TokenAST*>(childs[2])->getChilds();
        
        std::vector<ExpressionNode *> args;
        if(argumentList.size())
            args = processArgumentList(argumentList[0], symbolTable);
        
        auto symbol = dynamic_cast<SymbolAST *>(childs[0])->getSymbol();
        return new FunctionExpressionNode(symbol, args);
    }
    else{
        showError(__LINE__);
        return nullptr;
    }

}

/**
 * @brief handles all expression and returns an ExpressionNode* 
 * ExpressionNode* is root of the expression syntax tree.
 * 
 * @param expression  
 * @return ExpressionNode* 
 */
ExpressionNode* TreeWalker::processExpression(AST *expression, SymbolTable &symbolTable){
    auto childs = expression->getChilds();
    if(isNodeType(expression, NodeType::VARIABLE)){ // handles variable rules
        auto symbol = dynamic_cast<SymbolAST *>(childs[0])->getSymbol();
        // TODO: Handle array
        auto varSymbol = dynamic_cast<VariableSymbolInfo *>(symbolTable.lookup(symbol->getName()));
        if(varSymbol == nullptr){
            std::cerr << *symbol << std::endl;
            return new TerminalExpressionNode(symbol, symbol->getName());
        }
        else{
            return new TerminalExpressionNode(symbol, varSymbol->getAccessBy());
        }
    }
    else if(isNodeType(expression, NodeType::UNARY_EXP)){ //handles unary exp rules
        return processUnaryExpression(expression, symbolTable);
    }
    else if(isNodeType(expression, NodeType::FACTOR)){
        return processFactor(expression, symbolTable);
    }
    else if(childs.size() == 1){ // for 'expression -> expression' like rules
        return processExpression(childs[0], symbolTable);
    }
    else if(childs.size() == 3){ // for 'expression -> expression OP expression' like rules
        auto symbol = dynamic_cast<SymbolAST *>(childs[1])->getSymbol();
        auto left = processExpression(childs[0], symbolTable);
        auto right = processExpression(childs[2], symbolTable);

        return new BinaryExpressionNode(left, right, symbol, "");
    }
    else{
        showError(__LINE__);
        expression->print(std::cerr);
        return nullptr;
    }
}

TreeWalker::TreeWalker(/* args */)
{
}

TreeWalker::~TreeWalker()
{
}

std::vector<TokenAST*> TreeWalker::walkStatements(AST *root){
    if(root->getChilds().size() == 1){
        std::vector<TokenAST*> tokens;
        tokens.push_back(dynamic_cast<TokenAST*>(root->getChilds()[0]));
        return tokens;
    }else if(root->getChilds().size() == 2){
        auto tokens = walkStatements(root->getChilds()[0]);
        tokens.push_back(dynamic_cast<TokenAST*>(root->getChilds()[1]));
        return tokens;
    }
    else{
        std::vector<TokenAST*> tokens;
        return tokens;
    }
}

std::vector<TokenAST*> TreeWalker::walkCompundStatements(AST *root){
    std::vector<TokenAST*> statements;     
    if(root == nullptr){
        showError(__LINE__);
        return statements;
    }
    if(!isNodeType(root, NodeType::COMPOUND_STATEMENT)){
        showError(__LINE__);
        return statements;
    }

    // finding statements node
    TokenAST* stmnts;
    if(isNodeType(root->getChilds(), {NodeType::SYMBOL, NodeType::STATEMENTS, NodeType::SYMBOL})){
        stmnts = dynamic_cast<TokenAST*> (root->getChilds()[1]);
    }

    return walkStatements(stmnts);
}

 std::tuple<SymbolInfo, std::vector<SymbolInfo *>, std::vector<TokenAST *>>  TreeWalker::processFunction(AST* root){
    if(root == nullptr){
        showError(__LINE__);
        // return std::make_tuple(SymbolInfo(), std::vector<SymbolInfo*>(), std::vector<TokenAST*>());
    }
    if(!isNodeType(root, NodeType::FUNC_DEF)){
        showError(__LINE__);
        // return std::make_tuple(SymbolInfo(), std::vector<SymbolInfo*>(), std::vector<TokenAST*>());
    }

    std::vector<AST *> childs = root->getChilds();
    std::tuple<SymbolInfo, std::vector<SymbolInfo *>, std::vector<TokenAST *>> ans;

    SymbolInfo s(walkID(childs[1]), walkTypeSpecifier(childs[0]));
    auto paramList = walkParameterListFindIds(nullptr);
    std::vector<TokenAST *> statements;

    if(isNodeType(childs, {NodeType::TYPE_SPECIFIER, NodeType::SYMBOL, NodeType::SYMBOL, NodeType::PARAM_LIST, NodeType::SYMBOL, NodeType::COMPOUND_STATEMENT})){
        paramList = walkParameterListFindIds(childs[3]);
        statements = walkCompundStatements(childs[5]);
    }
    else if(isNodeType(childs, {NodeType::TYPE_SPECIFIER, NodeType::SYMBOL, NodeType::SYMBOL,  NodeType::SYMBOL, NodeType::COMPOUND_STATEMENT})){
        statements = walkCompundStatements(childs[4]);
    }
    else{
        showError(__LINE__);
    }

    return std::make_tuple(s, paramList, statements);
}