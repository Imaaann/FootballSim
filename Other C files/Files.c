#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME 64

int main() {

    char leagueName[] = "Test" ;
    int roundNum = 3;
    char roundStr[MAX_NAME];
    sprintf(roundStr,"%d",roundNum);

    char fileName[MAX_NAME];

    strncpy(fileName,"logs/",MAX_NAME);
    strcat(fileName,leagueName);
    strcat(fileName,"_round_");
    strcat(fileName,roundStr);
    strcat(fileName,".txt");

    printf("%s\n",fileName);






















    system("Pause");
    return 0;
}
