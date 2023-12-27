#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>


    #define MAX_NAME 64
    #define MAX_TABLE_SIZE 64
    #define SAY_DELAY 1

    typedef struct team{ 
        char name[MAX_NAME];
        int pts;
        int AttckW;
        int DefW;
        int MidW;
        int wins;
        int defeats;
        int goalsScored;
        int goalsConceded;
        int rank;
        struct team* next;
    } team; 


    // Global Variables
    team Dummy;
    team globalTeams[MAX_TABLE_SIZE];
    team* hash_Table[MAX_TABLE_SIZE];
    char leagueName[MAX_NAME];
    int numTeams;
    int hasCommentator;

    //Color Control
    void resetCLR();
    void red();
    void yellow();
    void whiteBold();
    void black();
    void cyan();
    void blue();
    void purple();
    void green();
    

    //Functions
    void simulate(team* team1, team* team2);
    int processAttack(team teamDEF, team teamATK, float bonusDEF, float bonusATK);
    void printArr(team Arr[], int n);
    team dummyFac();
    void* ballin();
    void printHashTable();
    unsigned int hash(char* name);
    int hashTableInsert(team *p);
    int unweightedRNG(int min,int max);
    void initHashTable();
    void initTeamArray(team* teamArray[], int n);
    void printTable(team Teams[], int n);
    void newGame();
    void leader();

int main() {
    srand(time(NULL));
    initHashTable();
    printf("========================\nWelcome to the football simulator hope everything goes well\n========================\n");
    system("Pause");

    printf("How many teams do you want in the game : ");
    do {
    scanf("%d",&numTeams);
    if (numTeams > 63) {
        printf("Too many teams, consider lowering it\n");
    }
    } while (numTeams > 63);
    newGame();
    system("Pause");
    system("cls");
    ballin();

    system("Pause");
    return 0;
}

void newGame() {
    char trash;
    team Teams[numTeams+1];

    //getting league name
    char buffer[MAX_NAME];
    printf("Enter the name of the league\n");
    scanf(" %[^\n]s",buffer);
    trash = getchar();
    strncpy(leagueName,buffer,MAX_NAME);

    //getting team names
    for (int i=0; i<numTeams; i++) {
        printf("Enter the name of the team number %d\n",i+1);
        scanf(" %[^\n]s",buffer);
        trash = getchar();
        strncpy(Teams[i].name,buffer,MAX_NAME);
    }

    //getting the kind of input
    printf("How do you want to input data:\n(m): manual input \n(r): random input\n(f): fair input\n");
    do {
        trash = getchar();
    } while (trash != 'm' && trash != 'r' && trash != 'f');

    //Processing the input
    switch (trash) {
        case 'f':
            for (int i=0; i<numTeams; i++) {
                Teams[i].AttckW = 50;
                Teams[i].MidW = 50;
                Teams[i].DefW = 50;
            }
        break; 
        case 'r':
            for (int i=0; i<numTeams; i++) {
                Teams[i].AttckW = unweightedRNG(40,99);
                Teams[i].MidW = unweightedRNG(40,99);
                Teams[i].DefW = unweightedRNG(40,99);
            }
        break;
        case 'm':
            for (int i=0; i<numTeams; i++) {
                int T;
                printf("Input the attacking weight of Team %s\n",Teams[i].name);
                do {
                    scanf("%d",&T);
                } while (T >= 100 || T < 1);
                Teams[i].AttckW = T;
                printf("Input the middle weight of Team %s\n",Teams[i].name);
                do {
                    scanf("%d",&T);
                } while (T >= 100 || T < 1);
                Teams[i].MidW = T;
                printf("Input the defending weight of Team %s\n",Teams[i].name);
                do {
                    scanf("%d",&T);
                } while (T >= 100 || T < 1);
                Teams[i].DefW = T;
            }
        break;
    }

    //Commentator toggle
    printf("Do you want to use a commentator for the game (y/n)\n");
    do {
        trash = getchar();
    } while (trash != 'y' && trash != 'n');
    if (trash == 'y') {
        hasCommentator = 1;
    } else {
        hasCommentator = 0;
    }

    //finish up the setup
    for (int i=0 ; i<numTeams; i++) {
        Teams[i].pts = 0;
        Teams[i].goalsConceded = 0;
        Teams[i].goalsScored = 0;
        Teams[i].wins = 0;
        Teams[i].defeats = 0;
        Teams[i].rank = i;
        hashTableInsert(&Teams[i]);
    }
    memcpy(globalTeams,Teams,sizeof(team)*numTeams);

    system("cls");
    printHashTable();

}

