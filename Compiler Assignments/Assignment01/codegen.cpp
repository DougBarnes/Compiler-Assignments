#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeNode.h"
#include "emitcode.h"
#include "codegen.h"
#include "symbolTable.h"
extern int goffset;
extern int foffset;
extern int memOffset;
extern SymbolTable symbolTable;
int toffset = -2;
bool storeFlag = false;
bool isUnaryFlag= true;
int breakLocation = 0;

FILE *code;

void codegen(char* outFile, TreeNode *tree)
{
	//printf("Start IOLIB %s\n", tree->attr.name);
	char* tempName = tree->attr.name;
	//printf("START OF IT!\n");
	code = fopen(outFile, "w");
	//printf("CODEGEN TEST: %s\n", outFile);
	IOLib();
	//printf("BEFORE CODEGENPARSER!\n");

	tree->attr.name = tempName;
	//printf("IOLIB %s\n", tree->attr.name);
	codegenParse(tree);
	codegenMain(tree);
	//printf("AFTER CODEGENPARSER!\n");
}

void codegenParse(TreeNode *tree)
{
	//printf("Start of codegen  NAME: %s\n", tree->attr.name);
	if(tree == NULL)
	{
		//printf("returned null\n");
		return;
	}
	//printf("START OF CODEGENPARSER\n");
  	//while (tree != NULL) {
	if (tree->nodekind==DeclK)
	{ 	switch (tree->subkind.decl) {
		case VarK:
			//printf("VarK: \n");
			if(tree->mem == Local)
			{
				if(tree->isArray)
				{
					emitRM((char *)"LDC",3,tree->memSize - 1,6,(char *)("load size of array"), (char *) tree->attr.name);
					emitRM((char *)"ST",3,toffset,1,(char *)("save size of array"), (char *) tree->attr.name);
					toffset = toffset - tree->memSize;
				}
				else
				{
					toffset -= tree->memSize;
					emitComment((char *)("TOFF dec:"), toffset);
				}
			}
			break;
		case FuncK:
		{
			//printf("FuncK: \n");
			
			int paramCount = 0;
			tree->codeLineNum = emitSkip(0);
			//printf("FUNCK %p\n", (void *) &tree);
			//printf("FUNCK %s , %d\n", tree->attr.name, tree->codeLineNum);
			emitComment((char *)("FUNCTION"), (char *) tree->attr.name);
			TreeNode* countParameters = tree->child[0];
			toffset = -2;
			emitComment((char *)("TOFF set:"), toffset);
			while(countParameters != NULL)
			{
				countParameters = countParameters->sibling;
				paramCount++;
				//toffset--;
				//emitComment((char *)("TOFF dec:"), toffset);
						
			}
			toffset = toffset - paramCount;
			//printf("funck paramCount: %d\n", paramCount);
			int tempoffset = toffset;
			emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
			for(int i = 0; i<MAXCHILDREN; i++)
			{
				if(tree->child[i] != NULL)
				{
					//printf("In FUNCK %s\n",  tree->attr.name);
					codegenParse(tree->child[i]);
				}
			}
			emitComment((char *)("Add standard closing in case there is no return statement"));
			emitRM((char *)"LDC", 2, 0, 6,(char *)"Set return value to 0");
			emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
			emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
			emitRM((char *)"JMP",7,0,3,(char *)("Return"));
			emitComment((char *)("END FUNCTION"), (char *) tree->attr.name);
			break;
		}
		case ParamK:
			//printf("ParamK: %s\n",tree->attr.name);
			/*for(int i = 0; i<MAXCHILDREN; i++)
			{
				codegenParse(tree->child[i]);
			}*/
			break;
		default:
			//printf("Unknown ExpNode kind\n");
			break;
		}
	}
    else if (tree->nodekind==StmtK)
    {	switch (tree->subkind.stmt) {
        case IfK:
		{
			//printf("If\n");
			storeFlag = false;
			emitComment((char *)("IF"));
			codegenParse(tree->child[0]);
			emitComment((char *)("THEN"));
			int elseLocation = 0;
			int thenLocation = emitSkip(1);
			codegenParse(tree->child[1]);
			if(tree->child[2] != NULL)
			{
				elseLocation = emitSkip(1);
			}
			backPatchAJumpToHere((char *)("JZR"),3,thenLocation, (char *)("Jump around the THEN if false [backpatch]"));
			if(tree->child[2] != NULL)
			{
				emitComment((char *)("ELSE"));
				codegenParse(tree->child[2]);
				backPatchAJumpToHere((char *)("JMP"),7,elseLocation, (char *)("Jump around the ELSE [backpatch]"));
			}
			emitComment((char *)("END IF"));
          	break;
		}
        case WhileK:
		{
			int backpatch = emitSkip(0);
			storeFlag = false;
			//printf("main address %p\n", (void *) &mainLookup);
			emitComment((char *)("WHILE"));
			codegenParse(tree->child[0]);
			int backBreak = breakLocation;
			breakLocation = emitSkip(0);
			//toffset++;
			//emitComment((char *)("TOFF inc:"), toffset);
			//emitRM((char *)"LD",4,tree->memOffset,1,(char *)("Pop left into acl"));
			//emitRO((char *)"TLT",3,4,3,(char *)("Op"), (char *)tree->child[0]->attr.name);
			emitRM((char *)"JNZ",3,1,7,(char *)("Jump to while part"));
			emitComment((char *)("DO"));
			int whileJump = emitSkip(1);
			codegenParse(tree->child[1]);
			//toffset--;
			//emitComment((char *)("TOFF dec:"), toffset);
			emitRM((char *)"JMP",7,backpatch-emitSkip(0)-1,7,(char *)("go to beginning of loop"));
			int jumpLocation = emitSkip(0);
			backPatchAJumpToHere(whileJump, (char *)("Jump past loop [backpatch]"));
			breakLocation = backBreak;
			emitNewLoc(jumpLocation);
			emitComment((char *)("END WHILE"));
          	//printf("While: \n");
          	break;
		}
        case ForK:
          	//printf("For: %s\n",tree->attr.name);
          	break;
        case CompoundK:
		{
          	//printf("Compound: %s\n",tree->attr.name);
			int ghostToffset = toffset;
			emitComment((char *)("COMPOUND"));
			//toffset = -2;

			emitComment((char *)("TOFF set:"), toffset);
			emitComment((char *)("Compound Body"));
			for(int i = 0; i<MAXCHILDREN; i++)
			{
				codegenParse(tree->child[i]);
			}
			//emitComment((char *)("TOFF set:"), toffset);
			toffset = ghostToffset;
			emitComment((char *)("TOFF set:"), toffset);
			emitComment((char *)("END COMPOUND"));
          	break;
		}
        case ReturnK:
          	//printf("ReturnK\n");
			emitComment((char *)("RETURN"));
			if(tree->child[0] != NULL)
			{
				if(tree->isArray)
				{
					if(!strcmp(tree->child[0]->attr.name, "["))
					{
						
					}
					else
					{
						storeFlag = false;
						codegenParse(tree->child[0]);
						emitRM((char *)"LDA",2,0,3,(char *)("Copy result to return register"));
					}
					
				}
				else
				{
					storeFlag = false;
					codegenParse(tree->child[0]);
					emitRM((char *)"LDA",2,0,3,(char *)("Copy result to return register"));
				}
			}
			emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
			emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
			emitRM((char *)"JMP",7,0,3,(char *)("Return"));
          	break;
		case BreakK:
			emitComment((char *)("BREAK"));
			emitRM((char *)"JMP",7,breakLocation-emitSkip(0),7,(char *)("break"));
          	//printf("BreakK\n");
          	break;
		case RangeK:
          	//printf("RangeK\n");
          	break;
        default:
          	//printf("Unknown ExpNode kind\n");
          	break;
      	}
    }
    else if (tree->nodekind==ExpK)
    { 
		//emitComment((char *)("EXPRESSION"));
		
		switch (tree->exp) {
        case OpK:
		{
			emitComment((char *)("OP EXPRESSION"));
          	//printf("Op: %s  %d\n",tree->attr.name, tree->attr.value);
			if(tree->child[1] == NULL) // unary
			{
				codegenParse(tree->child[0]);
				if(!strcmp(tree->attr.name, "-"))
				{
					emitRO((char *)"NEG",3,3,3,(char *)("Op unary"), (char *)tree->attr.name);
				}
				else if(!strcmp(tree->attr.name, "*"))
				{
					if(tree->mem == Global)
					{
						emitRM((char *)"LDA",3,tree->child[0]->memOffset,0,(char *)("Load address of base of array"), (char *)tree->child[0]->attr.name);
					}
					else if(tree->mem == Parameter)
					{
						emitRM((char *)"LD",3,tree->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[0]->attr.name);
					}
					else
					{
						emitRM((char *)"LDA",3,tree->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[0]->attr.name);
					}
					emitRM((char *)"LD",3,1,3,(char *)("Load array size"));
					
				}
				else if(!strcmp(tree->attr.name, "NOT"))
				{
					emitRM((char *)"LDC",4,1,6,(char *)("Load 1"));
					emitRO((char *)"XOR",3,3,4,(char *)("Op XOR to get logical not"));
				}
				else if(!strcmp(tree->attr.name, "?"))
				{
					emitRO((char *)"RND",3,3,3,(char *)("Op unary"), (char *)tree->attr.name);
				}
			}
			else //binary
			{
				
				if(tree->child[0] != NULL )
				{
					if(tree->child[0]->child[0] != NULL)
					{
						//printf("In Binary OPK %s\n", tree->child[0]->attr.name);
						if(tree->child[0]->child[0]->isArray) // is Array
						{
							//printf("OPK ARRAY\n");
							if(tree->child[0]->child[0]->mem == Global)
							{
								emitRM((char *)"LDA",3,tree->child[0]->child[0]->memOffset,0,(char *)("Load address of base of array"), (char *)tree->child[0]->child[0]->attr.name);
							}
							else if(tree->child[0]->child[0]->mem == Parameter)
							{
								emitRM((char *)"LD",3,tree->child[0]->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[0]->child[0]->attr.name);
							}
							else
							{
								emitRM((char *)"LDA",3,tree->child[0]->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[0]->child[0]->attr.name);
							}
							emitRM((char *)"ST",3,toffset,1,(char *)("Push left side"));
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
							codegenParse(tree->child[0]->child[1]);
							toffset++;
							emitComment((char *)("TOFF inc:"), toffset);
							emitRM((char *)"LD",4,toffset,1,(char *)("1 Pop left into acl"));
							emitRO((char *)"SUB",3,4,3,(char *)("compute location from index"));
							emitRM((char *)"LD",3,0,3,(char *)("Load array element"));
							emitRM((char *)"ST",3,toffset,1,(char *)("Push left side"));
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
							if(tree->child[1]->child[0]->mem == Global)
							{
								emitRM((char *)"LDA",3,tree->child[1]->child[0]->memOffset,0,(char *)("Load address of base of array"), (char *)tree->child[1]->child[0]->attr.name);
							}
							else if(tree->child[1]->child[0]->mem == Parameter)
							{
								emitRM((char *)"LD",3,tree->child[1]->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[1]->child[0]->attr.name);
							}
							else
							{
								emitRM((char *)"LDA",3,tree->child[1]->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[1]->child[0]->attr.name);
							}
							emitRM((char *)"ST",3,toffset,1,(char *)("Push left side"));
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
							codegenParse(tree->child[1]->child[1]);
							toffset++;
							emitComment((char *)("TOFF inc:"), toffset);
							emitRM((char *)"LD",4,toffset,1,(char *)("2 Pop left into acl"));
							emitRO((char *)"SUB",3,4,3,(char *)("compute location from index"));
							emitRM((char *)"LD",3,0,3,(char *)("Load arry element"));
							toffset++;
							emitComment((char *)("TOFF inc:"), toffset);
							emitRM((char *)"LD",4,toffset,1,(char *)("3 Pop left into acl"));
							if(!strcmp(tree->attr.name, "*"))
							{
								emitRO((char *)"MUL",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "+"))
							{
								emitRO((char *)"ADD",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "-"))
							{
								emitRO((char *)"SUB",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "/"))
							{
								emitRO((char *)"DIV",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "%"))
							{
								emitRO((char *)"MOD",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "<"))
							{
								emitRO((char *)"TLT",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, ">"))
							{
								emitRO((char *)"TGT",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, ":<:"))
							{
								emitRO((char *)"MIN",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, ":>:"))
							{
								emitRO((char *)"MAX",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, ">="))
							{
								emitRO((char *)"TGE",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "<="))
							{
								emitRO((char *)"TLE",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "!="))
							{
								emitRO((char *)"TNE",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "=="))
							{
								emitRO((char *)"TEQ",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "AND"))
							{
								emitRO((char *)"AND",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							else if(!strcmp(tree->attr.name, "OR"))
							{
								emitRO((char *)"OR",3,4,3,(char *)("Op"), (char *)tree->attr.name);
							}
							
						}
						if(!strcmp(tree->attr.name, "["))
						{
							emitRM((char *)"SUB",3,4,3,(char *)("compute location from index"));
							emitRM((char *)"LD",3,0,3,(char *)("Load array element"));
							toffset++;
							emitComment((char *)("TOFF inc:"), toffset);
						}
					}
					
					else // is NOT Array
					{
						//printf("OPK not array\n");
						storeFlag = false;
						codegenParse(tree->child[0]);
						emitRM((char *)"ST",3,toffset,1,(char *)("Push left side"));
						toffset--;
						emitComment((char *)("TOFF dec:"), toffset);
						codegenParse(tree->child[1]);
						toffset++;
						emitComment((char *)("TOFF inc:"), toffset);
						emitRM((char *)"LD",4,toffset,1,(char *)("4 Pop left into acl"));
						if(!strcmp(tree->attr.name, "*"))
						{
							emitRO((char *)"MUL",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "+"))
						{
							emitRO((char *)"ADD",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "-"))
						{
							emitRO((char *)"SUB",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "/"))
						{
							emitRO((char *)"DIV",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "%"))
						{
							emitRO((char *)"MOD",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "<"))
						{
							emitRO((char *)"TLT",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, ">"))
						{
							emitRO((char *)"TGT",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, ":<:"))
						{
							emitRO((char *)"MIN",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, ":>:"))
						{
							emitRO((char *)"MAX",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, ">="))
						{
							emitRO((char *)"TGE",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "<="))
						{
							emitRO((char *)"TLE",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "!="))
						{
							emitRO((char *)"TNE",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "=="))
						{
							emitRO((char *)"TEQ",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "AND"))
						{
							emitRO((char *)"AND",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "OR"))
						{
							emitRO((char *)"OR",3,4,3,(char *)("Op"), (char *)tree->attr.name);
						}
						else if(!strcmp(tree->attr.name, "["))
						{
							emitRM((char *)"SUB",3,4,3,(char *)("compute location from index"));
							emitRM((char *)"LD",3,0,3,(char *)("Load array element"));
							toffset++;
							emitComment((char *)("TOFF inc:"), toffset);
						}
					}
				}
			}
          	break;
		}
        case ConstantK:
		{
          	//printf("Const: %s  %d\n",tree->attr.name, tree->attr.value);
		  	if(tree->expType == Integer)
		  	{
				emitRM((char *)"LDC", 3, tree->attr.value, 6,(char *)"Load integer constant");
		  	}
		  	else if(tree->expType == Char)
		  	{
				emitRM((char *)"LDC", 3, tree->attr.cvalue, 6,(char *)"Load char constant");
		  	}
		  	else if(tree->expType == Boolean)
		  	{
				emitRM((char *)"LDC", 3, tree->attr.value, 6,(char *)"Load boolean constant");
		  	}
        	break;
		}
        case IdK:
		{
          	//printf("Id:  %s  %d\n",tree->attr.name, tree->attr.value);
			
			if (storeFlag)
			{
				
				if(tree->mem == Global)
				{
					if(tree->isArray)
					{
						
					}
					else
					{
						emitRM((char *)"ST",3,tree->memOffset,0,(char *)("Store variable"), tree->attr.name);
						storeFlag = false;
					}					
				}
				else if (tree->mem == Local)
				{
					if(tree->isArray)
					{
						
					}
					else
					{
						emitRM((char *)"ST",3,tree->memOffset,1,(char *)("Store variable"), tree->attr.name);
						storeFlag = false;
					}					
				}
				else if (tree->mem == LocalStatic)
				{
					if(tree->isArray)
					{
						
					}
					else
					{
						emitRM((char *)"ST",3,tree->memOffset,0,(char *)("Store variable"), tree->attr.name);
						storeFlag = false;
					}	
				}
			}
			else
			{
				if(tree->mem == Global)
				{
					if(isUnaryFlag)
					{
						if(tree->isArray)
						{
							emitRM((char *)"LD",3,tree->memOffset,0,(char *)("1 Load address of base of array"), tree->attr.name);
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
						}
						else
						{
							
							emitRM((char *)"LD",3,tree->memOffset,0,(char *)("1 Load variable"), tree->attr.name);
						}
					}
					else
					{
						emitRM((char *)"LD",4,tree->memOffset,0,(char *)("1 load lhs variable"), tree->attr.name);
					}					
				}
				else if (tree->mem == Local)
				{
					if(isUnaryFlag)
					{
						if(tree->isArray)
						{
							emitRM((char *)"LDA",3,tree->memOffset,1,(char *)("2 Load address of base of array"), tree->attr.name);
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
						}
						else
						{
							
							emitRM((char *)"LD",3,tree->memOffset,1,(char *)("2 Load variable"), tree->attr.name);
						}
					}
					else
					{
						emitRM((char *)"LD",4,tree->memOffset,1,(char *)("2 load lhs variable"), tree->attr.name);
					}					
				}
				else if(tree->mem == LocalStatic)
				{
					if(isUnaryFlag)
					{
						if(tree->isArray)
						{
							emitRM((char *)"LD",3,tree->memOffset,0,(char *)("3 Load address of base of array"), tree->attr.name);
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
						}
						else
						{
							
							emitRM((char *)"LD",3,tree->memOffset,0,(char *)("3 Load variable"), tree->attr.name);
						}
					}
					else
					{
						emitRM((char *)"LD",4,tree->memOffset,0,(char *)("3 load lhs variable"), tree->attr.name);
					}					
				}
				else if(tree->mem == Parameter)
				{
					if(isUnaryFlag)
					{
						if(tree->isArray)
						{
							emitRM((char *)"LD",3,tree->memOffset,1,(char *)("4 Load address of base of array"), tree->attr.name);
							toffset--;
							emitComment((char *)("TOFF dec:"), toffset);
						}
						else
						{
							
							emitRM((char *)"LD",3,tree->memOffset,1,(char *)("4 Load variable"), tree->attr.name);
						}
					}
					else
					{
						emitRM((char *)"LD",4,tree->memOffset,1,(char *)("4 load lhs variable"), tree->attr.name);
					}
				}
			}
          	break;
		}
        case AssignK://////////////////////////////////////////////////////////////////////////////////////////
		{
			emitComment((char *)("ASSIGN EXPRESSION"));
          	//printf("AssignK: %s  %d\n",tree->attr.name, tree->child[1]->attr.value);
			TreeNode* assignLookUp = (TreeNode*)symbolTable.lookup(tree->attr.name);
			//TreeNode* constantLookUp = (TreeNode*)symbolTable.lookup(tree->attr.name);
			//int backpatch = emitSkip(0);
			//printf("HERE %d %d %s\n", constantLookUp->codeLineNum, backpatch, tree->attr.name);
			/*if(tree->child[1] == NULL)
			{
				isUnaryFlag = true;
			}
			else
			{
				//isUnaryFlag = false;
			}*/

			if (strcmp(tree->attr.name, "=") == 0)
			{
				//printf("EQ is here\n");
				if(strcmp(tree->child[0]->attr.name, "["))
				{
					//printf("AssignK: %s  %d\n",(char *)tree->child[1], tree->attr.value);
					//printf("child1: %s  child2: %s\n", tree->child[1], t->child[0]);
					//isUnaryFlag = false;
					codegenParse(tree->child[1]);
					storeFlag = true;
					codegenParse(tree->child[0]);
					isUnaryFlag = true;
				}
				else
				{
					//printf("In Array\n");
					codegenParse(tree->child[0]->child[1]);
					emitRM((char *)"ST", 3, toffset, 1,(char *)"Push index");
					toffset--;
					emitComment((char *)("TOFF dec:"), toffset);
					codegenParse(tree->child[1]);
					toffset++;
					emitComment((char *)("TOFF inc:"), toffset);
					emitRM((char *)"LD", 4, toffset, 1,(char *)"Pop index");
					if(tree->child[0]->child[0]->mem == Global)
					{
						emitRM((char *)"LDA",5,tree->child[0]->child[0]->memOffset,0,(char *)("Load address of base of array"), (char *)tree->child[0]->child[0]->attr.name);
					}
					else
					{
						emitRM((char *)"LDA",5,tree->child[0]->child[0]->memOffset,1,(char *)("Load address of base of array"), (char *)tree->child[0]->child[0]->attr.name);
					}
					emitRO((char *)"SUB",5,5,4,(char *)("Compute offset of value"));
					emitRM((char *)"ST",3,0,5,(char *)("Store variable"), (char *)tree->child[0]->child[0]->attr.name);
				}
			}
			else if(tree->child[1] == NULL)
			{
				storeFlag = false;
				isUnaryFlag = true;
				codegenParse(tree->child[0]);
				if(strcmp(tree->attr.name, "++") == 0)
				{
					emitRM((char *)"LDA",3,1,3,(char *)("increment value of"), (char *)tree->child[0]->attr.name);
				}
				else if(strcmp(tree->attr.name, "--") == 0)
				{
					emitRM((char *)"LDA",3,-1,3,(char *)("decrement value of"), (char *)tree->child[0]->attr.name);
				}
	
				emitRM((char *)"ST",3,tree->child[0]->memOffset,1,(char *)("Store variable"), (char *)tree->child[0]->attr.name);
			}
			else///////////////////////////////////////////////
			{
				storeFlag = false;
				//isUnaryFlag = true;
				codegenParse(tree->child[1]);
				isUnaryFlag = false;
				codegenParse(tree->child[0]);
				if(strcmp(tree->attr.name, "+=") == 0)
				{
					emitRO((char *)"ADD",3,4,3,(char *)("op"), (char *)tree->attr.name);
				}
				else if(strcmp(tree->attr.name, "-=") == 0)
				{
					emitRO((char *)"SUB",3,4,3,(char *)("op"), (char *)tree->attr.name);
				}
				else if(strcmp(tree->attr.name, "*=") == 0)
				{
					emitRO((char *)"MUL",3,4,3,(char *)("op"), (char *)tree->attr.name);
				}
				else if(strcmp(tree->attr.name, "/=") == 0)
				{
					emitRO((char *)"DIV",3,4,3,(char *)("op"), (char *)tree->attr.name);
				}
				
				if(tree->child[0]->mem == Global)
				{
					emitRM((char *)"ST",3,tree->child[0]->memOffset,0,(char *)("Store variable"), (char *)tree->child[0]->attr.name);
				}
				else
				{
					emitRM((char *)"ST",3,tree->child[0]->memOffset,1,(char *)("Store variable"), (char *)tree->child[0]->attr.name);
				}
				isUnaryFlag = true;
			}
			
          	break;
		}
        case CallK:
		{
			emitComment((char *)("CALL EXPRESSION"));
		  	int paramCount = 0;
			bool childFlag = false;
		  	TreeNode* functionLookUp = (TreeNode*)symbolTable.lookup(tree->attr.name);
		  	emitComment((char *)("CALL"), tree->attr.name);
		  	int tempoffset = toffset;
		  	
			TreeNode* countParameters = tree->child[0];
			//paramCount++;
			while(countParameters != NULL)
			{
				countParameters = countParameters->sibling;
				paramCount++;
						
			}
			//printf("ParamCount: %d --- Name: %s\n", paramCount, tree->attr.name);
		  	if(tree->child[0] == NULL)//no parameters
		  	{
				emitRM((char *)"ST",1,toffset,1,(char *)("1 Store fp in ghost frame for"), (char *)tree->attr.name);
				emitComment((char *)("Param end"), tree->attr.name);
				emitRM((char *)"LDA", 1, tempoffset, 1,(char *)"Ghost frame becomes new active frame");
				
		  	}
		  	else
		  	{
				//printf("In the ELSE\n");
				childFlag = true;
				//printf("Name: %s\n", tree->child[0]->attr.name);
				if(paramCount == 1) // One parameter
				{
					//paramCount++;
					
					emitRM((char *)"ST",1,toffset,1,(char *)("2 Store fp in ghost frame for"), (char *)tree->attr.name);
					//toffset = toffset - paramCount;
					//emitComment((char *)("TOFF dec:"), toffset);
					//if(tree->child[0] != NULL)
					//{
						//printf("Before Array\n");
						/*if(!strcmp(tree->child[0]->attr.name, "[")) // is Array
						{
							printf("CALL is Array\n");
						}
						else // is not array
						{*/
							//printf("In the IF non array\n");
					toffset = toffset - 2;
					emitComment((char *)("TOFF dec:"), toffset);
					emitComment((char *)("Param 1"));
							//printf("Child 0 name: %d", tree->child[0]->attr.value);
							//printf("In the IF 02\n");
					//printf("NAME: %s\n", tree->child[0]->attr.name);
					codegenParse(tree->child[0]);
					if(!tree->child[0]->isArray)
					{
						toffset = toffset - paramCount;
						emitComment((char *)("TOFF dec:"), toffset);
						
					}
					emitRM((char *)"ST", 3, toffset, 1,(char *)"Push parameter");
					emitComment((char *)("Param end"), tree->attr.name);
					emitRM((char *)"LDA", 1, tempoffset, 1,(char *)"Ghost frame becomes new active frame");

						//}
					//}
					
				}
				else // Multi Parameters
				{
					/*TreeNode* countParameters = tree->child[0];
					//paramCount++;
					while(countParameters != NULL)
					{
						countParameters = countParameters->sibling;
						paramCount++;
						
					}*/
					
					//printf("ParamCount: %d\n", paramCount);
					int whileCountParam = 1;
					emitRM((char *)"ST",1,toffset,1,(char *)("3 Store fp in ghost frame for"), (char *)tree->attr.name);
					TreeNode* childTree = tree->child[0];
					toffset--;
					while(childTree != NULL)
					{
						toffset--;
						if(childTree->isArray)
						{
							emitComment((char *)("Param"), whileCountParam);
							if(childTree->mem == Global)
							{
								if(whileCountParam == 1)
								{
									emitRM((char *)"LDA",3,childTree->memOffset,0,(char *)("Load address of base of array"), (char *)childTree->attr.name);
								}
								else
								{
									emitRM((char *)"LDA",3,childTree->memOffset,0,(char *)("Load address of base of array"), (char *)childTree->attr.name);
								}
							}
							else
							{
								if(whileCountParam == 1)
								{
									emitRM((char *)"LDA",3,childTree->memOffset,1,(char *)("Load address of base of array"), (char *)childTree->attr.name);
								}
								else
								{
									emitRM((char *)"LDA",3,childTree->memOffset,1,(char *)("Load address of base of array"), (char *)childTree->attr.name);
								}
								
							}
							emitRM((char *)"ST", 3, toffset, 1,(char *)"Push parameter");
						}
						else // NON-ARRAY
						{
							if(childTree->expType == Integer)
						  	{
								emitRM((char *)"LDC", 3, childTree->attr.value, 6,(char *)"Load integer constant");
						  	}
						  	else if(childTree->expType == Char)
						  	{
								emitRM((char *)"LDC", 3, childTree->attr.cvalue, 6,(char *)"Load char constant");
						  	}
						  	else if(childTree->expType == Boolean)
						  	{
								emitRM((char *)"LDC", 3, childTree->attr.value, 6,(char *)"Load boolean constant");
						  	}
							emitRM((char *)"ST", 3, toffset, 1,(char *)"Push parameter");
						}
						whileCountParam++;
						
						childTree = childTree->sibling;
						
					}
					emitComment((char *)("Param end"), tree->attr.name);
					emitRM((char *)"LDA", 1, tempoffset, 1,(char *)"Ghost frame becomes new active frame");
				}
			
		  	}
			//printf("In Call\n");
		  //printf("%p\n", (void *) &functionLookUp); 
		  //printf("%p\n", (void *) &tree); 
		  functionLookUp = (TreeNode*)symbolTable.lookup(tree->attr.name);//"output"
		  emitRM((char *)"LDA", 3, 1, 7,(char *)"Return address in ac");
		  int backpatch = emitSkip(0);
			emitRM((char *)"JMP",7,functionLookUp->codeLineNum - backpatch - 1,7,(char *)("CALL"), tree->attr.name);
		  
		  emitRM((char *)"LDA", 3, 0, 2,(char *)"Save the result in ac");
		  emitComment((char *)("CALL end"), tree->attr.name);

		  toffset = tempoffset;
		  /*for(int i = 0; i<MAXCHILDREN; i++)
		  {
			codegenParse(tree->child[i]);
		  }*/
          //printf("CallK: %s\n",tree->attr.name);
		//check the number of children then siblings to count the number of parameters (toffset will decreament with number of paramiters. Also check if children are arrays.
          break;
		}
        default:
          //printf("Unknown ExpNode kind\n");
          break;
      }
    }
    else printf("Unknown node kind\n");
    //for (int i=0;i<MAXCHILDREN;i++)
         //printTree(tree->child[i]);
	if(tree->sibling != NULL)
	{
		//printf("SIBLING\n");
		codegenParse(tree->sibling);
    }
  }
//}

void globalsAndStatics(TreeNode* tree)
{
	if(tree == NULL)
	{
		return;
	}

	if(tree->subkind.decl == VarK)
	{
		if(tree->mem == Global)
		{
			if(tree->isArray)
			{
				emitRM((char *)"LDC", 3, tree->memSize - 1, 6,(char *)"load size of array", (char *) tree->attr.name);
				emitRM((char *)"ST", 3, tree->memOffset + 1, 0,(char *)"save size of array", (char *) tree->attr.name);
			}
			else
			{
				//codegenParse(tree->child[0]);
				//emitRM((char *)"ST", 3, tree->memOffset + 1, 0,(char *)"Store variable", (char *) tree->attr.name);
			}
		}
	}
	/*for(int i = 0; i<MAXCHILDREN; i++)
	{
		globalsAndStatics(tree->child[i]);
	}*/
	globalsAndStatics(tree->sibling);
}

void IOLib()
{
	emitSkip(1);
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));
	emitComment((char *)("FUNCTION input"));
	TreeNode *IOLookup = (TreeNode*)symbolTable.lookup((char *) "input");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "input";//
	//printf("%s , %d\n", IOLookup->attr.name, IOLookup->codeLineNum);
	emitRO((char *)"IN", 2, 2, 2,(char *)("Grab int input"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION input"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION output"));
	IOLookup = (TreeNode*)symbolTable.lookup((char *) "output");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "output";//
	//printf("%s , %d\n", IOLookupOutput->attr.name, IOLookupOutput->codeLineNum);
	//printf("should be output %s , %d\n", IOLookup->attr.name, IOLookup->codeLineNum);
	emitRM((char *)"LD", 3, -2, 1,(char *)("Load parameter"));
	emitRO((char *)"OUT",3,3,3,(char *)("Output integer"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION output"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION inputb"));
	IOLookup = (TreeNode*)symbolTable.lookup((char *) "inputb");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "inputb";//
	emitRO((char *)"INB", 2, 2, 2,(char *)("Grab bool input"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION inputb"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION outputb"));
	IOLookup = (TreeNode*)symbolTable.lookup((char *) "outputb");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "outputb";//
	emitRM((char *)"LD", 3, -2, 1,(char *)("Load parameter"));
	emitRO((char *)"OUTB",3,3,3,(char *)("Output bool"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION outputb"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION inputc"));
	IOLookup = (TreeNode*)symbolTable.lookup((char *) "inputc");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "inputc";//
	emitRO((char *)"INC", 2, 2, 2,(char *)("Grab char input"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION inputc"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION outputc"));
	IOLookup = (TreeNode*)symbolTable.lookup((char *) "outputc");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "outputc";//
	emitRM((char *)"LD", 3, -2, 1,(char *)("Load parameter"));
	emitRO((char *)"OUTC",3,3,3,(char *)("Output char"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION outputc"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	emitComment((char *)("FUNCTION outnl"));
	IOLookup = (TreeNode*)symbolTable.lookup((char *) "outnl");//
	emitRM((char *)"ST", 3, -1, 1,(char *)"Store return address");
	IOLookup->codeLineNum = emitSkip(0)-1;
	IOLookup->attr.name = (char *) "outnl";//
	emitRO((char *)"OUTNL",3,3,3,(char *)("Output a newline"));
	emitRM((char *)"LD",3,-1,1,(char *)("Load return address"));
	emitRM((char *)"LD",1,0,1,(char *)("Adjust fp"));
	emitRM((char *)"JMP",7,0,3,(char *)("Return"));
	emitComment((char *)("END FUNCTION outnl"));
	emitComment((char *)(""));
	emitComment((char *)("** ** ** ** ** ** ** ** ** ** ** **"));

	//printf("THIS %s , %d\n", IOLookupOutput->attr.name, IOLookupOutput->codeLineNum);
}

void codegenMain(TreeNode* tree)
{
	TreeNode* mainLookup;
	
	int backpatch = emitSkip(0)-1;
	emitNewLoc(0);
	mainLookup = (TreeNode*)symbolTable.lookup("main"); 
	//printf("main address %p\n", (void *) &mainLookup);
	emitRM((char *)"JMP",7,backpatch,7,(char *)("Jump to init [backpatch]"));
	emitComment((char *)("INIT"));
	emitSkip(backpatch);
	emitRM((char *)"LDA",1,0+goffset,0,(char *)("set first frame at end of globals"));
	emitRM((char *)"ST",1,0,1,(char *)("store old fp (point to self)"));
	emitComment((char *)("INIT GLOBALS AND STATICS"));
	globalsAndStatics(tree); // NEEDS WORK
	emitComment((char *)("END INIT GLOBALS AND STATICS"));
	emitRM((char *)"LDA",3,1,7,(char *)("Return address in ac"));
	backpatch = emitSkip(0);
	//printf("Main codeline %d\n", mainLookup->codeLineNum);
	emitRM((char *)"JMP",7,mainLookup->codeLineNum - backpatch - 1,7,(char *)("Jump to main"));
	emitRO((char *)"HALT",0,0,0,(char *)("DONE!"));
	emitComment((char *)("END INIT"));
}
