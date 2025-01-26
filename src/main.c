#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filemanager.h"
#include "taskmanager.h"
#include "log.h"

const char *getStatus(int status)
{
	switch (status)
	{
	case 0:
		return "To Do";
	case 1:
		return "In Progress";
	case 2:
		return "Done";
	default:
		return "Unknown";
	}
}

int createTask(const char *title)
{
	int id = getAvailableID();
	if (id == 0)
	{
		log(INFO, "Error getting available ID\n");
		exit(1);
	}

	Task *task = malloc(sizeof(Task));
	strcpy(task->title, title);
	task->id = id;
	task->status = 0;
	saveJSON(task);
	return id;
}

void listTasks()
{
}

void getTask(int id)
{
	Task *task = loadJSON(id);
	if (task == NULL)
	{
		log(INFO, "Task not found\n");
		return 0;
	}
	log(INFO, "Task:\n");
	char string[250];
	sprintf(string, "|  ID: %d\n", task->id);
	log(INFO, string);
	sprintf(string, "|  Title: %s\n", task->title);
	log(INFO, string);
	sprintf(string, "|  Status: %s\n", getStatus(task->status));
	log(INFO, string);
	log(INFO, "---------------\n");
}

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
			log(DEBUG, "Creating task\n");
			int id = createTask(argv[i + 1]);
			getTask(id);
			log(DEBUG, "Task created\n");
		}
		else if (strcmp(argv[i], "delete") == 0)
		{
			log(DEBUG, "Deleting task\n");
			int id = (int)strtol(argv[i + 1], NULL, 10);
			deleteJSON(id);
			log(DEBUG, "Task deleted\n");
		}
		else if (strcmp(argv[i], "list") == 0)
		{
			log(DEBUG, "Listing tasks\n");
		}
		else if (strcmp(argv[i], "get") == 0)
		{
			log(DEBUG, "loading task\n");
			int id = (int)strtol(argv[i + 1], NULL, 10);
			getTask(id);
		}
	}
	return 0;
}