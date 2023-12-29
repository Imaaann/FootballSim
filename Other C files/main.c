#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include<windows.h>

#define MAX_NAME 64
#define MAX_TABLE_SIZE 64
#define SAY_DELAY 1

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
        int weight;
        int AttckW;
        int DefW;
        int MidW;
        int wins;
        int defeats;
        int goalsScored;
        int goalsConceded;
        player players[10];
        goaler goalkeeper;
        struct team* next;
    } team; 

    team Dummy; // Dummy Team :)

    //Other functions
    void* calcWeight(team* Team);
    void printArr(team* Arr[], int n);
    void say(char *str);
    int unweightedRNG(int min,int max);
    team* dummyFactory();
    void strnLower(char* str);
    void simulate(team* Team1, team* Team2);
    int weightedRNG(int min, int max);
    int processAttack(team* TeamAttck, team* TeamDef, float Atck_Advantage, float Def_Advantage);

    //hashTable related functions
    void initHashTable();
    void printHashTable();
    unsigned int hash(char* name);
    int hashTableInsert(team *p);
    team* hashTableLookup(char* name);
    team* hashTableDelete(char* name);


    //user related functions
    void handleNewGame(team* teamArr[]);
    int randomStatInput();
    void manualInput(team Teams[]);
    void systimaticInput(team Teams[]);
    void fairInput(team Teams[]);
    void* handleNext(team* teamArr[]);
    int getNextCommand();



    // hash table initialisation / global variables
    team * hash_Table[MAX_TABLE_SIZE];
    int numTeams;
    int isInGame;
    int hasCommentator;
    char leagueName[MAX_NAME];
    char trash; 

int main() {
    isInGame = 0;
    hasCommentator = 0;
    srand(time(NULL));
    printf("========================\nWelcome to the football simulator hope everything goes well\n========================\n");
    system("Pause");
    printf("Enter the number of teams to play:\n");
    scanf("%d",&numTeams);
    team* teamArray[numTeams + 2];
    handleNewGame(teamArray);
    printArr(teamArray, numTeams);
    system("Pause");
    handleNext(teamArray);

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
                printf("%s (Weight: %d) -", tmp -> name, tmp -> weight);
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

void initHashTable() {
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        hash_Table[i] = NULL;
    }
}

// hash table functions -- END



// Command Function -- START 

void handleNewGame(team* teamArr[]) {
    char name[MAX_NAME];
    int trash;
    team Teams[numTeams+1];
    initHashTable();

    printf("Enter the title of the league\n");
    scanf(" %[1]d",&trash);
    scanf("%[^\n]s",name);
    strncpy(leagueName,name,64);
    isInGame = 1;

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

    printf("Do you want to use a commentator for your game (is slow)");
    char Comm;
    scanf(" %c",&Comm);
    if (Comm == 'y') {
        hasCommentator = 1;
    }


    for (int i=0;i<numTeams;i++) {
        Teams[i].pts = 0;
        calcWeight(&Teams[i]);
        hashTableInsert(&Teams[i]);
        teamArr[i] = &Teams[i];
    }

    printf("\n");
    system("cls");
    isInGame = 1;
    printHashTable();
}

void* handleNext(team* teamArr[]) { 
    int nextCommand;
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
            if (strncmp(team1->name,"Dummy",MAX_NAME) != 0 && strncmp(team2->name,"Dummy",MAX_NAME) != 0) {
                printf("==========\n");
                printf("%s (pts : %d) vs %s (pts : %d)\n", team1->name, team1->pts,team2->name,team2->pts);
                printf("==========\n");
                simulate(team1,team2);
            }
            team1 = NULL;
            team2 = NULL;
        }
        team* temp = teamArr[1];
        for (int i = 1; i < numTeams - 1; i++) {
            teamArr[i] = teamArr[i + 1];
        }
        teamArr[numTeams - 1] = temp;

        if (roundNum != rounds) {
        printf("=====================================================\n");
        printf("do u want to progress to next round ? ('h' for help):\n");
        printf("=====================================================\n");
        }
        if (roundNum == 1) {
            printf("There is 3 commands:\n1- 'y' send you to the next round \n2- 'l' shows you the leaderboards \n3- 's' saves this round to a log file\n4- 'q' quits the simulation\n5- 'p' prints the hashtables and shows the points (tmp cmd) ");
        }

        nextCommand = getNextCommand();
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
            case 3:
            printHashTable();
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

