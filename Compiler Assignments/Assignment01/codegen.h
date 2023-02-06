#ifndef CODE_GEN_H__
#define CODE_GEN_H__

void codegen(char* outFile, TreeNode *tree);
void codegenParse(TreeNode* tree);
void globalsAndStatics(TreeNode* tree);
void IOLib();
void codegenMain(TreeNode* tree);
#endif
