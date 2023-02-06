BIN = parser
CC = g++
OUTFILE = c-

SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.h treeNode.h treeNode.c ourGetopt.c ourGetopt.h semantic.h semantic.cpp symbolTable.cpp symbolTable.h codegen.cpp codegen.h emitcode.cpp emitcode.h yyerror.cpp yyerror.h
OBJS = treeNode.o ourGetopt.o semantic.o symbolTable.o codegen.o emitcode.o lex.yy.o yyerror.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(OUTFILE)

$(BIN).tab.h $(BIN).tab.c : treeNode.h semantic.h  $(BIN).y
	bison -v -t -d $(BIN).y

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l
	
treeNode.o : treeNode.h treeNode.c
	$(CC) -c treeNode.c

ourGetopt.o : ourGetopt.h ourGetopt.c
	$(CC) -c ourGetopt.c

semantic.o : semantic.h semantic.cpp
	$(CC) -c semantic.cpp

yyerror.o : yyerror.h yyerror.cpp
	$(CC) -c yyerror.cpp

symbolTable.o : symbolTable.h symbolTable.cpp
	$(CC) -c symbolTable.cpp

codegen.o : codegen.h codegen.cpp
	$(CC) -c codegen.cpp

emitcode.o : emitcode.h emitcode.cpp
	$(CC) -c emitcode.cpp

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) $(DOCS) makefile
