/*

start :  var_declaration
     | func_definition
     ;
		 
func_definition : type_specifier ID LPAREN vector<SymbolInfo*> RPAREN compound_statement 		;				

 		
compound_statement : vector<statement>
 		    
var_declaration : vector<symbolInfo *>
	   
statement : var_declaration  
	  | expression_statement : expression
	  | compound_statement  : compound_statement
	  | FOR LPAREN expression_statement expression_statement expression RPAREN statement
        : for, expression1, expression2, expression3, statement
        : compount_statement: expression1   while expression2 statement+ expression
	  | IF LPAREN expression RPAREN statement
        : if, expression, statement
	  | IF LPAREN expression RPAREN statement ELSE statement
        : if-else, expressionm statemet statement
	  | WHILE LPAREN expression RPAREN statement
        : while expression
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
        : print id
	  | RETURN expression SEMICOLON
        : return expression
	  ;
	  
variable : ID 		
	 | ID LTHIRD expression RTHIRD 
	 ;
	 
expression : logic_expression	
	   | variable ASSIGNOP logic_expression 	
	   ;
			
logic_expression : rel_expression 	
		 | rel_expression LOGICOP rel_expression 	
		 ;
			
rel_expression	: simple_expression 
		| simple_expression RELOP simple_expression	
		;
				
simple_expression : term 
		  | simple_expression ADDOP term 
		  ;
					
term :	unary_expression
     |  term MULOP unary_expression
     ;

unary_expression : ADDOP unary_expression  
		 | NOT unary_expression 
		 | factor 
		 ;
	
factor	: variable 
	| ID LPAREN argument_list RPAREN  : function call , id, vector<logic_expression>
	| LPAREN expression RPAREN
	| CONST_INT 
	| CONST_FLOAT
	| variable INCOP 
	| variable DECOP
	;


                        stnode
                        stmntnode
        expnode         comp_stmnt      var_decl    control_flow 
    unary binary term     
    ret    add,mul 
    unary
*/ 