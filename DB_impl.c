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
#include "DB_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_MAX 200

void importDB(char *fileName)
{
    char line[LINE_MAX], *token;
    int row = 0;
    // Allocate memory for the DataBase structure.
    Db = malloc(sizeof(DataBase));
    if (Db == NULL)
    {
        fprintf(stderr, "Memory allocation failed for DataBase\n");
        exit(EXIT_FAILURE);
    }
    // Allocate memory for the picnicTable table.
    Db->picnicTableTable = malloc(sizeof(PicnicTable *) * INIT_SIZE);
    Db->picnicTableCount = 0; // Initialize picnicTableCount to 0
    Db->picnicTableCapacity = INIT_SIZE;

    // Allocate memory for the tableType table and initialize it.
    Db->tableTypeTable = malloc(sizeof(Table));
    initTable(Db->tableTypeTable);

    FILE *fp = fopen(fileName, "r"); // Open the CSV file for reading
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file: %s", fileName);
        exit(EXIT_FAILURE);
    }

    fgets(line, LINE_MAX, fp); // Skip first line of CSV file.
    while (fgets(line, LINE_MAX, fp) != NULL)
    { // breaks if fgets() returns NULL (EOF).

        PicnicTable *picnicTableEntry = malloc(sizeof(PicnicTable));
        if (picnicTableEntry == NULL)
        {
            fprintf(stderr, "Memory allocation failed for PicnicTable\n");
            freeDB();
            exit(EXIT_FAILURE);
        }
        if (Db->picnicTableCount == Db->picnicTableCapacity)
        {
            printf("Resizing picnicTableTable...\n");
            // Resize the picnicTableTable when at capacity.
            Db->picnicTableCapacity *= 2; // Double the capacity.
            // Temporary PicnicTable pointer
            PicnicTable **temp = realloc(Db->picnicTableTable, sizeof(PicnicTable *) * Db->picnicTableCapacity);
            Db->picnicTableTable = temp; // point the picnicTableTable pointer to temp.
            if (Db->picnicTableTable == NULL)
            {
                fprintf(stderr, "Memory reallocation failed for picnicTableTable\n");
                freeDB();
                exit(EXIT_FAILURE);
            }
        }
        printf("%3d|", row);
        token = strtok(line, ","); // this will be siteID.
        printf("%s\t\t|", token);
        picnicTableEntry->siteID = atoi(token); // convert string to int.
        for (int i = 1; i < 10; i++)
        {
            // split line, using comma as the delimiter, into separate column values.
            token = strtok(NULL, ",");
            switch (i)
            {
            case 1: // tableTypeId
                // if the tableType table is empty, add the first entry.
                if (Db->tableTypeTable->size == 0)
                {
                    Db->tableTypeTable->entries[0] = malloc(strlen(token) + 1);
                    strcpy(Db->tableTypeTable->entries[0], token);
                    Db->tableTypeTable->size++;
                    break;
                }
                else
                {
                    for (int j = 0; j < Db->tableTypeTable->capacity; j++)
                    {
                        if (Db->tableTypeTable->size == Db->tableTypeTable->capacity)
                        {
                            // Resize the tableTypeTable if necessary.
                            resizeTable(Db->tableTypeTable, Db->tableTypeTable->capacity * 2);
                        }
                        if (Db->tableTypeTable->entries[j] == NULL)
                        {
                            // Add new entry to the tableType table.
                            Db->tableTypeTable->entries[j] = malloc(strlen(token) + 1);
                            strcpy(Db->tableTypeTable->entries[j], token);
                            picnicTableEntry->tableTypeId = j;
                            Db->tableTypeTable->size++;
                            break;
                        }
                        if (strcmp(Db->tableTypeTable->entries[j], token) == 0)
                        {
                            picnicTableEntry->tableTypeId = j;
                            break;
                        }
                    }
                }

            default:
                break;
            }
            printf("%s\t|", token);
        }
        printf("\n");

        // insert picnicTableEntry into Db->picnicTableTable.
        Db->picnicTableTable[row++] = picnicTableEntry;
        Db->picnicTableCount++;
    }

    fclose(fp);
}

void exportDB(char *fileName, DataBase *Db)
{
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Could not open file: %s", fileName);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

void resizeTable(Table *table, int newSize)
{
    char **temp = realloc(table->entries, sizeof(char *) * newSize);
    if (temp == NULL)
    {
        fprintf(stderr, "Memory reallocation failed for table entries\n");
        exit(EXIT_FAILURE);
    }
    table->capacity = newSize;
    table->entries = temp;
}

void initTable(Table *table)
{
    table->size = 0;                                      // Initialize size to 0
    table->capacity = INIT_SIZE;                          // Initialize capacity to INIT_SIZE
    table->entries = malloc(sizeof(char **) * INIT_SIZE); // Allocate memory for entries
    if (table->entries == NULL)
    {
        fprintf(stderr, "Memory allocation failed for table entries\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < INIT_SIZE; i++)
    {
        table->entries[i] = NULL; // Initialize each entry to NULL
    }
}
