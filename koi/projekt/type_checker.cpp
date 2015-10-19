#include "global.h"

enum type type_checker(node *root)
{
    if(root == 0)
		return VOID;
        
    type_checker(root->args[0]);
	type_checker(root->args[1]);
	type_checker(root->args[2]);
	type_checker(root->args[3]);
	
	switch(root->node_type)
	{
		//Leafs - should already have var_type set, no need to deduce
		//case NUM: break;
        //case ASGMNTID: break;;
		//case ID: break;
			


		//Statements & Statementlists
		case ';': 
            root->var_type = VOID;
            if(root->args[0] != 0 && root->args[0]->var_type == TYPE_ERROR)
                root->var_type = TYPE_ERROR;                
            if(root->args[1] != 0 && root->args[1]->var_type == TYPE_ERROR)
                root->var_type = TYPE_ERROR;
            break;
        
        case WHILE: 
            if(root->args[0]->var_type == INTEGER && root->args[1]->var_type == VOID)
                root->var_type = VOID;
            else
                root->var_type = TYPE_ERROR;
            break;
        
        case IF: 
        case '?': 
            if(root->args[0]->var_type == INTEGER && root->args[1]->var_type == VOID && root->args[2]->var_type == VOID)
                root->var_type = VOID;
            else
                root->var_type = TYPE_ERROR;
            break;
        
        case PRINT: 
        case READ: 
            if(root->args[0]->var_type == TYPE_ERROR)
                root->var_type = TYPE_ERROR;
            else
                root->var_type = VOID; 
            break;
		

			
		//Assignment & Basic operators
		case '+':
		case '-':
		case '*':
		case '/':
		case DIV:
		case MOD:
		case '%':
		case '&':
		case '|':
		case '<':
		case '>':
            if(root->args[0]->var_type == root->args[1]->var_type)
                root->var_type = root->args[0]->var_type;
            else
                root->var_type = TYPE_ERROR;
            break;
            
		case '=': 
            if(symtable[root->args[0]->leaf_value].var_type == root->args[1]->var_type)
                root->var_type = root->args[0]->var_type;
            else
                root->var_type = TYPE_ERROR;
            break;
        
	}
    return root->var_type;
}