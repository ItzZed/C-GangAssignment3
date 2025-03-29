/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataBase *Db = NULL;

void freeDB()
{
    if (Db != NULL)
    {
        // Free each entry in the picnicTable.
        if (Db->picnicTableTable != NULL)
        {
            for (int i = 0; i < Db->picnicTableCount; i++)
            {
                // Free the picnicTable entry and any members with dynamic memory.
                if (Db->picnicTableTable[i] != NULL)
                {
                    // free(Db->picnicTableTable[i]->streetAvenue);
                    free(Db->picnicTableTable[i]);
                }
            }
            free(Db->picnicTableTable);
            Db->picnicTableTable = NULL; // Set to NULL after freeing
        }
        // Free all of the tables if not NULL.
        if (Db->tableTypeTable != NULL)
        {
            for (int i = 0; i < Db->tableTypeTable->size; i++)
            {
                if (Db->tableTypeTable->entries[i] != NULL)
                {
                    free(Db->tableTypeTable->entries[i]);
                }
            }
            free(Db->tableTypeTable->entries);
            free(Db->tableTypeTable);
            Db->tableTypeTable = NULL; // Set to NULL after freeing
        }
            
        // if (Db->surfaceMaterialTable != NULL)
        //     free(Db->surfaceMaterialTable);
        // if (Db->structuralMaterialTable != NULL)
        //     free(Db->structuralMaterialTable);
        // if (Db->neighborhoodTable != NULL)
        //     free(Db->neighborhoodTable);

        // Free the DataBase structure itself.
        free(Db);
        Db = NULL;
    }
}