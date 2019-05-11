/*
Nicholas Rahbany
CS231
Assignment4 - compare.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void runCompare(int pipe[2], char *dictionary)
{

    // runCompare prepares the pipes and arguments for .\compare.out then
    // executes .\compare.out with said arguments

    // data table
    // NAME       | DESCRIPTION
    // pipe       | parameter - the pipe that will be stdout
    // dictionary | parameter - the name of the dictonary file
    // args       | string for the arguments of ./compare.out

    dup2(pipe[0], STDIN_FILENO);
    char *args[3] = {"./compare.out", dictionary, NULL};
    execv(args[0], args);
    close(pipe[0]);
}

void runUniq(int pipeIn[2], int pipeOut[2])
{

    // runUniq prepares the pipes and arguments for uniq (unique pipe)
    // then executes uniq with the said arguments

    // data table
    // NAME    | DESCRIPTION
    // pipeIn  | parameter - the pipe that will be stdin
    // pipeOut | parameter - the pipe that will be stdout
    // args    | string for the arguments of uniq

    dup2(pipeIn[0], STDIN_FILENO);
    dup2(pipeOut[1], STDOUT_FILENO);
    char *args[3] = {"uniq", "-i", NULL};
    execvp(args[0], args);
    close(pipeIn[0]);
    close(pipeOut[1]);
    close(pipeOut[0]); // Read end of pipe
}

void runSort(int pipeIn[2], int pipeOut[2])
{

    // runUniq prepares the pipes and arguments for sort
    // (sort pipe) then executes sort for the said
    // arguments

    // data table
    // pipeIn  | parameter - the pipe that will be stdin
    // pipeOut | parameter - the pipe that will be stdout
    // args    | string for the arguments of sort

    dup2(pipeIn[0], STDIN_FILENO);
    dup2(pipeOut[1], STDOUT_FILENO);
    char *args[3] = {"sort", "-f", NULL};
    execvp(args[0], args);
    close(pipeIn[0]);
    close(pipeOut[1]);
    close(pipeOut[0]); // Read end of pipe
}

void runLex(int pipe[2], char *file)
{

    // runLex prepares the pipes and arguments for .\lex.out then executes
    // .\lex.out with said arguments

    // data table
    // NAME | DESCRIPTION
    // pipe | parameter - the pipe that will be stdout
    // file | parameter - the name of the file to check the spelling of
    // args | string for the arguments of ./lex.out

    dup2(pipe[1], STDOUT_FILENO);
    char *args[3] = {"./lex.out", file, NULL};
    execv(args[0], args);
    close(pipe[1]);
    close(pipe[0]); // Read end of pipe
}

void writeSpellCheckerLog(int pidLex, int pidSort, int pidUniq,
                          int pidCompare)
{

    // this function creates or opens a file named "spellCheck.log"
    // and writes the pids of lex, compare, sort, and uniq to the file.

    // data table
    // NAME       | DESCRIPTION
    // pidLex     | parameter - the PID of lex
    // pidSort    | parameter - the PID of sort
    // pidUniq    | parameter - the PID of uniq
    // pidCompare | parameter - the PID of compare
    // file       | FILE object for the log file

    FILE *file = fopen("spellCheck.log", "w");  //open log in write
    fprintf(file, "lex.out pid: %d\n", pidLex); //mode
    fprintf(file, "sort pid: %d\n", pidSort);
    fprintf(file, "uniq pid: %d\n", pidUniq);
    fprintf(file, "compare.out pid: %d\n", pidCompare);
    fclose(file);
}

void spellChecker(char *file, char *dictionary)
{

    // this function calls the pipes and the functions
    // so that the process can be done in an orderly manner.
    // That being said, it first calls lex, then sort, then uniq,
    // then compare with the dictionary file

    // data table
    // NAME              | DESCRIPTION
    // file              | parameter - the name of the file that needs its
    //                   |     spelling checked
    // dictionary        | parameter - the name of the dictionary file
    // pidLex            | the PID of the lex child
    // pidSort           | the PID of the sort child
    // pidUniq           | the PID of the uniq child
    // pidCompare        | the PID of the compare child
    // pipeLexToSort     | the pipe from lex to sort
    // pipeSortToUniq    | the pipe from sort to uniq
    // pipeUniqToCompare | the pipe from uniq to compare

    pid_t pidLex = -1;        // pid for lex
    pid_t pidSort = -1;       // pid for sort
    pid_t pidUniq = -1;       // pid for uniq
    pid_t pidCompare = -1;    // pid for compare
    int pipeLexToSort[2];     // pipe from lex to sort
    int pipeSortToUniq[2];    // pipe from sort to unique after pipeLexToSort
    int pipeUniqToCompare[2]; // pipe to compare after pipeSortToUniq

    pipe(pipeLexToSort);
    pidLex = fork();
    if (pidLex == 0)
    {
        runLex(pipeLexToSort, file);
        return;
    }
    close(pipeLexToSort[1]); // NEEDS TO CLOSE HERE
    waitpid(pidLex, NULL, 0);
    pipe(pipeSortToUniq);
    pidSort = fork();
    if (pidSort == 0)
    {
        runSort(pipeLexToSort, pipeSortToUniq);
        return;
    }
    close(pipeSortToUniq[1]);
    waitpid(pidSort, NULL, 0);
    pipe(pipeUniqToCompare);
    pidUniq = fork();
    if (pidUniq == 0)
    {
        runUniq(pipeSortToUniq, pipeUniqToCompare);
        return;
    }
    close(pipeUniqToCompare[1]);
    waitpid(pidUniq, NULL, 0);
    pidCompare = fork();
    if (pidCompare == 0)
    {
        runCompare(pipeUniqToCompare, dictionary);
        return;
    }
    waitpid(pidCompare, NULL, 0);
    close(pipeLexToSort[0]);
    close(pipeSortToUniq[0]);
    close(pipeUniqToCompare[0]);
    writeSpellCheckerLog(pidLex, pidSort, pidUniq, pidCompare);
}

void main(int argc, char *argv[])
{

    // Is called at the beginning of the class, and it checks
    // if all the arguments are in order

    // data table
    // NAME | DESCRIPTION
    // argc | parameter - the number of commandline arguments
    // argv | parameter - the commandline arguments

    if (argc != 3)
    {
        fprintf(stderr, "Call spellCheck.c like this >>> ./spellCheck (input file).txt dictionary.txt\n");
        exit(1);
    }
    spellChecker(argv[1], argv[2]);
}