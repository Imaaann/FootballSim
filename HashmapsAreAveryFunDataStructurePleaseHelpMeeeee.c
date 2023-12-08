#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 64
#define MAX_TABLE_SIZE 10

typedef struct team{
    char name[MAX_NAME];
    int pts;
    // ... stuff
    struct team *next;
} team;
// test
team * hash_Table[MAX_TABLE_SIZE];

void initHashTable();
void printHashTable();
unsigned int hash(char* name);
int hashTableInsert(team *p);
team* hashTableLookup(char* name);
team* hashTableDelete(char* name);
void hashTableCopy(team* teamArr[]);
void printArr(team* Arr[], int n);



int main() {

    // intiliasiation test

    initHashTable();
    printHashTable();

    // insetion test

    team Imad = {.name = "Imad", .pts=82}; 
    team Mouad = {.name = "Mouad", .pts=82}; 
    team Fraantic = {.name = "Fraantic", .pts=82}; 
    team Shoty = {.name = "Shoty", .pts=82}; 
    team Kc = {.name = "Kc", .pts=82}; 
    team whitey = {.name = "Whitey", .pts=82};

    hashTableInsert(&Imad);
    hashTableInsert(&Mouad);
    hashTableInsert(&Fraantic);
    hashTableInsert(&Shoty);
    hashTableInsert(&Kc);
    hashTableInsert(&whitey);

    printHashTable();


    // lookup test
    printf("Looking for Mouad");
    team*  tmp =  hashTableLookup("Ymak");
    if (tmp != NULL) {
        printf("\nWe found %s\n", tmp -> name);
    } else {
        printf("\nNo one found\n");
    }
    printf("Done \n");

    // delete test
    hashTableDelete("Imad");

    tmp =  hashTableLookup("Imad");
    if (tmp != NULL) {
        printf("We found %s\n", tmp -> name);
    } else {
        printf("No one found\n");
    }
    printf("Done \n");

    // Copy & Print test;
    team* Arr[MAX_TABLE_SIZE];
    hashTableCopy(Arr);
    printArr(Arr,5);

    printf("\n");
    system("Pause");
    return 0;
}


void initHashTable() {
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        hash_Table[i] = NULL;
    }
    // table is Empty Yiiipee
}



void printHashTable() {
    printf("New Hash Table Print\n");
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        if (hash_Table[i] == NULL) {
            printf("\t%i\t----\n",i);
        } else {
            printf("\t%i\t-",i);
            team* tmp = hash_Table[i];
            while (tmp != NULL) {
                printf("%s -", tmp -> name);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
    printf("End of hash Table Print\n");
}



unsigned int hash(char* name) {
    int strLength = strnlen(name, MAX_NAME);
    unsigned int hashValue = 0;
    for (int i=0; i<strLength; i++) {
        hashValue += name[i];
        hashValue = ( hashValue * name[i]) % MAX_TABLE_SIZE;

    }
    return hashValue;
}



int hashTableInsert(team *p) {
    if (p == NULL) {
        return 0;
    }
    int index = hash(p -> name);
    p -> next = hash_Table[index];
    hash_Table[index] = p;
    return 1;
} 



team* hashTableLookup(char* name) {
    int index = hash(name);
    team *tmp = hash_Table[index];
    while (tmp != NULL && strncmp(tmp -> name, name, MAX_NAME) != 0) 
    {
        tmp = tmp -> next;
    }
    return tmp;
}



team* hashTableDelete(char* name) {
    int index = hash(name);
    team* tmp = hash_Table[index];
    team* prv = NULL;
    while (tmp != NULL && strncmp(tmp -> name, name, MAX_NAME) != 0) 
    {
        prv = tmp;
        tmp = tmp -> next;
    }
    if (tmp == NULL) return NULL;
    if (prv == NULL) {
        // delete head of linked list by pushing the next on in the linked list to the first
        hash_Table[index] = tmp -> next;
    } else {
        prv -> next = tmp -> next; // delete node at tmp by pushing the pointers away from it
    } 
    return tmp;
}

void hashTableCopy(team* teamArr[]) {
    int j=0;
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        if (hash_Table[i] != NULL) {
            team* tmp = hash_Table[i];
            while (tmp != NULL) {
                teamArr[j] = tmp;
                j++;
                tmp = tmp -> next;
            }
        }
    }
}


void printArr(team* Arr[], int n) {
    printf("[");
    for (int i=0; i<(n-1); i++) {
        printf("%s ,", Arr[i]->name);
    }
    printf("%s]", Arr[n-1]->name);
}