void* ballin() {
    // yeah we ballin'
    char nextCommand;
    
    // Forcing Number of teams to be even
    if (numTeams % 2 != 0) {
        globalTeams[numTeams] = dummyFac();
        numTeams++;
    }


    // Start of the main event loop
    int rounds = numTeams - 1;
    int roundNum = 1;
    while(roundNum <= rounds) {
        red();
        printf("Round %d:\n", roundNum);
        resetCLR();
        for (int i = 0; i < numTeams / 2; i++) {
            team* team1 = &(globalTeams[i]);
            team* team2 = &(globalTeams[numTeams - 1 - i]);
            if (strncmp(team1->name,"Dummy",MAX_NAME) != 0 && strncmp(team2->name,"Dummy",MAX_NAME) != 0 ) {
                // event happening
                printf("%s vs %s\n", team1->name, team2->name);
                simulate(team1,team2);
            }
        }
        team tempTeam = globalTeams[1];
        for (int i = 1; i < numTeams - 1; i++) {
            globalTeams[i] = globalTeams[i + 1];
        }
        globalTeams[numTeams - 1] = tempTeam;

        //Showing Help Menu if on 1st Itteration
        if (roundNum == 1) {
        printf("Next Command Control Panel:\n");
        printf("(n) : Continues to the next round\n");
        printf("(l) : Shows and updates the leaderboards\n");
        printf("(p) : Prints specific info about a team\n");
        printf("(s) : Save the current round to a file\n");
        printf("(q) : Quit The simulation\n");
        }

        //Fetching next Command
        int paused = 1;
        while (paused) {
            yellow();
            printf("Enter the next command\n");
            resetCLR();
            do {
                nextCommand = getchar();
            } while (nextCommand != 'n' && nextCommand != 'l' && nextCommand != 'p' && nextCommand != 's' && nextCommand !=  'q');

            switch (nextCommand) {
                case 'n':
                roundNum++;
                paused = 0;
                system("Pause");
                break;
                case 'l':
                leader();
                break;
                case 'p':
                // printTeam()
                break;
                case 's':
                // Save()
                break;
                case 'q':
                return NULL;
                break;
            }
        }

        system("cls");
    }

}

void leader() {
    printTable(globalTeams,numTeams);
}

void printTable(team Teams[], int n) {
    printf("+---------------------------------------------+\n");
    printf("|                 LEADERBOARD                  |\n");
    printf("+---------------------------------------------+\n");
    printf("| Rank | Team Name        | Points | Wins | Losses |\n");
    printf("|------+------------------+--------+------+--------|\n");

    for (int i = 0; i < n; i++) {
        printf("|   %d  | %-16s | %-6d | %-4d | %-6d |\n", i + 1, Teams[i].name, Teams[i].pts, Teams[i].wins, Teams[i].defeats);
    }

    printf("+---------------------------------------------+\n");
}

