#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Redirect standard output to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return 1;
    }

    // Now printf will write to output.txt instead of the console
    printf("This will be written to output.txt\n");

    close(fd);
    return 0;
}
