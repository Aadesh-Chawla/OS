#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

// Function prototypes
void processSystemCalls();
void fileSystemCalls();
void communicationSystemCalls();
void informationSystemCalls();

int main() {
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Process related system calls\n");
        printf("2. File related system calls\n");
        printf("3. Communication system calls\n");
        printf("4. Information related system calls\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                processSystemCalls();
                break;
            case 2:
                fileSystemCalls();
                break;
            case 3:
                communicationSystemCalls();
                break;
            case 4:
                informationSystemCalls();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to demonstrate process related system calls
void processSystemCalls() {
    pid_t childPid;
    int status;

    childPid = fork();

    if (childPid < 0) {
        perror("fork");
        return;
    } else if (childPid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), childPid);
        wait(&status);
    }
}

// Function to demonstrate file related system calls
void fileSystemCalls() {
    int fd;
    char buffer[100];
    ssize_t bytesRead, bytesWritten;

    // Create and open a new file
    fd = open("hello.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd < 0) {
        perror("open");
        return;
    }

    // Write data to the file
    bytesWritten = write(fd, "Hello, this is a sample file!", strlen("Hello, this is a sample file!"));

    if (bytesWritten < 0) {
        perror("write");
    }

    // Read data from the file
    lseek(fd, 0, SEEK_SET); // Move the file offset to the beginning
    bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead < 0) {
        perror("read");
    } else {
        buffer[bytesRead] = '\0';
        printf("Read from file: %s\n", buffer);
    }

    // Close the file
    close(fd);

    // Remove the file
    unlink("hello.txt");
}

// Function to demonstrate communication system calls
void communicationSystemCalls() {
    int fd[2]; // File descriptors for the pipe
    char buffer[100];
    ssize_t bytesRead, bytesWritten;

    // Create a pipe
    if (pipe(fd) < 0) {
        perror("pipe");
        return;
    }

    pid_t childPid = fork();

    if (childPid < 0) {
        perror("fork");
        return;
    } else if (childPid == 0) {
        // Child process - write to the pipe
        close(fd[0]); // Close the read end of the pipe
        char message[] = "Hello from the child process!";
        bytesWritten = write(fd[1], message, strlen(message));
        close(fd[1]); // Close the write end of the pipe

        if (bytesWritten < 0) {
            perror("write");
        }
    } else {
        // Parent process - read from the pipe
        close(fd[1]); // Close the write end of the pipe
        bytesRead = read(fd[0], buffer, sizeof(buffer));
        close(fd[0]); // Close the read end of the pipe

        if (bytesRead < 0) {
            perror("read");
        } else {
            buffer[bytesRead] = '\0';
            printf("Message received from child process: %s\n", buffer);
        }

        wait(NULL); // Wait for the child process to finish
    }
}

// Function to demonstrate information related system calls
void informationSystemCalls() {
    struct stat fileStat;

    if (stat("hello.txt", &fileStat) < 0) {
        perror("stat");
        return;
    }

    printf("Information about 'sample_file.txt':\n");
    printf("File Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Number of Links: %ld\n", (long)fileStat.st_nlink);
    printf("File inode: %ld\n", (long)fileStat.st_ino);
    printf("File Permissions: %o\n", fileStat.st_mode);
    printf("File UID: %d\n", fileStat.st_uid);
    printf("File GID: %d\n", fileStat.st_gid);
}
