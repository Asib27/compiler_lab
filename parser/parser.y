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
Printer printer(logout, true);
SymbolTable symbolTable(10, &printer);
SymbolInfo *curSymbol = nullptr;


void yyerror(char *s)
{
	//write your code
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

 		
// compound_statement : LCURL statements RCURL
//  		    | LCURL RCURL
//  		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON 
		{	
			cout << "var_declaration found" << endl;
			$2->print(cout);
		}
 		 ;
 		 
type_specifier	: INT {cout << "int found" << endl;}
 		| FLOAT {cout << "float found" << endl;}
 		| VOID {cout << "void found" << endl;}
 		;
 		
declaration_list : declaration_list COMMA ID
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
 		  | ID 
		  {
			cout << "id: " << *curSymbol << " found" << endl;
		  	$$ = new AST(NodeType::VARIABLE,curSymbol,yylineno);
		  }
 		  | ID LTHIRD CONST_INT RTHIRD {cout << "array declaration" << endl;}
 		  ;
 		  
// statements : statement
// 	   | statements statement
// 	   ;
	   
// statement : var_declaration
// 	  | expression_statement
// 	  | compound_statement
// 	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
// 	  | IF LPAREN expression RPAREN statement
// 	  | IF LPAREN expression RPAREN statement ELSE statement
// 	  | WHILE LPAREN expression RPAREN statement
// 	  | PRINTLN LPAREN ID RPAREN SEMICOLON
// 	  | RETURN expression SEMICOLON
// 	  ;
	  
// expression_statement 	: SEMICOLON			
// 			| expression SEMICOLON 
// 			;
	  
// variable : ID 	{cout << "found id" << curSymbol << " " << *curSymbol << endl;}	
// 	 | ID LTHIRD expression RTHIRD 
// 	 ;
	 
// expression : logic_expression	
// 	   | variable ASSIGNOP logic_expression 	
// 	   ;
			
// logic_expression : rel_expression 	
// 		 | rel_expression LOGICOP rel_expression 	
// 		 ;
			
// rel_expression	: simple_expression 
// 		| simple_expression RELOP simple_expression	
// 		;
				
// simple_expression : term 
// 		  | simple_expression ADDOP term 
// 		  ;
					
// term :	unary_expression
//      |  term MULOP unary_expression
//      ;

// unary_expression : ADDOP unary_expression  
// 		 | NOT unary_expression 
// 		 | factor 
// 		 ;
	
// factor	: variable 
// 	| ID LPAREN argument_list RPAREN
// 	| LPAREN expression RPAREN
// 	| CONST_INT 
// 	| CONST_FLOAT
// 	| variable INCOP 
// 	| variable DECOP
// 	;
	
// argument_list : arguments
// 			  |
// 			  ;
	
// arguments : arguments COMMA logic_expression
// 	      | logic_expression
// 	      ;
 
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
	
	return 0;
}

