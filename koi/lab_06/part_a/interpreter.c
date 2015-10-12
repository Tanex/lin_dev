#include "global.h"

int interpreter(node *root)
{
	switch(root->node_type)
	{
		//Leafs
		case NUM: case ASGMNTID:
			return root->leaf_value;
		case ID: 
			return symtable[interpreter(root->args[0])].value;
			
		//Assignemnt
		case '=': 
			return symtable[interpreter(root->args[0])].value = interpreter(root->args[0]);

		//Statementlists
		case ';': 
			return interpreter(root->args[0]), interpreter(root->args[1]);
		
		//Statements
		case WHILE:  
			return while(interpreter(root->args[0])) { interpreter(root->args[1]) };
		case IF: 
			return interpreter(root->args[0]) ? interpreter(root->args[1]) : interpreter(root->args[2]);
		case PRINT: 
			return printf("%s = %d", symtable[interpreter(root->args[0])].lexptr, symtable[interpreter(root->args[0])].value);
		case READ;
			return printf("%s := ", symtable[interpreter(root->args[0])].lexptr), scanf("%d", symtable[interpreter(root->args[0])].value)
			
		//Basic operators
		case '+': 
			return interpreter(root->args[0]) + interpreter(root->args[1]);
		case '-': 
			return interpreter(root->args[0]) - interpreter(root->args[1]);
		case '*': 
			return interpreter(root->args[0]) * interpreter(root->args[1]);
		case '/': 
			return interpreter(root->args[0]) / interpreter(root->args[1]);
		case DIV: 
			return interpreter(root->args[0]) / interpreter(root->args[1]);
		case MOD: 
			return interpreter(root->args[0]) % interpreter(root->args[1]);
		case '%': 
			return interpreter(root->args[0]) % interpreter(root->args[1]);
		case '&': 
			return interpreter(root->args[0]) & interpreter(root->args[1]);
		case '|': 
			return interpreter(root->args[0]) | interpreter(root->args[1]);
		case '<': 
			return interpreter(root->args[0]) < interpreter(root->args[1]);
		case '>': 
			return interpreter(root->args[0]) > interpreter(root->args[1]);
		case '?': 
			return interpreter(root->args[0]) ? interpreter(root->args[1]) : interpreter(root->args[2]);
	}
}