int getNextCommand() {
    char r;
    char r1;
    do {
        scanf("%s",&r);
        trash = getchar();
        char r1 = (char) r; 
        switch (r1) {
            case 'y':
            return 0;
            case 'l':
            return 1;
            case 's':
            return 2;
            case 'p':
            return 3;
            case 'q':
            return -1;
            default:
            printf("There is 3 commands:\n1- 'y' send you to the next round \n2- 'l' shows you the leaderboards \n3- 's' saves this round to a log file\n4- 'q' quits the simulation\n5- 'p' prints the hashtables and shows the points (tmp cmd) ");
        }
    } while (1);
}
// Command Functions -- END



// Other functions -- START

void* calcWeight(team* Team) {
    if (Team == NULL) {
        return NULL;
    } else {
        int Weight = 0;
        // PartialWeight Cus the equation would be TOO LONG
        int DefWeight = 0;
        int CMDWeight = 0;
        int MiddleWeight = 0;
        int AttackerWeight = 0;

        DefWeight = Team->goalkeeper.Overall;
        for (int i=0; i<4; i++) {
            DefWeight = DefWeight + ((Team -> players[i].pace) + (Team -> players[i].defend) + (Team -> players[i].physique)  + (Team -> players[i].Overall))/4;
        }
        
        MiddleWeight = ((Team -> players[4].dribble) + (Team -> players[4].pass)  + (Team -> players[4].Overall) + ((Team -> players[4].defend)+(Team -> players[4].physique)+(Team -> players[4].shoot))/3)/4;
        // the middle players numbers are 8 and 10 
        for (int i=6; i<9; i=i+2) {
            MiddleWeight = MiddleWeight + ((Team -> players[i].dribble) + (Team -> players[i].pass) + (Team -> players[i].Overall)  + ((Team -> players[i].defend) + (Team -> players[i].physique) +  (Team -> players[i].shoot))/3)/4;
        }
        // the attack players numbers are 5 , 7 and 9
        for (int i=5; i<10; i=i+2) {
            AttackerWeight = AttackerWeight + ((Team -> players[i].pace) + (Team -> players[i].dribble) + (Team -> players[i].shoot)  + (Team -> players[i].Overall) + ((Team -> players[i].pass) + (Team -> players[i].physique))/2)/5;
        }

        // Filling the team
        Team->AttckW = AttackerWeight/3;
        Team->DefW = DefWeight/5;
        Team->MidW = MiddleWeight/3;

        Weight = (DefWeight + MiddleWeight + AttackerWeight)/11;
        Team->weight = Weight;

    }
}

void printArr(team* Arr[], int n) {
    printf("[");
    for (int i=0; i<(n-1); i++) {
        printf("%s ,", Arr[i] -> name );
    }
    printf("%s]\n", Arr[n-1] -> name);
}



int unweightedRNG(int min,int max) {
    return ((rand()%(max-min+1))+min);
}

team* dummyFactory() {
    strncpy(Dummy.name,"Dummy",MAX_NAME);
    Dummy.defeats = 0;
    Dummy.pts = 0;
    Dummy.goalsConceded = 0;
    Dummy.goalsScored = 0;
    Dummy.next = NULL;
    Dummy.weight = 0.0;
    Dummy.wins = 0;
    strncpy(Dummy.goalkeeper.name, "Dummy Goalkeeper", MAX_NAME);
    Dummy.goalkeeper.div = 0;
    Dummy.goalkeeper.hand = 0;
    Dummy.goalkeeper.kick = 0;
    Dummy.goalkeeper.position = 0;
    Dummy.goalkeeper.reflex = 0;
    Dummy.goalkeeper.speed = 0;
    Dummy.goalkeeper.Overall = 0;
    for (int i=0 ; i<10; i++) {
        strncpy(Dummy.players[i].name, "Dummy Player", MAX_NAME);
        Dummy.players[i].pace = 0;
        Dummy.players[i].pass = 0;
        Dummy.players[i].physique = 0;
        Dummy.players[i].defend = 0;
        Dummy.players[i].dribble = 0;
        Dummy.players[i].shoot = 0;
        Dummy.players[i].Overall = 0;
    }
    return &Dummy;
}

void strnLower(char* str) {
    int length = strlen(str);
    str[0]=toupper(str[0]);
    for (int i=1; i<length; i++) {
        str[i] = tolower(str[i]);
    }
}

