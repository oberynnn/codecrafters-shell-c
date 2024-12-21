#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define 	EXIT_0 	"exit 0"
#define 	ECHO 	"echo "

// HELPER FUNCTION HEADERS
static void myExit(void);
static void myEcho(char *str);
static int driver(void);

// MAIN FUNCTION
int main(void) {
	return driver();
}

// HELPER FUNCTIONS
static void myExit(void) {
	exit(EXIT_SUCCESS);
}

static void myEcho(char *str) {
	printf("%s\n", str);
}

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
		printf("%s: command not found\n", input);
	}
	return 0;
}