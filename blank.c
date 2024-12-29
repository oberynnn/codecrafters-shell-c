#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void myEcho(const char *input) {
    int i = 0;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    while (input[i] != '\0') {
        if (input[i] == '\'' && !in_double_quotes) {
            in_single_quotes = !in_single_quotes; // Toggle single quotes
        } else if (input[i] == '"' && !in_single_quotes) {
            in_double_quotes = !in_double_quotes; // Toggle double quotes
        } else if (input[i] == '\\' && input[i + 1] != '\0') {
            // Handle escape sequences
            i++;
            if (input[i] == 'n') {
                putchar('\n');
            } else if (input[i] == 't') {
                putchar('\t');
            } else {
                putchar(input[i]); // Print the escaped character
            }
        } else {
            putchar(input[i]); // Print normal characters
        }
        i++;
    }
    putchar('\n');
}

int main() {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
        if (strncmp(buffer, "echo ", 5) == 0) {
            myEcho(buffer + 5);
        } else if (strncmp(buffer, "cat ", 4) == 0) {
            printf("cat command is not handled in this program.\n");
        } else {
            printf("Unknown command: %s\n", buffer);
        }
    }
    return 0;
}
