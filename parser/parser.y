%{
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include"lib/symbolTable.h"
#include "lib/symbolInfo.h"
#include "lib/ast.h"
#include "lib/treeWalker.h"

using namespace std;

int yyparse(void);
int yylex(void);

extern FILE *yyin;
extern int yylineno;

ofstream logout("log.txt"), tokenout("token.txt");
// PrintUtil printUtil(tokenout, logout);
Printer printer(logout, true);
SymbolTable symbolTable(10, &printer);
TreeWalker treeWalker;


void yyerror(char *s)
{
	//write your code
}

%}

// %union {
// 	class AST *ast;
// }

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
		$$->print(cout);
		delete $$;
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
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
			{
				$$ = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
				$$->addChild({$1, $2, $3, $4, $5, $6});		

				logout << "func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON" << endl;
			}
		| type_specifier ID LPAREN RPAREN SEMICOLON
			{
				$$ = new TokenAST(NodeType::FUNC_DECL, "type_specifier ID LPAREN RPAREN SEMICOLON", yylineno);
				$$->addChild({$1, $2, $3, $4, $5});

				logout << "func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON" << endl;
			}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement
			{
				$$ = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN parameter_list RPAREN compound_statement", yylineno);
				$$->addChild({$1, $2, $3, $4, $5, $6});		

				logout << "func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement" << endl;
			}
		| type_specifier ID LPAREN RPAREN compound_statement
			{
				$$ = new TokenAST(NodeType::FUNC_DEF, "type_specifier ID LPAREN RPAREN compound_statement", yylineno);
				$$->addChild({$1, $2, $3, $4, $5});

				logout << "func_definition: type_specifier ID LPAREN RPAREN compound_statement" << endl;
			}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
				$$->addChild({$1, $2, $3, $4});

				logout << "parameter_list : parameter_list COMMA type_specifier ID" << endl;
			}
		| parameter_list COMMA type_specifier
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
				$$->addChild({$1, $2, $3});

				logout << "parameter_list: parameter_list COMMA type_specifier" << endl;
			}
 		| type_specifier ID
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", yylineno);
				$$->addChild({$1, $2});

				logout << "parameter_list : type_specifier ID" << endl;
			}
		| type_specifier
			{
				$$ = new TokenAST(NodeType::PARAM_LIST, "type_specifier", yylineno);
				$$->addChild($1);

				logout << "parameter_list : type_specifier" << endl;
			}
 		;

 		
