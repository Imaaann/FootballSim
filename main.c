#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 64
#define MAX_TABLE_SIZE 64
    typedef struct {
        char name[MAX_NAME];
        // stats
        int pace;
        int pass;
        int shoot;
        int dribble;
        int defend;
        int physique;
        int Overall;

    } player; // goaler but he gets the goals not defend from them

    typedef struct {
        char name[MAX_NAME];
        
        int div;
        int hand;
        int kick;
        int reflex;
        int speed;
        int position;
        int Overall;

    } goaler; // defends from the goals :skull:
    
    typedef struct team{
        char name[MAX_NAME];
        int pts;
        float weight;
        int wins;
        int defeats;
        int goalsScored;
        int goalsConceded;
        //test
        struct team *next;
        player players[10];
        goaler goalkeeper;
    } team; 

    //Utilities

    //hashTable related functions
    void initHashTable();
    void printHashTable();
    unsigned int hash(char* name);
    int hashTableInsert(team *p);
    team* hashTableLookup(char* name);
    team* hashTableDelete(char* name);
    //Command functions
    void handleNewGame();


    team * hash_Table[MAX_TABLE_SIZE];

int main() {

    char command;
    printf("============\nWelcome to the football simulator ('h' to open help menu)\n============\n");
    do {
    printf("Enter a command\n");
    scanf("%s",&command);
    char command1 = (char) command; 
    switch (command1) {
    case 'n':
        printf("\n======\nStarting a new game\n======\n");
        handleNewGame();
        break;
    case 'f':
        printf("\nYou have forwarded the game to the next day\n");
        break;
    case 's':
        printf("\nYou have saved today's matches in a new file\n");
        break;
    case 'l':
        printf("\nYou have printed the leaderboards as of day %d\n",0);
        break;
    case 'q':
        printf("\nThanks for using my application!\n");
        break;
    case 'h':
        printf("============\nWelcome to the football simulator help page\n============\nHere is the list of the possible commands:\n");
        printf("new (n): Will start a new game and all data about the previous games will get ovverriden\nforward (f): Will continue the simulation and move it to the next day\nsave (s): Will save the matches of the day in a new file located in the logs folder of the project\nleaderboards (l): Will display the leaderboards as of the current time in the championship\nquit (q): Will quit the program and all data will be lost\nhelp (h): Will take you to this menu\n");
        break;
    default:
        printf("Invalid command\n");
    }
    } while (command != 'q');
return 0;
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

void handleNewGame() {

    initHashTable();

    int numTeams;
    printf("Enter the number of teams to play:\n");
    scanf("%d",&numTeams);

    char Teams[numTeams+1][MAX_NAME];
    char name[MAX_NAME];
    int trash;
    for (int i=0; i<numTeams;i++) {
        printf("Enter the name for the %d team\n",i+1);
        if (i==0) scanf(" %[1]d",&trash);
        fgets(name,64,stdin);
        printf("You entered %s",name);
        strncpy(Teams[i],name,64);
    }
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