#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc > 3) {
		printf("Too many arguments!\n(Make sure to use underscores instead of spaces)\n");
		return 0;
	}
	if (argc == 1)
	{
		printf("You can add arguments like create Task_name\n(underscores get replaced by spaces)\n");
	}


    	for (int i = 1; i < argc; i++)
    	{
		printf("Argument %d: %s\n", i, argv[i]);
	}
    	printf("Hello, World!\n");
    	return 0;
}