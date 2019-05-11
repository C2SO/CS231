/*
    Nicholas Rahbany
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
void runCompare(int pipe[2], char *dictionary)
{
/*  
    runCompare prepares the pipes and arguments for .\compare.out then
    executes .\compare.out
 
data table
NAME            DESCRIPTION
pipe            parameter - the pipe that will be stdout
dictionary      parameter - the name of the dictonary file
args            string for the arguments of ./compare.out
*/
    dup2(pipe[0], STDIN_FILENO);
    close(pipe[0]);
    char *args[3] = {"./compare.out", dictionary, NULL};
    execv(args[0], args);
}
 
void runUniq(int pipeIn[2], int pipeOut[2])
{
/*  
    runUniq prepares the pipes and arguments for uniq then executes
    uniq -i
 
data table
NAME        DESCRIPTION
pipeIn      parameter - the pipe that will be stdin
pipeOut     parameter - the pipe that will be stdout
args        string for the arguments of uniq
*/
    dup2(pipeIn[0], STDIN_FILENO);
    close(pipeIn[0]);
    close(pipeOut[0]); //close read end of pipe
    dup2(pipeOut[1], STDOUT_FILENO);
    close(pipeOut[1]);
    char *args[3] = {"uniq", "-i", NULL};
    execvp(args[0], args);
}
 
void runSort(int pipeIn[2], int pipeOut[2])
{
/*  
    runUniq prepares the pipes and arguments for sort then executes
    sort -f
 
data table
pipeIn      parameter - the pipe that will be stdin
pipeOut     parameter - the pipe that will be stdout
args        string for the arguments of sort
*/
    dup2(pipeIn[0], STDIN_FILENO);
    close(pipeIn[0]);
    close(pipeOut[0]); //close read end of pipe
    dup2(pipeOut[1], STDOUT_FILENO);
    close(pipeOut[1]);
    char *args[3] = {"sort", "-f", NULL};
    execvp(args[0], args);
}
 
void runLex(int pipe[2], char *fileN) {
   
/*  
    runLex prepares the pipes and arguments for .\lex.out then executes
    .\lex.out
 
data table
NAME        DESCRIPTION
pipe        parameter - the pipe that will be stdout
fileN       parameter - the name of the file to check the spelling of
args        string for the arguments of ./lex.out
*/
    close(pipe[0]); //close read end of pipe
    dup2(pipe[1], STDOUT_FILENO);
    close(pipe[1]);
    char *args[3] = {"./lex.out", fileN, NULL};
    execv(args[0], args);
}
 
void writeSpellCheckerLog(int pidLex, int pidSort, int pidUniq,
    int pidCompare)
{
/*  
    writeSpellCheckerLog creates or opens a file names spellCheck.log
    and writes thepids of lex, compare, sort, and uniq to the file.
 
data table
NAME            DESCRIPTION
pidLex          parameter - the PID of lex
pidSort         parameter - the PID of sort
pidUniq         parameter - the PID of uniq
pidCompare      parameter - the PID of compare
logFile         FILE object for the log file
*/
    FILE *logFile = fopen("spellCheck.log", "w");//open log in write
    fprintf(logFile, "lex.out pid: %d\n", pidLex);  //mode
    fprintf(logFile, "sort pid: %d\n", pidSort);
    fprintf(logFile, "uniq pid: %d\n", pidUniq);
    fprintf(logFile, "compare.out pid: %d\n", pidCompare);
    fclose(logFile);
}
 
void spellChecker(char *file, char *dictionary)
{
/*  
    spellChecker creates a pipe that connects the lex to the sort, then
    forks lex. The parent process then creates a pipe that connects sort
    to uniq, then forks sort. The parent process then creates a pipe
    that connects uniq to compare then forks uniq. The parent process
    then forks compare and writes all of the pids of the created child
    lex, compare, sort, and uniq calls to a log file.
 
data table
NAME                DESCRIPTION
file                parameter - the name of the file that needs its
                        spelling checked
dictionary          parameter - the name of the dictionary file
pidLex              the PID of the lex child
pidSort             the PID of the sort child
pidUniq             the PID of the uniq child
pidCompare          the PID of the compare child
pipeLexToSort       the pipe from lex to sort
pipeSortToUniq      the pipe from sort to uniq
pipeUniqToCompare   the pipe from uniq to compare
*/
    pid_t pidLex = -1;
    pid_t pidSort = -1;
    pid_t pidUniq = -1;
    pid_t pidCompare = -1;
    int pipeLexToSort[2];
    int pipeSortToUniq[2];
    int pipeUniqToCompare[2];
   
    pipe(pipeLexToSort);
    pidLex = fork();
    if (pidLex == 0)
    {
        runLex(pipeLexToSort, file);
        return;
    }
    close(pipeLexToSort[1]); //close write end of pipe
    waitpid(pidLex, NULL, 0);
    pipe(pipeSortToUniq);
    pidSort = fork();
    if (pidSort == 0)
    {
        runSort(pipeLexToSort, pipeSortToUniq);
        return;
    }
    close(pipeSortToUniq[1]); //close write end of pipe
    waitpid(pidSort, NULL, 0);
    pipe(pipeUniqToCompare);
    pidUniq = fork();
    if (pidUniq == 0)
    {
        runUniq(pipeSortToUniq, pipeUniqToCompare);
        return;
    }
    close(pipeUniqToCompare[1]); //close write end of pipe
    waitpid(pidUniq, NULL, 0);
    pidCompare = fork();
    if(pidCompare == 0)
    {
        runCompare(pipeUniqToCompare, dictionary);
        return;
    }
    waitpid(pidCompare, NULL, 0);
    close(pipeLexToSort[0]);//close read end of child pipes
    close(pipeSortToUniq[0]);
    close(pipeUniqToCompare[0]);
    writeSpellCheckerLog(pidLex, pidSort, pidUniq, pidCompare);
}
 
int main(int argc, char *argv[])
{
/*
    main check that the proper number of peramiters are given to the
    program, assigns those file names to strings then has spellChecker
    run the spellchecking
 
data table
NAME    DESCRIPTION
argc    parameter - the number of commandline arguments
argv    parameter - the commandline arguments
*/
    if (argc < 3)
        fprintf(stderr, "spellCheck: Less than two files supplied\n");
    if (argc > 3)
        fprintf(stderr, "spellCheck: More than two files supplied\n");
    if (argc != 3)
        exit(1);
    spellChecker(argv[1], argv[2]);
    return 0;
}