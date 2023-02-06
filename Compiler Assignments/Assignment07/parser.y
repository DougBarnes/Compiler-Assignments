%{
// // // // // // // // // // // // // // // // // // // // // // // 
// CS445 - Parser for c- files built upon from calc given to
// 	   class by Robert Heckendorn
//
// Doug Barnes
// Jan 30, 2021    
#include "ourGetopt.h"   //read in a command line
#include "scanType.h"    // TokenData Type
#include "treeNode.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <string.h>
#include "yyerror.h"
#include "codegen.h"


double vars[26];    
bool printOffsetFlag = false;
extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern int numWarning;
extern int yydebug;
extern int goffset;
extern SymbolTable symbolTable;
extern TreeNode *addSibling(TreeNode *t, TreeNode *s);
extern TreeNode *newDeclNode(DeclKind kind);
extern TreeNode *newStmtNode(StmtKind kind);
extern TreeNode *newExpNode(ExpKind kind);
extern void addIOLibrary(TreeNode *tree);
extern void printTree(TreeNode *tree);
extern void codegen(char* outFile, TreeNode *tree);
//extern void printTreeTypes(Semantic *tree);

TreeNode *syntaxTree;
//Semantic *syntaxTree;

#define YYERROR_VERBOSE
/*void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;
}*/

%}

// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union { 
    ExpType expType;            // for passing types.  typespec to pass up a type in decl like int or bool
    DeclKind declKind;
    TokenData *tokenData;    // for terminals.  token data comes from yylex() in the $ variables
    TreeNode *tree;          // for nonterminals.   these tree nodes as you build the tree
}

%token <tokenData> ID NUMCONST OPERATOR EQ ADDASS SUBASS MULTASS DIVASS STRINGCONST CHARCONST DEC MIN MAX GEQ LEQ INC NEQ BOOLCONST STATIC INT BOOL CHAR IF THEN ELSE WHILE FOR DO NOT BY RETURN BREAK OR AND TO EQASS ADD SUB STAR DIV MOD LESS GREATER RAND OPENCURLY CLOSEDCURLY OPENBRACKET CLOSEDBRACKET
%type <tree> program declList decl varDecl scopedVarDecl varDeclList varDeclInit varDeclId funDecl parms parmList parmTypeList parmIdList parmId stmt matched unmatched returnStmt breakStmt expStmt compoundStmt andExp unaryRelExp relExp minmaxExp sumExp mulExp unaryExp factor immutable mutable call constant argList exp localDecls stmtList args simpleExp iterRange unaryop
%type <expType> typeSpec 
//STATIC { printf("Line Token: STATIC"); } 

%%
program				: declList 									{ syntaxTree = $1;}
					;

declList			: declList decl								{ $$ = addSibling($1, $2);}
		    		| decl										{ $$ = $1;}
		    		;

decl				: varDecl									{ $$ = $1;}
		    		| funDecl									{ $$ = $1;}
					| error										{ $$ = NULL;}
		    		;


varDecl				: typeSpec varDeclList ';'					{ TreeNode* t = $2;
                   													if (t != NULL)
                   										  			{ 	while (t->sibling != NULL)
																		{
                        									    			t = t->sibling;
																			if ($1 == Integer){t->expType=Integer;}
												  				  			else if ($1 == Boolean){t->expType=Boolean;}
												  				  			else if ($1 == Char){t->expType=Char;}
																		}
                     										  			$$ = $2; 
																		yyerrok;}
                     												else $$ = NULL;
																	if($$ != NULL)
																	{
																	  	if ($1 == Integer){$$->expType=Integer;}
													  				  	else if ($1 == Boolean){$$->expType=Boolean;}
													  				  	else if ($1 == Char){$$->expType=Char;}
																	}
                 												}
					| error varDeclList	';'						{ $$ = NULL; yyerrok;}
					| typeSpec error ';'						{ $$ = NULL; yyerrok;}
		    		;

