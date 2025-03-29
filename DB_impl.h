/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 *
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */

#ifndef DB_IMPL_H
#define DB_IMPL_H

// Function to initialize the Table structure,
// allocates memory for the entries array and initializes its size and capacity
// It also initializes each entry to NULL
void initTable(Table *table);

// Function resizes a tableType table to a new size,
// reallocates memory for the entries array and updates the capacity
void resizeTable(Table *table, int newSize);

// Imports from a CSV file into the DataBase structure
// Allocates memory for the various tables in the DataBase structure
// Populates lookup tables for tableType, surfaceMaterial, structuralMaterial, and neighborhood
// Populates the picnicTableTable with PicnicTable entries
void importDB(char *fileName);

void exportDB(char *fileName);

#endif