void simulate(team* Team1, team* Team2) {
    // getting the number of encounters
    int w1,w2;
    w1 = (Team1->weight)/1;
    w2 = (Team2->weight)/1;
    int encounterNum = abs(w1-w2) + unweightedRNG(1,3);
    int E=0;
    
    int isInCA = 0;
    int coin;
    int goalKeeperR;
    int r;
    int G1,G2;
    int Mw1 = Team1->MidW;
    int Mw2 = Team2->MidW;
    G1 = 0;
    G2 = 0;
    while(E<encounterNum) {
        if (!isInCA) {
            coin = unweightedRNG(-(w1+Mw1),w2+Mw2);
        } else {
            coin = (-1)*coin;
        }
        if (coin >= 0) { // Team2 is Attacking
            printf("!! %s is attacking %s\n",Team2->name,Team1->name);
            if (!isInCA) {
                r = processAttack(Team2,Team1,1,1);
            } else {
                r = processAttack(Team2,Team1,1.25,0.75);
                isInCA = 0;
            }
            switch (r) {
                case 3:
                    G2++;
                    Team2->goalsScored += 1;
                    Team1->goalsConceded += 1;
                    E++;
                    break;
                case 2:
                    G2++;
                    Team2->goalsScored += 1;
                    Team1->goalsConceded += 1;
                    E++;
                    break;
                case 1:
                    E++;
                    break;
                case 0:
                    E++;
                    break;
                case 4:
                    isInCA = 1;
                    break;
            }
        } else {
            printf("!! %s is attacking %s\n",Team1->name,Team2->name);
            if (!isInCA) {
                r = processAttack(Team1,Team2,1,1);
            } else {
                r = processAttack(Team1,Team2,1.25,0.75);
                isInCA = 0;
            }
            switch (r) {
                case 3:
                    G1++;
                    Team1->goalsScored += 1;
                    Team2->goalsConceded += 1;
                    E++;
                    break;
                case 2:
                    G1++;
                    Team1->goalsScored += 1;
                    Team2->goalsConceded += 1;
                    E++;
                    break;
                case 1:
                    E++;
                    break;
                case 0:
                    E++;
                    break;
                case 4:
                    isInCA = 1;
                    break;
            }
        }
    }
    printf("\nScore: %s\t%d-%d\t%s\n",Team1->name,G1,G2,Team2->name);
    if (G1 > G2) {
        Team1->pts += 3;
        Team1->wins += 1;
        Team2->defeats += 1;
    } else if (G1 < G2) {
        Team2->pts += 3;
        Team2->wins += 1;
        Team1->defeats += 1;
    } else {
        Team1->pts += 1;
        Team2->pts += 1;
    }
}

int processAttack(team* TeamAttck, team* TeamDef, float Atck_Advantage, float Def_Advantage) {
    int gk = 0;
    
    int wA = (TeamAttck->AttckW) * Atck_Advantage;
    int wD = (TeamDef->DefW) *  Def_Advantage;

    wA = (wA < 0) ? 0 : wA;
    wD = (wD < 0) ? 0 : wD;

  
    int result = unweightedRNG(-wD,wA);

    if (result >= 0.5*wA) {
        // Attack succeeded
        printf("W-A: %d\nW-D: %d\nS: Direct Goal\n", wA, wD);
        return 3; // Direct Goal
    } else if (result >= 0) {
        gk = weightedRNG(TeamDef->goalkeeper.Overall / 2,wA);
        if (gk == 1) {
            printf("W-A: %d\nW-D: %d\nS: Goalkeeper 1v1 Attacker's Score\n", wA, wD);
            return 2; // Goalkeeper 1v1 Success
        } else {
            // Goalkeeper 1v1 Fail
            printf("W-A: %d\nW-D: %d\nS: Goalkeeper 1v1 Clutch\n", wA, wD);
            return 1;
        }
    } else if (result >= 0.75*(-wD)) {
        printf("W-A: %d\nW-D: %d\nS: Direct Defense\n", wA, wD);
        return 0;
    } else {
        printf("W-A: %d\nW-D: %d\nS: Counter Attack\n", wA, wD);
        return 4;
    }
}

int weightedRNG(int min, int max) {
    int coin = unweightedRNG(-min,max);
    if (coin >= 0) {
        return 1;
    } else {
        return -1;
    }
}

