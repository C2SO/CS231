/* 
Nicholas Rahbany
CS231 
Assignment 4 - lex.c
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *openFile(char *fileName); // Function to open the requested file
void printFile(FILE *inFile);   // Function that prints the file

void main(int argc, char *argv[])
// The first function that is called when the program
// starts. It takes in the user's arguments, will then
// check if there are any argument errors, then will
// call the openFile and printFile function if there
// are no arguments

// data table
// NAME | DESCRIPTION
// argc | The number of arguments the user passed in
// argv | The specific arguments the user defined
// file | The file that the user requested to open

{
    if (argc != 2)
    // If there are more or less than two commands when calling the program
    {
        // Close the program and print an error
        printf("Please use this command format >>> ./lex (file).txt\n");
        return;
    }
    FILE *file = openFile(argv[1]);
    // Sets the file to the file the user passed in
    printFile(file); // Prints the file
    fclose(file);    // Closes the file
}

FILE *openFile(char *fileName)
// This function sets the program's
// file to the file that the user
// defined to the program

// data table
// NAME          | DESCRIPTION
// fileName      | The file name that the user passed in
// requestedFile | If the file was present, this is the file object

{
    FILE *requestedFile = fopen(fileName, "r");
    // Sets requestedFile to the file that the user defined
    if (requestedFile) // If the file is present
    {
        return requestedFile; // Return the found file
    }
    // If the file was not found
    printf("Cannot find the requested file.\n"); // Print an error
    exit(0);                                     // Exit the program
}

void printFile(FILE *inFile)
// This function is used to print the file's
// contents into the console

// data table
// NAME        | DESCRIPTION
// inFile      | The file that the user defined
// size        | The size of the line
// line        | The current line of the file
// wordPrinted | Boolean to check if the word was printed
// length      | The length of the line
// index       | The index for the length of the line

{
    size_t size;                          // Used to define the size of the line
    char **line = malloc(sizeof(char *)); // Used to store the line
    // Need to make double pointer because line holds an array of words
    // which holds an array of characters
    while (getline(line, &size, inFile) != -1) //  While the line exists
    {
        int wordPrinted = 0;          // The word has not been printed
        int length = strlen(line[0]); // Sets the length of the line
        for (int index = 0; index < length; index++)
        // For every character in the line
        {
            if (isalpha(line[0][index]))
            // If the character is part of the alphabet
            {
                printf("%c", line[0][index]); // Print the character
                wordPrinted = 1;              // The word has been printed
            }
            // If the character is not part of the alphabet
            else if (wordPrinted)
            // If the word has been printed
            {
                printf("\n");    // Print a new line character
                wordPrinted = 0; // The new word has not been printed
            }
        }
    }
}