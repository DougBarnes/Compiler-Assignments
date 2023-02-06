#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeNode.h"

extern int numErrors;


TreeNode *newDeclNode(DeclKind kind) //ExpType type,//TokenData *token=NULL,//TreeNode *c0=NULL,//TreeNode *c1=NULL,//TreeNode *c2=NULL);  // save TokenData block!!
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
  	
    for (i=0;i<MAXCHILDREN;i++)
	{
		t->child[i] = NULL;
    	t->sibling = NULL;
    	t->nodekind = DeclK;
    	t->subkind.decl = kind;
    	t->linenum = 0;
		t->codeLineNum = 0;
		t->isArray = false;
		t->isUnarySub = false;
		t->isUnaryStar = false;
		t->isIO = false;
	}
	t->memSize = 1;
}

TreeNode *newStmtNode(StmtKind kind) //TokenData *token,//TreeNode *c0=NULL,//TreeNode *c1=NULL,//TreeNode *c2=NULL);
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
  	for (i=0;i<MAXCHILDREN;i++)
	{
		t->child[i] = NULL;
    	t->sibling = NULL;
    	t->nodekind = StmtK;
    	t->subkind.stmt = kind;
    	t->linenum = 0;
		t->codeLineNum = 0;
		t->isArray = false;
		t->isUnarySub = false;
		t->isUnaryStar = false;
		t->isIO = false;
	}
	t->memSize = 1;
}

TreeNode *newExpNode(ExpKind kind) //TokenData *token,//TreeNode *c0=NULL,//TreeNode *c1=NULL,//TreeNode *c2=NULL);
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;
  	for (i=0;i<MAXCHILDREN;i++)
	{
		t->child[i] = NULL;
    	t->sibling = NULL;
    	t->nodekind = ExpK;
    	t->exp = kind;
    	t->linenum = 0;
		t->codeLineNum = 0;
		t->isArray = false;
		t->isUnarySub = false;
		t->isUnaryStar = false;
		t->isIO = false;
	}
	t->memSize = 1;
}

// add a TreeNode to a list of siblings.
// Adding a NULL to the list is probably a programming error!
TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s==NULL && numErrors==0) {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
    if (t!=NULL) { 
        TreeNode *tmp;

        tmp = t;
        while (tmp->sibling!=NULL) tmp = tmp->sibling;
        tmp->sibling = s; 
        return t;
    }
    return s;
}


// pass the static and type attribute down the sibling list
void setType(TreeNode *t, ExpType type, bool isStatic)
{
    while (t) {
        t->expType = type;
        t->isStatic = isStatic;

        t = t->sibling;
    }
}

/* macros to increase/decrease indentation */
//#define INDENT indentno+=2
//#define UNINDENT indentno-=2
static int INDENT = 0;

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ 	
	//printf("INDENT==========> %d", INDENT);
	int i;
	if(INDENT > 4)
	{
  		for (i=0;i<INDENT-4;i++)
  		{
			if(i%4==0)
			{
				printf(".");
			}
  			printf(" ");
		}
  	}
	else
	{/* DO NOTHING */}
}

void printOffsets(TreeNode *tree, bool offsetKFlag)
{
	if(printOffsetFlag && offsetKFlag)
	{
		if(tree->mem == Global)
		{
			printf("[mem: Global loc: %d size: %d] ", tree->memOffset, tree->memSize);
		}
		else if(tree->mem == LocalStatic)
		{
			printf("[mem: LocalStatic loc: %d size: %d] ", tree->memOffset, tree->memSize);
		}
		else if(tree->mem == Parameter)
		{
			printf("[mem: Parameter loc: %d size: %d] ", tree->memOffset, tree->memSize);
		}
		else if(tree->mem == Local)
		{
			printf("[mem: Local loc: %d size: %d] ", tree->memOffset, tree->memSize);
		}
		else
		{
			printf("[mem: None loc: %d size: %d] ", tree->memOffset, tree->memSize);
		}
	}
}

int childCount = 0;
int siblingCount[100];
int treeLevel = 0;
bool boolChild = false;
bool boolSibling = false;

