%{
#include<iostream>
#include<fstream>
#include<set>
#include "lib/symbolTable.h"
#include "lib/symbolInfo.h"
#include "lib/ast.h"
#include "lib/treeWalker.h"
#include "lib/printUtil.h"
#include "lib/codegen.h"

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern int yylineno;

ofstream logout("log.txt"), tokenout("token.txt"), errorout("error.txt"), codeout("code.asm");
ofstream treeout("parseTree.txt");
PrintUtil printUtil(tokenout, logout, errorout);
Printer printer(logout, false);
SymbolTable symbolTable(11, &printer);
TreeWalker treeWalker;

bool inFunction = false;

set<FunctionSymbolInfo *> funcDefined;

string errorString = "";

void yyerror(char *s)
{
}

std::string getDataType(AST *node){
	auto t = dynamic_cast<ExpressionAST *> (node);
	if(t != nullptr) return t->getDataType();
	
	return "";
}

SymbolInfo *getSymbol(AST *node){
	auto t = dynamic_cast<SymbolAST *>(node);
	if(t != nullptr){
		auto name = t->getSymbol()->getName();
		auto symbol = symbolTable.lookup(name);

		return symbol;
	}
	return nullptr;
}

bool isAssignopCorrect(string lhs, string rhs){
	return !(lhs == "INT" && rhs == "FLOAT");
}

string getAddopType(string lhs, string rhs){
	return (lhs == "FLOAT" || rhs == "FLOAT") ? "FLOAT" : "INT";
}

bool errorIfVoid(AST *exp){
	auto type = getDataType(exp);
	if(type == "VOID"){
		printUtil.printError("Void cannot be used in expression",  exp->getBeginLine());
		return true;
	}
	return false;
}

void handleFunctionDeclaration(AST* ts, AST* rid, vector<string> paramList){
	auto type = treeWalker.walkTypeSpecifier(ts);
	auto name = treeWalker.walkID(rid);

	auto id = new FunctionSymbolInfo(name, type, paramList);
	auto prev = symbolTable.lookup(name);

	if(prev != nullptr){
		if(prev->getType() == "FUNCTION"){
			auto t = dynamic_cast<FunctionSymbolInfo *> (prev);
			if(t->getReturnType() != type){
				printUtil.printError("Conflicting types for \'" + name + "\'" , yylineno);
			}
		}else{
			printUtil.printError("\'" + name + "\' redeclared as different kind of symbol", yylineno);
		}
	}
	else{
		symbolTable.insert(id);
	}
}

void handleFunctionDefination(AST* ts, AST* rid, vector<string> paramList){
	auto returnType = treeWalker.walkTypeSpecifier(ts);
	auto funcName = treeWalker.walkID(rid);
	auto prev = symbolTable.lookup(funcName);
	auto funcId = dynamic_cast<FunctionSymbolInfo *> (prev);
	auto newId = new FunctionSymbolInfo(funcName, returnType, paramList);

	if(prev != nullptr){
		if(funcDefined.count(funcId)){
			printUtil.printError("Redefination of function '" + funcName +"'", "",yylineno);
		}
		else if(funcId == nullptr){
			printUtil.printError("'" + funcName +"' redeclared as different kind of symbol" , "",yylineno);
		}
		else if(funcId->getReturnType() != returnType || !funcId->matchParam(paramList)){
			printUtil.printError("Conflicting types for \'" + funcName + "\'", rid->getBeginLine());
		}
		delete newId;
	}
	else{
		symbolTable.insert(newId);
		funcDefined.insert(newId);
	}

	symbolTable.enterScope();
	inFunction = true;
}

%}

%code requires {
	#include "lib/ast.h"
}
%define api.value.type { AST* }

%token IF FOR DO INT FLOAT VOID SWITCH DEFAULT ELSE WHILE BREAK 
%token CHAR DOUBLE RETURN CASE CONTINUE MAIN
%token CONST_INT CONST_FLOAT CONST_CHAR 
%token ASSIGNOP NOT LPAREN RPAREN LTHIRD RTHIRD LCURL RCURL COMMA SEMICOLON
%token ADDOP MULOP INCOP DECOP RELOP LOGICOP BITOP ID PRINTLN

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start start

%%


start : program
	{
		$$ = new TokenAST(NodeType::START, "program", yylineno);
		$$->addChild($1); 

		logout << "start : program" << endl;
		$$->print(treeout);

		Codegen codegen($$);
		codegen.generateCode();
		codegen.printCode(codeout);

		delete $$;

		logout << "Total Lines: " << yylineno << endl;
		logout << "Total Errors: " << printUtil.getErrorCount() << endl;
	}
	;

