#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "treeNode.h"
#include "symbolTable.h"

const char* expTypeCheck(ExpType type);

SymbolTable symbolTable;
extern int numErrors;
extern int numWarning;
extern TreeNode *newDeclNode(DeclKind kind);
int goffset = 0;
int foffset = -2;

int memSizeGlobal = -2;
int scopeDepth = 1;
bool scopeEntered = false;

void printTreeSemantic(TreeNode *tree)
{
	int i;
	int loffset = 0;
	bool returnFlag = false;
	
		if (tree == NULL)
		{
			return;
		}

		if (tree->nodekind==DeclK)
		{ 
		  	TreeNode *functionName;
			if(symbolTable.insert(tree->attr.name, tree) == 0 /*&& tree->subkind.decl != VarK*/)
			{
				functionName = (TreeNode*)symbolTable.lookup(tree->attr.name); 
				printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->linenum, tree->attr.name, functionName->linenum);
				numErrors++;
			}
		  	switch (tree->subkind.decl) {
				case VarK:
				  //printf("VarK: %s\n	", tree->attr.name );
				  for(int i = 0; i<MAXCHILDREN; i++)
				  {
				  	printTreeSemantic(tree->child[i]);
				  }
				  //printf("Name: %s	child %s	isconst: %d\n", tree->attr.name, tree->child[0]->attr.name, tree->child[0]->isConst);
				  if(tree->child[0] != NULL && tree->child[1] != NULL)
				  {
					if(!(tree->child[0]->isConst && tree->child[1]->isConst))
					{
						numErrors++;
						printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->linenum, tree->attr.name);
					}
				  }
				  else if(tree->child[0] != NULL)
				  {
					  if(!tree->child[0]->isConst)
					  {
						numErrors++;
						printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->linenum, tree->attr.name);
					  }
				  }
				  if(scopeDepth == 1)
				  {
				
					tree->mem = Global;
					if(tree->isArray)
					{
						tree->memOffset = goffset - 1;
					}
					else
					{
						tree->memOffset = goffset;
					}
					goffset = goffset - tree->memSize;
				  }
				  else if (tree->isStatic)
				  {
					tree->mem = LocalStatic;
					if(tree->isArray)
					{
						tree->memOffset = goffset - 1;
					}
					else
					{
						tree->memOffset = goffset;
					}
					goffset = goffset - tree->memSize;
				  }
				  else
				  {
					tree->mem = Local;
					if(tree->isArray)
					{
						tree->memOffset = foffset - 1;
					}
					else
					{
						tree->memOffset = foffset;
					}
					foffset = foffset - tree->memSize;
				  }

				  /*TreeNode *variableName;
				  if(symbolTable.insert(tree->attr.name, tree) == 0)
				  {
				 	variableName = (TreeNode*)symbolTable.lookup(tree->attr.name); 
					printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->linenum, tree->attr.name, variableName->linenum);
					numErrors++;
				  }*/
				  break;
				case FuncK:
				  //printf("FuncK: %s\n", tree->attr.name);	  
				  //scope stuff needs to happen here
				  symbolTable.enter(tree->attr.name);
				  scopeDepth++;
				  //printf("ENTERED SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				  scopeEntered = true;
				  foffset = -2;
				  
				  for(int i = 0; i<MAXCHILDREN; i++)
				  {
					 /*if(tree->child[i] != NULL)
					 {
					 	memSizeGlobal--;
					 }
					 tree->memSize = memSizeGlobal;*/
					 printTreeSemantic(tree->child[i]);
				  }
				  if(!returnFlag && tree->expType != Void)
				  {
					//numWarning++;
					//printf("WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", tree->linenum, expTypeCheck(tree->expType), tree->attr.name);
				  }
				  tree->memSize = memSizeGlobal;
				  memSizeGlobal = -2;
				  tree->mem = Global;
				  symbolTable.leave();
				  scopeDepth--;

				  //printf("LEFT SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				  break;
				case ParamK:
				  //printf("ParamK: %s\n",tree->attr.name);
				  
				  for(int i = 0; i<MAXCHILDREN; i++)
				  {
				  	printTreeSemantic(tree->child[i]);
				  }
				  memSizeGlobal--;
				  tree->mem = Parameter;
				  tree->memOffset = foffset;
				  foffset = foffset - tree->memSize;
				  break;
				default:
				  printf("Unknown ExpNode kind\n");
				  break;
			}
		}
    	else if (tree->nodekind==StmtK)
    	{ switch (tree->subkind.stmt) {
        	case IfK:
				//printf("If\n");
				//scope stuff needs to happen here
				symbolTable.enter("if");
				scopeDepth++;
				loffset = foffset;
				//printf("ENTERED SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				scopeEntered = true;
				for(int i = 0; i<MAXCHILDREN; i++)
				{
					printTreeSemantic(tree->child[i]);
				}
				if(tree->child[0]->isArray)
				{
					numErrors++;
					printf("ERROR(%d): Cannot use array as test condition in if statement.\n", tree->linenum);
				}
				if(tree->child[0]->expType != Boolean)
				{
					numErrors++;
					printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", tree->linenum, expTypeCheck(tree->child[0]->expType));
				}
				
				symbolTable.leave();
				scopeDepth--;
				foffset = loffset;
				//printf("LEFT SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				scopeEntered = false;
          		break;
        	case WhileK:
          		//printf("While: \n");
				//scope stuff needs to happen here
				symbolTable.enter("while");
				scopeDepth++;
				loffset = foffset;
				//printf("ENTERED SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				scopeEntered = true;
				for(int i = 0; i<MAXCHILDREN; i++)
				{
					printTreeSemantic(tree->child[i]);
				}
				if(tree->child[0]->expType != Boolean)
				{
					numErrors++;
					printf("ERROR(%d): Expecting Boolean test condition in while statement but got type %s.\n", tree->linenum, expTypeCheck(tree->child[0]->expType));
				}
				symbolTable.leave();
				scopeDepth--;
				foffset = loffset;
				//printf("LEFT SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				scopeEntered = false;
          		break;
        	case ForK:
          		//printf("For: \n");
				//scope stuff needs to happen here
				symbolTable.enter("for");
				scopeDepth++;
				loffset = foffset;
				//printf("ENTERED SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				scopeEntered = true;
				//printf("FOFFSET: %d	-- LOFFSET: %d  LineNum: %d\n",foffset, loffset, tree->linenum);
				for(int i = 0; i<MAXCHILDREN; i++)
				{
					printTreeSemantic(tree->child[i]);
				}
				//printf("NAME: %s 	LINENUM: %d\n", tree->attr.name, tree->linenum);
				if(tree->child[0] != NULL && tree->child[1] != NULL && tree->child[1]->child[0] != NULL && tree->child[1]->child[1] != NULL)
				{
					//printf("LineNum: %d		child %s is array: %d --- \n",tree->child[0]->linenum, tree->child[0]->attr.name, tree->child[0]->isArray/*, tree->child[1]->child[0]->attr.name, tree->child[1]->child[0]->isArray*/);
					if(tree->child[1]->child[0]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): Cannot use array in position 1 in range of for statement.\n", tree->linenum); ////////////////////////////////////////////////////////////////////////////////////
					}
					if(tree->child[1]->child[1]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): Cannot use array in position 2 in range of for statement.\n", tree->linenum); ////////////////////////////////////////////////////////////////////////////////////
					}
					if(tree->child[1]->child[2] != NULL)
					{
						//printf("LineNum: %d		child %s is array: %d\n",tree->linenum, tree->child[2]->attr.name, tree->child[2]->isArray);
						if(tree->child[1]->child[2]->isArray)
						{
							numErrors++;
							printf("ERROR(%d): Cannot use array in position 3 in range of for statement.\n", tree->linenum); ////////////////////////////////////////////////////////////////////////////////////
						}
					}
					if(tree->child[1]->child[0]->expType != Integer && tree->child[1]->child[0]->expType != UndefinedType)
					{
						numErrors++;
						printf("ERROR(%d): Expecting type int in position 1 in range of for statement but got type %s.\n", tree->linenum, expTypeCheck(tree->child[1]->child[0]->expType));
					}
					if(tree->child[1]->child[1]->expType != Integer && tree->child[1]->child[1]->expType != UndefinedType)
					{
						numErrors++;
						printf("ERROR(%d): Expecting type int in position 2 in range of for statement but got type %s.\n", tree->linenum, expTypeCheck(tree->child[1]->child[1]->expType));
					}
					if(tree->child[1]->child[2] != NULL)
					{
						//printf("LineNum: %d		child %s is array: %d\n",tree->linenum, tree->child[2]->attr.name, tree->child[2]->isArray);
						if(tree->child[1]->child[2]->expType != Integer && tree->child[1]->child[2]->expType != UndefinedType)
						{ 
							numErrors++;
							printf("ERROR(%d): Expecting type int in position 3 in range of for statement but got type %s.\n", tree->linenum, expTypeCheck(tree->child[1]->child[2]->expType));
						}
					}
				}				
				
				//"ERROR(%d): Expecting %s in position %d in range of for statement but got %s.\n"
				tree->memSize = foffset;
				symbolTable.leave();
				scopeDepth--;
				foffset = loffset;
				//printf("LEFT SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				scopeEntered = false;
          		break;
        	case CompoundK: {
		      	//printf("Compound: \n");
				//scope stuff needs to happen here
				bool scopeView = scopeEntered;
				if(!scopeView)
				{
					symbolTable.enter("compound");
					scopeDepth++;
					loffset = foffset;
					//printf("ENTERED SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				}
				else
				{
					scopeEntered = false;
				}
				//printf("BEFORE: 	FOFFSET: %d	-- LOFFSET: %d  LineNum: %d\n",foffset, loffset, tree->linenum);
				for(int i = 0; i<MAXCHILDREN; i++)
				{
					printTreeSemantic(tree->child[i]);
				}
				tree->memSize = foffset;
				//printf("AFTER: 		FOFFSET: %d	-- LOFFSET: %d  LineNum: %d\n",foffset, loffset, tree->linenum);
				if(!scopeView)
				{
					symbolTable.leave();
					//printf("FOFFSET %d -- LOFFSET %d \n", foffset, loffset);
					
					scopeDepth--;
					foffset = loffset;
					
					//printf("LEFT SCOPE!	Scope Depth: %d	Name: %s	Line Number: %d\n", scopeDepth, tree->attr.name, tree->linenum);
				}
          		break; }
        	case ReturnK:
          		//printf("ReturnK\n");
				printTreeSemantic(tree->child[0]);
				if(tree->child[0] != NULL)
				{
					if(tree->child[0]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): Cannot return an array.\n", tree->child[0]->linenum);
					}
					returnFlag = true;
				}
          		break;
			case BreakK:
				if(scopeDepth <= 2)
				{
					numErrors++;
					printf("ERROR(%d): Cannot have a break statement outside of loop.\n", tree->linenum);
				}
				/*
				while(1)
				{}
				
				void asdf()
				{
					break
				}
				*/
          		break;
			case RangeK:
				for(int i = 0; i<MAXCHILDREN; i++)
				{
					printTreeSemantic(tree->child[i]);
				}
				/*if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)
				{
					numErrors++;
					printf("ERROR(%d): Expecting type %s in position 1 in range of for statement but got type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[1]->expType), expTypeCheck(tree->child[0]->expType));
				} */
				//scope stuff needs to happen here
				//printf("line: %d 	Name: %s	1child name: %s		exptype1: %s	2child name: %s		exptype2: %s\n", tree->child[0]->linenum, tree->attr.name, tree->child[0]->attr.name ,expTypeCheck(tree->child[0]->expType), tree->child[1]->attr.name ,expTypeCheck(tree->child[1]->expType));
          		break;
        	default:
          		printf("Unknown ExpNode kind\n");
          		break;
      	}
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->exp) {
//////////////////////////////////////// AssignK ////////////////////////////////////////
 		case AssignK: {
			TreeNode *leftAssignLookUp;
			TreeNode *rightAssignLookUp;

			for(int i = 0; i<MAXCHILDREN; i++)
			{	
				printTreeSemantic(tree->child[i]);
			}

			if(tree->child[0] != NULL)
			{

				leftAssignLookUp = (TreeNode*)symbolTable.lookup(tree->child[0]->attr.name);
				if(leftAssignLookUp != NULL)
				{
					tree->child[0]->expType = leftAssignLookUp->expType;
					tree->child[0]->isArray = leftAssignLookUp->isArray;
					tree->isArray = leftAssignLookUp->isArray;
				}
			}
			
			if(tree->child[1] == NULL)	/*is unary*/
			{
				tree->expType = Integer;
				if(tree->child[0]->isArray)
				{
					numErrors++;
					printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[0]->linenum, tree->attr.name);
				}
				if(tree->child[0]->expType != Integer)
				{
					numErrors++;
					printf("ERROR(%d): Unary '%s' requires an operand of type int but was given type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType));
				}
			}
			else // is not unary
			{

				if(tree->child[1] != NULL)
				{
					if(tree->child[1]->exp == IdK)
					{
						rightAssignLookUp = (TreeNode*)symbolTable.lookup(tree->child[1]->attr.name);
						if(rightAssignLookUp != NULL)
						{
							tree->child[1]->expType = rightAssignLookUp->expType;
							tree->child[1]->isArray = rightAssignLookUp->isArray;

					  		//printf("AssignK: %s		Tree Name: %s	Child Name: %s		Line: %d\n",expTypeCheck(tree->child[1]->expType), tree->attr.name, tree->child[1]->attr.name, tree->linenum);
							
							if(strcmp(tree->attr.name, "=") == 0)
							{
								//printf("Tree name: %s 	LineNumber %d	Child 0: %d		Child 1: %d\n", tree->attr.name, tree->linenum, tree->child[0]->expType, tree->child[1]->expType);
								//printf("line: %d 	Name: %s	1child name: %s		exptype1: %s	2child name: %s		exptype2:	%s\n", tree->child[0]->linenum, tree->attr.name, tree->child[0]->attr.name ,expTypeCheck(tree->child[0]->expType), tree->child[1]->attr.name ,expTypeCheck(tree->child[1]->expType));
								tree->expType = tree->child[0]->expType;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								} 
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
							}
							else
							{
								//printf("line: %d 	Name: %s	1child name: %s		exptype1: %s\n", tree->child[0]->linenum, tree->attr.name, tree->child[0]->attr.name ,expTypeCheck(tree->child[0]->expType));
								tree->expType = Integer;
								if(tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)
								{
									if(tree->child[0]->expType != Integer)
									{
										numErrors++;
										printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType));
									}
									if(tree->child[1]->expType != Integer)
									{
										numErrors++;
										printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->child[1]->linenum, tree->attr.name, expTypeCheck(tree->child[1]->expType));
									}
								}
								if(tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[1]->linenum, tree->attr.name);
								}
								if(tree->child[0]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[0]->linenum, tree->attr.name);
								}
							}
						}
					}
					else
					{
						if(strcmp(tree->attr.name, "=") == 0)
						{
							//printf("Tree name: %s 	LineNumber %d	Child 0: %d		Child 1: %d\n", tree->attr.name, tree->linenum, tree->child[0]->expType, tree->child[1]->expType);
							//printf("line: %d 	Name: %s	1child name: %s		exptype1: %s	2child name: %s		exptype2: %s\n", tree->child[0]->linenum, tree->attr.name, tree->child[0]->attr.name ,expTypeCheck(tree->child[0]->expType), tree->child[1]->attr.name ,expTypeCheck(tree->child[1]->expType));
							tree->expType = tree->child[0]->expType;
							if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
							}
							if(tree->child[0]->isArray && !tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
							}
							if(!tree->child[0]->isArray && tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
							}
						}
						else
						{
							//printf("line: %d 	Name: %s	1child name: %s		exptype1: %s\n", tree->child[0]->linenum, tree->attr.name, tree->child[0]->attr.name ,expTypeCheck(tree->child[0]->expType));
							tree->expType = Integer;
							
							if(tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)
							{
								if(tree->child[0]->expType != Integer)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType));
								}
								if(tree->child[1]->expType != Integer)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->child[1]->linenum, tree->attr.name, expTypeCheck(tree->child[1]->expType));
								}
							}
							if(tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[1]->linenum, tree->attr.name);
							}
							if(tree->child[0]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[0]->linenum, tree->attr.name);
							}
						}
					}
					
				}
				/*if(leftAssignLookUp != NULL)
				{
					//TreeNode *rightAssignLookUp = tree->child[1];
					//printf("Right Assign: %s	Left Assign: %s\n", rightAssignLookUp->attr.name, leftAssignLookUp->attr.name);
				}*/
				
				/*if(assignLookUp->subkind.decl != VarK)
				{
					printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n", tree->child[0]->linenum);
				}*/
			}
          	break; }  
