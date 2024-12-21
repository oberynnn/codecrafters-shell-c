#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define 	EXIT_0 	"exit 0"

// HELPER FUNCTION HEADERS
static void myExit(void);

// MAIN FUNCTION
int main(void) {
	// Flush after every printf
	setbuf(stdout, NULL);
	// Uncomment this block to pass the first stage
	printf("$ ");
	// Wait for user input
	char input[100];
	fgets(input, 100, stdin);
	int inputLength = strlen(input);
	input[inputLength - 1] = '\0';
	if (strcmp(input, EXIT_0) == 0) {
		myExit();
	}
	printf("%s: command not found\n", input);
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
		printf("%s: command not found\n", input);
	}
	return 0;
}

// HELPER FUNCTIONS
static void myExit(void) {
	exit(EXIT_SUCCESS);
}