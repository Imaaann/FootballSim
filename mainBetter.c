#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>


    #define MAX_NAME 64
    #define MAX_TEAMS 64
    #define SAY_DELAY 10

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

    typedef struct {
        team* GoldMedal;
        team* SilverMedal;
        team* BronzeMedal;
    } podium;


    // Global Variables
    team Dummy;
    team globalTeams[MAX_TEAMS];
    char leagueName[MAX_NAME];
    int numTeams;
    int hasCommentator;
    FILE* file;
    int isSaving;

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
    void yellowNRM();
    void redNRM();

    //Functions
    void drawCup();
    void CommentateOn(team* team1, team* team2, int result);
    void say(char *str);
    void printStrArr(char* str);
    team* linearSearchByName(char* targetName);
    void requestTeam();
    void printTeam(team* team);
    void strnLower(char* str);
    team* hashTableLookup(char* name);
    void bubbleSort(team arr[], int n); // for GD
    void quickSort(team arr[], int low, int high); // for pts
    int partition(team arr[], int low, int high);
    void swap(team* a, team* b);
    void simulate(team* team1, team* team2);
    int processAttack(team teamDEF, team teamATK, float bonusDEF, float bonusATK);
    void printArr(team Arr[], int n);
    team dummyFac();
    void* ballin();
    int unweightedRNG(int min,int max);
    void initTeamArray(team* teamArray[], int n);
    void printTable(team Teams[], int n);
    void newGame();
    podium leader(int status);
    void TrophyCeremony(podium FinalPodium);

int main() {
    isSaving = 0;
    podium FinalPod;
    char C;
    srand(time(NULL));
    printf("========================\nWelcome to the football simulator hope everything goes well\n========================\n");
    system("Pause");

    //Getting Number of teams
    printf("How many teams do you want in the game : ");
    do {
    scanf("%d",&numTeams);
    if (numTeams > MAX_TEAMS) {
        printf("Too many teams, consider lowering it\n");
    }
    } while (numTeams > MAX_TEAMS);

    //Setting up the game
    newGame();
    system("cls");

    //Playing the game
    ballin();

    //Sorting the winners and what not and getting the top 3
    FinalPod = leader(1);
    system("Pause");
    system("cls");

    //Trophy Ceremony
    drawCup();
    TrophyCeremony(FinalPod);


    red();
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
        strnLower(buffer);
        strncpy(Teams[i].name,buffer,MAX_NAME);
    }

    //getting the kind of input
    printf("How do you want to input data:\n(m): manual input \n(r): random input\n(f): fair input\n");
    do {
        trash = getchar();
        trash = tolower(trash);
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
        trash = tolower(trash);
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
    }
    memcpy(globalTeams,Teams,sizeof(team)*numTeams);

    system("cls");
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
    int roundNum = 0;
    while(roundNum <= rounds) {


        //Showing Help Menu if on 1st Itteration
        if (roundNum == 0) {
        printf("\v");
        printf("Next Command Control Panel:\n");
        printf("(n) : Continues to the next round\n");
        printf("(l) : Shows and updates the leaderboards\n");
        printf("(p) : Prints specific info about a team\n");
        printf("(s) : Saves the next round to a file\n");
        printf("(q) : Quit The simulation\n");
        }

        //Fetching next Command
        int paused = 1;
        while (paused) {
            yellow();
            printf("\vEnter the next command\n");
            resetCLR();
            do {
                nextCommand = getchar();
                nextCommand = tolower(nextCommand);
            } while (nextCommand != 'n' && nextCommand != 'l' && nextCommand != 'p' && nextCommand != 's' && nextCommand !=  'q');

            switch (nextCommand) {
                case 'n':
                roundNum++;
                paused = 0;
                system("Pause");
                system("cls");

                break;
                case 'l':
                leader(1);
                break;
                case 'p':
                requestTeam();
                break;
                case 's':
                save(roundNum+1);
                break;
                case 'q':
                return NULL;
                break;
            }
        }

        red();
        printf("Round %d:\n", roundNum);
        resetCLR();
        for (int i = 0; i < numTeams / 2; i++) {
            team* team1 = &(globalTeams[i]);
            team* team2 = &(globalTeams[numTeams - 1 - i]);
            if (strncmp(team1->name,"Dummy",MAX_NAME) != 0 && strncmp(team2->name,"Dummy",MAX_NAME) != 0 ) {
                // event happening
                blue();
                printf("%s vs %s\n", team1->name, team2->name);
                resetCLR();
                if (hasCommentator) {
                    CommentateOn(team1,team2,-1);
                }

                if (isSaving && file != NULL) {
                    fprintf(file,"%s vs %s\n",team1->name,team2->name);
                }


                simulate(team1,team2);
            }
        }
        team tempTeam = globalTeams[1];
        for (int i = 1; i < numTeams - 1; i++) {
            globalTeams[i] = globalTeams[i + 1];
        }
        globalTeams[numTeams - 1] = tempTeam;

        if(isSaving && file != NULL) {
            leader(0);
            isSaving = 0;
            fclose(file);
        }

    }

}

