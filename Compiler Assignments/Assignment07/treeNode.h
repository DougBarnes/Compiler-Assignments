#ifndef _TREENODE_H_ 
#define _TREENODE_H_ 
#include <stdio.h> 
#include <stdlib.h> 
extern bool printOffsetFlag;
// the exact type of the token or node involved.  These are divided into
// various "kinds" in the enums that follow

// Kinds of Operators
// these are the token numbers for the operators same as in flex
typedef int OpKind;  

// Kinds of Statements
//typedef enum {DeclK, StmtK, ExpK} NodeKind;
typedef enum {DeclK, StmtK, ExpK} NodeKind;

// Subkinds of Declarations
typedef enum {VarK, FuncK, ParamK} DeclKind;

// Subkinds of Statements
typedef enum {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK} StmtKind;

// Subkinds of Expressions
typedef enum {OpK, ConstantK, IdK, AssignK, InitK, CallK} ExpKind;

// ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
typedef enum {Void, Integer, Boolean, Char, CharInt, Equal, UndefinedType} ExpType;

// What kind of scoping is used?  (decided during typing)
typedef enum {None, Local, Global, Parameter, LocalStatic} MemKind;

#define MAXCHILDREN 3 
typedef struct TreeNode
{
    // connectivity in the tree
    struct TreeNode *child[MAXCHILDREN];   // children of the node
    struct TreeNode *sibling;              // siblings for the node

    // what kind of node
    int linenum;                            // linenum relevant to this node
    NodeKind nodekind;                     // type of this node
    union                                  // subtype of type
    {
	DeclKind decl;                     // used when DeclK
	StmtKind stmt;                     // used when StmtK
	//ExpKind exp;                       // used when ExpK
    } subkind;
    
    // extra properties about the node depending on type of the node
    union                                  // relevant data to type -> attr
    {
    OpKind op;                         // type of token (same as in bison)
	int value;                         // used when an integer constant or boolean
    unsigned char cvalue;               // used when a character
	char *string;                      // used when a string constant
	char *name;                        // used when IdK
    } attr;                                 
    ExpType expType;		           // used when ExpK for type checking
    bool isArray;                          // is this an array
    bool isStatic;                         // is staticly allocated?
	int stringLength;
	bool isUnarySub;
	bool isUnaryStar;
	bool isIO;
	bool isConst;
	int memSize;
	int memOffset;
	int codeLineNum;
	ExpKind exp;                       // used when ExpK
	MemKind mem;

    // even more semantic stuff will go here in later assignments.
} TreeNode;
#endif
