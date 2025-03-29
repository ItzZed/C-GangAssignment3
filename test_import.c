#include <stdio.h>
#include <stdlib.h>
#include "DB.h"
#include "DB_impl.h"

int main()
{
    // Test the importDB function
    importDB("PicnicTableSmall.csv");
    printf("%d\n", Db->picnicTableCount);

    // Print the picnicTableTable entries
    printf("%d entries:\n", Db->picnicTableCount);
    printf("tableId|siteId|tableTypeId|surfaceMaterialId|structuralMaterialId|streetAvenue|neighbourhoodId|Ward|Latitude|Longitude\n");
    for (int i = 0; i < Db->picnicTableCount; i++)
    {
        printf("%7d|%6d|%11d|\n", i, Db->picnicTableTable[i]->siteID, Db->picnicTableTable[i]->tableTypeId);
    }

    printf("\ntableType Table:\n");
    for (int i = 0; i < Db->tableTypeTable->capacity; i++)
    {
        printf("%d: %s\n", i, Db->tableTypeTable->entries[i]);
    }
    freeDB();
    return 0;
}