#ifndef HEAP_H
#define HEAP_H

#include "tree.h"

typedef struct
{
	TreeNode **data;
	int size;
	int capacity;
} MinHeap;

MinHeap *create_heap(int capacity);
void free_heap(MinHeap *heap);
void push_heap(MinHeap *heap, TreeNode *node);
TreeNode *pop_heap(MinHeap *heap);

#endif