scopedVarDecl	   	: STATIC typeSpec varDeclList ';'			{ TreeNode* t = $3;
                   										  			if (t != NULL)
                   										  			{	
																		t->isStatic = true;
																		while (t->sibling != NULL)
																		{
																			if ($2 == Integer){t->expType=Integer;}
												  				  			else if ($2 == Boolean){t->expType=Boolean;}
												  				  			else if ($2 == Char){t->expType=Char;}
																			
                        									    			t = t->sibling;
																			t->isStatic = true;
																		}
                     										    		$$ = $3; 
																		yyerrok;}
                     										  		else $$ = NULL;
																	if($$ != NULL)
																	{
																		if ($2 == Integer){t->expType=Integer;}
													  				  	else if ($2 == Boolean){t->expType=Boolean;}
													  				  	else if ($2 == Char){t->expType=Char;}
																	}
																}
		   			| typeSpec varDeclList ';'					{ TreeNode* t = $2;
                   										  			if (t != NULL)
                   										  		  	{	while (t->sibling != NULL)
																		{
                        									    			t = t->sibling;
																			if ($1 == Integer){t->expType=Integer;}
												  				  			else if ($1 == Boolean){t->expType=Boolean;}
												  				  			else if ($1 == Char){t->expType=Char;}
																		}
                     										    		$$ = $2; 
																		yyerrok;}
                     										  		else $$ = NULL;
																	if($$ != NULL)
																	{
																		if ($1 == Integer){$$->expType=Integer;}
													  				  	else if ($1 == Boolean){$$->expType=Boolean;}
													  				  	else if ($1 == Char){$$->expType=Char;}
																	}
																}
					| error varDeclList ';'						{ $$ = NULL; yyerrok; }
		   			;

varDeclList	   		: varDeclList ',' varDeclInit				{ $$ = addSibling($1, $3); yyerrok;}
		   			| varDeclInit								{ $$ = $1;}
					| varDeclList ',' error						{ $$ = $1; yyerrok;}
					| error										{ $$ = NULL;}
		   			;

varDeclInit	   		: varDeclId									{ $$ = $1;}
		   			| varDeclId ':' simpleExp					{ $1->child[0] = $3;
												  				  $$ = $1;}
					| error ':' simpleExp						{ $$ = NULL; yyerrok;}
					| varDeclId ':' error						{ $$ = $1; }
		   			;

varDeclId	   		: ID										{ //printf("IN THE ID GRAMMAR\n");
																  $$ = newDeclNode(VarK);
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
																}
		   			| ID OPENBRACKET NUMCONST CLOSEDBRACKET		{ $$ = newDeclNode(VarK);
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->isArray = true;
																  $$->memSize = $3->numValue + 1;
																  //printf("tokenstr %s linenum %d\n", $1->tokenstr, $1->linenum);
																}
					| ID '[' error								{ $$ = NULL; }//yyerrok;
					| error ']'									{ $$ = NULL; yyerrok;}
		   			;

typeSpec	   		: INT										{$$ = Integer;}
		   			| BOOL										{$$ = Boolean;}
		   			| CHAR										{$$ = Char;}
		   			;


funDecl		   		: typeSpec ID '(' parms ')' stmt			{ $$ = newDeclNode(FuncK);
												  				  $$->linenum = $2->linenum;
												  				  $$->child[0] = $4;
												  				  $$->child[1] = $6;
												  				  $$->subkind.decl = FuncK;
												  				  $$->attr.name = $2->tokenstr;
												  				  if ($1 == Integer){$$->expType=Integer;}
												  				  else if ($1 == Boolean){$$->expType=Boolean;}
												  				  else if ($1 == Char){$$->expType=Char;} }					
		   			| ID '(' parms ')' stmt						{ $$ = newDeclNode(FuncK);
												  				  $$->linenum = $1->linenum;
												  				  $$->child[0] = $3;
												  				  $$->child[1] = $5;
												  				  $$->subkind.decl = FuncK;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->expType = Void;}
					| typeSpec error							{ $$ = NULL;}
					| typeSpec ID '(' error						{ $$ = NULL;}
					| ID '(' error								{ $$ = NULL;}
					| ID '(' parms ')' error					{ $$ = NULL;}
		   			;

parms		   		: parmList									{ $$ = $1;}
		   			| /*epsilon*/								{ $$ = NULL;}
		   			;

