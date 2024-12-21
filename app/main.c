#include <stdio.h>
#include <string.h>

int main() {
  // Flush after every printf
  setbuf(stdout, NULL);

  // Uncomment this block to pass the first stage
  printf("$ ");

  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);
  int inputLength = strlen(input);
  input[inputLength - 1] = '\0';
  printf("%s: command not found\n", input);
  return 0;
}
