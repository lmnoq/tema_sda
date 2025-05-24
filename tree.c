#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

TreeNode *create_node(int freq, const char *name, TreeNode *left, TreeNode *right)
{
	TreeNode *node = malloc(sizeof(TreeNode));
	node->freq = freq;
	node->name = strdup(name);
	node->left = left;
	node->right = right;
	return node;
}

void free_tree(TreeNode *root)
{
	if (!root)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root->name);
	free(root);
}

void print_tree_levels(FILE *out, TreeNode *root)
{
	if (!root)
		return;

	TreeNode **queue = malloc(1000 * sizeof(TreeNode *));
	int start = 0, end = 0;
	int level_nodes = 1;

	queue[end++] = root;

	while (start < end)
	{
		int next_level = 0;
		for (int i = 0; i < level_nodes; ++i)
		{
			TreeNode *node = queue[start++];
			fprintf(out, "%d-%s", node->freq, node->name);
			if (i != level_nodes - 1)
				fprintf(out, " ");
			if (node->left)
				queue[end++] = node->left, next_level++;
			if (node->right)
				queue[end++] = node->right, next_level++;
		}
		fprintf(out, "\n");
		level_nodes = next_level;
	}
	free(queue);
}

void decode_and_print(TreeNode *root, const char *code, FILE *out)
{
	TreeNode *node = root;
	int i = 0;
	int first = 1;
	while (code[i])
	{
		if (code[i] == '0')
			node = node->left;
		else if (code[i] == '1')
			node = node->right;

		if (node->left == NULL && node->right == NULL)
		{
			if (!first)
				fprintf(out, " ");
			fprintf(out, "%s", node->name);
			first = 0;
			node = root;
		}
		i++;
	}
	fprintf(out, "\n");
}
void generate_codes(TreeNode *node, SatelliteCode *codes, int *count, char *current_code, int depth)
{
	if (!node)
		return;
	if (!node->left && !node->right)
	{
		current_code[depth] = '\0';
		strcpy(codes[*count].name, node->name);
		strcpy(codes[*count].code, current_code);
		(*count)++;
		return;
	}
	if (node->left)
	{
		current_code[depth] = '0';
		generate_codes(node->left, codes, count, current_code, depth + 1);
	}
	if (node->right)
	{
		current_code[depth] = '1';
		generate_codes(node->right, codes, count, current_code, depth + 1);
	}
}

char *find_code(SatelliteCode *codes, int count, const char *name)
{
	for (int i = 0; i < count; ++i)
		if (strcmp(codes[i].name, name) == 0)
			return codes[i].code;
	return NULL;
}
TreeNode *find_node(TreeNode *root, const char *name)
{
	if (!root)
		return NULL;
	if (root->name && strcmp(root->name, name) == 0)
		return root;
	TreeNode *found = find_node(root->left, name);
	if (found)
		return found;
	return find_node(root->right, name);
}

TreeNode *lca(TreeNode *root, TreeNode *n1, TreeNode *n2)
{
	if (!root)
		return NULL;
	if (root == n1 || root == n2)
		return root;
	TreeNode *left = lca(root->left, n1, n2);
	TreeNode *right = lca(root->right, n1, n2);
	if (left && right)
		return root;
	return left ? left : right;
}