program : program unit 
		{
			$$ = new TokenAST(NodeType::PROGRAM, "program unit", yylineno);
			$$->addChild({$1, $2});

			logout << "program : program unit" << endl;
		}
	| unit
		{
			$$ = new TokenAST(NodeType::PROGRAM, "unit", yylineno);
			$$->addChild($1);

			logout << "program : unit" << endl;
		}
	;
	
unit : var_declaration
	{
        $$ = new TokenAST(NodeType::UNIT, "var_declaration", yylineno);
		$$->addChild($1);

		logout << "unit : var_declaration" << endl;
	}
     | func_declaration
	{
        $$ = new TokenAST(NodeType::UNIT, "func_declaration", yylineno);
		$$->addChild($1);
		
		logout << "unit : func_declaration" << endl;
	}
     | func_definition
	{
        $$ = new TokenAST(NodeType::UNIT, "func_definition", yylineno);
		$$->addChild($1);
		
		logout << "unit : func_definition" << endl;
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN
{
	handleFunctionDeclaration($1, $2, treeWalker.walkParameterList($4));
}
 SEMICOLON
{
	$$ = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
	$$->addChild({$1, $2, $3, $4, $5, $7});	

	logout << "func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON" << endl;
}
		
| type_specifier ID LPAREN RPAREN
{
	handleFunctionDeclaration($1, $2, vector<string> ());
} SEMICOLON
{
	$$ = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN RPAREN SEMICOLON", yylineno);
	$$->addChild({$1, $2, $3, $4, $6});	

	logout << "func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON" << endl;
}
;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN 
{
	handleFunctionDefination($1, $2, treeWalker.walkParameterList($4));

	auto params = treeWalker.walkParameterListFindIds($4);
	for(auto i: params){
		auto isInserted = symbolTable.insert(i);
		if(!isInserted){
			printUtil.printError("Redefinition of parameter \'" + i->getName() + "\'", $4->getBeginLine());
			delete i;
		}
		
	}
}
compound_statement
{
	$$ = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN parameter_list RPAREN compound_statement", yylineno);
	$$->addChild({$1, $2, $3, $4, $5, $7});
	
	logout << "func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement" << endl;
}
| type_specifier ID LPAREN RPAREN 
{
	handleFunctionDefination($1, $2, vector<string>());
}
compound_statement
{
	$$ = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN RPAREN compound_statement", yylineno);
	$$->addChild({$1, $2, $3, $4, $6});

	logout << "func_definition : type_specifier ID LPAREN RPAREN compound_statement" << endl;
}
;				


parameter_list  : parameter_list COMMA type_specifier ID
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "parameter_list COMMA type_specifier ID", yylineno);
				$$->addChild({$1, $2, $3, $4});

				logout << "parameter_list : parameter_list COMMA type_specifier ID" << endl;
			}
		| parameter_list COMMA type_specifier
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "parameter_list COMMA type_specifier", yylineno);
				$$->addChild({$1, $2, $3});

				logout << "parameter_list: parameter_list COMMA type_specifier" << endl;
			}
 		| type_specifier ID
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID", yylineno);
				$$->addChild({$1, $2});

				logout << "parameter_list : type_specifier ID" << endl;
			}
		| type_specifier 
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "type_specifier", yylineno);
				$$->addChild($1);

				logout << "parameter_list : type_specifier" << endl;
			}
		| parameter_list error
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "parameter_list error", yylineno);

				delete $2;
				delete $1;

				yyclearin;
				
				printUtil.printError("Syntax error at parameter list of function definition", "", yylineno);
			}
 		;

 		
