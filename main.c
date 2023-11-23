#include <stdio.h>
#include <stdlib.h>

int main() {

    char command;
    printf("============\nWelcome to the football simulator ('h' to open help menu)\n============\n");
    do {
    printf("Enter a command\n");
    scanf("%s",&command);
    switch (command) {
    case 'n':
        printf("\n======\nStarting a new game\n======\n");
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