//////////////////////////////////////// OpK //////////////////////////////////////// 
		case OpK: {
          	//printf("Op: %s	Line: %d\n",tree->attr.name, tree->linenum);
			TreeNode *leftOpLookUp;
			TreeNode *rightOpLookUp;

			for(int i = 0; i<MAXCHILDREN; i++)
			{
				printTreeSemantic(tree->child[i]);
				tree->expType = UndefinedType;
			}
			//tree->expType = UndefinedType;
			//printf("HERE IS SEG linenumber: %d 	name: %s\n",tree->child[0]->linenum, tree->attr.name);
			if(tree->child[0] != NULL && tree->child[0]->exp == IdK)
			{
				leftOpLookUp = (TreeNode*)symbolTable.lookup(tree->child[0]->attr.name);
				if(leftOpLookUp != NULL)
				{
					tree->child[0]->expType = leftOpLookUp->expType;
					tree->child[0]->isArray = leftOpLookUp->isArray;
				}

			}
			
			if(tree->child[1] == NULL) // is unary
			{
				tree->isConst = true;

				if(strcmp(tree->attr.name, "NOT") == 0)
				{
					tree->expType = Boolean;
					if(tree->child[0]->expType != Boolean && tree->child[0]->expType != UndefinedType)	
					{
						numErrors++;
						printf("ERROR(%d): Unary 'not' requires an operand of type bool but was given type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
					}
					tree->isArray = tree->child[0]->isArray;
					if(tree->child[0]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): The operation 'not' does not work with arrays.\n", tree->child[0]->linenum);
					}

				}

				if(strcmp(tree->attr.name, "-") == 0)
				{
					tree->expType = Integer;
					if(tree->child[0]->expType != Integer && tree->child[0]->expType != UndefinedType)	
					{
						numErrors++;
						printf("ERROR(%d): Unary 'chsign' requires an operand of type int but was given type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
					}
					//tree->isArray = tree->child[0]->isArray;
					if(tree->child[0]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): The operation 'chsign' does not work with arrays.\n", tree->child[0]->linenum);
					}
				}
				if(strcmp(tree->attr.name, "*") == 0)
				{
					tree->expType = Integer;
					//tree->isArray = tree->child[0]->isArray;
					if(!tree->child[0]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", tree->child[0]->linenum);
					}

				}
				if(strcmp(tree->attr.name, "?") == 0)
				{
					tree->expType = Integer;
					tree->isConst = false;
					if(tree->child[0]->expType != Integer && tree->child[0]->expType != UndefinedType)	
					{
						numErrors++;
						printf("ERROR(%d): Unary '?' requires an operand of type int but was given type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
					}
					tree->isArray = tree->child[0]->isArray;
					if(tree->child[0]->isArray)
					{
						numErrors++;
						printf("ERROR(%d): The operation '?' does not work with arrays.\n", tree->child[0]->linenum);
					}

				}
			}
			else // is not unary
			{
				
				if(tree->child[1] != NULL)
				{
					
					if(tree->child[0]->isConst && tree->child[1]->isConst)
					{
						tree->isConst = true;
						
					}
					//printf("LINE: %d	IsConst: %d		Value: %s		Child1 isconst: %d		Child1 name: %d		Child2 isconst: %d		Child2 name: %d\n", tree->linenum, tree->isConst, tree->attr.name, tree->child[0]->isConst, tree->child[0]->attr.value, tree->child[1]->isConst, tree->child[1]->attr.value);
					if(tree->child[1]->exp == IdK)
					{

						rightOpLookUp = (TreeNode*)symbolTable.lookup(tree->child[1]->attr.name);
						if(rightOpLookUp != NULL)
						{
							tree->child[1]->expType = rightOpLookUp->expType;
							tree->child[1]->isArray = rightOpLookUp->isArray;


							if(strcmp(tree->attr.name, "AND") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != Boolean && tree->child[0]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): 'and' requires operands of type bool but lhs is of type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
								}
								if(tree->child[1]->expType != Boolean && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): 'and' requires operands of type bool but rhs is of type %s.\n", tree->child[1]->linenum, expTypeCheck(tree->child[1]->expType));
								}
								tree->isArray = tree->child[0]->isArray;
								if(tree->child[0]->isArray || tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): The operation 'and' does not work with arrays.\n", tree->child[0]->linenum);
								}
									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, "OR") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != Boolean && tree->child[0]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): 'or' requires operands of type bool but lhs is of type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
								}
								if(tree->child[1]->expType != Boolean && tree->child[0]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): 'or' requires operands of type bool but rhs is of type %s.\n", tree->child[1]->linenum, expTypeCheck(tree->child[1]->expType));
								}
								tree->isArray = tree->child[0]->isArray;
								if(tree->child[0]->isArray || tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): The operation 'or' does not work with arrays.\n", tree->child[0]->linenum);
								}
									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, "==") == 0)
							{
								//tree->expType = tree->child[0]->expType;
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
										
										//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
								}

							else if(strcmp(tree->attr.name, "!=") == 0)
							{
								//tree->expType = tree->child[0]->expType;
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}

									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, "<=") == 0)
							{
								//tree->expType = tree->child[0]->expType;
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, "<") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, ">=") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, ">") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, "[") == 0)
							{
								tree->expType = tree->child[0]->expType;
								if(!tree->child[0]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): Cannot index nonarray '%s'.\n", tree->child[0]->linenum, tree->child[0]->attr.name);
								}
								if(tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): Array index is the unindexed array '%s'.\n", tree->child[0]->linenum, tree->child[1]->attr.name);
								}
								if(tree->child[1]->expType != Integer && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n", tree->child[0]->linenum, tree->child[0]->attr.name, expTypeCheck(tree->child[1]->expType));
								}
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else
							{
								tree->expType = Integer;
									//if(tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)
									//{
								if(tree->child[0]->expType != Integer && tree->child[0]->expType != UndefinedType)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType));
								}
								if(tree->child[1]->expType != Integer && tree->child[1]->expType != UndefinedType)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->child[1]->linenum, tree->attr.name, expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray || tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[1]->linenum, tree->attr.name);
								}

							}
									
						}
					}
					else
					{
						if(strcmp(tree->attr.name, "AND") == 0)
						{
							tree->expType = Boolean;
							if(tree->child[0]->expType != Boolean && tree->child[0]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): 'and' requires operands of type bool but lhs is of type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
							}
							if(tree->child[1]->expType != Boolean && tree->child[1]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): 'and' requires operands of type bool but rhs is of type %s.\n", tree->child[1]->linenum, expTypeCheck(tree->child[1]->expType));
							}
							//tree->isArray = tree->child[0]->isArray;
							if(tree->child[0]->isArray || tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): The operation 'and' does not work with arrays.\n", tree->child[0]->linenum);
							}
									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
						}
						else if(strcmp(tree->attr.name, "OR") == 0)
						{
							tree->expType = Boolean;
							if(tree->child[0]->expType != Boolean && tree->child[0]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): 'or' requires operands of type bool but lhs is of type %s.\n", tree->child[0]->linenum, expTypeCheck(tree->child[0]->expType));
							}
							if(tree->child[1]->expType != Boolean && tree->child[1]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): 'or' requires operands of type bool but rhs is of type %s.\n", tree->child[1]->linenum, expTypeCheck(tree->child[1]->expType));
							}
							//tree->isArray = tree->child[0]->isArray;
							if(tree->child[0]->isArray || tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): The operation 'or' does not work with arrays.\n", tree->child[0]->linenum);
							}
									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
						}
						else if(strcmp(tree->attr.name, "==") == 0)
						{
							//tree->expType = tree->child[0]->expType;
							tree->expType = Boolean;
							if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
							}
							if(tree->child[0]->isArray && !tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
							}
							if(!tree->child[0]->isArray && tree->child[1]->isArray)
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
							}
									
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
						}
						else if(strcmp(tree->attr.name, "!=") == 0)
						{
							tree->expType = Boolean;
							if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
							}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}

							//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
						}
						else if(strcmp(tree->attr.name, "<=") == 0)
						{
							tree->expType = Boolean;
							if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
							}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
							//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
						}
						else if(strcmp(tree->attr.name, "<") == 0)
						{
							tree->expType = Boolean;
							if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
							{
								numErrors++;
								printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
							}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
							//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
						}
							else if(strcmp(tree->attr.name, ">=") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, ">") == 0)
							{
								tree->expType = Boolean;
								if(tree->child[0]->expType != tree->child[1]->expType && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType), expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray && !tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
								if(!tree->child[0]->isArray && tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->child[0]->linenum, tree->attr.name);
								}
									//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else if(strcmp(tree->attr.name, "[") == 0)
							{
								tree->expType = tree->child[0]->expType;
								if(!tree->child[0]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): Cannot index nonarray '%s'.\n", tree->child[0]->linenum, tree->child[0]->attr.name);
								}
								if(tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): Array index is the unindexed array '%s'.\n", tree->child[0]->linenum, tree->child[1]->attr.name);
								}
								if(tree->child[1]->expType != Integer && tree->child[0]->expType != UndefinedType && tree->child[1]->expType != UndefinedType)	
								{
									numErrors++;
									printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n", tree->child[0]->linenum, tree->child[0]->attr.name, expTypeCheck(tree->child[1]->expType));
								}
								//printf("TEST(%d): 	'%s'\n", tree->child[0]->linenum, tree->attr.name);
							}
							else
							{
								tree->expType = Integer;

								if(tree->child[0]->expType != Integer && tree->child[0]->expType != UndefinedType)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->child[0]->linenum, tree->attr.name, expTypeCheck(tree->child[0]->expType));
								}
								if(tree->child[1]->expType != Integer && tree->child[1]->expType != UndefinedType)
								{
									numErrors++;
									printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->child[1]->linenum, tree->attr.name, expTypeCheck(tree->child[1]->expType));
								}
								if(tree->child[0]->isArray || tree->child[1]->isArray)
								{
									numErrors++;
									printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->child[1]->linenum, tree->attr.name);
								}

							}
					}
			
				}

			}
          break; }