compound_statement : LCURL 
{
	if(!inFunction)
		symbolTable.enterScope();
	inFunction = false;
} 
statements RCURL
{
	$$ = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL statement RCURL", yylineno);
	$$->addChild({$1, $3, $4});

	logout << "compound_statement: LCURL statements RCURL" << endl;

	logout << symbolTable;
	symbolTable.exitScope();

}
| LCURL
{
	if(!inFunction)
		symbolTable.enterScope();
	inFunction = false;
}RCURL
{
	$$ = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL RCURL", yylineno);
	$$->addChild({$1, $3});

	logout << "compound_statement : LCURL RCURL" << endl;	

	logout << symbolTable;
	symbolTable.exitScope();
}
;

 		    
var_declaration : type_specifier declaration_list SEMICOLON 
		{	
			$$ = new TokenAST(NodeType::VAR_DECL, "type_specifier declaration_list SEMICOLON", yylineno);
			$$->addChild({$1, $2, $3});

			auto symbols = treeWalker.walkDeclarationList($2);
			auto type = treeWalker.walkTypeSpecifier($1);

			if(type == "VOID"){
				for(auto symbol: symbols){
					printUtil.printError("Variable or field \'" + symbol->getSymbol()->getName()  + "\' declared void", yylineno);
					delete symbol;
				}

				symbols.clear();
			}

			for(int ii = symbols.size()-1; ii >= 0; ii--){
				auto symbol = symbols[ii];

				auto i = symbol->getSymbol();
        		i->setType(type);
				auto isInserted = symbolTable.insert(i);

				if(!isInserted){
					printUtil.printError("Conflicting types for\'" + i->getName() + "\'", symbol->getBeginLine());
					delete i;
				}

				symbol->setSymbol(nullptr);
				delete symbol;
			}

			// cout << symbolTable << endl;

			logout << "var_declaration : type_specifier declaration_list SEMICOLON" << endl;
		}
 		 ;
 		 
type_specifier	: INT 
	{
		$$ = new TokenAST(NodeType::TYPE_SPECIFIER, "INT", yylineno);
		$$->addChild($1);

		logout << "type_specifier : INT" << endl;
	}
 		| FLOAT 
	{
		$$ = new TokenAST(NodeType::TYPE_SPECIFIER, "FLOAT", yylineno);
		$$->addChild($1);

		logout << "type_specifier : FLOAT" << endl;
	}	
 		| VOID
	{
		$$ = new TokenAST(NodeType::TYPE_SPECIFIER, "VOID", yylineno);
		$$->addChild($1);

		logout << "type_specifier : VOID" << endl;
	}
 		;
 		
declaration_list : declaration_list COMMA ID
			{
				$$ = new TokenAST(NodeType::DECL_LIST, "declaration_list COMMA ID", yylineno);
				$$->addChild({$1, $2, $3});

				logout << "declaration_list : declaration_list COMMA ID" << endl;
			}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
		  {
			$$ = new TokenAST(NodeType::DECL_LIST, "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE", yylineno);
			$$->addChild({$1, $2, $3, $4, $5, $6});

 		  	logout << "declaration_list : declaration_list COMMA ID LSQUARE CONST_INT RSQUARE" << endl;
		  }
 		  | ID 
		  {
			$$ = new TokenAST(NodeType::DECL_LIST, "ID", yylineno);
			$$->addChild($1);

			logout << "declaration_list : ID" << endl;
		  }
 		  | ID LTHIRD CONST_INT RTHIRD 
		  {
			$$ = new TokenAST(NodeType::DECL_LIST, "ID LSQUARE CONST_INT RSQUARE", yylineno);
			$$->addChild({$1, $2, $3, $4});

			logout << "declaration_list : ID LSQUARE CONST_INT RSQUARE" << endl;
		  }
		  | declaration_list error
		  {
			$$ =  new TokenAST(NodeType::DECL_LIST, "error", yylineno);
			yyclearin;

			delete $2;
			delete $1;

			printUtil.printError("Syntax error at declaration list of variable declaration", "", yylineno);
		  }
 		  ;

statements : statement
		{
			$$ = new TokenAST(NodeType::STATEMENTS, "statement", yylineno);
			$$->addChild($1);		

			logout << "statements : statement" << endl;
		}
	   | statements statement
	   {
			$$ = new TokenAST(NodeType::STATEMENTS, "statements statement", yylineno);
			$$->addChild({$1, $2});

			logout << "statements : statements statement" << endl;
	   }
	   ;
	   
