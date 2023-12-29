#include <stdio.h>


void teamfight(char* teams[], int numTeams) {
  if (numTeams % 2 != 0) {
      teams[numTeams] = "Dummy";
      numTeams++;
  }
  int rounds = numTeams - 1;
  for (int roundNum = 1; roundNum <= rounds; roundNum++) {
    printf("Round %d:\n", roundNum);
    for (int i = 0; i < numTeams / 2; i++) {
        char* team1 = teams[i];
        char* team2 = teams[numTeams - 1 - i];
        if (team1 != "Dummy" && team2 != "Dummy") {
            printf("%s vs %s\n", team1, team2);
        }
    }
    char* temp = teams[1];
    for (int i = 1; i < numTeams - 1; i++) {
        teams[i] = teams[i + 1];
    }
    teams[numTeams - 1] = temp;
  }
}

int main() {
    int wait;
    char* teams[] = {"TeamA", "TeamB", "TeamC", "TeamD", "TeamE" ,"TeamF" ,"TeamG" ,"TeamH" ,"TeamI" ,"TeamJ" ,"TeamK" ,"TeamL" ,"TeamM" ,"TeamN" ,"TeamO" ,"TeamP" ,"TeamQ" ,"TeamR" ,"TeamS" ,"TeamT"};
	int numTeams = sizeof(teams) / sizeof(teams[0]);
	teamfight(teams, numTeams);

    scanf("%d",&wait);
	return 0;
	}
