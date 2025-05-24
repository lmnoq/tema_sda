#include <stdio.h>
#ifndef TREE_H
#define TREE_H

typedef struct TreeNode
{
	int freq;
	char *name;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;
typedef struct
{
	char name[20];
	char code[100];
} SatelliteCode;
TreeNode *create_node(int freq, const char *name, TreeNode *left, TreeNode *right);
void free_tree(TreeNode *root);
void print_tree_levels(FILE *out, TreeNode *root);
void decode_and_print(TreeNode *root, const char *code, FILE *out);
void generate_codes(TreeNode *node, SatelliteCode *codes, int *count, char *current_code, int depth);
char *find_code(SatelliteCode *codes, int count, const char *name);
TreeNode *lca(TreeNode *root, TreeNode *n1, TreeNode *n2);
TreeNode *find_node(TreeNode *root, const char *name);
#endif
