#include "global.h"

void interpreter(node *root)
{
	if(root == 0)
		return;
	
	switch(root->node_type)
	{
		//Leafs
		case NUM: case ASGMNTID:
			return root->leaf_value;
		case ID: 
			return symtable[root->leaf_value].value;
			
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
			if (interpreter(root->args[0]))
				return interpreter(root->args[1]);
			else 
				return interpreter(root->args[2]);
		case PRINT:
		{
			struct entry *variable = &symtable[interpreter(root->args[0])];
			printf("%s = %d\n", variable->lexptr, variable->value);
			return variable->value;
		}
		case READ:
		{
			struct entry *variable = &symtable[interpreter(root->args[0])];
			printf("%s := ", variable->lexptr);
			scanf("%d", &variable->value);
			return variable->value;
		}
			
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