#include "global.h"
#include <stdio.h>


node* mknode(int node_type, node* arg0, node* arg1, node* arg2, node* arg3)
{
	//debug
	//printf("mknode %d\n", node_type);
	node* new_node = (node*)malloc(sizeof(node));

	new_node->node_type = node_type;
	new_node->leaf_value = 0;

	new_node->args[0] = arg0;
	new_node->args[1] = arg1;
	new_node->args[2] = arg2;
	new_node->args[3] = arg3;

	return new_node;
}

node* mkleaf(int node_type, int leaf_value)
{
	//debug
	//printf("mkleaf %d\t%d\n", node_type, leaf_value);
	node* new_node = (node*)malloc(sizeof(node));
	new_node->node_type = node_type;
	new_node->leaf_value = leaf_value;
	new_node->args[0] = new_node->args[1] = new_node->args[2] = new_node->args[3] = 0;

	return new_node;
}

void delete_tree(node* root)
{
	int i = 0;
	while(root->args[i] != 0)
		delete_tree(root->args[i++]);

	free((void*)root);
}

void printtree1(node* root, int level) {
	if (root == 0)
	;
	else if (root->node_type == ID) {
		printf("%*s", 2*level, "");
		printf("%s\n", symtable[root->leaf_value].lexptr);
	}
	else if (root->node_type == NUM) {
		printf("%*s", 2*level, "");
		printf("%d\n", root->leaf_value);
	}
	else if (root->node_type == ';') {
		printf("%*s", 2*level, "");
		printtree1(root->args[0], level + 1);
		printf("%*s", 2*level, "");
		printf(";\n");
		printtree1(root->args[1], level);
	}
	else if (root->node_type == MOD) {
		printf("%*s", 2*level, "");
		printf("mod\n");
		printtree1(root->args[0], level + 1);
		printtree1(root->args[1], level + 1);
	}
	else if (root->node_type == DIV) {
		printf("%*s", 2*level, "");
		printf("div\n");
		printtree1(root->args[0], level + 1);
		printtree1(root->args[1], level + 1);
	}
	else { //if (root->node_type == '+') {
		printf("%*s", 2*level, "");
		printf("%c\n", root->node_type);
		printtree1(root->args[0], level + 1);
		printtree1(root->args[1], level + 1);
	}	
}

void treeprint(node* root)
{
	printf("Syntax tree:\n");
  	printtree1(root, 0);
}