void printTree(TreeNode *tree)
{
	int i;
	bool offsetKFlag = true;
	/*if(tree->sibling)
  	{
  		printf("DOWN TREE\n");
  	}*/
  	INDENT+=4;
	treeLevel++;
  	while (tree != NULL) {
		// if sib or child print off here... temp bools, vars. 
    	printSpaces();

		if(boolChild)
		{	
			printf("Child: %d  ", childCount);
		}
		else if (boolSibling)
		{
			siblingCount[treeLevel]++;
			printf("Sibling: %d  ", siblingCount[treeLevel]);
		}
		else {/*DO NOTHING*/}

    	if (tree->nodekind==StmtK)
    	{ switch (tree->subkind.stmt) {
        	case IfK:
          		printf("If ");
				offsetKFlag = false;
          		break;
        	case WhileK:
          		printf("While ");
				offsetKFlag = false;
          		break;
        	case ForK:
          		printf("For ");
				offsetKFlag = true;
          		break;
        	case CompoundK:
          		printf("Compound ");
				offsetKFlag = true;
          		break;
        	case ReturnK:
          		printf("Return ");
				offsetKFlag = false;
          		break;
			case BreakK:
          		printf("Break ");
				offsetKFlag = false;
          		break;
			case RangeK:
          		printf("Range ");
				offsetKFlag = false;
          		break;
        	default:
          		printf("Unknown ExpNode kind");
          		break;
      		}
		}
		else if (tree->nodekind==ExpK)
		{ switch (tree->exp) {
		    case OpK:
			  offsetKFlag = false;
			  if(tree->isUnarySub)
			  {
				printf("Op: chsign ");
				if(tree->isArray)
				{
					printf("of array ");
				}
				if(tree->expType == Integer)
				{
					printf("of type int ");
				}
				else if(tree->expType == Boolean)
				{
					printf("of type bool ");
				}
				else if(tree->expType == Char)
				{
					printf("of type char ");
				}
				else
				{
					printf("of type void ");
				}
			  }
			  else if(tree->isUnaryStar)
			  {
				printf("Op: sizeof ");
				if(tree->isArray)
				{
					printf("of array ");
				}
				if(tree->expType == Integer)
				{
					printf("of type int ");
				}
				else if(tree->expType == Boolean)
				{
					printf("of type bool ");
				}
				else if(tree->expType == Char)
				{
					printf("of type char ");
				}
				else
				{
					printf("of type void ");
				}
			  }
			  else
			  {
/////////////////////
				if(strcmp(tree->attr.name, "NOT") == 0)
				{
					printf("Op: not ");
				}
				else if (strcmp(tree->attr.name, "AND") == 0)
				{
					printf("Op: and ");
				}
				else if (strcmp(tree->attr.name, "OR") == 0)
				{
					printf("Op: or ");
				}
				else
				{
			  		printf("Op: %s ", tree->attr.name);
				}
				if(tree->isArray)
				{
					printf("of array ");
				}
				if(tree->expType == Integer)
				{
					printf("of type int ");
				}
				else if(tree->expType == Boolean)
				{
					printf("of type bool ");
				}
				else if(tree->expType == Char)
				{
					printf("of type char ");
				}
				else
				{
					printf("of type void ");
				}
/////////////////Child: 0 Const "pipsissewa" of array of type char [mem: Global loc: -1 size: 11] [line: 1]
			  }
		      break;
		    case ConstantK:
		      printf("Const ");//Child: 1 Const of type int: 11 [line: 7]
			  //printOffsets(tree, offsetKFlag);
			  offsetKFlag = false;
			  /*if(tree->isArray)
			  {
				printf("of array ");
			  }*/
			  if(tree->expType == Integer)
			  {
				//offsetKFlag = false;
				printf("%d of type int ", tree->attr.value);
			  }
			  else if(tree->expType == Boolean)
			  {
				if(tree->attr.value)
			    {
					printf("true ");
				}
				else
				{
					printf("false ");
				}
				printf("of type bool ");
				//offsetKFlag = false;
			  }

			  else if(tree->expType == Char)
			  {
				if(tree->isArray)
				{
					offsetKFlag = true;
					for(int i = 0; i< tree->stringLength; i++)
					{
						printf("%c", tree->attr.string[i]);
					}
					printf(" of array of type char ");
				}
				else
				{
					printf("'%c' of type char ", tree->attr.cvalue);
				}
			  }

			  else
			  {
				printf("of type void ");
			  }
		      break;
////////////////////////
		    case IdK:
		      printf("Id: %s of ",tree->attr.name);
			  if(tree->isStatic)
			  {
				printf("static ");
			  }
			  if(tree->isArray)
			  {
				printf("array of ");
			  }
			  if(tree->expType == Integer)
			  {
				printf("type int ");
				offsetKFlag = true;
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("type bool ");
				offsetKFlag = true;
			  }
			  else if(tree->expType == Char)
			  {
				printf("type char ");
				offsetKFlag = true;
			  }
			  else
			  {
				printf("type void ");
			  }
		      break;
		    case AssignK:
		      printf("Assign: %s ",tree->attr.name);
			  offsetKFlag = false;
			  if(tree->isArray)
			  {
				printf("of array ");
			  }
			  if(tree->expType == Integer)
			  {
				printf("of type int ");
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("of type bool ");
			  }
			  else if(tree->expType == Char)
			  {
				printf("of type char ");
			  }
			  else
			  {
				printf("of type void ");
			  }
		      break;
		    case InitK:
		      printf("Init: %s ",tree->attr.name);
			  if(tree->isArray)
			  {
				printf("of array ");
			  }
			  if(tree->expType == Integer)
			  {
				printf("of type int ");
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("of type bool ");
			  }
			  else if(tree->expType == Char)
			  {
				printf("of type char ");
			  }
			  else
			  {
				printf("of type void ");
			  }
		      break;
		    case CallK:
		      printf("Call: %s ",tree->attr.name);
			  offsetKFlag = false;
			  if(tree->isArray)
			  {
				printf("of array ");
			  }
			  if(tree->expType == Integer)
			  {
				printf("of type int ");
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("of type bool ");
			  }
			  else if(tree->expType == Char)
			  {
				printf("of type char ");
			  }
			  else
			  {
				printf("of type void ");
			  }
		      break;
		    default:
		      printf("Unknown ExpNode kind");
		      break;
//////////////////////
		  }
		}
		else if (tree->nodekind==DeclK)
		{ 	//printf("IN DECLK!!!!");
			switch (tree->subkind.decl) {
//Var
		    case VarK: //Sibling: 1 Var: c of static array of type int [mem: LocalStatic loc: -13 size: 34] [line: 7
		      printf("Var: %s of ", tree->attr.name);
			  if(tree->isStatic)
			  {
				printf("static ");
			  }
			  if(tree->isArray)
			  {
				printf("array of ");
			  }
			  if(tree->expType == Integer)
			  {
				printf("type int ");
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("type bool ");
			  }
			  else if(tree->expType == Char)
			  {
				printf("type char ");
			  }
			  else
			  {
				printf("type void ");
			  }
		      break;
//Func
		    case FuncK:
		      printf("Func: %s returns ", tree->attr.name);
			  if(tree->expType == Integer)
			  {
				printf("type int ");
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("type bool ");
			  }
			  else if(tree->expType == Char)
			  {
				printf("type char ");
			  }
			  else
			  {
				printf("type void ");
			  }
		      break;
//Parm
		    case ParamK:
		      printf("Parm: %s ", tree->attr.name);
			  if(tree->isArray)
			  {
				printf("of array ");
			  }
			  if(tree->expType == Integer)
			  {
				printf("of type int ");
			  }
			  else if(tree->expType == Boolean)
			  {
				printf("of type bool ");
			  }
			  else if(tree->expType == Char)
			  {
				printf("of type char ");
			  }
			  else
			  {
				printf("of type void ");
			  }
		      break;
		    default:
		      printf("Unknown ExpNode kind");
		      break;
		  }
    }
    else printf("Unknown node kind\n");

	printOffsets(tree, offsetKFlag);

	printf("[line: %d]\n", tree->linenum);

    for (i=0;i<MAXCHILDREN;i++)//childCount set to i, reset after recusion.
	{
		childCount = i;
		boolChild = true;
		boolSibling = true;
        printTree(tree->child[i]);
		childCount = 0;
		boolChild = false;
	}
    tree = tree->sibling;
	//if(tree->sibling)
	//{
		//printf("SIBLING===> %s", tree);
		//siblingCount--;
	//}

  }
  /*if(tree->sibling)
  {
  	printf("UP TREE\n");
  }*/
  INDENT-=4;
  if (treeLevel>1)
  {
	siblingCount[treeLevel] = 0;
  }
  treeLevel--;
}

