podium leader(int status) {
    team sortedTeams[numTeams+1];
    //pruning the array from globalTeams
    int rnk;
    for (int i=0; i<numTeams; i++) {
        rnk = globalTeams[i].rank;
        sortedTeams[rnk] = globalTeams[i];
    }

    //Sorting the array according to pts (using quick sort)
    quickSort(sortedTeams,0,numTeams-1);
    bubbleSort(sortedTeams,numTeams);

    // printing the leaderboard
    if (status) {
        printTable(sortedTeams,numTeams);
    } else {
        printTableToFile(file,sortedTeams,numTeams);
    }

    //assigning the new ranks
    team* tmp = NULL;

    for (int i = 0; i < numTeams; i++) {
        tmp = linearSearchByName(sortedTeams[i].name);
        if (tmp != NULL) {
            tmp->rank = i;
        }
    }

    //returning pointer to the team at the top
    podium P;
    P.GoldMedal = linearSearchByName(sortedTeams[0].name);
    P.SilverMedal = linearSearchByName(sortedTeams[1].name);
    P.BronzeMedal = linearSearchByName(sortedTeams[2].name);
    return P;
}

void requestTeam() {

    char buffer[MAX_NAME];
    char trash;

    purple();
    printf("Enter the name of the team you want to check\n");
    resetCLR();
    scanf(" %[^\n]s",buffer);
    trash = getchar();
    strnLower(buffer);

    team* tmp = NULL;
    tmp = linearSearchByName(buffer);
    if (tmp != NULL) {
        printTeam(tmp);
    } else {
        red();
        printf("The Team Doesn't exist\n");
        resetCLR();
    }

}

void printTeam(team* teamPtr) {
    printf(" +------------------------------------------------------+\n");
    printf(" | %-23s League: %s |\n", teamPtr->name, leagueName);
    printf(" |  Points: %-4d | Rank: %-3d | Wins: %-3d | Defeats: %-3d | Goals: %d-%d |\n", teamPtr->pts, teamPtr->rank, teamPtr->wins, teamPtr->defeats, teamPtr->goalsScored, teamPtr->goalsConceded);
    printf(" | AttckW: %-3d |  MidW: %-3d | DefW: %-3d | GD: %3d   |\n", teamPtr->AttckW, teamPtr->MidW, teamPtr->DefW, teamPtr->goalsScored - teamPtr->goalsConceded);
    printf(" +------------------------------------------------------+\n");
}

void save(int round) {
    char roundStr[MAX_NAME];
    sprintf(roundStr,"%d",round);

    char fileName[MAX_NAME];

    strncpy(fileName,"logs/",MAX_NAME);
    strcat(fileName,leagueName);
    strcat(fileName,"_round_");
    strcat(fileName,roundStr);
    strcat(fileName,".txt");

    file = fopen(fileName,"w");
    isSaving = 1;
}

