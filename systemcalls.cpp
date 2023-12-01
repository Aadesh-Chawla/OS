#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;
// Function prototypes


void processSystemCalls()
{

    pid_t child_id;

    int status;

    child_id = fork();

    if (child_id < 0)
    {

        perror("fork");

        return;
    }
    else if (child_id == 0)
    {


        printf("Child process: PID = %d\n", getpid());

        exit(0);
    }
    else
    {

        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), childPid);

        wait(&status);
    }
}


void fileSystemCalls()
{

    int fd;
    char buffer[100];
    ssize_t bytes_Read, bytes_Written;

    fd = open("sample.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (fd < 0)
    {
        perror("FILE OPEN");
        return;
    }


    bytes_Written = write(fd, "This is a sample file", strlen("This is a sample file"));

    if (bytes_Written < 0)
    {

        perror("FILE WRITE");
    }
    lseek(fd, 0, SEEK_SET);
    bytes_Read = read(fd, buffer, sizeof(buffer));
    if (bytes_Read < 0)
    {

        perror("FILE READ");
    }
    else
    {
        buffer[bytes_Read] = '\0';
        printf("READ FROM THE FILE: %s\n", buffer);
    }
    close(fd);
    unlink("sample.txt");
}


void communicationSystemCalls()
{

    int fd[2]; 
    char buffer[100];
    ssize_t bytes_Read, bytes_Written;
    if (pipe(fd) < 0)
    {
        perror("PIPE CREATION");
        return;
    }
    pid_t child_id = fork();
    if (child_id < 0)
    {
        perror("fork");
        return;
    }
    else if (child_id == 0)
    {

        close(fd[0]);

        char message[] = "Child Process Executing.\n";

        bytes_Written = write(fd[1], message, strlen(message));

        close(fd[1]);

        if (bytes_Written < 0)
        {

            perror("write");
        }
    }
    else
    {

        close(fd[1]); 
        bytes_Read = read(fd[0], buffer, sizeof(buffer));
        close(fd[0]); 

        if (bytes_Read < 0)
        {

            perror("read");
        }
        else
        {

            buffer[bytesRead] = '\0';

            printf("Msg from child process: %s\n", buffer);
        }
        wait(NULL);
    }
}



void informationSystemCalls()
{

    struct stat file_Stat;
    if (stat("test.txt", &file_Stat) < 0)
    {

        perror("stat");

        return;
    }
    printf("Details of teh file:\n");
    printf("Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("UID: %d\n", fileStat.st_uid);
    printf("GID: %d\n", fileStat.st_gid);
    printf("File inode: %ld\n", (long)fileStat.st_ino);
    printf("Permissions: %o\n", fileStat.st_mode);
    printf("Number of Links: %ld\n", (long)fileStat.st_nlink);
}



int main()
{

    int choice;

    while (true)
    {

        cout << "\nChoose the appropriate:\n";
        cout << "1. Process related system calls\n";
        cout << "2. File related system calls\n";
        cout << "3. Communication system calls\n";
        cout << "4. Information related system calls\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {

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

            cout << "Exiting..." << endl;

            exit(0);

        default:

            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}