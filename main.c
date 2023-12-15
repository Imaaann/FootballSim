#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>

#define MAX_NAME 64
#define MAX_TABLE_SIZE 64

    char* positions[] ={"Right Back","Left Back","Center Back","Center Back","Central Defensive Midfielder","Right Winger","Right Centre Midfielder","Striker","Left Centre Midfielder","Left Winger"};


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
    
    typedef struct team{ // ~1108 bytes
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

    team Dummy; // Dummy Team :)

    //Utilities
    double calcWeight(team* Team);
    void printArr(team* Arr[], int n);
    int unweightedRNG(int min,int max);
    team* dummyFactory();
    void strnLower(char* str);

    //hashTable related functions
    void initHashTable();
    void printHashTable();
    unsigned int hash(char* name);
    int hashTableInsert(team *p);
    team* hashTableLookup(char* name);
    team* hashTableDelete(char* name);


    //user related functions
    void handleNewGame();
    int randomStatInput();
    void manualInput(team Teams[]);
    void systimaticInput(team Teams[]);
    void fairInput(team Teams[]);
    void* handleNext();
    char getCommand();
    int getNextCommand();



    // hash table initialisation / global variables
    team * hash_Table[MAX_TABLE_SIZE];
    int numTeams;
    int isInGame;
    char leagueName[MAX_NAME];

int main() {
    isInGame = 0;
    srand(time(NULL));
    char command;
    printf("============\nWelcome to the football simulator ('h' to open help menu)\n============\n");
    do {
    command = getCommand();
    } while(command !=  'q');


    system("Pause");
    return 0;
}

// hash table functions -- START

void printHashTable() {
    printf("New Hash Table Print\n");
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        if (hash_Table[i] == NULL) {
            printf("\t%i\t----\n",i);
        } else {
            printf("\t%i\t-",i);
            team* tmp = hash_Table[i];
            while (tmp != NULL) {
                printf("%s (Weight: %f) -", tmp -> name, tmp -> weight);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
    printf("End of hash Table Print\n");
}

// should only be called after handleNewGame() will return an empty array if called before 
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

void initHashTable() {
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        hash_Table[i] = NULL;
    }
}

// hash table functions -- END



// Command Function -- START 

void handleNewGame() {
    char name[MAX_NAME];
    int trash;
    initHashTable();

    printf("Enter the title of the league\n");
    scanf(" %[1]d",&trash);
    scanf("%[^\n]s",name);
    strncpy(leagueName,name,64);
    isInGame = 1;

    printf("Enter the number of teams to play:\n");
    scanf("%d",&numTeams);
    team Teams[numTeams+1];

    for (int i=0; i<numTeams;i++) {
        printf("Enter the name for the %d team\n",i+1);
        scanf(" %[1]d",&trash);
        scanf("%[^\n]s",name);
        strnLower(name);
        strncpy(Teams[i].name,name,64);
    }

    int randomStat = randomStatInput();
    switch (randomStat) {
        case 0:
        manualInput(Teams);
        break;
        case 1:
        systimaticInput(Teams);
        break;
        case 2:
        fairInput(Teams);
        break;
    }


    for (int i=0;i<numTeams;i++) {
        Teams[i].pts = 0;
        Teams[i].weight = calcWeight(&Teams[i]);
        hashTableInsert(&Teams[i]);
    }

    printf("\n");
    system("cls");
    printHashTable();
}

void* handleNext() {
    team* teamArr[numTeams+5];
    hashTableCopy(teamArr);
    if (numTeams % 2 != 0) {
    teamArr[numTeams] = dummyFactory();
    numTeams++;
    }
    int rounds = numTeams - 1;
    int roundNum = 1;
    while(roundNum <= rounds) {
        printf("Round %d:\n", roundNum);
        for (int i = 0; i < numTeams / 2; i++) {
            team* team1 = teamArr[i];
            team* team2 = teamArr[numTeams - 1 - i];
            if (strncmp(team1->name,"Dummy",MAX_NAME) != 0 && strncmp(team2->name,"Dummy",MAX_NAME)) {
                printf("%s vs %s\n", team1->name, team2->name);
                // gameplay starts here
            }
        }
        team* temp = teamArr[1];
        for (int i = 1; i < numTeams - 1; i++) {
            teamArr[i] = teamArr[i + 1];
        }
        teamArr[numTeams - 1] = temp;

        int nextCommand = getNextCommand();
        switch (nextCommand) {
            case 0:
            roundNum++;
            break;
            case 1:
            // handleLeaderBoard
            roundNum++;
            case 2:
            // handleSave
            roundNum++;
            case -1:
            return NULL;
        }
    }

}

int randomStatInput() {
    char r;
    char r1;
    printf("do u want to fill the stats randomly? ('h' for help):\n");
    do {
        scanf("%s",&r);
        char r1 = (char) r; 
        switch (r1) {
            case 'y':
            return 1;
            case 'n':
            return 0;
            case 'f':
            return 2;
            default:
            printf("There is 3 commands:\n1- 'y' fills stats randomly \n2- 'n' asks you to fill it manually \n3- 'f' fills all the stats equally to 50\n");
        }
    } while (1);
}

void manualInput(team Teams[]) {
    int trash;
    // Goalkeeper stats
    for (int i=0; i<numTeams; i++) {
        printf("Enter the name of the goalkeeper for team %s\n",Teams[i].name);
        scanf(" %[1]d",&trash);
        scanf("%[^\n]s",Teams[i].goalkeeper.name);
        printf("Enter the diving of the goalkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.div);
        } while(Teams[i].goalkeeper.div >= 100 || Teams[i].goalkeeper.div < 0);


        printf("Enter the handling of the goalkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.hand);
        } while(Teams[i].goalkeeper.hand >= 100 || Teams[i].goalkeeper.hand < 0);


        printf("Enter the kicking of the goalkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.kick);
        } while(Teams[i].goalkeeper.kick >= 100 || Teams[i].goalkeeper.kick < 0);


        printf("Enter the reflexes of the goalkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.reflex);
        } while(Teams[i].goalkeeper.reflex >= 100 || Teams[i].goalkeeper.reflex < 0);


        printf("Enter the speed of the goalkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.speed);
        } while(Teams[i].goalkeeper.speed >= 100 || Teams[i].goalkeeper.speed < 0);


        printf("Enter the positioning of the goalkeeper : ");
        do {
            scanf("%d",&Teams[i].goalkeeper.position);
        } while(Teams[i].goalkeeper.position >= 100 || Teams[i].goalkeeper.position < 0);

        Teams[i].goalkeeper.Overall=(Teams[i].goalkeeper.div+Teams[i].goalkeeper.hand+Teams[i].goalkeeper.kick+Teams[i].goalkeeper.reflex+Teams[i].goalkeeper.speed+Teams[i].goalkeeper.position)/6;
        printf("the overall power of the goalkeeper %s is: %d\n",Teams[i].goalkeeper.name,Teams[i].goalkeeper.Overall);

        for (int j=0;j<10;j++) {

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


            printf("Enter the physique of the player %s : ",Teams[i].players[j].name);
            do {
                scanf("%d",&Teams[i].players[j].physique);
            } while(Teams[i].players[j].physique >= 100 || Teams[i].players[j].physique < 0);

            Teams[i].players[j].Overall=(Teams[i].players[j].pace+Teams[i].players[j].pass+Teams[i].players[j].physique+Teams[i].players[j].shoot+Teams[i].players[j].defend+Teams[i].players[j].dribble)/6;
            printf("the overall power of the player %s is: %d\n",Teams[i].players[j].name,Teams[i].players[j].Overall);

        }
    }
}

void systimaticInput(team Teams[]) {
    int trash;
    // Goalkeeper stats
    for (int i=0; i<numTeams; i++) {
        printf("Enter the name of the goalkeeper for team %s\n",Teams[i].name);
        scanf(" %[1]d",&trash);
        scanf("%[^\n]s",Teams[i].goalkeeper.name);

        Teams[i].goalkeeper.div= unweightedRNG(1,99);
        Teams[i].goalkeeper.hand= unweightedRNG(1,99);
        Teams[i].goalkeeper.kick= unweightedRNG(1,99);
        Teams[i].goalkeeper.reflex= unweightedRNG(1,99);
        Teams[i].goalkeeper.speed= unweightedRNG(1,99);
        Teams[i].goalkeeper.position= unweightedRNG(1,99);
        Teams[i].goalkeeper.Overall=(Teams[i].goalkeeper.div+Teams[i].goalkeeper.hand+Teams[i].goalkeeper.kick+Teams[i].goalkeeper.reflex+Teams[i].goalkeeper.speed+Teams[i].goalkeeper.position)/6;
        
        printf("the overall power of the goalkeeper %s is: %d\n",Teams[i].goalkeeper.name,Teams[i].goalkeeper.Overall);

        for (int j=0;j<10;j++) {
            printf("Enter the name for the %s for team %s\n",positions[j],Teams[i].name);
            scanf(" %[1]d",&trash);
            scanf("%[^\n]s",Teams[i].players[j].name);

            Teams[i].players[j].pace= unweightedRNG(1,99);
            Teams[i].players[j].pass= unweightedRNG(1,99);
            Teams[i].players[j].shoot= unweightedRNG(1,99);
            Teams[i].players[j].dribble= unweightedRNG(1,99);
            Teams[i].players[j].defend= unweightedRNG(1,99);
            Teams[i].players[j].physique= unweightedRNG(1,99);
            Teams[i].players[j].Overall=(Teams[i].players[j].pace+Teams[i].players[j].pass+Teams[i].players[j].physique+Teams[i].players[j].shoot+Teams[i].players[j].defend+Teams[i].players[j].dribble)/6;

            printf("the overall power of the player %s is: %d\n",Teams[i].players[j].name,Teams[i].players[j].Overall);
        }
    }
}

void fairInput(team Teams[]) {
    int trash;
    // Goalkeeper stats
    for (int i=0; i<numTeams; i++) {
        printf("Enter the name of the goalkeeper for team %s\n",Teams[i].name);
        scanf(" %[1]d",&trash);
        scanf("%[^\n]s",Teams[i].goalkeeper.name);

        Teams[i].goalkeeper.div= 50;
        Teams[i].goalkeeper.hand= 50;
        Teams[i].goalkeeper.kick= 50;
        Teams[i].goalkeeper.reflex= 50;
        Teams[i].goalkeeper.speed= 50;
        Teams[i].goalkeeper.position= 50;
        Teams[i].goalkeeper.Overall=(Teams[i].goalkeeper.div+Teams[i].goalkeeper.hand+Teams[i].goalkeeper.kick+Teams[i].goalkeeper.reflex+Teams[i].goalkeeper.speed+Teams[i].goalkeeper.position)/6;

        for (int j=0;j<10;j++) {
            printf("Enter the name for the %s for team %s\n",positions[j],Teams[i].name);
            scanf(" %[1]d",&trash);
            scanf("%[^\n]s",Teams[i].players[j].name);

            Teams[i].players[j].pace= 50;
            Teams[i].players[j].pass= 50;
            Teams[i].players[j].shoot= 50;
            Teams[i].players[j].dribble= 50;
            Teams[i].players[j].defend= 50;
            Teams[i].players[j].physique= 50;
            Teams[i].players[j].Overall=(Teams[i].players[j].pace+Teams[i].players[j].pass+Teams[i].players[j].physique+Teams[i].players[j].shoot+Teams[i].players[j].defend+Teams[i].players[j].dribble)/6;
        }
    }
}

char getCommand() {
    char command;
    printf("Enter a command\n");
    scanf("%s",&command);
    char command1 = (char) command; 
    switch (tolower(command1)) {
    case 'n':
        handleNewGame();
        break;
    case 'b':
        handleNext();
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
    default :
        printf("=========================================================================================");
        printf("\nWelcome to the football simulator help page\nHere is the list of the possible commands:\n");
        printf("=========================================================================================\n");
        printf("new (n): Will start a new game and all data about the previous games will get ovverriden\nbegin (b): Will start the simulation and move it to the next day\nsave (s): Will save the matches of the day in a new file located in the logs folder of the project\nleaderboards (l): Will display the leaderboards as of the current time in the championship\nquit (q): Will quit the program and all data will be lost\nhelp (h): Will take you to this menu\n");
        break;
    }
    return tolower(command1);
}

int getNextCommand() {
    char r;
    char r1;
    printf("=====================================================\n");
    printf("do u want to progress to next round ? ('h' for help):\n");
    printf("=====================================================\n");
    do {
        scanf("%s",&r);
        char r1 = (char) r; 
        switch (r1) {
            case 'y':
            return 0;
            case 'l':
            return 1;
            case 's':
            return 2;
            case 'q':
            return -1;
            default:
            printf("There is 3 commands:\n1- 'y' send you to the next round \n2- 'l' shows you the leaderboards \n3- 's' saves this round to a log file\n4- 'q' quits the simulation\n");
        }
    } while (1);
}
// Command Functions -- END



// Other functions -- START

double calcWeight(team* Team) {
    if (Team == NULL) {
        return 0;
    } else {
        double Weight;
        // PartialWeight Cus the equation would be TOO LONG
        double DefWeight = 0;
        double CMDWeight = 0;
        double MiddleWeight = 0;
        double AttackerWeight = 0;

        for (int i=0; i<4; i++) {
            DefWeight = DefWeight + ((Team -> players[i].pace) + (Team -> players[i].defend) + (Team -> players[i].physique)  + (Team -> players[i].Overall))/4;
        }
        
        CMDWeight = ((Team -> players[4].dribble) + (Team -> players[4].pass)  + (Team -> players[4].Overall) + ((Team -> players[4].defend)+(Team -> players[4].physique)+(Team -> players[4].shoot))/3)/4;
        // the middle players numbers are 8 and 10 
        for (int i=6; i<9; i=i+2) {
            MiddleWeight = MiddleWeight + ((Team -> players[i].dribble) + (Team -> players[i].pass) + (Team -> players[i].Overall)  + ((Team -> players[i].defend) + (Team -> players[i].physique) +  (Team -> players[i].shoot))/3)/4;
        }
        // the attack players numbers are 5 , 7 and 9
        for (int i=5; i<10; i=i+2) {
            AttackerWeight = AttackerWeight + ((Team -> players[i].pace) + (Team -> players[i].dribble) + (Team -> players[i].shoot)  + (Team -> players[i].Overall) + ((Team -> players[i].pass) + (Team -> players[i].physique))/2)/5;
        }

        Weight = (DefWeight + CMDWeight + MiddleWeight + AttackerWeight + (Team -> goalkeeper.Overall))/11;
        
        return Weight;
    }
}

void printArr(team* Arr[], int n) {
    printf("[");
    for (int i=0; i<(n-1); i++) {
        printf("%s ,", Arr[i] -> name );
    }
    printf("%s]", Arr[n-1] -> name);
}

int unweightedRNG(int min,int max) {
    return ((rand()%(max-min+1))+min);
}

team* dummyFactory() {
    strncpy(Dummy.name,"Dummy",MAX_NAME);
    return &Dummy;
}

void strnLower(char* str) {
    int length = strlen(str);
    str[0]=toupper(str[0]);
    for (int i=1; i<length; i++) {
        str[i] = tolower(str[i]);
    }
}

// other functions - END