parmList	   		: parmList ';' parmTypeList					{ $$ = addSibling($1, $3); yyerrok;}
		   			| parmTypeList								{ $$ = $1;}
					| parmList ';' error						{ $$ = $1;}
					| error										{ $$ = NULL;}
		   			;

parmTypeList	   	: typeSpec parmIdList						{ TreeNode* t = $2;
                   										  		  if (t != NULL)
                   										  		  {		while (t->sibling != NULL)
																		{
                        									    			t = t->sibling;
																			if ($1 == Integer){t->expType=Integer;}
												  				  			else if ($1 == Boolean){t->expType=Boolean;}
												  				  			else if ($1 == Char){t->expType=Char;}
																		}
                     										    		$$ = $2; }
                     										  	  else $$ = NULL;
																  if($$ != NULL)
																  {
																	if ($1 == Integer){$$->expType=Integer;}
												  				  	else if ($1 == Boolean){$$->expType=Boolean;}
												  				  	else if ($1 == Char){$$->expType=Char;}
																  }
																}
		   			;

parmIdList	   		: parmIdList ',' parmId						{ $$ = addSibling($1, $3); yyerrok;}
		   			| parmId									{ $$ = $1;}
					| parmIdList ',' error						{ $$ = NULL;}
					| error										{ $$ = NULL;}
		   			;

parmId		   		: ID										{ $$ = newDeclNode(ParamK);
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->subkind.decl = ParamK;}
		   			| ID OPENBRACKET CLOSEDBRACKET								{ $$ = newDeclNode(ParamK);
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->subkind.decl = ParamK;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->isArray = true;}	
					| error CLOSEDBRACKET						  { $$ = NULL; yyerrok;}				
		   			;


stmt		   		: matched									{ $$ = $1;}
		   			| unmatched									{ $$ = $1; }
		   			;

matched   	  		: IF simpleExp THEN matched ELSE matched	{ $$ = newStmtNode(IfK);
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[0] = $2;
												  				  $$->child[1] = $4;
												  				  $$->child[2] = $6;
																}

					| WHILE simpleExp DO matched				{ $$ = newStmtNode(WhileK);
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[0] = $2;
												  				  $$->child[1] = $4;
																}

		   			| FOR ID EQASS iterRange DO matched			{ $$ = newStmtNode(ForK);
												  				  $$->child[0] = newDeclNode(VarK);
																  $$->child[0]->attr.name = $2->tokenstr;
																  $$->child[0]->linenum = $2->linenum;
																  $$->child[0]->expType=Integer;
												  				  $$->child[1] = $4;
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[2] = $6;
																}
												  
          	   		| returnStmt								{ $$ = $1;}
		   			| breakStmt									{ $$ = $1;}
		   			| expStmt									{ $$ = $1;}
		   			| compoundStmt								{ $$ = $1;}
					| IF error									{ $$ = NULL;}
					| IF error ELSE matched                   	{ $$ = NULL; yyerrok; }
              		| IF error THEN matched ELSE matched      	{ $$ = NULL; yyerrok; }
              		| WHILE error DO matched                  	{ $$ = NULL; yyerrok;}
              		| WHILE error                             	{ $$ = NULL; yyerrok;}
              		| FOR ID '=' error DO matched             	{ $$ = NULL; yyerrok; }
              		| FOR error                               	{ $$ = NULL; }
          	   		;

unmatched 	   		: IF simpleExp THEN stmt					{ $$ = newStmtNode(IfK); ///changed stmt to matched
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[0] = $2;
												  				  $$->child[1] = $4; }
          	   		//| IF simpleExp THEN unmatched
          	   		| IF simpleExp THEN matched ELSE unmatched	{ $$ = newStmtNode(IfK);
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[0] = $2;
												 			 	  $$->child[1] = $4; 
												  				  $$->child[2] = $6; }
					| WHILE simpleExp DO unmatched				{ $$ = newStmtNode(WhileK);
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[0] = $2;
												  				  $$->child[1] = $4;
																}

		   			| FOR ID EQASS iterRange DO unmatched		{ $$ = newStmtNode(ForK);
												  				  $$->child[0] = newDeclNode(VarK);
																  $$->child[0]->attr.name = $2->tokenstr;
																  $$->child[0]->linenum = $2->linenum;
																  $$->child[0]->expType=Integer;
												  				  $$->child[1] = $4;
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[2] = $6;
																}
					| IF error THEN stmt                      	{ $$ = NULL; yyerrok; }
              		| IF error THEN matched ELSE unmatched    	{ $$ = NULL; yyerrok; }
					| WHILE error DO unmatched                  { $$ = NULL; yyerrok; }
          	   		;

