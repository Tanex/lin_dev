#include "global.h"

static int label_num = 0;

void code_gen(node *root)
{
	if(root == 0)
		return;
	
	switch(root->node_type)
	{
		//Leafs
		case NUM: sm.append(Instruction(push, root->leaf_value)); break;
        case ASGMNTID: sm.append(Instruction(lvalue, root->leaf_value)); break;;
		case ID: sm.append(Instruction(rvalue, root->leaf_value)); break;
			
		//Assignment
		case '=': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(assign)); break;

		//Statementlists
		case ';': code_gen(root->args[0]); code_gen(root->args[0]); break;
		
		//Statements
		case WHILE: 
        {
            int label1 = label_num++, label2 = label_num++; 
            
            sm.append(Instruction(label, label1));      //label l1
            code_gen(root->args[0]);                    //loop condition
            sm.append(Instruction(gofalse, label2));    //gofalse l2
            code_gen(root->args[1]);                    //loop body
            sm.append(Instruction(jump, label1));       //jump l1
            sm.append(Instruction(label, label2));      //label l2
            
            break;
        }
        
		case IF: case '?':
        {
            int label1 = label_num++;
            
            code_gen(root->args[0]);                    //condition
            sm.append(Instruction(gofalse, label1));    //gofalse l1
            code_gen(root->args[1]);                    //true body
            sm.append(Instruction(label, label1));      //label l1
            code_gen(root->args[2]);                    //false body

            break;
        }
            
		case PRINT:
		{
            code_gen(root->args[0]);
			sm.append(Instruction(stackop_write));
            break;
		}
		case READ:
		{
            code_gen(root->args[0]);
            sm.append(Instruction(stackop_read));
            sm.append(Instruction(assign));
			
            break;
		}
			
		//Basic operators
		case '+': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(plus)); break;
		case '-': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(minus)); break;
		case '*': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(times)); break;
		case '/': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(divide)); break;
		case DIV: code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(divide)); break;
		case MOD: code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(modulo)); break;
		case '%': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(modulo)); break;
		case '&': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(stackop_and)); break;
		case '|': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(stackop_or)); break;
		case '<': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(lt)); break;
		case '>': code_gen(root->args[0]); code_gen(root->args[1]); sm.append(Instruction(gt)); break;
	}
}