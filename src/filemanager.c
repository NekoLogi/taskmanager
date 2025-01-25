#include <stdio.h>
#include <dirent.h>
#include "cJSON.h"
#include "taskmanager.h"
#include "log.h"

char *path = "./tasks";

void saveJSON(const char *title)
{
	// Create JSON object
	log(DEBUG, "Creating JSON object\n");
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "title", title);
	cJSON_AddNumberToObject(root, "status", 0);

	// Convert JSON object to string
	log(DEBUG, "Convert JSON object to string\n");
	char *json_string = cJSON_Print(root);

	dirExists() == 1 ? log(DEBUG, "Directory exists, checking for available id...\n") : dirCreate();
	int id = getAvailableID();

	// Write JSON string to file
	log(DEBUG, "Write JSON string to file\n");
	char string[200];
	sprintf(string, "%s/%d.json", path, id);
	FILE *file = fopen(string, "w");
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
	log(DEBUG, "Json created and resources freed\n");
}

int dirExists()
{
	DIR *dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return 1;
	}
	return 0;
}

void dirCreate()
{
	if (mkdir(path, 0777) == -1)
	{
		log(DEBUG, "Error creating directory");
	}
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
		log(DEBUG, "Error parsing JSON\n");
		free(json_string);
		return NULL;
	}

	// Access JSON values
	cJSON *name = cJSON_GetObjectItem(root, "title");
	cJSON *age = cJSON_GetObjectItem(root, "status");

	if (cJSON_IsString(name) && cJSON_IsNumber(age))
	{
		log(DEBUG, ("Name: %s\n", cJSON_GetStringValue(name)));
		log(DEBUG, (const char)("Age: %d\n", cJSON_GetNumberValue(age)));
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
	for (int i = 1; i < 9999999; i++)
	{
		char string[200];
		sprintf(string, "Checking ID: %d\n", i);
		log(DEBUG, string);
		sprintf(string, "%s/%d.json", path, i);
		FILE *file = fopen(string, "r");
		if (file == NULL)
		{
			sprintf(string, "Available ID: %d\n", i);
			log(DEBUG, string);

			return i;
		}
		fclose(file);
	}
	return 0;
}