//////////////////////////////////////// IdK ////////////////////////////////////////
        case IdK: {
			TreeNode *idLookUp = (TreeNode*)symbolTable.lookup(tree->attr.name);
			tree->expType = UndefinedType;
         	//printf("Id: %s\n",tree->attr.name);
			if(idLookUp == NULL)
			{
				numErrors++;
				printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->linenum, tree->attr.name);
			}
			else
			{
				tree->subkind.decl = idLookUp->subkind.decl; 
				tree->expType = idLookUp->expType;
				tree->isArray = idLookUp->isArray;
				tree->isStatic = idLookUp->isStatic;
				//printf("Id: %s  lineNum: %d  isArray%d\n",tree->attr.name, tree->linenum, tree->isArray);
				//printf("IDLOOKUP: %d lineNum: %d  isArray%d\n", idLookUp->isArray, tree->linenum, tree->isArray);
				if(tree->subkind.decl == FuncK)
				{
					numErrors++;
					printf("ERROR(%d): Cannot use function '%s' as a variable.\n", tree->linenum, tree->attr.name);
				}
				
				tree->mem = idLookUp->mem;
				tree->memOffset = idLookUp->memOffset;
				tree->memSize = idLookUp->memSize;

				/*for(int i = 0; i<MAXCHILDREN; i++)
				{
					if(tree->child[i] != NULL)
					{
						printf("In ID loop, NAME: %s", tree->child[i]->attr.name);
					}
					printTreeSemantic(tree->child[i]);
					if(tree->child[i] != NULL)//
					{
						if(!tree->child[i]->isArray && tree->exp == OpK)
						{
							printf("ERROR(%d): Cannot index nonarray '%s'.\n", tree->linenum, tree->attr.name);
						}
					}
				}*/
			}

          break; }
		case ConstantK:
          //printf("Const: \n");
			for(int i = 0; i<MAXCHILDREN; i++)
			{
				printTreeSemantic(tree->child[i]);
			}
			if(tree->isArray)
			{
				tree->mem = Global;
				tree->memOffset = goffset - 1;
				goffset = goffset - tree->memSize;
			}
          break;
        case InitK:
          //printf("InitK: %s\n",tree->attr.name);
          break;

        case CallK: {
			/*"ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n"
			"ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n"
			"ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n"
			"ERROR(%d): Expecting %s in parameter %i of call to '%s' declared on line %d but got %s.\n"*/
          	//printf("CallK: %s\n",tree->attr.name);
			bool isIOCall = false;
			for(int i = 0; i<MAXCHILDREN; i++)
			{
				printTreeSemantic(tree->child[i]);
			}
			TreeNode *callLookUp;

			callLookUp = (TreeNode*)symbolTable.lookup(tree->attr.name);
			/*if(callLookUp != NULL)
			{
				printf("CallNAME: %s - CallISIO: %d --- treeNAME: %s - treeISIO: %d\n", callLookUp->attr.name, callLookUp->isIO, tree->attr.name, tree->isIO);
			}*/
			if(!strcmp("output", tree->attr.name) || !strcmp("outputb", tree->attr.name) || !strcmp("outputc", tree->attr.name) /*|| !strcmp("input", tree->attr.name) || !strcmp("inputb", tree->attr.name) || !strcmp("inputc", tree->attr.name)*/ || !strcmp("outnl", tree->attr.name))
			{
				isIOCall = true;
			}
			if(callLookUp == NULL)
			{
				numErrors++;
				printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->linenum, tree->attr.name);
				tree->expType = UndefinedType;
			}
			else if(callLookUp->subkind.decl != FuncK && !isIOCall)
			{
				numErrors++;
				printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", tree->linenum, tree->attr.name);
			}
			else 
			{
				if(!isIOCall)
				{
					tree->expType = callLookUp->expType;
				}
				/*if(tree->child[0] != NULL)
				{
					if(tree->child[0]->exp == ConstantK)
					{
						tree->expType = tree->child[0]->expType;
					}
				}
				else
				{
					
				}*/
			}
			
          break; }

        default:
          printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else printf("Unknown node kind\n");
	
	if(tree->sibling != NULL)
	{
		printTreeSemantic(tree->sibling);
	}

}

