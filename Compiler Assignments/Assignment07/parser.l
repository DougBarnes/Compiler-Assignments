%{
// this *order* of these includes is mandatory
#include "scanType.h"    // TokenData Type
#include "treeNode.h"
#include "parser.tab.h"  // token definitions from the bison

int line = 1;
int numErrors = 0;    // ERR err count
int numWarning = 0;

static int setValue(int linenum, int tokenClass, char *svalue)
{
	//printf("in set value %s %d\n", svalue, tokenClass);///

    int i = 0;
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = strdup(svalue);  // duplicating string!!
	yylval.tokenData->tokenclass = tokenClass; 

	//printf("tokenstr %s class %d linenum %d\n", yylval.tokenData->tokenstr, tokenClass, linenum);///

//NUMCONST  
    if (tokenClass == NUMCONST) 
	{
        yylval.tokenData->numValue = atoi(svalue); 
    }
//ID
    else if (tokenClass == ID)
	{
        yylval.tokenData->idIndex = svalue[0]-'a';
    }
//BOOLCONST
    else if (tokenClass == BOOLCONST)
	{
		yylval.tokenData->idIndex = svalue[0]-'a';
		if(!strcmp(yylval.tokenData->tokenstr, "true"))
		{
	    	yylval.tokenData->numValue = 1;
		}
		else if(!strcmp(yylval.tokenData->tokenstr, "false"))
		{
	    	yylval.tokenData->numValue = 0;
		}
    }

//STRINGCONST
	else if (tokenClass == STRINGCONST)
	{
		int len, count = 0;
		len = strlen(yylval.tokenData->tokenstr);
		char tokenInstance, tokenInstancePlus;
		//printf("IN STRING CONST -> %d\n", len);
		while(i<=len)
		{
	    	tokenInstance = yylval.tokenData->tokenstr[i];
	    	tokenInstancePlus = yylval.tokenData->tokenstr[i+1];
	    	if(tokenInstance == '\\')
	    	{
				if(tokenInstancePlus == 'n')
				{
		   			yylval.tokenData->avalue[count] = '\n';
		    		i++;
		    		count++;
				}
				else if(tokenInstancePlus == '0')
				{
		    		yylval.tokenData->avalue[count] = '\0';
		    		i++;
		    		count++;
				}
				else if(tokenInstancePlus == '\\')
				{
		   			yylval.tokenData->avalue[count] = '\\';
		    		i++;
		    		count++;
				}
	    	}
	    	else
	    	{
				yylval.tokenData->avalue[count] = tokenInstance;
				count++;
	    	}
	    	i++;
		}
		yylval.tokenData->countValue = strlen(yylval.tokenData->avalue);
    }
//CHARCONST
    else if (tokenClass == CHARCONST)
	{
		int len;
		len = strlen(yylval.tokenData->tokenstr);

		char tokenInstance, tokenInstancePlus;
		tokenInstance = yylval.tokenData->tokenstr[1];
		tokenInstancePlus = yylval.tokenData->tokenstr[2];

		if (len > 4)
		{
			numWarning ++;
			printf("WARNING(%d): character is %d characters long and not a single character: '%s'. The first char will be used.\n", yylval.tokenData->linenum, len-2, yylval.tokenData->tokenstr);
			yylval.tokenData->cvalue = tokenInstance;
		}
		else
		{
			if(tokenInstance == '\\')
			{
				if(tokenInstancePlus == 'n')
				{
					yylval.tokenData->cvalue = '\n';
				}
				else if(tokenInstancePlus == '0')
				{
					yylval.tokenData->cvalue = '\0';
					//printf("Line %d Token: CHARCONST Value: '%c%c%c' Input: %s\n", yylval.tokenData->linenum, '\\', '0', '0', yylval.tokenData->tokenstr);
				}
				else if(tokenInstancePlus == '\\')
				{
					yylval.tokenData->cvalue = '\\';
				}
				else
				{
					yylval.tokenData->cvalue = tokenInstancePlus;
				}
			}
			// double char warning 
			else if(tokenInstance == '^')
			{
				numWarning++;
				printf("WARNING(%d): character is %d characters long and not a single character: '%s'. The first char will be used.\n", yylval.tokenData->linenum, len-2, yylval.tokenData->tokenstr);
				yylval.tokenData->cvalue = tokenInstance;
			}
			else
			{
				yylval.tokenData->cvalue = tokenInstance;
			}
			i++;
		}
		//yylval.tokenData->countValue = strlen(yylval.tokenData->avalue);
    }

//STATIC
    else if(tokenClass == STATIC)
    {
		//printf("in print static\n");
		char strST[]="STATIC";
        while(strST[i])
        {
	    	yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//INT
    else if(tokenClass == INT)
    {
		//printf("in print INT!!\n");
		char strST[]="INT";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//BOOL
    else if(tokenClass == BOOL)
    {
		//printf("in print static\n");
		char strST[]="BOOL";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//CHAR
    else if(tokenClass == CHAR)
    {
		//printf("in print static\n");
		char strST[]="CHAR";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//IF
    else if(tokenClass == IF)
    {
		//printf("in print static\n");
		char strST[]="IF";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//THEN
    else if(tokenClass == THEN)
    {
		//printf("in print static\n");
		char strST[]="THEN";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//ELSE
    else if(tokenClass == ELSE)
    {
		//printf("in print static\n");
		char strST[]="ELSE";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//WHILE
    else if(tokenClass == WHILE)
    {
		//printf("in print static\n");
		char strST[]="WHILE";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//FOR
    else if(tokenClass == FOR)
    {
		//printf("in print static\n");
		char strST[]="FOR";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//DO
    else if(tokenClass == DO)
    {
		//printf("in print static\n");
		char strST[]="DO";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//TO
    else if(tokenClass == TO)
    {
		//printf("in print static\n");
		char strST[]="TO";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        } 
    }
//BY
    else if(tokenClass == BY)
    {
		//printf("in print static\n");
		char strST[]="BY";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//RETURN
    else if(tokenClass == RETURN)
    {
		//printf("in print static\n");
		char strST[]="RETURN";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//BREAK
    else if(tokenClass == BREAK)
    {
		//printf("in print static\n");
		char strST[]="BREAK";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//OR
    else if(tokenClass == OR)
    {
		//printf("in print static\n");
		char strST[]="OR";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//AND
    else if(tokenClass == AND)
    {
		//printf("in print static\n");
		char strST[]="AND";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }
//NOT
    else if(tokenClass == NOT)
    {
		//printf("in print static\n");
		char strST[]="NOT";
        while(strST[i])
        {
            yylval.tokenData->avalue[i] = strST[i];
            i++;
        }
    }

    yylval.tokenData->tokenstr = strdup(svalue);  // duplicating string!!

	//printf("at end of setvalue\n");///

    // return the tokenclass
    return tokenClass;
}
//charConst StringConst ||| for double quotes ["][^"]*["]
%}

%option noyywrap

%%
\n               	{ line++; }
\/\/.*              ;
"static"	       	{ return setValue(line, STATIC, yytext); }
"int"		       	{ return setValue(line, INT, yytext); }
"bool"		       	{ return setValue(line, BOOL, yytext); }
"char"		       	{ return setValue(line, CHAR, yytext); }
"if"		       	{ return setValue(line, IF, yytext); }
"then"		       	{ return setValue(line, THEN, yytext); }
"else"		       	{ return setValue(line, ELSE, yytext); }
"while"		       	{ return setValue(line, WHILE, yytext); }
"for"		       	{ return setValue(line, FOR, yytext); }
"do"		       	{ return setValue(line, DO, yytext); }
"to"		       	{ return setValue(line, TO, yytext); }
"by"		       	{ return setValue(line, BY, yytext); }
"return"	       	{ return setValue(line, RETURN, yytext); }
"break"		       	{ return setValue(line, BREAK, yytext); }
"or"		       	{ return setValue(line, OR, yytext); }
"and"		       	{ return setValue(line, AND, yytext); }
"not"	       	    { return setValue(line, NOT, yytext); }
"true"|"false"	    { return setValue(line, BOOLCONST, yytext); }
[0-9]+        	    { return setValue(line, NUMCONST, yytext); }
[a-zA-Z0-9]+        { return setValue(line, ID, yytext); }

"=="		       	{ return setValue(line, EQ, yytext); }
"+="		       	{ return setValue(line, ADDASS, yytext); }
"-="		       	{ return setValue(line, SUBASS, yytext); }
"*="		       	{ return setValue(line, MULTASS, yytext); }
"/="		       	{ return setValue(line, DIVASS, yytext); }
"!="		       	{ return setValue(line, NEQ, yytext); }
"--"		       	{ return setValue(line, DEC, yytext); }
"++"		       	{ return setValue(line, INC, yytext); }
":<:"		       	{ return setValue(line, MIN, yytext); }
":>:"		       	{ return setValue(line, MAX, yytext); }
">="		       	{ return setValue(line, GEQ, yytext); }
"<="		       	{ return setValue(line, LEQ, yytext); }
"="		       		{ return setValue(line, EQASS, yytext); }

"+"		       		{ return setValue(line, ADD, yytext); }
"-"		       		{ return setValue(line, SUB, yytext); }
"*"		       		{ return setValue(line, STAR, yytext); }
"/"		       		{ return setValue(line, DIV, yytext); }
"%"		       		{ return setValue(line, MOD, yytext); }
"<"		       		{ return setValue(line, LESS, yytext); }
">"		       		{ return setValue(line, GREATER, yytext); }
"?"		       		{ return setValue(line, RAND, yytext); }
"{"		       		{ return setValue(line, OPENCURLY, yytext); }
"}"		       		{ return setValue(line, CLOSEDCURLY, yytext); }
"["		       		{ return setValue(line, OPENBRACKET, yytext); }
"]"		       		{ return setValue(line, CLOSEDBRACKET, yytext); }

"("|")"|":"|";"|","	       		   		   {return yytext[0];}
["]([^\"\\|\n]*(\\.[^\"\\]*)*)["] 	       { return setValue(line, STRINGCONST, yytext); }
\'([^\'\\|\n]*(\\.[^'\\|\n]*)*)\' 	       { return setValue(line, CHARCONST, yytext); }

[ \t]                  ;
.                      { printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%