compound_statement : LCURL statements RCURL
			{
				$$ = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL statement RCURL", yylineno);
				$$->addChild({$1, $2, $3});

				logout << "compound_statement: LCURL statements RCURL" << endl;

			}
 		    | LCURL RCURL
			{
				$$ = new TokenAST(NodeType::COMPOUND_STATEMENT, "LCURL RCURL", yylineno);
				$$->addChild({$1, $2});

				logout << "compound_statement : LCURL RCURL" << endl;	

			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON 
		{	
			$$ = new TokenAST(NodeType::VAR_DECL, "type_specifier declaration_list SEMICOLON", yylineno);
			$$->addChild({$1, $2, $3});

			auto symbols = treeWalker.walkDeclarationList($2);
			auto type = treeWalker.walkTypeSpecifier($1);

			for(auto i: symbols){
        		i->setType(type + i->getType());
				symbolTable.insert(i);
			}

			cout << symbolTable << endl;

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

 		  	logout << "declaration_list : declaration_list COMMA ID LSQUARE int_const RSQUARE" << endl;
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

			logout << "statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement" << endl;
		}
	  | IF LPAREN expression RPAREN statement	%prec LOWER_THAN_ELSE 
		{
			$$ = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5});

			logout << "statement : IF LPAREN expression RPAREN statement" << endl;
		}
	  | IF LPAREN expression RPAREN statement ELSE statement
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "IF LPAREN expression RPAREN statement ELSE statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5, $6, $7});

			logout << "statement : IF LPAREN expression RPAREN statement ELSE statement" << endl;
		}
	  ;
	  | WHILE LPAREN expression RPAREN statement
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "WHILE LPAREN expression RPAREN statement", yylineno);
			$$->addChild({$1, $2, $3, $4, $5});

			logout << "statement : WHILE LPAREN expression RPAREN statement" << endl;
		}
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  	{
			$$ = new TokenAST(NodeType::STATEMENT, "PRINTLN LPAREN ID RPAREN SEMICOLON", yylineno);
			$$->addChild({$1, $2, $3, $4, $5});

			logout << "statement: PRINTLN LPAREN ID RPAREN SEMICOLON";
		}
	  | RETURN expression SEMICOLON
		{
			$$ = new TokenAST(NodeType::STATEMENT, "RETURN expression SEMICOLON", yylineno);
			$$->addChild({$1, $2, $3});
			
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
			;
	  
variable : ID 	
		{
			$$ = new TokenAST(NodeType::VARIABLE, "ID", yylineno);
			$$->addChild($1);

			logout << "variable : ID" << endl;
		}	
	 | ID LTHIRD expression RTHIRD 
		{
			$$ = new TokenAST(NodeType::VARIABLE, "ID LSQUARE expression RSQUARE", yylineno);
			$$->addChild({$1, $2, $3, $4});

			logout << "variable : ID LSQUARE expression RSQUARE" << endl;
		}
	 ;
	 
expression : logic_expression	
		{
			$$ = new TokenAST(NodeType::EXP, "logic_expression", yylineno);
			$$->addChild($1);

			logout << "expression : logic_expression" << endl;
		}
	   | variable ASSIGNOP logic_expression 	
	   {
			$$ = new TokenAST(NodeType::EXP, "variable ASSIGNOP logic_expression", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "expression : variable ASSIGNOP logic_expression" << endl;
	   }
	   ;
			
logic_expression : rel_expression 	
		{
			$$ = new TokenAST(NodeType::LOGIC_EXP, "rel_expression", yylineno);
			$$->addChild($1);

			logout << "logic_expression : rel_expression" << endl;
		}
		 | rel_expression LOGICOP rel_expression
		{
			$$ = new TokenAST(NodeType::LOGIC_EXP, "rel_expression LOGICOP rel_expression", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "logic_expression : rel_expression LOGICOP rel_expression" << endl;
		}
		 ;
			
rel_expression	: simple_expression 
		{
			$$ = new TokenAST(NodeType::REL_EXP, "simple_expression", yylineno);
			$$->addChild($1);

			logout << "rel_expression : simple_expression" << endl;
		}
		| simple_expression RELOP simple_expression	
		{
			$$ = new TokenAST(NodeType::REL_EXP, "simple_expression RELOP simple_expression", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "rel_expression : simple_expression RELOP simple_expression" << endl;
		}
		;
				
simple_expression : term 
		{
			$$ = new TokenAST(NodeType::SIMPLE_EXP, "term", yylineno);
			$$->addChild($1);

			logout << "simple_expression : term" << endl;
		}
		  | simple_expression ADDOP term 
		{
			$$ = new TokenAST(NodeType::SIMPLE_EXP, "simple_expression ADDOP term", yylineno);
			$$->addChild({$1, $2, $3});
			
			logout << "simple_expression : simple_expression ADDOP term" << endl;
		}

		  ;
					
term :	unary_expression
		{
			$$ = new TokenAST(NodeType::TERM, "unary_expression", yylineno);
			$$->addChild($1);

			logout << "term : unary_expression" << endl;
		}
     |  term MULOP unary_expression
		{
			$$ = new TokenAST(NodeType::TERM, "term MULOP unary_expression", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "term : term MULOP unary_expression" << endl;
		}
     ;

unary_expression : ADDOP unary_expression  
		{
			$$ = new TokenAST(NodeType::UNARY_EXP, "ADDOP unary_expression", yylineno);
			$$->addChild({$1, $2});

			logout << "unary_expression : ADDOP unary_expression" << endl;
		}
		 | NOT unary_expression 
		{
			$$ = new TokenAST(NodeType::UNARY_EXP, "NOT unary_expression", yylineno);
			$$->addChild({$1, $2});

			logout << "NOT unary_expression" << endl;
		}
		 | factor 
		{
			$$ = new TokenAST(NodeType::UNARY_EXP, "factor", yylineno);
			$$->addChild($1);

			logout << "unary_expression : factor" << endl;
		}
		 ;
	
factor	: variable 
		{
			$$ = new TokenAST(NodeType::FACTOR, "variable", yylineno);
			$$->addChild($1);

			logout << "factor : variable" << endl;
		}
		
	| ID LPAREN argument_list RPAREN
		{
			$$ = new TokenAST(NodeType::FACTOR, "ID LPAREN argument_list RPAREN", yylineno);
			$$->addChild({$1, $2, $3, $4});

			logout << "factor : ID LPAREN expression RPAREN" << endl;
		}
	| LPAREN expression RPAREN
		{
			$$ = new TokenAST(NodeType::FACTOR, "LPAREN expression RPAREN", yylineno);
			$$->addChild({$1, $2, $3});

			logout << "factor : LPAREN expression RPAREN" << endl;
		}
	| CONST_INT
		{
			$$ = new TokenAST(NodeType::FACTOR, "CONST_INT", yylineno);
			$$->addChild($1);

			logout << "factor : CONST_INT" << endl;
		}
	| CONST_FLOAT
		{
			$$ = new TokenAST(NodeType::FACTOR, "CONST_FLOAT", yylineno);
			$$->addChild($1);

			logout << "factor : CONST_FLOAT" << endl;
		}
	| variable INCOP 
		{
			$$ = new TokenAST(NodeType::FACTOR, "variable INCOP", yylineno);
			$$->addChild({$1, $2});

			logout << "factor : variable INCOP" << endl;
		}

	| variable DECOP
		{
			$$ = new TokenAST(NodeType::FACTOR, "variable DECOP", yylineno);
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