void printTable(team Teams[], int n) {
    printf("+-------------------------------------------------------------+\n");
    printf("|                          LEADERBOARD                        |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("| Rank | Team Name           | Points | Wins | Losses | GD   |\n");
    printf("|------+---------------------+--------+------+--------+------|\n");


    for (int i = 0; i < n; i++) {
        if (strncmp(Teams[i].name,"Dummy",MAX_NAME) != 0) {
            int goalDifference = Teams[i].goalsScored - Teams[i].goalsConceded;
            int rankWidth = (i + 1 < 10) ? 2 : 1;

            if (Teams[i].rank > i) {
                green();
            } else if (Teams[i].rank < i) {
                red();
            }


            if (i == 0) { // throughout heaven and earth I alone am the honored one
                yellow();
            }

            printf("|   %-*d | %-19s | %-6d | %-4d | %-6d | %+4d |\n", rankWidth, i + 1, Teams[i].name, Teams[i].pts, Teams[i].wins, Teams[i].defeats, goalDifference);
            resetCLR();
        }
    }


    printf("+-------------------------------------------------------------+\n");
}

void printTableToFile(FILE* outputFile, team Teams[], int n) {
    // Check if the output file is provided
    if (outputFile == NULL) {
        fprintf(stderr, "Error: Output file is not provided.\n");
        return;
    }

    // Print to the file
    fprintf(outputFile, "+-------------------------------------------------------------+\n");
    fprintf(outputFile, "|                          LEADERBOARD                        |\n");
    fprintf(outputFile, "+-------------------------------------------------------------+\n");
    fprintf(outputFile, "| Rank | Team Name           | Points | Wins | Losses | GD   |\n");
    fprintf(outputFile, "|------+---------------------+--------+------+--------+------|\n");

    for (int i = 0; i < n; i++) {
        if (strncmp(Teams[i].name, "Dummy", MAX_NAME) != 0) {
            int goalDifference = Teams[i].goalsScored - Teams[i].goalsConceded;
            int rankWidth = (i + 1 < 10) ? 2 : 1;

            // Print to the file
            fprintf(outputFile, "|   %-*d | %-19s | %-6d | %-4d | %-6d | %+4d |\n", rankWidth, i + 1, Teams[i].name, Teams[i].pts, Teams[i].wins, Teams[i].defeats, goalDifference);
        }
    }

    // Print to the file
    fprintf(outputFile, "+-------------------------------------------------------------+\n");
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
            if (hasCommentator) {
                CommentateOn(team2,team1,result);
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
            if (hasCommentator) {
                CommentateOn(team1,team2,result);
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

    printf("Final score: %s  %d-%d  %s\n", team1->name, Goals1, Goals2, team2->name);
    if (isSaving && file != NULL) {
        fprintf(file,"Final score: %s  %d-%d  %s\n", team1->name, Goals1, Goals2, team2->name);
    }
    if(hasCommentator) {
        system("Pause");
        system("cls");
    }
}

void initTeamArray(team* teamArray[], int n) {
    for (int i=0; i<n; i++) {
        teamArray[i] = NULL;
    }
}

int unweightedRNG(int min,int max) {
    return ((rand()%(max-min+1))+min);
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
    Dummy.rank = numTeams;

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

void swap(team* a, team* b) {
    team temp = *a;
    *a = *b;
    *b = temp;
}

int partition(team arr[], int low, int high) {
    int pivot = arr[high].pts;
    int indx = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].pts >= pivot) {
            indx++;
            swap(&arr[indx], &arr[j]);
        }
    }

    swap(&arr[indx + 1], &arr[high]);
    return indx + 1;
}

void quickSort(team arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void bubbleSort(team arr[], int n) { // bubble sort for GD
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int isNotDummy = (strncmp(arr[j].name,"Dummy",MAX_NAME) != 0 && strncmp(arr[j+1].name,"Dummy",MAX_NAME) != 0) ? 1:0;
            int GD1 = arr[j].goalsScored - arr[j].goalsConceded;
            int GD2 = arr[j+1].goalsScored - arr[j+1].goalsConceded;
            if (arr[j].pts == arr[j+1].pts && (GD1 <= GD2) && isNotDummy) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void strnLower(char* str) {
    int length = strlen(str);
    str[0]=toupper(str[0]);
    for (int i=1; i<length; i++) {
        str[i] = tolower(str[i]);
    }
}

team* linearSearchByName(char* targetName) {
    for (int i = 0; i < numTeams; i++) {
        if (strcmp(globalTeams[i].name, targetName) == 0) {
            return &globalTeams[i]; // Return a pointer to the found team
        }
    }
    return NULL; // Return NULL if the team with the specified name is not found
}

void printStrArr(char* str) {
    int len = strlen(str);
    printf("[");
    for (int i=0; i<(len-1); i++) {
        printf("%c ,", str[i] );
    }
    printf("%c]\n", str[len-1]);
}

void CommentateOn(team* team1, team* team2, int result) {
    /*
    Using the same codes as the processAttack:
    -1 : Introduction
    0 : Counter Attack from team2
    1 : Direct defense from team2
    2 : Direct Goal from team1
    3 : Trophy Party
    */
    int dice ;
    dice = rand()%6;
    say("---");
    switch (result) {
        case -1:
            switch (dice) {
                case 0:
                    say("Welcome, football enthusiasts, to a clash that promises to be nothing short of extraordinary! ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(" are set to ignite the pitch with their unparalleled skill and determination. Get ready for a spectacle that will keep you on the edge of your seats!");
                    break;
                case 1:
                    say("Ladies and gentlemen, brace yourselves for an epic showdown as the titans of football, ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(", prepare to go head-to-head. The stage is set, the players are primed, and the atmosphere is electric. It's time for 90 minutes of heart-pounding action!");
                    break;
                case 2:
                    say("Greetings, sports aficionados! Get ready for a football extravaganza as ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(" grace the field with their presence. This is more than a match; it's a collision of footballing ideologies, a duel that promises skill, passion, and unforgettable moments!");
                    break;
                case 3:
                    say("A warm welcome to all football lovers tuning in for this epic encounter between ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(". The anticipation is palpable, and the stage is set for a riveting match that will leave an indelible mark on the beautiful game!");
                    break;
                case 4:
                    say("Get ready for a football spectacle like no other as we witness the clash between ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(". The players are ready, the fans are eager, and the excitement is contagious. It's time to kick off a match that promises skill, strategy, and pure footballing magic!");
                    break;
                case 5:
                    say("Football fans, rejoice! We're about to witness a showdown of epic proportions as ");
                    say(team1->name);
                    say(" and ");
                    say(team2->name);
                    say(" take center stage. The energy is high, the stakes are higher, and the thrill of the game is about to unfold. Stay tuned for a footballing extravaganza!");
                    break;
            }
        break;
        case 0:
            switch (dice) {
                case 0:
                    say("In a stunning turn of events, ");
                    say(team2->name);
                    say(" launches a swift counterattack against ");
                    say(team1->name);
                    say(", catching everyone off guard. The momentum has shifted, and the underdogs are making their move!");
                break;
                case 1:
                    say("Hold your breath, folks! A sudden burst of energy from ");
                    say(team2->name);
                    say(" as they counterattack against ");
                    say(team1->name);
                    say(". The tables have turned, and the dynamics of the game are in for a thrilling twist!");
                break;
                case 2:
                    say("Watch out! ");
                    say(team2->name);
                    say(" seizes the opportunity to counterattack against ");
                    say(team1->name);
                    say(", unleashing a flurry of strategic moves that could change the course of this match!");
                break;
                case 3:
                    say("A moment of brilliance from ");
                    say(team2->name);
                    say(" as they swiftly counterattack against ");
                    say(team1->name);
                    say(". The game takes an unexpected turn, and the excitement levels are off the charts!");
                break;
                case 4:
                    say("Hold on tight! ");
                    say(team2->name);
                    say(" executes a perfectly timed counterattack against ");
                    say(team1->name);
                    say(", leaving their opponents scrambling to defend. The stadium erupts in cheers as the plot thickens!");
                break;
                case 5:
                    say("Get ready for fireworks! ");
                    say(team2->name);
                    say(" pulls off a lightning-fast counterattack against ");
                    say(team1->name);
                    say(", showcasing their prowess on the pitch. The crowd roars as the intensity reaches a whole new level!");
                break;
            }
        break;
        case 1:
            switch (dice) {
                case 0:
                    say("A relentless assault from ");
                    say(team1->name);
                    say(" puts pressure on ");
                    say(team2->name);
                    say(". However, the defense holds firm, thwarting every attempt to breach their goal. A stellar display of resilience!");
                    break;
                case 1:
                    say(team1->name);
                    say(" launches a fierce attack against ");
                    say(team2->name);
                    say(", testing their defensive prowess. Yet, the solid defense stands tall, denying any passage to the net. What a defensive masterclass!");
                    break;
                case 2:
                    say("In a high-stakes moment, ");
                    say(team1->name);
                    say(" aggressively attacks ");
                    say(team2->name);
                    say("'s goal. But the defenders stand like a wall, repelling every shot and securing their territory!");
                    break;
                case 3:
                    say("A relentless offensive from ");
                    say(team1->name);
                    say(" puts ");
                    say(team2->name);
                    say(" on the back foot. Remarkably, the defenders intercept every move, denying any chance for the ball to reach the net.");
                    break;
                case 4:
                    say("The stadium holds its breath as ");
                    say(team1->name);
                    say(" intensifies the attack against ");
                    say(team2->name);
                    say(". The defenders, however, showcase exceptional skills, ensuring the ball doesn't breach their fortress. A defensive spectacle!");
                    break;
                case 5:
                    say(team1->name);
                    say("'s onslaught against ");
                    say(team2->name);
                    say(" is met with an ironclad defense. The defenders thwart every attempt, ensuring the ball remains far from their net. Defensive brilliance on display!");
                    break;
            }
        break;
        case 2:
            switch (dice) {
                case 0:
                    say("A masterful offensive from ");
                    say(team1->name);
                    say(" as they break through the defense of ");
                    say(team2->name);
                    say(". The ball finds the back of the net, and the crowd erupts in jubilation!");
                    break;
                case 1:
                    say(team1->name);
                    say(" orchestrates a brilliant attack, leaving ");
                    say(team2->name);
                    say(" scrambling to defend. The ball sails past the goalkeeper, and the net ripples. Goal for ");
                    say(team1->name);
                    say("!");
                    break;
                case 2:
                    say("In a dazzling display of skill, ");
                    say(team1->name);
                    say(" outmaneuvers the defense of ");
                    say(team2->name);
                    say(". The shot is perfectly placed, and the scoreboard reflects the goal!");
                    break;
                case 3:
                    say(team1->name);
                    say("'s relentless assault pays off as they breach the defense of ");
                    say(team2->name);
                    say(". The crowd goes wild as the ball hits the mark. Goal for ");
                    say(team1->name);
                    say("!");
                    break;
                case 4:
                    say("An electrifying moment as ");
                    say(team1->name);
                    say(" executes a clinical attack against ");
                    say(team2->name);
                    say(". The defense is left helpless, and the ball finds its way into the net. Spectacular goal!");
                    break;
                case 5:
                    say("Cheers reverberate through the stadium as ");
                    say(team1->name);
                    say(" outplays the defense of ");
                    say(team2->name);
                    say(". The ball is sent into the goal with precision. Goal for ");
                    say(team1->name);
                    say("!");
                    break;
            }
        break;
    }
    printf("\n");
}

void TrophyCeremony(podium FinalPodium) {
    int dice = rand()%6;
    switch (dice) {
        case 0:
            say("Ladies and gentlemen, a thunderous applause for our champions of the ");
            say(leagueName);
            say(" league!");
            say("As the golden confetti rains down, the triumphant teams stand tall on the podium.");
            say("Taking the gold medal is ");
            say(FinalPodium.GoldMedal->name);
            say(", showcasing exceptional skill and determination.");
            say("The silver medal goes to ");
            say(FinalPodium.SilverMedal->name);
            say(", a team that has displayed remarkable prowess throughout the ");
            say(leagueName);
            say(" season.");
            say("And let's not forget the bronze, claimed by ");
            say(FinalPodium.BronzeMedal->name);
            say(", a team that fought valiantly and secured their place among the best.");
            break;
        case 1:
            say("In the spotlight of triumph, the silver medal is awarded to ");
            say(FinalPodium.SilverMedal->name);
            say(" in the ");
            say(leagueName);
            say(" league!");
            say("Amidst cheers and applause, they embrace the moment, a shining testament to their skill and dedication.");
            say("The journey to this podium has been long, but the silver gleams brightly around the necks of ");
            say(FinalPodium.GoldMedal->name);
            say(" and ");
            say(FinalPodium.SilverMedal->name);
            say("!");
            say("Meanwhile, the bronze medal finds a worthy recipient in ");
            say(FinalPodium.BronzeMedal->name);
            say(", a team that captured hearts with their spirited performance.");
            break;
        case 2:
            say("Bronze, the medal of valor, finds its deserving home with ");
            say(FinalPodium.BronzeMedal->name);
            say(" in the ");
            say(leagueName);
            say(" league!");
            say("With a jubilant spirit, they proudly accept the bronze, a symbol of resilience and sportsmanship.");
            say("Their journey has been a testament to the indomitable spirit that defines champions.");
            say("Joining them on the podium are ");
            say(FinalPodium.GoldMedal->name);
            say(" and ");
            say(FinalPodium.SilverMedal->name);
            say(", the gold and silver medalists, respectively, in this incredible display of football excellence.");
            break;
        case 3:
            say("As the stadium echoes with the roar of victory, the coveted gold medal is bestowed upon ");
            say(FinalPodium.GoldMedal->name);
            say(" in the ");
            say(leagueName);
            say(" league!");
            say("Their stellar performance has etched them in the annals of footballing greatness.");
            say("Sharing the podium is ");
            say(FinalPodium.SilverMedal->name);
            say(", the silver medalist, who showcased exceptional skills and sportsmanship.");
            say("Completing the trio of champions is ");
            say(FinalPodium.BronzeMedal->name);
            say(", recipient of the bronze, a testament to their tenacity and dedication.");
            break;
        case 4:
            say("A symphony of cheers erupts as ");
            say(FinalPodium.GoldMedal->name);
            say(" claims the gold medal in the ");
            say(leagueName);
            say(" league!");
            say("Their journey has been nothing short of extraordinary, marked by moments of brilliance and sheer determination.");
            say("Standing alongside them on the podium is ");
            say(FinalPodium.SilverMedal->name);
            say(", the silver medalist, who contributed to the tournament's spectacle with their skillful play.");
            say("And let's not forget the bronze medal, proudly worn by ");
            say(FinalPodium.BronzeMedal->name);
            say(", a team that captivated the audience with their resilience.");
            break;
        case 5:
            say("A grand salute to our champions of the ");
            say(leagueName);
            say(" league!");
            say("The gold medal finds a worthy home with ");
            say(FinalPodium.GoldMedal->name);
            say(", a team that showcased football mastery.");
            say("On the podium beside them is ");
            say(FinalPodium.SilverMedal->name);
            say(", the silver medalist, who added their unique flair to the ");
            say(leagueName);
            say(" season.");
            say("Completing the trio is ");
            say(FinalPodium.BronzeMedal->name);
            say(", the bronze medalist, a team that fought with unmatched spirit and determination.");
            break;
    }
    printf("\n");
}

void say(char *str) {
    int i = 0 ;
    for(int i =0 ; str[i]!='\0';i++){
        printf("%c",str[i]);
        Sleep(SAY_DELAY);
    }
}

void drawCup() {
    yellow();
    printf("      ===============");
    yellowNRM();
    printf("***************\n");
    yellow();
    printf("        -------------");
    yellowNRM();
    printf("============\n");
    yellow();
    printf("   ======------------");
    yellowNRM();
    printf("============>>>>>>\n");
    yellow();
    printf("  =======------------");
    yellowNRM();
    printf("============>>>>>>>\n");
    yellow();
    printf("   ==    -----------");
    printf("\033[1;36m>\033[0;36m[");
    yellowNRM();
    printf("===========    >>\n");
    yellow();
    printf("   ===   ----------");
    printf("\033[1;36m>>\033[0;36m[");
    yellowNRM();
    printf("===========   >>>\n");
    yellow();
    printf("    ==   -----------");
    printf("\033[1;36m>\033[0;36m[");
    yellowNRM();
    printf("==========   >>\n");
    yellow();
    printf("    ====  ----------");
    printf("\033[1;36m>\033[0;36m[");
    yellowNRM();
    printf("==========  >>>\n");
    yellow();
    printf("      === ----------");
    printf("\033[1;36m>\033[0;36m[");
    yellowNRM();
    printf("========== >>>\n");
    yellow();
    printf("       ====----------");
    yellowNRM();
    printf("==========>>>>\n");
    yellow();
    printf("         ==~---------");
    yellowNRM();
    printf("=========*>>\n");
    yellow();
    printf("            ~--------");
    yellowNRM();
    printf("========*\n");
    yellow();
    printf("              -------");
    yellowNRM();
    printf("=======\n");
    yellow();
    printf("                -----");
    yellowNRM();
    printf("====~\n");
    yellow();
    printf("                 ++++");
    yellowNRM();
    printf(">>>^\n");
    yellow();
    printf("                 ++++");
    yellowNRM();
    printf(">>>>\n");
    yellow();
    printf("                 ++++");
    yellowNRM();
    printf(">>>>\n");
    yellow();
    printf("              -------");
    yellowNRM();
    printf("=======\n");
    yellow();
    printf("             --------");
    yellowNRM();
    printf("========\n");
    resetCLR();
    red();
    printf("         ))))))))))))");
    redNRM();
    printf("}}}}}}}}}}}[         \n");
    red();
    printf("         <)))))))))))");
    redNRM();
    printf("}}}}}}}}}}}[         \n");
    printf("\v\v\v\v");
    resetCLR();
}

// colors
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
void yellowNRM() {
    printf("\033[0;33m");
}
void redNRM() {
    printf("\033[0;31m");
}
