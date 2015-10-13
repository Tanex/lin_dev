#include "global.h"

int interpreter(node *root)
{
	struct entry *variable;

	if(root == 0)
		return 0;
	
	switch(root->node_type)
	{
		//Leafs
		case NUM: case ASGMNTID:
			return root->leaf_value;
		case ID: 
			return symtable[interpreter(root->args[0])].value;
			
		//Assignemnt
		case '=': 
			return symtable[interpreter(root->args[0])].value = interpreter(root->args[1]);

		//Statementlists
		case ';': 
            if(root->args[1] == 0)
                return interpreter(root->args[0]);
            else
            {
                interpreter(root->args[0]);
                return interpreter(root->args[1]);
            }
		
		//Statements
		case WHILE:  
			while(interpreter(root->args[0])) { interpreter(root->args[1]); }
			return 0;
		case IF: 
			return interpreter(root->args[0]) ? interpreter(root->args[1]) : interpreter(root->args[2]);
		case PRINT:
			variable = &symtable[interpreter(root->args[0])];
			printf("%s = %d\n", variable->lexptr, variable->value);
			return variable->value;
		case READ:
			return printf("%s := ", symtable[interpreter(root->args[0])].lexptr), scanf("%d", &symtable[interpreter(root->args[0])].value);
			
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
	return 0;
}