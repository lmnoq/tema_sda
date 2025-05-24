#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "heap.h"
#include "huffman.h"

TreeNode *build_huffman_tree(FILE *in)
{
	int n;
	fscanf(in, "%d", &n);
	MinHeap *heap = create_heap(n * 2);
	for (int i = 0; i < n; ++i)
	{
		int freq;
		char name[20];
		fscanf(in, "%d %s", &freq, name);
		TreeNode *node = create_node(freq, name, NULL, NULL);
		push_heap(heap, node);
	}
	while (heap->size > 1)
	{
		TreeNode *left = pop_heap(heap);
		TreeNode *right = pop_heap(heap);
		char *new_name = malloc(strlen(left->name) + strlen(right->name) + 1);
		strcpy(new_name, left->name);
		strcat(new_name, right->name);
		TreeNode *parent = create_node(left->freq + right->freq, new_name, left, right);
		free(new_name);
		push_heap(heap, parent);
	}
	TreeNode *root = pop_heap(heap);
	free_heap(heap);
	return root;
}