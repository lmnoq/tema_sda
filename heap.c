#include <stdlib.h>
#include <string.h>
#include "heap.h"

MinHeap *create_heap(int capacity)
{
	MinHeap *heap = malloc(sizeof(MinHeap));
	heap->data = malloc(capacity * sizeof(TreeNode *));
	heap->size = 0;
	heap->capacity = capacity;
	return heap;
}

void free_heap(MinHeap *heap)
{
	free(heap->data);
	free(heap);
}
static int compare(TreeNode *a, TreeNode *b)
{
	if (a->freq != b->freq)
		return a->freq - b->freq;
	return strcmp(a->name, b->name);
}
void push_heap(MinHeap *heap, TreeNode *node)
{
	int idx = heap->size;
	heap->data[idx] = node;
	while (idx > 0)
	{
		int parent = (idx - 1) / 2;
		if (compare(heap->data[idx], heap->data[parent]) < 0)
		{
			TreeNode *tmp = heap->data[idx];
			heap->data[idx] = heap->data[parent];
			heap->data[parent] = tmp;
			idx = parent;
		}
		else
		{
			break;
		}
	}
	heap->size++;
}

TreeNode *pop_heap(MinHeap *heap)
{
	if (heap->size == 0)
		return NULL;
	TreeNode *root = heap->data[0];
	heap->size--;
	heap->data[0] = heap->data[heap->size];
	int idx = 0;
	while (1)
	{
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		int smallest = idx;

		if (left < heap->size && compare(heap->data[left], heap->data[smallest]) < 0)
			smallest = left;
		if (right < heap->size && compare(heap->data[right], heap->data[smallest]) < 0)
			smallest = right;

		if (smallest != idx)
		{
			TreeNode *tmp = heap->data[idx];
			heap->data[idx] = heap->data[smallest];
			heap->data[smallest] = tmp;
			idx = smallest;
		}
		else
		{
			break;
		}
	}
	return root;
}