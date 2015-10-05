#include <stdio.h>

int state = 1;
	
int main()
{
	char input;
	for(;;)
	{
		printf("Current state = %d: ", state);
		input = getchar();
		while (getchar() != '\n')
			;
		switch (state)
		{
			case 1: 
				if (input == 'a')
					state = 2;
				else
					state = 4;
				break;

			case 2: 
				if (input == 'b')
					state = 1;
				else if (input == 'a')
					state = 3;
				else
					state = 4;
				break;

			case 3: break;
			case 4: break;
		}
	}
}