expStmt		   		: exp ';'									{ $$ = $1;  }//yyerrok;
		   			| ';'										{ $$ = NULL;  }//yyerrok;
					| error ';'                               	{ $$ = NULL; yyerrok; }
		   			;

compoundStmt	   	: OPENCURLY localDecls stmtList CLOSEDCURLY	  { $$ = newStmtNode(CompoundK);
																  $$->linenum = $1->linenum;
												  				  $$->child[0] = $2;
												  				  $$->child[1] = $3; 
																  yyerrok;}
		   			;

localDecls	   		: localDecls scopedVarDecl					{ $$ = addSibling($1, $2);}
		   			| /*epsilon*/								{ $$ = NULL;}
		   			;

stmtList	   		: stmtList stmt								{if($2 != NULL)
																{$$ = addSibling($1, $2);}
																else
																{$$ = $1;}}
		   			| /*epsilon*/								{$$ = NULL;}
		   			;

/*iterStmt	   		: WHILE simpleExp DO stmt					{ $$ = newStmtNode(WhileK);
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[0] = $2;
												  				  $$->child[1] = $4;
																}

		   			| FOR ID EQASS iterRange DO stmt			{ $$ = newStmtNode(ForK);
												  				  $$->child[0] = newDeclNode(VarK);
																  $$->child[0]->attr.name = $2->tokenstr;
																  $$->child[0]->linenum = $2->linenum;
												  				  $$->child[1] = $4;
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;
												  				  $$->child[2] = $6;
																}
		   			;*/

iterRange	   		: simpleExp TO simpleExp					{ $$ = newStmtNode(RangeK);
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $2->tokenstr;
												  				  $$->child[0] = $1;
												  				  $$->child[1] = $3; }
		   			| simpleExp TO simpleExp BY simpleExp		{ $$ = newStmtNode(RangeK);
												  				  $$->linenum = $2->linenum;
												  				  $$->attr.name = $2->tokenstr;
												  				  $$->child[0] = $1;
												  				  $$->child[1] = $3; 
																  $$->child[2] = $5;}
					| simpleExp TO error                      	{ $$ = NULL; }
              		| error BY error                          	{ $$ = NULL; yyerrok; }
              		| simpleExp TO simpleExp BY error         	{ $$ = NULL; }
		   			;

