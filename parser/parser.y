%{
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include"lib/symbolTable.h"
#include "lib/symbolInfo.h"
#include "lib/ast.h"
#define YYSTYPE AST*

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern int yylineno;

ofstream logout("log.txt"), tokenout("token.txt");
// PrintUtil printUtil(tokenout, logout);
Printer printer(logout, true), noPrint(cout, false);
SymbolTable symbolTable(10, &printer), constTable(10, &noPrint);
SymbolInfo *curSymbol = nullptr;


void yyerror(char *s)
{
	//write your code
}

SymbolInfo int_symbol("int", "INT"), float_symbol("float", "FLOAT"),
		   void_symbol("void", "VOID"), lthird_symbol("[", "LTHIRD"),
		   rthird_symbol("]", "RTHIRD")
;

SymbolInfo* getSymbol(string name, string type){
	auto t = constTable.lookup(name);
	if(t == nullptr){
		SymbolInfo s(name, type);
		t = constTable.insert(s);
	}

	return t;
}


%}

// %union {
// 	class AST *ast;
// }


%token IF FOR DO INT FLOAT VOID SWITCH DEFAULT ELSE WHILE BREAK 
%token CHAR DOUBLE RETURN CASE CONTINUE MAIN
%token CONST_INT CONST_FLOAT CONST_CHAR 
%token ASSIGNOP NOT LPAREN RPAREN LTHIRD RTHIRD LCURL RCURL COMMA SEMICOLON
%token ADDOP MULOP INCOP DECOP RELOP LOGICOP BITOP ID PRINTLN

%start compound_statement

%%


// start : arguments
// 	{
// 		//write your code in this block in all the similar blocks below
// 	}
// 		: program
// 	;

// program : program unit 
// 	| unit
// 	;
	
// unit : var_declaration
//      | func_declaration
//      | func_definition
//      ;
     
// func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
// 		| type_specifier ID LPAREN RPAREN SEMICOLON
// 		;
		 
// func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
// 		| type_specifier ID LPAREN RPAREN compound_statement
//  		;				


