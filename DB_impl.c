/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Authors: Zachary Bell, Gian Cua, Scott Weaver, Thomas Schuster
 * Lab Instructor’s Name: Ardalan Rahmatidehkordi
 * Lecture Instructor’s Name: Abdullah Mohiuddin, Ardalan Rahmatidehkordi
 */

#include "DB.h" /* Import the public database header. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX 200

DataBase *importDB(char *fileName)
{
    char line[LINE_MAX], *token;
    int row = 0;
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file: %s", fileName);
        exit(EXIT_FAILURE);
    }
    fgets(line, LINE_MAX, fp); // Skip first line of CSV file.
    while (fgets(line, LINE_MAX, fp) != NULL)
    {   // breaks if fgets() returns NULL (EOF).
        // line[strcspn(line, "\n")] = 0; // Set newline at end of string to \0
        printf("DEBUG || Row %d\n", row++, line);
        token = strtok(line, ",");
        for(int i = 0; i < 10; i++){
            printf("DEBUG || Column %d || %s\n", i, token);
            // split line, using comma as the delimiter, into separate column values.
            token = strtok(NULL, ",");
        }
    }
    return NULL; // return DataBase
}

void exportDB(char *fileName, DataBase *Db)
{
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file: %s", fileName);
        exit(EXIT_FAILURE);
    }
}
