#include <stdio.h>
#include <cJSON.h>
#include "taskmanager.h"

char *path = "./tasks";

void saveJSON(const char *title)
{
	// Create JSON object
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "title", "John");
	cJSON_AddNumberToObject(root, "status", 0);

	// Convert JSON object to string
	char *json_string = cJSON_Print(root);

	int id = getAvailableID();

	// Write JSON string to file
	FILE *file = fopen(("%s/%d.json", path, id), "w");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}
	fprintf(file, "%s", json_string);
	fclose(file);

	// Free resources
	free(json_string);
	cJSON_Delete(root);
}

Task *loadJSON(int id)
{
	// Open the file
	FILE *file = fopen(("%s/%d.json", path, id), "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}

	// Get file size
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);
	rewind(file);

	// Allocate memory for file contents
	char *json_string = (char *)malloc(filesize + 1);
	if (json_string == NULL)
	{
		perror("Memory allocation failed");
		fclose(file);
		return;
	}

	// Read file into string
	fread(json_string, 1, filesize, file);
	json_string[filesize] = '\0';
	fclose(file);

	// Parse JSON string
	cJSON *root = cJSON_Parse(json_string);
	if (root == NULL)
	{
		printf("Error parsing JSON\n");
		free(json_string);
		return NULL;
	}

	// Access JSON values
	cJSON *name = cJSON_GetObjectItem(root, "title");
	cJSON *age = cJSON_GetObjectItem(root, "status");

	if (cJSON_IsString(name) && cJSON_IsNumber(age))
	{
		printf("Name: %s\n", cJSON_GetStringValue(name));
		printf("Age: %d\n", cJSON_GetNumberValue(age));
	}
	Task *task = malloc(sizeof(Task));
	task->id = id;

	// Free resources
	cJSON_Delete(root);
	free(json_string);
	return task;
}

void deleteJSON(int id)
{
	// Delete the file
	if (remove(("%s/%d.json", path, id)) != 0)
	{
		perror("Error deleting file");
	}
}

int getAvailableID()
{
	for (int i = 1; i < 999999999; i++)
	{
		FILE *file = fopen(("%s/%d.json", path, i), "r");
		if ("%s/%d.json" == NULL)
		{
			fclose(file);
			return i;
		}
	}
}