const char* expTypeCheck(ExpType type)
{
	switch(type){
		case 0:
			return "void";
		break;
		case 1:
			return "int";
		break;
		case 2:
			return "bool";
		break;
		case 3:
			return "char";
		break;
		case 4:
			return "CharInt";
		break;
		case 5:
			return "Equal";
		break;
		case 6:
			return "UndefinedType";
		break;
		
	}
}

void addIOLibrary(TreeNode *t)
{
	TreeNode* tree[7];//7

	tree[0] = newDeclNode(FuncK);
	tree[0]->linenum = -1;
	tree[0]->attr.name = strdup("output");
	tree[0]->expType = Void;
	tree[0]->child[0] = newDeclNode(ParamK);
	tree[0]->child[0]->linenum = -1;
	tree[0]->child[0]->expType = Integer;
	tree[0]->child[0]->attr.name = strdup("*dummy*");
	tree[0]->isIO = true;
	symbolTable.insert(tree[0]->attr.name, tree[0]);//

	tree[1] = newDeclNode(FuncK);
	tree[1]->linenum = -1;
	tree[1]->attr.name = strdup("outputb");
	tree[1]->expType = Void;
	tree[1]->child[0] = newDeclNode(ParamK);
	tree[1]->child[0]->linenum = -1;
	tree[1]->child[0]->expType = Boolean;
	tree[1]->child[0]->attr.name = strdup("*dummy*");
	tree[1]->isIO = true;
	symbolTable.insert(tree[1]->attr.name, tree[1]);//

	tree[2] = newDeclNode(FuncK);
	tree[2]->linenum = -1;
	tree[2]->attr.name = strdup("outputc");
	tree[2]->expType = Void;
	tree[2]->child[0] = newDeclNode(ParamK);
	tree[2]->child[0]->linenum = -1;
	tree[2]->child[0]->expType = Char;
	tree[2]->child[0]->attr.name = strdup("*dummy*");
	tree[2]->isIO = true;
	symbolTable.insert(tree[2]->attr.name, tree[2]);//

	tree[3] = newDeclNode(FuncK);
	tree[3]->linenum = -1;
	tree[3]->attr.name = strdup("outnl");
	tree[3]->expType = Void;
	tree[3]->child[0] = newDeclNode(ParamK);
	tree[3]->child[0]->linenum = -1;
	tree[3]->child[0]->expType = Void;
	tree[3]->child[0]->attr.name = strdup("*dummy*");
	tree[3]->isIO = true;
	symbolTable.insert(tree[3]->attr.name, tree[3]);//

	tree[4] = newDeclNode(FuncK);
	tree[4]->linenum = -1;
	tree[4]->attr.name = strdup("input");
	tree[4]->expType = Integer;
	tree[4]->isIO = true;
	symbolTable.insert(tree[4]->attr.name, tree[4]);//
	
	tree[5] = newDeclNode(FuncK);
	tree[5]->linenum = -1;
	tree[5]->attr.name = strdup("inputb");
	tree[5]->expType = Boolean;
	tree[5]->isIO = true;
	symbolTable.insert(tree[5]->attr.name, tree[5]);//

	tree[6] = newDeclNode(FuncK);
	tree[6]->linenum = -1;
	tree[6]->attr.name = strdup("inputc");
	tree[6]->expType = Char;
	tree[6]->isIO = true;
	symbolTable.insert(tree[6]->attr.name, tree[6]);//

	tree[0]->sibling = tree[1];
	tree[1]->sibling = tree[2];
	tree[2]->sibling = tree[3];
	tree[3]->sibling = tree[4];
	tree[4]->sibling = tree[5];
	tree[5]->sibling = tree[6];
	tree[6]->sibling = t;
}



