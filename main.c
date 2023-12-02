#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_NAME 64
#define MAX_TABLE_SIZE 64
    char* positions []={"Right Back","Left Back","Center Back","Center Back","Central Defensive Midfielder","Right Winger","Right Centre Midfielder","Striker","Left Centre Midfielder","Left Winger"};
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

system("Pause");
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

    team Teams[numTeams+1];
    char name[MAX_NAME];
    int trash;
    for (int i=0; i<numTeams;i++) {
        printf("Enter the name for the %d team\n",i+1);
        scanf(" %[1]d",&trash);
        scanf("%[^\n]s",name);
        strncpy(Teams[i].name,name,64);
    }
    for (int i=0; i<numTeams; i++) {
        printf("Enter the name of the goalkeeper for team %s\n",Teams[i].name);
        scanf(" %[1]d",&trash);
        scanf("%[^\n]s",Teams[i].goalkeeper.name);
        printf("Enter the diving of the goalerkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.div);
        } while(Teams[i].goalkeeper.div >= 100 || Teams[i].goalkeeper.div < 0);


        printf("Enter the handling of the goalerkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.hand);
        } while(Teams[i].goalkeeper.hand >= 100 || Teams[i].goalkeeper.hand < 0);


        printf("Enter the kicking of the goalerkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.kick);
        } while(Teams[i].goalkeeper.kick >= 100 || Teams[i].goalkeeper.kick < 0);


        printf("Enter the reflexes of the goalerkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.reflex);
        } while(Teams[i].goalkeeper.reflex >= 100 || Teams[i].goalkeeper.reflex < 0);


        printf("Enter the speed of the goalerkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.speed);
        } while(Teams[i].goalkeeper.speed >= 100 || Teams[i].goalkeeper.speed < 0);


        printf("Enter the positioning of the goalerkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.position);
        } while(Teams[i].goalkeeper.position >= 100 || Teams[i].goalkeeper.position < 0);

        Teams[i].goalkeeper.Overall=(Teams[i].goalkeeper.div+Teams[i].goalkeeper.hand+Teams[i].goalkeeper.kick+Teams[i].goalkeeper.reflex+Teams[i].goalkeeper.speed+Teams[i].goalkeeper.position)/6;
        printf("the overall power of the goalkeeper %s is: %d\n",Teams[i].goalkeeper.name,Teams[i].goalkeeper.Overall);




        for (int j=0;j<11;j++) {
            printf("Enter the name for the %s for team %s\n",positions[j],Teams[i].name);
            scanf(" %[1]d",&trash);
            scanf("%[^\n]s",Teams[i].players[j].name);

            printf("Enter the pace of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].pace);
            } while(Teams[i].players[j].pace >= 100 || Teams[i].players[j].pace < 0);

            
            printf("Enter the pass of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].pass);
            } while(Teams[i].players[j].pass >= 100 || Teams[i].players[j].pass < 0);


            printf("Enter the dribble of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].dribble);
            } while(Teams[i].players[j].dribble >= 100 || Teams[i].players[j].dribble < 0);


            printf("Enter the defend of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].defend);
            } while(Teams[i].players[j].defend >= 100 || Teams[i].players[j].defend < 0);


            printf("Enter the shooting of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].shoot);
            } while(Teams[i].players[j].shoot >= 100 || Teams[i].players[j].shoot < 0);


            printf("Enter the physic of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].physique);
            } while(Teams[i].players[j].physique >= 100 || Teams[i].players[j].physique < 0);

            Teams[i].players[j].Overall=(Teams[i].players[j].pace+Teams[i].players[j].pass+Teams[i].players[j].physique+Teams[i].players[j].shoot+Teams[i].players[j].defend+Teams[i].players[j].dribble)/6;
        printf("the overall power of the player %s is: %d\n",Teams[i].players[j].name,Teams[i].players[j].Overall);

        }

    }


    for (int i=0;i<numTeams;i++) {
        hashTableInsert(&Teams[i]);
    }

    printHashTable();

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



void initHashTable() {
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        hash_Table[i] = NULL;
    }
}
