#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////
#define 	EXIT_0 	"exit 0"
#define 	ECHO 	"echo "
#define 	TYPE 	"type "
#define 	PWD 	"pwd"

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
static void myExec(char *path, int argc, char **argv);
static bool fileExists(char *str);
static char *getFile(char *str);
static void myPwd(void);

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
		else if (strcmp(input, PWD) == 0) {
			myPwd();
			continue;
		}
		else {
			char *argv[15];
			int argc = 0;
			char *token = strtok(input, " ");
			while (token != NULL && argc < 15) {
				argv[argc++] = token;
				token = strtok(NULL, " ");
			}
			argv[argc] = NULL;
			char *path = getFile(argv[0]);
			if (path != NULL) {
				myExec(path, argc, argv);
			}
			else {
				printf("%s: command not found\n", argv[0]);
			}
		}
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
	char commands[][16] = {"echo", "exit", "type", "pwd"};
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

static void myExec(char *path, int argc, char **argv) {
	pid_t pid = fork();
	if (pid == 0) {
		execv(path, argv);
		fprintf(stderr, "error in execv\n");
		exit(1);
	}
	else if (pid < 0) {
		fprintf(stderr, "error in fork\n");
		exit(0);
	}
	else {
		int status;
		waitpid(pid, &status, 0);
	}
}

static bool fileExists(char *str) {
	char *path = getenv("PATH");
	int pathLength = strlen(path);
	char *filePath = malloc(pathLength * sizeof(char));
	strcpy(filePath, path);
	char *dirpath = strtok(filePath, ":");
	while (dirpath != NULL) {
		DIR *d = opendir(dirpath);
		if (d == NULL) {
			dirpath = strtok(NULL, ":");
			continue;
		}
		struct dirent *file;
		while ((file = readdir(d)) != NULL) {
			if (strcmp(str, file->d_name) == 0) {
				free(filePath);
				closedir(d);
				return true;
			}
		}
		dirpath = strtok(NULL, ":");
		closedir(d);
	}
	free(filePath);
	return false;
}

static char *getFile(char *str) {
	char *path = getenv("PATH");
	int pathLength = strlen(path);
	char *filePath = malloc(pathLength * sizeof(char));
	strcpy(filePath, path);
	char *dirPath = strtok(filePath, ":");
	static char fullPath[1024];
	while (dirPath != NULL) {
		snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, str);
		if (access(fullPath, X_OK) == 0) {
			free(filePath);
			return fullPath;
		}
		dirPath = strtok(NULL, ":");
	}
	free(filePath);
	return NULL;
}

static void myPwd(void) {
	char *buffer = malloc(MAXPATHLEN * sizeof(char));
	if (getcwd(buffer, MAXPATHLEN) != NULL) {
		printf("%s\n", buffer);
	}
	else {
		fprintf(stderr, "An error occurred.\n");
	}
}