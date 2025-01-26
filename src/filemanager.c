#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "cJSON.h"
#include "taskmanager.h"
#include "log.h"

char *path = "./tasks";

void saveJSON(Task *task)
{
	dirExists() == 1 ? log(DEBUG, "Directory exists, checking for available id...\n") : dirCreate();

	// Create JSON object
	log(DEBUG, "Creating JSON object\n");
	cJSON *root = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "title", task->title);
	cJSON_AddNumberToObject(root, "status", task->status);
	cJSON_AddNumberToObject(root, "id", task->id);

	// Convert JSON object to string
	log(DEBUG, "Convert JSON object to string\n");
	char *json_string = cJSON_Print(root);

	// Write JSON string to file
	log(DEBUG, "Write JSON string to file\n");
	char string[200];
	sprintf(string, "%s/%d.json", path, task->id);
	FILE *file = fopen(string, "w");
	if (file == NULL)
	{
		perror("Error opening file");
		return;
	}
	fprintf(file, "%s", json_string);
	fclose(file);

	// Free resources
	free(task);
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
	log(DEBUG, "Opening file...\n");
	char string[200];
	sprintf(string, "%s/%d.json", path, id);
	FILE *file = fopen(string, "r");
	if (file == NULL)
	{
		perror("Error opening file");
		return NULL;
	}

	// Get file size
	log(DEBUG, "Getting file size...\n");
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);
	rewind(file);

	// Allocate memory for file contents
	log(DEBUG, "Allocating memory for file contents...\n");
	char *json_string = (char *)malloc(filesize + 1);
	if (json_string == NULL)
	{
		perror("Memory allocation failed");
		fclose(file);
		return NULL;
	}

	// Read file into string
	log(DEBUG, "Reading file into string...\n");
	fread(json_string, 1, filesize, file);
	json_string[filesize] = '\0';
	fclose(file);

	// Parse JSON string
	log(DEBUG, "Parsing JSON string...\n");
	cJSON *root = cJSON_Parse(json_string);
	if (root == NULL)
	{
		log(DEBUG, "Error parsing JSON\n");
		free(json_string);
		return NULL;
	}

	// Access JSON values
	log(DEBUG, "Accessing JSON values and converting to task struct...\n");
	cJSON *nameJSON = cJSON_GetObjectItem(root, "title");
	cJSON *statusJSON = cJSON_GetObjectItem(root, "status");
	cJSON *idJSON = cJSON_GetObjectItem(root, "id");

	Task *task = malloc(sizeof(Task));
	task->id = id;
	strcpy(task->title, cJSON_GetStringValue(nameJSON));
	task->status = cJSON_GetNumberValue(statusJSON);
	task->id = cJSON_GetNumberValue(idJSON);

	// Free resources
	cJSON_Delete(root);
	free(json_string);
	return task;
}

void deleteJSON(int id)
{
	char string[200];
	sprintf(string, "%s/%d.json", path, id);
	if (remove(string) != 0)
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