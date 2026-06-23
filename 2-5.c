// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char** items;
    int index;
    int capacity;
} stringVect;

void initialize(stringVect* strV)
{
    strV->index = 0;
    strV->capacity = 2;
    strV->items = malloc(sizeof(char*) * strV->capacity);

}

void addString(stringVect* strV, char* buffer)
{
    size_t len = strlen(buffer) + 1;
    strncpy(strV->items[strV->index++], buffer, len);
}

void print(stringVect* strV)
{
    printf("the address of the double pointer in memory is %p\nthe address of the first value of the array is %p\n\n\nthe value at the first address is %s\n", &(strV->items),&(strV->items[0]), strV->items[0]);
}


int main() {
    char buffer0[] = "str0";
    char buffer1[] = "str1";
    stringVect strV;
    stringVect* strVp = &strV;
    initialize(strVp);
    addString(strVp, buffer0);
    //addString(strVp, buffer1);
}