#include <stdio.h>
#include <stdlib.h>
#include "DB.h"
#include "DB_impl.h"

int main()
{
    DataBase *test_DB;
    test_DB = importDB("PicnicTableSmall.csv");
    return 0;
}