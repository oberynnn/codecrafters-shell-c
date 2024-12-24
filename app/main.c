#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////
#define 	EXIT_0 	"exit 0"
#define 	ECHO 	"echo "
#define 	TYPE 	"type "

///////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTION HEADERS
static int driver(void);
static void myExit(void);
static void myEcho(char *str);
static void myType(char *str);
static bool myTypeCommandsCheck(char *str, char commands[][16], int commandsSize);
static void myTypeCommands(char *str, char commands[][16], int commandsSize);
static bool myTypeFileCheck(char *str);
static void myTypeFile(char *str);

///////////////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
int main(void) {
	return driver();
}

///////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
static int driver(void) {
	while (true) {
		setbuf(stdout, NULL);
		printf("$ ");
		// Wait for user input
		char input[100];
		fgets(input, 100, stdin);
		int inputLength = strlen(input);
		input[inputLength - 1] = '\0';
		if (strcmp(input, EXIT_0) == 0) {
			myExit();
		}
		else if (strncmp(input, ECHO, 5 * sizeof(char)) == 0) {
			char *buffer = malloc(100 * sizeof(char));
			strcpy(buffer, input + 5);
			myEcho(buffer);
			free(buffer);
			continue;
		}
		else if (strncmp(input, TYPE, 5 * sizeof(char)) == 0) {
			char *buffer = malloc(100 * sizeof(char));
			strcpy(buffer, input + 5);
			myType(buffer);
			free(buffer);
			continue;
		}
		printf("%s: command not found\n", input);
	}
	return 0;
}

static void myExit(void) {
	exit(EXIT_SUCCESS);
}

static void myEcho(char *str) {
	printf("%s\n", str);
}

static void myType(char *str) {
	char commands[][16] = {"echo", "exit", "type"};
	int commandsSize = sizeof(commands) / sizeof(commands[0]);
	if (myTypeCommandsCheck(str, commands, commandsSize) == true) {
		myTypeCommands(str, commands, commandsSize);
	}
	else if (myTypeFileCheck(str) == true) {
		myTypeFile(str);
	}
	else {
		printf("%s: not found\n", str);
	}
}

static bool myTypeCommandsCheck(char *str, char commands[][16], int commandsSize) {
	for (int i = 0; i < commandsSize; i++) {
		if (strcmp(str, commands[i]) == 0) {
			return true;
		}
	}
	return false;
}

static void myTypeCommands(char *str, char commands[][16], int commandsSize) {
	for (int i = 0; i < commandsSize; i++) {
		if (strcmp(str, commands[i]) == 0) {
			printf("%s is a shell builtin\n", str);
			return;
		}
	}
}

static bool myTypeFileCheck(char *str) {
	char *path = getenv("PATH");
	int pathLength = strlen(path);
	char *envPath = malloc(pathLength * sizeof(char));
	strcpy(envPath, path);
	char *dirpath = strtok(envPath, ":");
	while (dirpath != NULL) {
		DIR *directory = opendir(dirpath);
		if (directory == NULL) {
			dirpath = strtok(NULL, ":");
			continue;
		}
		struct dirent *file;
		while ((file = readdir(directory)) != NULL) {
			if (strcmp(file->d_name, str) == 0) {
				free(envPath);
				closedir(directory);
				return true;
			}
		}
		dirpath = strtok(NULL, ":");
		closedir(directory);
	}
	free(envPath);
	return false;
}

static void myTypeFile(char *str) {
	char *path = getenv("PATH");
	int pathLength = strlen(path);
	char *envPath = malloc(pathLength * sizeof(char));
	strcpy(envPath, path);
	char *dirpath = strtok(envPath, ":");
	while (dirpath != NULL) {
		DIR *directory = opendir(dirpath);
		if (directory == NULL) {
			dirpath = strtok(NULL, ":");
			continue;
		}
		struct dirent *file;
		while ((file = readdir(directory)) != NULL) {
			if (strcmp(file->d_name, str) == 0) {
				printf("%s is %s/%s\n", str, dirpath, file->d_name);
				free(envPath);
				closedir(directory);
				return;
			}
		}
		dirpath = strtok(NULL, ":");
		closedir(directory);
	}
	free(envPath);
	printf("%s not found\n", str);
	return;
}