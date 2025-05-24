#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "heap.h"
#include "huffman.h"
char code[100];
int N;

int main(int argc, char *argv[])
{
	FILE *in = fopen(argv[2], "r");
	FILE *out = fopen(argv[3], "w");
	TreeNode *root = build_huffman_tree(in);

	if (strcmp(argv[1], "-c1") == 0)
	{
		print_tree_levels(out, root);
	}
	else if (strcmp(argv[1], "-c2") == 0)
	{
		int m;
		fscanf(in, "%d", &m);
		for (int i = 0; i < m; ++i)
		{
			fscanf(in, "%s", code);
			decode_and_print(root, code, out);
		}
	}
	else if (strcmp(argv[1], "-c3") == 0)
	{
		SatelliteCode codes[256];
		int code_count = 0;
		char temp_code[256];
		generate_codes(root, codes, &code_count, temp_code, 0);

		fscanf(in, "%d", &N);

		char result[8192] = "";

		for (int i = 0; i < N; ++i)
		{
			char sat_name[64];
			fscanf(in, "%s", sat_name);

			char *sat_code = find_code(codes, code_count, sat_name);
			if (sat_code)
			{
				if (strlen(result) + strlen(sat_code) < sizeof(result) - 1)
					strcat(result, sat_code);
			}
		}

		fprintf(out, "%s\n", result);
	}
	else if (strcmp(argv[1], "-c4") == 0)
	{
		fscanf(in, "%d", &N);
		TreeNode *nodes[N];
		for (int i = 0; i < N; ++i)
		{
			char name[64];
			fscanf(in, "%s", name);
			nodes[i] = find_node(root, name);
		}

		TreeNode *lca_node = nodes[0];
		for (int i = 1; i < N; ++i)
		{
			lca_node = lca(root, lca_node, nodes[i]);
		}

		fprintf(out, "%s\n", lca_node->name);
	}
	free_tree(root);
	fclose(in);
	fclose(out);
	return 0;
}