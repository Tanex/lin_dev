#include "global.h"

void bin_oper_opti(int oper, node* node_copy);
int pre_calculate(int oper, int l_op, int r_op);

node* optimizer(node* root)
{
	if(root == 0)
		return 0;

	//Create a new node and make it a copy of the one in the original tree but with optimized subtrees
	node* node_copy = new node();

	node_copy->node_type = root->node_type;
	node_copy->leaf_value = root->leaf_value;
	node_copy->args[0] = optimizer(root->args[0]);
	node_copy->args[1] = optimizer(root->args[1]);
	node_copy->args[2] = optimizer(root->args[2]);
	node_copy->args[3] = optimizer(root->args[3]);

	//optimize this subtree

	switch(root->node_type)
	{
		//non optimized nodes
		//case NUM: 
        //case ASGMNTID: 
		//case ID: 
		//case '=': 
		//case ';': 		            
		//case PRINT:
		//case READ:
		
		//Statements
		case WHILE://optimization: if condition is always false, remove the loop
			//if non numerical condition 
			if(node_copy->args[0]->node_type != NUM)
				break;
			//if the numerical value is 0 (alwaysfalse) 
			else if(node_copy->args[0]->leaf_value == 0)
			{
				//make it a simple linkage node and null all the pointers in this node
				node_copy->node_type = ';';
				node_copy->args[0] = node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
                break;
			}
			else //this means the statement is always true, such as while(1)
				break;


		case IF: case '?': //optimization: if always false or always true
			//if non numerical condition 
			if(node_copy->args[0]->node_type != NUM)
				break;
			//if the numerical value is not 0 (always true) 
			else if(node_copy->args[0]->leaf_value != 0)
			{
				//make it a simple linkage node and with one subtree
				node_copy->node_type = ';';
				node_copy->args[0] = node_copy->args[1];
				node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
				break;
			}			
			else //this means the statement is always false
			{
				node_copy->node_type = ';';
				node_copy->args[0] = node_copy->args[2];
				node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
				break;
			}

			
		//Basic operators
		case '+': bin_oper_opti('+', node_copy); break;					
		case '-': bin_oper_opti('-', node_copy); break;
		case '*': bin_oper_opti('*', node_copy); break;
		case '/': bin_oper_opti('/', node_copy); break;
		case DIV: bin_oper_opti(DIV, node_copy); break;
		case MOD: bin_oper_opti(MOD, node_copy); break;
		case '%': bin_oper_opti('%', node_copy); break;
		case '&': bin_oper_opti('&', node_copy); break;
		case '|': bin_oper_opti('|', node_copy); break;
		case '<': bin_oper_opti('<', node_copy); break;
		case '>': bin_oper_opti('>', node_copy); break;
	}

	return node_copy;
}

void bin_oper_opti(int oper, node* node_copy)
{
	//if both operands are simple constant numerics
	if(node_copy->args[0]->node_type == NUM && node_copy->args[1]->node_type == NUM)
	{
		//make this a numerical node
		node_copy->node_type = NUM;

		//pre calculate the nodes value and store it as leaf_value
		node_copy->leaf_value = pre_calculate(oper, node_copy->args[0]->leaf_value, node_copy->args[1]->leaf_value);

		//null all the pointers in this node
		node_copy->args[0] = node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
	}

	//if the left operand is a variable and the right a constant
	else if(node_copy->args[0]->node_type == ID && node_copy->args[1]->node_type == NUM)
	{
		//if the numeric is a 0 and the operand is +,- or the numeric is a 1 and the operand is *,/
		if((node_copy->args[1]->leaf_value == 0 && (oper == '+' || oper == '-')) || 
		   (node_copy->args[1]->leaf_value == 1 && (oper == '*' || oper == '/')))
		{
			//the operand does nothing and just results in the variable
			node_copy->node_type = ID;
			node_copy->leaf_value = node_copy->args[0]->leaf_value;
			node_copy->args[0] = node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
		}
		//if multiplying with 0
		else if(node_copy->args[1]->leaf_value == 0 && oper == '*')
		{
			node_copy->node_type = NUM;
			node_copy->leaf_value = 0;
			node_copy->args[0] = node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
		}
	}

	//if the left operand is a constant and the right a variable
	else if(node_copy->args[0]->node_type == NUM && node_copy->args[1]->node_type == ID)
	{
		//if the numeric is a 0 and the operand is +,- or the numeric is a 1 and the operand is *,/
		if((node_copy->args[0]->leaf_value == 0 && (oper == '+' || oper == '-')) || 
		   (node_copy->args[0]->leaf_value == 1 && (oper == '*' || oper == '/')))
		{
			//the operand does nothing and just results in the variable
			node_copy->node_type = ID;
			node_copy->leaf_value = node_copy->args[1]->leaf_value;
			node_copy->args[0] = node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
		}
		//if multiplying with 0
		else if(node_copy->args[0]->leaf_value == 0 && oper == '*')
		{
			node_copy->node_type = NUM;
			node_copy->leaf_value = 1;
			node_copy->args[0] = node_copy->args[1] = node_copy->args[2] = node_copy->args[3] = 0;
		}
	}

	else
		;//do nothing
}

int pre_calculate(int oper, int l_op, int r_op)
{
	switch(oper)
	{
		case '+': return l_op + r_op;					
		case '-': return l_op - r_op;
		case '*': return l_op * r_op;
		case '/': return l_op / r_op;
		case DIV: return l_op / r_op;
		case MOD: return l_op % r_op;
		case '%': return l_op % r_op;
		case '&': return l_op & r_op;
		case '|': return l_op | r_op;
		case '<': return l_op < r_op;
		case '>': return l_op > r_op;
	}
	return 0;
}