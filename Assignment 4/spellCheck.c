/*
Nicholas Rahbany
CS231
Assignment4 - spellCheck.c
*/

#include <ctype.h>  // Used to check isupper()
#include <stdio.h>  // Used for standard input and output
#include <stdlib.h> // Used for malloc, exit, and for file types
#include <string.h> // Used for strlen

void main(int argc, char *argv[])

// data table
// NAME | DESCRIPTION
// argc | The number of arguments the user passed in
// argv | The specific arguments the user defined

{
    if (argc != 3)
    // If there are more or less than two commands when calling the program
    {
        // Close the program and print an error
        printf("Please use this command format >>> ./spellCheck (file).txt (file).txt\n");
        return;
    }
}