returnStmt	   		: RETURN ';'								{$$ = newStmtNode(ReturnK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;}
		   			| RETURN exp ';'							{$$ = newStmtNode(ReturnK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;
																 $$->child[0] = $2;
																 yyerrok;}
              		| RETURN error ';'                        	{ $$ = NULL; yyerrok; }
		   			;

breakStmt	   		: BREAK	';'									{ $$ = newStmtNode(BreakK);
												  				  $$->linenum = $1->linenum;
												  				  $$->attr.name = $1->tokenstr;}
		   			;

exp		   			: mutable EQASS exp							{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| mutable ADDASS exp						{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| mutable SUBASS exp						{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| mutable MULTASS exp						{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| mutable DIVASS exp						{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
	   	   			| mutable INC								{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;}
		   			| mutable DEC								{$$ = newExpNode(AssignK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;}
		   			| simpleExp									{ $$ = $1;}
					| error EQASS exp                      	    { $$ = NULL; yyerrok; }
					| error ADDASS error                      	{ $$ = NULL; yyerrok; }
					| error SUBASS exp                      	{ $$ = NULL; yyerrok; }
					| error MULTASS exp                      	{ $$ = NULL; yyerrok; }
					| error DIVASS exp                      	{ $$ = NULL; yyerrok; }
              		| mutable EQASS error                  		{ $$ = NULL; }
              		| mutable ADDASS error                  	{ $$ = NULL; }
              		| mutable SUBASS error                  	{ $$ = NULL; }
              		| mutable MULTASS error                  	{ $$ = NULL; }
              		| mutable DIVASS error                  	{ $$ = NULL; }
              		| error INC                               	{ $$=NULL; yyerrok; }
              		| error DEC                               	{ $$=NULL; yyerrok; }
		   			;

simpleExp	   		: simpleExp OR andExp						{$$ = newExpNode(OpK);//$1->avalue
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->avalue;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| andExp									{ $$ = $1;}
					| simpleExp OR error                      	{ $$ = $1; };
		   			;

andExp		   		: andExp AND unaryRelExp					{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->avalue;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| unaryRelExp								{ $$ = $1;}
					| andExp AND error                        	{ $$ = NULL; }
		   			;

unaryRelExp	   		: NOT unaryRelExp							{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->avalue;
												  				 $$->child[0] = $2;}
		   			| relExp									{ $$ = $1;}
					| NOT error                               	{ $$ = NULL; }
		   			;

relExp		   		: minmaxExp LEQ minmaxExp					{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					|  minmaxExp LESS minmaxExp					{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| minmaxExp GREATER minmaxExp				{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| minmaxExp GEQ minmaxExp					{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| minmaxExp EQ minmaxExp					{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| minmaxExp NEQ minmaxExp					{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| minmaxExp									{ $$ = $1;}
					| minmaxExp LEQ error                   	{ $$ = NULL; }
					| minmaxExp LESS error                   	{ $$ = NULL; }
					| minmaxExp GREATER error                   { $$ = NULL; }
					| minmaxExp GEQ error                   	{ $$ = NULL; }
					| minmaxExp EQ error                   		{ $$ = NULL; }
					| minmaxExp NEQ error                   	{ $$ = NULL; }
		   			;


minmaxExp	   		: minmaxExp MAX sumExp				    	{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| minmaxExp MIN sumExp				    	{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| sumExp									{ $$ = $1;}
		   			;


sumExp		   		: sumExp ADD mulExp							{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| sumExp SUB mulExp							{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| mulExp									{ $$ = $1;}
					| sumExp ADD error                      	{ $$ = NULL; yyerrok; }
					| sumExp SUB error                      	{ $$ = NULL; yyerrok;}
		   			;


mulExp		   		: mulExp STAR unaryExp						{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| mulExp DIV unaryExp						{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
					| mulExp MOD unaryExp						{$$ = newExpNode(OpK);
																 $$->linenum = $2->linenum;
												  				 $$->attr.name = $2->tokenstr;
																 $$->child[0] = $1;
												  				 $$->child[1] = $3;}
		   			| unaryExp									{ $$ = $1;}
					| mulExp STAR error                      	{ $$ = NULL; }
					| mulExp DIV error                      	{ $$ = NULL; }
					| mulExp MOD error                      	{ $$ = NULL; }
		   			;

/*mulop		   		: STAR										{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;}
		   			| DIV										{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;}
		   			| MOD										{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;}
		   			;*/

unaryExp	   		: unaryop unaryExp							{ $$->child[0] = $2;}
		   			| factor									{ $$ = $1;}
					| unaryop error                           	{ $$ = NULL; }
		   			;

unaryop		   		: SUB										{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;
																 $$->isUnarySub = true;}
		   			| STAR										{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;
																 $$->isUnaryStar = true;}
		   			| RAND										{$$ = newExpNode(OpK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;}
		   			;

factor		   		: immutable									{ $$ = $1;}
		   			| mutable									{ $$ = $1;}
		   			;
////////////////////////
mutable		   		: ID										{//printf("Line: %d	Token: %s\n", $1->linenum, $1->tokenstr);
																$$ = newExpNode(IdK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;
																//printf("Line: %d	Token: %s	subkind: %d\n", $1->linenum, $1->tokenstr, $$->exp);
																}
		   			| ID OPENBRACKET exp CLOSEDBRACKET			{$$ = newExpNode(OpK);
																 $$->child[0] = newExpNode(IdK);
																 $$->child[0]->attr.name = $1->tokenstr;
																 $$->child[0]->linenum = $1->linenum;
																 $$->attr.name = $2->tokenstr;
																 $$->linenum = $1->linenum;
																 //$$->isArray = true;
																 $$->child[1] = $3; 
																}
		   			;
/////////////////////////

immutable	   		: '(' exp ')'								{ $$ = $2; yyerrok;}
		   			| call										{ $$ = $1;}
	 	   			| constant									{ $$ = $1;}
					| '(' error									{ $$ = NULL; yyerrok;}
		   			;

call		   		: ID '(' args ')'							{$$ = newExpNode(CallK);
																 $$->linenum = $1->linenum;
												  				 $$->attr.name = $1->tokenstr;
																 $$->child[0] = $3;}
					| error '('                               	{ $$ = NULL; yyerrok; }
		   			;

args		   		: argList									{ $$ = $1;}
		   			| /*epsilon*/								{ $$ = NULL;}
		   			;

argList		   		: argList ',' exp							{ $$ = addSibling($1, $3); yyerrok;}
		   			| exp										{ $$ = $1;}
					| argList ',' error                       	{ $$=NULL; }
		   			;

constant	   		: NUMCONST									{$$ = newExpNode(ConstantK);
																 $$->expType = Integer;
												  				 $$->attr.value = $1->numValue;
																 $$->linenum = $1->linenum;
																 $$->isConst = true;
																 yyerrok;}
		   			| CHARCONST									{$$ = newExpNode(ConstantK);
																 $$->expType = Char;
												  				 $$->attr.cvalue = $1->cvalue;
																 $$->linenum = $1->linenum;
																 $$->isConst = true;
																 yyerrok;}
		   			| STRINGCONST								{$$ = newExpNode(ConstantK);
																 $$->expType = Char;
												  				 $$->attr.string = $1->avalue;
																 $$->linenum = $1->linenum;
																 $$->isArray = true;
																 $$->stringLength = $1->countValue;
																 $$->memSize = $1->countValue - 1;
																 $$->isConst = true;
																 yyerrok;}
		   			| BOOLCONST									{$$ = newExpNode(ConstantK);
																 $$->expType = Boolean;
												  				 $$->attr.value = $1->numValue;
																 $$->linenum = $1->linenum; 
																 $$->isConst = true;
																 yyerrok;}
		   			;
%%

/*
statementlist      : statementlist statement
		   | statement
		   ;


statement     : '\n'
	      | STATIC { printf("Line %d Token: STATIC\n", $1->linenum); }
	      | ID     { printf("Line %d Token: ID Value: %s\n", $1->linenum, $1->tokenstr); }
	      | NUMBER { printf("Line %d Token: NUMCONST Value: %d Input: %s\n", $1->linenum, $1->numValue, $1->tokenstr); }
	      | OPERATOR { printf("Line %d Token: %s\n", $1->linenum, $1->tokenstr); }
	      | KEYWORD { printf("Line %d Token: %s\n", $1->linenum, $1->avalue); }

	      | EQ 	{ printf("Line %d Token: EQ\n", $1->linenum); }
	      | NEQ 	{ printf("Line %d Token: NEQ\n", $1->linenum); }
	      | DEC 	{ printf("Line %d Token: DEC\n", $1->linenum); }
	      | INC 	{ printf("Line %d Token: INC\n", $1->linenum); }
	      | MIN 	{ printf("Line %d Token: MIN\n", $1->linenum); }
	      | MAX 	{ printf("Line %d Token: MAX\n", $1->linenum); }
	      | GEQ 	{ printf("Line %d Token: GEQ\n", $1->linenum); }
	      | LEQ 	{ printf("Line %d Token: LEQ\n", $1->linenum); }
	      | ADDASS  { printf("Line %d Token: ADDASS\n", $1->linenum); }

	      | STRINGCONST 	{ printf("Line %d Token: STRINGCONST Value: %s Len: %d Input: %s\n", $1->linenum, $1->avalue, $1->countValue-2, $1->tokenstr); }
	      | CHARCONST   	{ printf("Line %d Token: CHARCONST Value: '%s' Input: %s\n", $1->linenum, $1->avalue, $1->tokenstr); }
	      | BOOLCONST 	{ printf("Line %d Token: BOOLCONST Value: %d Input: %s\n", $1->linenum, $1->numValue, $1->tokenstr); }
              ;
*/

extern int yydebug;
char* outFile;
int main(int argc, char *argv[])
{
	initErrorProcessing();
    extern int   opterr;					
    extern int   optind;					
    extern char *optarg;
	FILE *fp;
    int printTreeFlag = 0, printTreeType = 0;
    int c = 0;
	numErrors = 0;

	if(argc == 1)
	{
		yyparse();         // parse and build the tree in the global var syntaxTree.
	}
    else if (argc > 1) {
		while ((c = ourGetopt(argc, argv, (char *)"dphgDPM")) != EOF)
     	{   
	    	switch (c) {
            case        'd': //Turn on parser debugging
                yydebug = 1;
                break;
			case        'D': //Turn on symbol table debugging
                //printf("debugging symbol table... please wait...");
				symbolTable.debug(1); 
			printTreeType= 1;
                break;
			case        'h': //this usage message
                printf("Usage: c- [options] [sourceFile]\noptions:\n-d		- turn on parser debugging\n-D		- turn on symbol table debugging\n-h	- this usage message\n-p 	- print the abstract syntax tree\n-P	- print the abstract syntax tree plus type information\n");
                break;
	   		case        'p': //Print the abstract syntax tree
                printTreeFlag = 1;
                break;
			case        'P': //Print the abstract syntax tree plus type information
                printTreeType= 1;
                break;
			case        'M':
                printOffsetFlag = true;
				printTreeType= 1;
                break;
		default:
			printTreeType= 1;
		break;
           }
		}
		if(argc > optind)
		{
			/*fp = fopen(argv[optind], "r");
         		if (!fp){
            			fprintf(stderr, "Cannot open file\n");
            			exit(1);
         		}
        		yyin = fp;
         		do{
            			yyparse();
         		} while (!feof(yyin));
         		fclose(fp);*/
            if ((yyin = fopen(argv[optind], "r"))) {
				do{ yyparse(); } while (!feof(yyin));
                // file open successful
            }
            else {
                // failed to open file
				numErrors++;
                printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[1]);
				printf("Number of warnings: %d\n", numWarning);   // Warn
   				printf("Number of errors: %d\n", numErrors);   // ERR
                exit(1);
            }
		}
    }

    // init variables a through z
    for (int i=0; i<26; i++) vars[i] = 0.0;

    // do the parsing
    if (printTreeFlag) //in treeNode.c make a printTree function, simular to util.c in tiny.
    {
		printTree(syntaxTree);  // printTreeFlag is set by -p option
    }
	else if (printTreeType && numErrors == 0)
	{
		addIOLibrary(syntaxTree);
		printTreeSemantic(syntaxTree);  // printTreeTypes is set by -P option
		if((TreeNode*)symbolTable.lookup("main") == NULL)
		{
			numErrors++;
			printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
		}
		
		if(numErrors == 0)
		{
			printTree(syntaxTree);
			if (printOffsetFlag)
			{
				printf("Offset for end of global space: %d\n", goffset);
			}
		}
	}
	else if (numErrors == 0){
		addIOLibrary(syntaxTree);
		printTreeSemantic(syntaxTree); 
	}
	printf("Number of warnings: %d\n", numWarning);   // Warn
    printf("Number of errors: %d\n", numErrors);   // ERR
	      // Extract the filename from argv if given

	
	
	if(numErrors == 0)	
		{
			int i = 0;
			int stringLen = strlen(argv[optind]);
			char tempOut[stringLen];
			char *out = argv[optind];
			while(out[i] != '.' || i> stringLen)
			{
				tempOut[i] = out[i]; 
				//printf("%c", tempOut[i]);
				i++;
			}
			tempOut[i] = '.';
			tempOut[i+1] = 't';
			tempOut[i+2] = 'm';
			tempOut[i+3] = '\0';
			
			outFile = tempOut;
			//printf("codegen\n");
			codegen(outFile, syntaxTree);
		}
	

    return 0;
}