void simulate(team *team1, team *team2) {
    int w1, w2;
    w1 = (team1->AttckW + team1->DefW + team1->MidW) / 3;
    w2 = (team2->AttckW + team2->DefW + team2->MidW) / 3;

    // getting the number of encounters
    int encounterNum;
    encounterNum = abs(((w1 + team1->MidW) / 2) - ((w2 + team2->MidW) / 2));

    // Goals
    int Goals1 = 0;
    int Goals2 = 0;

    // Starting the encounter loop
    int coin = 0;            // Side decides who is attacking
    int result;              // stores the result of the encounter
    int CounterAttack = 0;   // counter Attack flag
    int Enc = 0;
    while (Enc < encounterNum) {
        if (!CounterAttack) {
            coin = unweightedRNG(-(w1 + team1->MidW), w2 + team2->MidW);
        } else {
            coin = (-1) * coin;
        }

        // Choosing the side
        if (coin > 0) {
            if (!CounterAttack) {
                result = processAttack(*team1, *team2, 1, 1);
            } else {
                result = processAttack(*team1, *team2, 0.75, 1.25);
                CounterAttack = 0;
            }
            switch (result) {
                case 2:
                    Goals2++;
                    team2->goalsScored += 1;
                    team1->goalsConceded += 1;
                    Enc++;
                    break;
                case 1:
                    Enc++;
                    break;
                case 0:
                    CounterAttack = 1;
                    break;
            }

        } else {
            if (!CounterAttack) {
                result = processAttack(*team2, *team1, 1, 1);
            } else {
                result = processAttack(*team2, *team1, 0.75, 1.25);
                CounterAttack = 0;
            }
            switch (result) {
                case 2:
                    Goals1++;
                    team1->goalsScored += 1;
                    team2->goalsConceded += 1;
                    Enc++;
                    break;
                case 1:
                    Enc++;
                    break;
                case 0:
                    CounterAttack = 1;
                    break;
            }
        }
    }

    if (Goals1 > Goals2) {
        team1->wins += 1;
        team1->pts += 3;
        team2->defeats += 1;
    } else if (Goals2 > Goals1) {
        team2->wins += 1;
        team2->pts += 3;
        team1->defeats += 1;
    } else {
        team1->pts += 1;
        team2->pts += 1;
    }

    printf("Final score: %s\t%d-%d\t%s\n", team1->name, Goals1, Goals2, team2->name);
}


void initTeamArray(team* teamArray[], int n) {
    for (int i=0; i<n; i++) {
        teamArray[i] = NULL;
    }
}

void initHashTable() {
    for (int i = 0; i<MAX_TABLE_SIZE; i++) {
        hash_Table[i] = NULL;
    }
}

int unweightedRNG(int min,int max) {
    return ((rand()%(max-min+1))+min);
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

unsigned int hash(char* name) {
    int strLength = strnlen(name, MAX_NAME);
    unsigned int hashValue = 0;
    for (int i=0; i<strLength; i++) {
        hashValue += name[i];
        hashValue = ( hashValue * name[i]) % MAX_TABLE_SIZE;

    }
    return hashValue;
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
                printf("%s (Def: %d, Mid: %d, Attck: %d)-", tmp -> name,tmp->DefW,tmp->MidW,tmp->AttckW);
                tmp = tmp -> next;
            }
            printf("\n");
        }
    }
    printf("End of hash Table Print\n");
}

team dummyFac() {
    strncpy(Dummy.name,"Dummy",MAX_NAME);
    Dummy.AttckW = 1;
    Dummy.DefW = 1;
    Dummy.MidW = 1;
    Dummy.goalsConceded = 0;
    Dummy.goalsScored = 0;
    Dummy.wins = 0;
    Dummy.defeats = 0;

    return (Dummy);
}

void printArr(team Arr[], int n) {
    printf("[");
    for (int i=0; i<(n-1); i++) {
        printf("%s ,", Arr[i].name );
    }
    printf("%s]\n", Arr[n-1].name);
}

int processAttack(team teamDEF, team teamATK, float bonusDEF, float bonusATK) {
    int wATK = teamATK.AttckW*bonusATK;
    int wDEF = teamDEF.DefW*bonusDEF;

    int r = unweightedRNG(-wDEF,wATK);
    if (r>=0.2*wATK) {
        return 2;
    } else if (r>= 0.75*(-wDEF)) {
        return 1;
    } else {
        return 0;
    }
}

void red() {
  printf("\033[1;31m");
}

void black() {
  printf("\033[1;30m");
}

void green() {
  printf("\033[1;32m");
}

void blue() {
  printf("\033[1;34m");
}

void purple() {
  printf("\033[1;35m");
}

void cyan() {
  printf("\033[1;36m");
}

void whiteBold() {
  printf("\033[1;37m");
}

void yellow() {
  printf("\033[1;33m");
}

void resetCLR() {
  printf("\033[0m");
}