statement : var_declaration
		{
			$$ = new TokenAST(NodeType::STATEMENT, "var_declaration", yylineno);
			$$->addChild($1);

			logout << "statement : var_declaration" << endl;
		}
		| func_declaration
		{
			$$ = new TokenAST(NodeType::STATEMENT, "error", yylineno);

			printUtil.printError("Nested function declaration is not allowed", yylineno);
		}
		| func_definition
		{
			$$ = new TokenAST(NodeType::STATEMENT, "error", yylineno);

			printUtil.printError("Nested function definition is not allowed", yylineno);
		}

	  | expression_statement
		{
			$$ = new TokenAST(NodeType::STATEMENT, "expression_statement", yylineno);
			$$->addChild($1);

			logout << "statement : expression_statement" << endl;
		}
	  | compound_statement
	  {
			$$ = new TokenAST(NodeType::STATEMENT, "compound_statement", yylineno);
			$$->addChild($1);

			logout << "statement : compound_statement" << endl;

	  }
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "FOR LPAREN expression_statement expression_statement expression RPAREN statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5, $6, $7});

			errorIfVoid($3->getChilds()[0]);
			errorIfVoid($4->getChilds()[0]);
			errorIfVoid($5);

			logout << "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement" << endl;
		}
	  | IF LPAREN expression RPAREN statement	%prec LOWER_THAN_ELSE 
		{
			$$ = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5});

			errorIfVoid($3);

			logout << "statement : IF LPAREN expression RPAREN statement" << endl;
		}
	  | IF LPAREN expression RPAREN statement ELSE statement
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement ELSE statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5, $6, $7});

			errorIfVoid($3);

			logout << "statement : IF LPAREN expression RPAREN statement ELSE statement" << endl;
		}
	  ;
	  | WHILE LPAREN expression RPAREN statement
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "WHILE LPAREN expression RPAREN statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5});

			errorIfVoid($3);

			logout << "statement : WHILE LPAREN expression RPAREN statement" << endl;
		}
	  | PRINTLN LPAREN variable RPAREN SEMICOLON
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "PRINTLN LPAREN ID RPAREN SEMICOLON", yylineno);
			$$->addChild({$1, $2, $3, $4, $5});

			logout << "statement: PRINTLN LPAREN ID RPAREN SEMICOLON";
		}
	  | RETURN expression SEMICOLON
		{
			$$ = new TokenAST(NodeType::STATEMENT, "RETURN expression SEMICOLON", yylineno);
			$$->addChild({$1, $2, $3});

			errorIfVoid($2);
			
			logout << "statement : RETURN expression SEMICOLON" << endl;
		}	
	  ;
	  
expression_statement 	: SEMICOLON	
			{
				$$ = new TokenAST(NodeType::EXPR_STMNT, "SEMICOLON", yylineno);
				$$->addChild($1);

				logout << "expression_statement : SEMICOLON" << endl;
			}		
			| expression SEMICOLON 
			{
				$$ = new TokenAST(NodeType::EXPR_STMNT, "expression SEMICOLON", yylineno);
				$$->addChild({$1, $2});


				logout << "expression_statement : expression SEMICOLON" << endl;
			}
			| error SEMICOLON
		{
			$$ = new TokenAST(NodeType::EXPR_STMNT, "expression SEMICOLON", yylineno);
			delete $1;
			$1 = new TokenAST(NodeType::EXP, "error", yylineno);
			$$->addChild({$1, $2});


			printUtil.printError("Syntax error at expression of expression statement", yylineno);
		}
			;
	  
variable : ID 	
		{
			auto symbol = getSymbol($1);
			string type = "INT";
			if(symbol == nullptr){
				printUtil.printError("Undeclared variable \'" + treeWalker.walkID($1) + "\'", yylineno);
			}else if(symbol->getType() == "FUNCTION"){
				printUtil.printError("Function cannot used as variable", yylineno);
			}else if(dynamic_cast<VariableSymbolInfo *>(symbol) != nullptr){
				// printUtil.printError("array used as normal variable", yylineno);
				printUtil.printError("\'" + symbol->getName() + "\' is an array", yylineno);
				type = symbol->getType();
			}else{
				type = symbol->getType();
			}
			
			$$ = new ExpressionAST(NodeType::VARIABLE, "ID", type, yylineno);
			$$->addChild($1);

			logout << "variable : ID" << endl;
		}	
	 | ID LTHIRD expression RTHIRD 
		{
			auto symbol = getSymbol($1);
			string type = "INT";
			if(symbol == nullptr){
				printUtil.printError("Undeclared variable \'" + treeWalker.walkID($1) + "\'", yylineno);
			}else if(symbol->getType() == "FUNCTION"){
				printUtil.printError("function cannot used as variable", "", yylineno);
			}else if( dynamic_cast<VariableSymbolInfo *>(symbol) == nullptr){
				printUtil.printError("\'" + symbol->getName() + "\' is not an array", yylineno);
				type = symbol->getType();
			}else{
				type = symbol->getType();
			}

			if(getDataType($3) != "INT"){
				printUtil.printError("Array subscript is not an integer", yylineno);
			}
			
			$$ = new ExpressionAST(NodeType::VARIABLE, "ID LSQUARE expression RSQUARE", type, yylineno);
			$$->addChild({$1, $2, $3, $4});

			logout << "variable : ID LSQUARE expression RSQUARE" << endl;
		}
	 ;
	 
