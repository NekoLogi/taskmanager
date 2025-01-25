#include <stdio.h>
#include <string.h>
#include "filemanager.h"
#include "taskmanager.h"
#include "log.h"

int main(int argc, char *argv[])
{
	setLogLevel(INFO);

	if (argc > 3)
	{
		log(INFO, "Too many arguments!\n(Make sure to use underscores instead of spaces)\n");
		return 0;
	}
	if (argc == 1)
	{
		log(INFO, "You can add arguments like create Task_name\n(underscores get replaced by spaces)\n");
	}

	for (int i = 1; i < argc; i++)
	{
		log(DEBUG, ("Argument %d: %s\n", i, argv[i]));
		if (strcmp(argv[i], "create") == 0)
		{
			log(INFO, "Creating task\n");
			saveJSON(argv[i + 1]);
		}
		else if (strcmp(argv[i], "delete") == 0)
		{
			log(DEBUG, "Deleting task\n");
		}
		else if (strcmp(argv[i], "list") == 0)
		{
			log(DEBUG, "Listing tasks\n");
		}
	}
	return 0;
}