void CommentateOn(team* team1, team* team2, int result) {
    /*
    Using the same codes as the processAttack:
    -1 : Introduction
    0 : Direct defense from team2
    1 : Goalkeeper clutch from team2
    2 : Goalkeeper sucess from team1
    3 : Direct Goal from team1
    4 : Counter Attack from team2
    */
    int dice ;
    dice = rand()%6;
    switch (result) {
        case -1:
            switch (dice) {
                case 0:
                    say("Ladies and gentlemen, brace yourselves for a clash of titans as the mighty ");
                    say(team1->name);
                    say("square off against their fierce rivals,");
                    say(team2->name);
                    say(", in a showdown that promises to set the pitch ablaze! The stakes are high, the atmosphere is electric, and both teams are hungry for glory.Get ready for 90 minutes of heart-stopping action as these football juggernauts go head-to-head in a battle that will be etched into the annals of sporting history!");
                    break;
                case 1 :
                    say("Greetings, sports aficionados! Tonight, we are privileged to witness a football extravaganza as ");
                    say(team1->name);
                    say("and");
                    say(team2->name);
                    say("lock horns in a contest that transcends mere competition.This is a clash of ideologies, a duel of skill and strategy that will unfold on the sacred green canvas. With the roar of the crowd as their soundtrack, these teams are set to dazzle and amaze.Buckle up, folks, because this is more than a game; it's a spectacle, a symphony of soccer, and it starts right here, right now!");
                    break;
                case 2 :
                    say("Get ready for a football spectacle that defies expectation! In one corner, we have the formidable force of ");
                    say(team1->name);
                    say(", known for their lightning-quick attacks and impenetrable defense.In the other corner, the challengers, ");
                    say(team2->name);
                    say(", bring a mix of flair and tenacity that keeps fans on the edge of their seats. The stage is set for an epic encounter, where each pass, every dribble, and every shot will be a brushstroke on the canvas of greatness.This is not just a match; it's a collision of footballing philosophies, and you're about to witness the magic unfold!");
                case 3:
                    say("Ladies and gentlemen, welcome to the epic showdown at the heart of football fervor! The stage is set, the floodlights are ablaze, and the air is charged with anticipation. Brace yourselves for a match that promises to redefine sporting brilliance as ");
                    say(team1->name);
                    say("and ");
                    say(team2->name);
                    say(" prepare to go head-to-head. This is not just a game; it's a spectacle, a clash of titans that will echo through the annals of football history. Get ready for 90 minutes of breathtaking skill, heart-stopping moments, and a crescendo of cheers that will reverberate across the cosmos! The atmosphere is electric, and the stakes are high as these two formidable teams enter the arena, ready to leave it all on the pitch. Let the battle commence!");
                    break;
                case 4:
                    say("Greetings, football aficionados! Prepare to be catapulted into a realm where passion meets precision, and athleticism dances with artistry. Today, we bear witness to a celestial convergence of talent on the hallowed pitch as ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(" take center stage. It's more than a match; it's a symphony of strategy, a ballet of finesse, and a drama that unfolds with each touch of the ball. Buckle up as these gladiators of the beautiful game, representing their respective colors and legacies, collide, creating a spectacle that transcends the ordinary and ascends to the extraordinary. The anticipation is palpable, and the energy is electric as we embark on this exhilarating journey with <team1> and <team2>. Get ready for a football experience like no other!");
                    break;
                case 5:
                    say("Welcome, sports enthusiasts, to a kaleidoscope of skill and spectacle! The stadium is pulsating with the rhythmic heartbeat of thousands of fans, and the players from ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(" are ready to embark on a journey that will leave an indelible mark on the canvas of footballing greatness. This is not just a game; it's a tapestry woven with moments of brilliance, a canvas painted with the strokes of determination and flair from these two powerhouse teams. As the whistle blows, immerse yourselves in the theater of dreams, where heroes are born, and legends are etched in the lore of the beautiful game! The stage is set for <team1> and <team2> to showcase their skills and leave an enduring imprint on the hearts of football fans around the world. Let the symphony of sport unfold!");
                break;
            }
        break;
        case 0:
            switch (dice) {
                case 0:
                break;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5:
                break;
            }
        break;
        case 1:
            switch (dice) {
                case 0:
                break;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5:
                break;
            }
        break;
        case 2:
            switch (dice) {
                case 0:
                break;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5:
                break;
            }
        break;
        case 3:
            switch (dice) {
                case 0:
                break;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5:
                break;
            }
        break;
        case 4:
            switch (dice) {
                case 0:
                break;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5:
                break;
            }
        break;
    }
}

// other functions - END