// parameter_list  : parameter_list COMMA type_specifier ID
// 		| parameter_list COMMA type_specifier
//  		| type_specifier ID
// 		| type_specifier
//  		;

 		
compound_statement : LCURL statements RCURL
			{
				$$ = new AST(NodeType::COMPOUND_STATEMENT, "LCURL statement RCURL", yylineno);

				auto t = new AST(getSymbol("{", "LCURL"), yylineno);
				$$->addChild(t);

				$$->addChild($2);

				t = new AST(getSymbol("}", "RCURL"), yylineno);
				$$->addChild(t);

				logout << "compound_statement: LCURL statements RCURL" << endl;

				$$->print(cout);
			}
 		    | LCURL RCURL
			{
				$$ = new AST(NodeType::COMPOUND_STATEMENT, "LCURL RCURL", yylineno);

				auto t = new AST(getSymbol("{", "LCURL"), yylineno);
				$$->addChild(t);

				t = new AST(getSymbol("}", "RCURL"), yylineno);
				$$->addChild(t);	

				logout << "compound_statement : LCURL RCURL" << endl;	

				$$->print(cout);
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON 
		{	
			$$ = new AST(NodeType::VAR_DECL, "type_specifier declaration_list SEMICOLON", yylineno);
			$$->addChild($1);
			$$->addChild($2);

			auto t = new AST(getSymbol(";", "SEMICOLON"), yylineno);
			$$->addChild(t);

			logout << "var_declaration : type_specifier declaration_list SEMICOLON" << endl;
		}
 		 ;
 		 
type_specifier	: INT 
	{
		auto s = getSymbol("int", "INT");
		auto t = new AST(s, yylineno);
		$$ = new AST(NodeType::TYPE_SPECIFIER, "INT", yylineno);
		$$->addChild(t);

		logout << "type_specifier : INT" << endl;
	}
 		| FLOAT 
	{
		auto s = getSymbol("float", "FLOAT");
		auto t = new AST(s, yylineno);
		$$ = new AST(NodeType::TYPE_SPECIFIER, "FLOAT", yylineno);
		$$->addChild(t);

		logout << "type_specifier : FLOAT" << endl;
	}	
 		| VOID
	{
		auto s = getSymbol("void", "VOID");
		auto t = new AST(s, yylineno);
		$$ = new AST(NodeType::TYPE_SPECIFIER, "VOID", yylineno);
		$$->addChild(t);

		logout << "type_specifier : VOID" << endl;
	}
 		;
 		
declaration_list : declaration_list COMMA identifier
			{
				$$ = new AST(NodeType::DECL_LIST, "declaration_list COMMA ID", yylineno);
				$$->addChild($1);

				$$->addChild(new AST(getSymbol(",", "COMMA"), yylineno));
				$$->addChild($3);

				logout << "declaration_list : declaration_list COMMA identifier" << endl;
			}
 		  | declaration_list COMMA identifier LTHIRD int_const RTHIRD
		  {
			$$ = new AST(NodeType::DECL_LIST, "declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", yylineno);
			$$->addChild($1);

			$$->addChild(new AST(getSymbol(",", "COMMA"), yylineno));
			$$->addChild($3);

			$$->addChild(new AST(getSymbol("[", "LTHIRD"), yylineno));
			$$->addChild($5);
			$$->addChild(new AST(getSymbol("]", "RTHIRD"), yylineno));

 		  	logout << "declaration_list : declaration_list COMMA identifier LTHIRD int_const RTHIRD" << endl;
		  }
 		  | identifier 
		  {
			$$ = new AST(NodeType::DECL_LIST, "ID", yylineno);
			$$->addChild($1);

			logout << "declaration_list : identifier" << endl;
		  }
 		  | identifier LTHIRD int_const RTHIRD 
		  {
			$$ = new AST(NodeType::DECL_LIST, "ID LTHIRD CONST_INT RTHIRD", yylineno);
			$$->addChild($1);

			auto t = new AST(getSymbol("[", "LTHIRD"), yylineno);
			$$->addChild(t);

			$$->addChild($3);

			t = new AST(getSymbol("]", "RTHIRD"), yylineno);
			$$->addChild(t);

			logout << "declaration_list : identifier LTHIRD CONST_INT RTHIRD" << endl;
		  }
 		  ;

int_const : CONST_INT 
		{
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			$$ = new AST(t, yylineno);
			
		}		  

float_const : CONST_FLOAT 
		{
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			$$ = new AST(t, yylineno);
			
		}		

addop : ADDOP
		{
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			$$ = new AST(t, yylineno);	
		}  
logicop : LOGICOP
		{
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			$$ = new AST(t, yylineno);	
		}  

mulop : MULOP
		{
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			$$ = new AST(t, yylineno);	
		}  

relop : RELOP
		{
			auto t = getSymbol(curSymbol->getName(), curSymbol->getType());
			delete curSymbol;
			$$ = new AST(t, yylineno);	
		}  

identifier : ID
		{
			$$ = new AST(curSymbol, yylineno);
		}
statements : statement
		{
			$$ = new AST(NodeType::STATEMENTS, "statement", yylineno);
			$$->addChild($1);		

			logout << "statements : statement" << endl;
		}
	   | statements statement
	   {
			$$ = new AST(NodeType::STATEMENTS, "statements statement", yylineno);
			$$->addChild($1);
			$$->addChild($2);

			logout << "statements : statements statement" << endl;
	   }
	   ;
	   
statement : var_declaration
		{
			$$ = new AST(NodeType::STATEMENT, "var_declaration", yylineno);
			$$->addChild($1);

			logout << "statement : var_declaration" << endl;
		}
	  | expression_statement
		{
			$$ = new AST(NodeType::STATEMENT, "expression_statement", yylineno);
			$$->addChild($1);

			logout << "statement : expression_statement" << endl;
		}
	  ;
	  | compound_statement
	  {
			$$ = new AST(NodeType::STATEMENT, "compound_statement", yylineno);
			$$->addChild($1);

			logout << "statement : compound_statement" << endl;

	  }
	//   | FOR LPAREN expression_statement expression_statement expression RPAREN statement
	//   | IF LPAREN expression RPAREN statement
	//   | IF LPAREN expression RPAREN statement ELSE statement
	//   | WHILE LPAREN expression RPAREN statement
	//   | PRINTLN LPAREN ID RPAREN SEMICOLON
	//   | RETURN expression SEMICOLON
	//   ;
	  
expression_statement 	: SEMICOLON	
			{
				$$ = new AST(NodeType::EXPR_STMNT, "SEMICOLON", yylineno);
				
				auto t = new AST(getSymbol(";", "SEMICOLON"), yylineno);
				$$->addChild(t);

				logout << "expression_statement : SEMICOLON" << endl;
			}		
			| expression SEMICOLON 
			{
				$$ = new AST(NodeType::EXPR_STMNT, "SEMICOLON", yylineno);

				$$->addChild($1);
				
				auto t = new AST(getSymbol(";", "SEMICOLON"), yylineno);
				$$->addChild(t);

				logout << "expression_statement : expression SEMICOLON" << endl;
			}
			;
	  
variable : identifier 	
		{
			$$ = new AST(NodeType::VARIABLE, "ID", yylineno);
			$$->addChild($1);

			logout << "variable : identifier" << endl;
		}	
	 | identifier LTHIRD expression RTHIRD 
		{
			$$ = new AST(NodeType::VARIABLE, "identifier LTHIRD expression RTHIRD", yylineno);
			$$->addChild($1);

			auto t = new AST(getSymbol("[", "LTHIRD"), yylineno);
			$$->addChild(t);

			$$->addChild($3);

			t = new AST(getSymbol("]", "RTHIRD"), yylineno);
			$$->addChild(t);

			logout << "variable : identifier LTHIRD expression RTHIRD" << endl;
		}
	 ;
	 
expression : logic_expression	
		{
			$$ = new AST(NodeType::EXP, "logic_expression", yylineno);
			$$->addChild($1);

			logout << "expression : logic_expression" << endl;
		}
	   | variable ASSIGNOP logic_expression 	
	   {
			$$ = new AST(NodeType::EXP, "variable ASSIGNOP logic_expression", yylineno);
			$$->addChild($1);

			auto t = new AST(getSymbol("=", "ASSIGNOP"), yylineno);
			$$->addChild(t);

			$$->addChild($3);

			logout << "expression : variable ASSIGNOP logic_expression" << endl;
	   }
	   ;
			
logic_expression : rel_expression 	
		{
			$$ = new AST(NodeType::LOGIC_EXP, "rel_expression", yylineno);
			$$->addChild($1);

			logout << "logic_expression : rel_expression" << endl;
		}
		 | rel_expression logicop rel_expression
		{
			$$ = new AST(NodeType::LOGIC_EXP, "rel_expression LOGICOP rel_expression", yylineno);
			$$->addChild($1);
			$$->addChild($2);
			$$->addChild($3);

			logout << "logic_expression : rel_expression LOGICOP rel_expression" << endl;
		}
		 ;
			
rel_expression	: simple_expression 
		{
			$$ = new AST(NodeType::REL_EXP, "simple_expression", yylineno);
			$$->addChild($1);

			logout << "rel_expression : simple_expression" << endl;
		}
		| simple_expression relop simple_expression	
		{
			$$ = new AST(NodeType::REL_EXP, "simple_expression RELOP simple_expression", yylineno);
			$$->addChild($1);
			$$->addChild($2);
			$$->addChild($3);

			logout << "rel_expression : simple_expression RELOP simple_expression" << endl;
		}
		;
				
simple_expression : term 
		{
			$$ = new AST(NodeType::SIMPLE_EXP, "term", yylineno);
			$$->addChild($1);

			logout << "simple_expression : term" << endl;
		}
		  | simple_expression addop term 
		{
			$$ = new AST(NodeType::REL_EXP, "simple_expression ADDOP term", yylineno);
			$$->addChild($1);
			$$->addChild($2);
			$$->addChild($3);
			
			logout << "simple_expression : simple_expression ADDOP term" << endl;
		}

		  ;
					
term :	unary_expression
		{
			$$ = new AST(NodeType::TERM, "unary_expression", yylineno);
			$$->addChild($1);

			logout << "term : unary_expression" << endl;
		}
     |  term mulop unary_expression
		{
			$$ = new AST(NodeType::TERM, "term MULOP unary_expression", yylineno);
			$$->addChild($1);
			$$->addChild($2);
			$$->addChild($3);

			logout << "term : term MULOP unary_expression" << endl;
		}
     ;

unary_expression : addop unary_expression  
		{
			$$ = new AST(NodeType::UNARY_EXP, "ADDOP unary_expression", yylineno);
			$$->addChild($1);
			$$->addChild($2);

			logout << "unary_expression : ADDOP unary_expression" << endl;
		}
		 | NOT unary_expression 
		{
			$$ = new AST(NodeType::UNARY_EXP, "NOT unary_expression", yylineno);

			auto t = new AST(getSymbol("!", "NOT"), yylineno);
			$$->addChild(t);

			$$->addChild($2);

			logout << "NOT unary_expression" << endl;
		}
		 | factor 
		{
			$$ = new AST(NodeType::UNARY_EXP, "factor", yylineno);
			$$->addChild($1);

			logout << "unary_expression : factor" << endl;
		}
		 ;
	
factor	: variable 
		{
			$$ = new AST(NodeType::FACTOR, "variable", yylineno);
			$$->addChild($1);

			logout << "factor : variable" << endl;
		}
		
	| identifier LPAREN argument_list RPAREN
		{
			$$ = new AST(NodeType::FACTOR, "ID LPAREN argument_list RPAREN", yylineno);
			$$->addChild($1);

			auto t = new AST(getSymbol("(", "LPAREN"), yylineno);
			$$->addChild(t);

			$$->addChild($3);

			t = new AST(getSymbol(")", "RPAREN"), yylineno);
			$$->addChild(t);

			logout << "factor : ID LPAREN expression RPAREN" << endl;
		}
	| LPAREN expression RPAREN
		{
			$$ = new AST(NodeType::FACTOR, "LPAREN expression RPAREN", yylineno);

			auto t = new AST(getSymbol("(", "LPAREN"), yylineno);
			$$->addChild(t);

			$$->addChild($2);

			t = new AST(getSymbol(")", "RPAREN"), yylineno);
			$$->addChild(t);

			logout << "factor : LPAREN expression RPAREN" << endl;
		}
	| int_const
		{
			$$ = new AST(NodeType::FACTOR, "CONST_INT", yylineno);
			$$->addChild($1);

			logout << "factor : CONST_INT" << endl;
		}
	| float_const
		{
			$$ = new AST(NodeType::FACTOR, "CONST_FLOAT", yylineno);
			$$->addChild($1);

			logout << "factor : CONST_FLOAT" << endl;
		}
	| variable INCOP 
		{
			$$ = new AST(NodeType::FACTOR, "variable INCOP", yylineno);
			$$->addChild($1);

			auto t = new AST(getSymbol("++", "INCOP"), yylineno);
			$$->addChild(t);

			logout << "factor : variable INCOP" << endl;
		}

	| variable DECOP
		{
			$$ = new AST(NodeType::FACTOR, "variable DECOP", yylineno);
			$$->addChild($1);

			auto t = new AST(getSymbol("--", "DECOP"), yylineno);
			$$->addChild(t);

			logout << "factor : variable DECOP" << endl;
		}
	;
	
argument_list : arguments
		{
			$$ = new AST(NodeType::ARG_LIST, "arguments", yylineno);
			$$->addChild($1);

			logout << "argument_list : arguments" << endl;
		}
			| 
		{
			$$ = new AST(NodeType::ARG_LIST, "", yylineno);
			logout << "argument_list : " << endl;
		}
			  ;
	
arguments : arguments COMMA logic_expression
		{
			$$ = new AST(NodeType::ARGS, "arguments COMMA logic_expression", yylineno);
			$$->addChild($1);


			auto t = new AST(getSymbol(",", "COMMA"), yylineno);
			$$->addChild(t);

			$$->addChild($3);

			logout << "arguments : arguments COMMA logic_expression" << endl;
		}
	      | logic_expression
		{
			$$ = new AST(NodeType::ARGS, "logic_expression", yylineno);
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

	// auto fp2= fopen(argv[2],"w");
	// fclose(fp2);
	// auto fp3= fopen(argv[3],"w");
	// fclose(fp3);
	
	// fp2= fopen(argv[2],"a");
	// fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	

	// fclose(fp2);
	// fclose(fp3);
	fclose(fp);
	
	return 0;
}