expression : logic_expression	
		{
			$$ = new ExpressionAST(NodeType::EXP, "logic_expression", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "expression : logic_expression" << endl;
		}
	   | variable ASSIGNOP logic_expression 	
	   {
			if(getDataType($3) == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
			}else if(!isAssignopCorrect(getDataType($1), getDataType($3))){
				printUtil.printError("Warning: possible loss of data in assignment of FLOAT to INT", yylineno);
			}

			$$ = new ExpressionAST(NodeType::EXP, "variable ASSIGNOP logic_expression", getDataType($1), yylineno);
			$$->addChild({$1, $2, $3});

			logout << "expression : variable ASSIGNOP logic_expression" << endl;
	   }
	   ;
			
logic_expression : rel_expression 	
		{
			$$ = new ExpressionAST(NodeType::LOGIC_EXP, "rel_expression", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "logic_expression : rel_expression" << endl;
		}
		 | rel_expression LOGICOP rel_expression
		{
			auto lhsType = getDataType($1);
			auto rhsType = getDataType($3);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression",  yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			$$ = new ExpressionAST(NodeType::LOGIC_EXP, "rel_expression LOGICOP rel_expression", "INT", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "logic_expression : rel_expression LOGICOP rel_expression" << endl;
		}
		 ;
			
rel_expression	: simple_expression 
		{
			$$ = new ExpressionAST(NodeType::REL_EXP, "simple_expression", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "rel_expression : simple_expression" << endl;
		}
		| simple_expression RELOP simple_expression	
		{
			auto lhsType = getDataType($1);
			auto rhsType = getDataType($3);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			$$ = new ExpressionAST(NodeType::REL_EXP, "simple_expression RELOP simple_expression", "INT", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "rel_expression : simple_expression RELOP simple_expression" << endl;
		}
		;
				
simple_expression : term 
		{
			$$ = new ExpressionAST(NodeType::SIMPLE_EXP, "term", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "simple_expression : term" << endl;
		}
		  | simple_expression ADDOP term 
		{
			auto lhsType = getDataType($1);
			auto rhsType = getDataType($3);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			auto type = getAddopType(lhsType, rhsType);

			$$ = new ExpressionAST(NodeType::SIMPLE_EXP, "simple_expression ADDOP term", type, yylineno);
			$$->addChild({$1, $2, $3});
			
			logout << "simple_expression : simple_expression ADDOP term" << endl;
		}

		  ;
					
term :	unary_expression
		{
			$$ = new ExpressionAST(NodeType::TERM, "unary_expression", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "term : unary_expression" << endl;
		}
     |  term MULOP unary_expression
		{
			auto lhsType = getDataType($1);
			auto rhsType = getDataType($3);

			if(lhsType == "VOID" || rhsType == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				if(lhsType == "VOID") lhsType = "INT";
				if(rhsType == "VOID") rhsType = "INT";
			}

			auto type = getAddopType(lhsType, rhsType);
			auto opType = treeWalker.walkID($2);
			if(opType == "%"){
				if(lhsType != "INT" || rhsType != "INT"){
					printUtil.printError("Operands of modulus must be integers", yylineno);
				}
				type = "INT";
			}

			int value = treeWalker.walkUnaryExpressionValue($3);
			if(opType == "%" || opType == "/"){
				if(value == 0){
					printUtil.printError("Warning: division by zero i=0f=1Const=0", yylineno);
				}				
			}

			$$ = new ExpressionAST(NodeType::TERM, "term MULOP unary_expression", type, yylineno);
			$$->addChild({$1, $2, $3});

			logout << "term : term MULOP unary_expression" << endl;
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			auto type = getDataType($2);
			if(type == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				type = "INT";
			}

			$$ = new ExpressionAST(NodeType::UNARY_EXP, "ADDOP unary_expression", type, yylineno);
			$$->addChild({$1, $2});

			logout << "unary_expression : ADDOP unary_expression" << endl;
		}
		 | NOT unary_expression 
		{
			auto type = getDataType($2);
			if(type == "VOID"){
				printUtil.printError("Void cannot be used in expression", yylineno);
				type = "INT";
			}

			$$ = new ExpressionAST(NodeType::UNARY_EXP, "NOT unary_expression", "INT", yylineno);
			$$->addChild({$1, $2});

			logout << "unary_expression : NOT unary_expression" << endl;
		}
		 | factor 
		{
			$$ = new ExpressionAST(NodeType::UNARY_EXP, "factor", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "unary_expression : factor" << endl;
		}
		 ;
	
factor	: variable 
		{
			$$ = new ExpressionAST(NodeType::FACTOR, "variable", getDataType($1), yylineno);
			$$->addChild($1);

			logout << "factor : variable" << endl;
		}
		
	| ID LPAREN argument_list RPAREN
		{
			auto name = treeWalker.walkID($1);
			auto symbol = symbolTable.lookup(name);
			auto arguments = treeWalker.walkArgumentList($3);
			string type = "INT";

			if(symbol == nullptr){
				printUtil.printError("Undeclared function '" + name + "'", yylineno);
			}else if(symbol->getType() != "FUNCTION"){
				printUtil.printError("'" + name + "'' is not a function", "", yylineno);
			}else{
				auto functionSymbol = dynamic_cast<FunctionSymbolInfo *>(symbol);

				vector<int> errors;	
				if(!functionSymbol->matchParam(arguments, errors)){
					if(errors.size() == 0){
						if(functionSymbol->getNoParam() > arguments.size()){
							printUtil.printError("Too few arguments to function \'" + name + "\'", yylineno);
						}
						else{
							printUtil.printError("Too many arguments to function \'" + name + "\'", yylineno);
						}
					}
					else{
						for(auto i : errors){
							printUtil.printError(string("Type mismatch for argument ") + to_string(i) + string(" of \'") + name + "\'", yylineno);
						}
					}
				}else{
					type = functionSymbol->getReturnType();
				}
			}

			$$ = new ExpressionAST(NodeType::FACTOR, "ID LPAREN argument_list RPAREN", type, yylineno);
			$$->addChild({$1, $2, $3, $4});

			logout << "factor : ID LPAREN argument_list RPAREN" << endl;
		}
	| LPAREN expression RPAREN
		{
			$$ = new ExpressionAST(NodeType::FACTOR, "LPAREN expression RPAREN", getDataType($2), yylineno);
			$$->addChild({$1, $2, $3});

			logout << "factor : LPAREN expression RPAREN" << endl;
		}
	| CONST_INT
		{
			$$ = new ExpressionAST(NodeType::FACTOR, "CONST_INT", "INT", yylineno);
			$$->addChild($1);

			logout << "factor : CONST_INT" << endl;
		}
	| CONST_FLOAT
		{
			$$ = new ExpressionAST(NodeType::FACTOR, "CONST_FLOAT", "FLOAT", yylineno);
			$$->addChild($1);

			logout << "factor : CONST_FLOAT" << endl;
		}
	| variable INCOP 
		{
			auto type = getDataType($1);
			if(type == "VOID"){
				printUtil.printError("void function cannot be used in expression", "", yylineno);
				type = "INT";
			}

			$$ = new ExpressionAST(NodeType::FACTOR, "variable INCOP", type, yylineno);
			$$->addChild({$1, $2});

			logout << "factor : variable INCOP" << endl;
		}

	| variable DECOP
		{
			auto type = getDataType($1);
			if(type == "VOID"){
				printUtil.printError("void function cannot be used in expression", "", yylineno);
				type = "INT";
			}

			$$ = new ExpressionAST(NodeType::FACTOR, "variable DECOP", type, yylineno);
			$$->addChild({$1, $2});

			logout << "factor : variable DECOP" << endl;
		}
	;
	
argument_list : arguments
		{
			$$ = new TokenAST(NodeType::ARG_LIST, "arguments", yylineno);
			$$->addChild($1);

			logout << "argument_list : arguments" << endl;
		}
			| 
		{
			$$ = new TokenAST(NodeType::ARG_LIST, "", yylineno);
			logout << "argument_list : " << endl;
		}
			  ;
	
arguments : arguments COMMA logic_expression
		{
			$$ = new TokenAST(NodeType::ARGS, "arguments COMMA logic_expression", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "arguments : arguments COMMA logic_expression" << endl;
		}
	      | logic_expression
		{
			$$ = new TokenAST(NodeType::ARGS, "logic_expression", yylineno);
			$$->addChild($1);

			logout << "arguments : logic_expression" << endl;
		}
	      ;
 
%%
int main(int argc,char *argv[])
{
	auto fp = fopen(argv[1], "r");
	if(fp==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}

	yyin=fp;
	yyparse();
	
	fclose(fp);
	
	return 0;
}

