#include <stdbool.h>
#include <stdio.h>
void calculateScore(int[], const int, int[], int[], const int, int*, int*);  // calculate the score of each user
int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int boxes[BoxesNum], userOne[ChoicesNum], userTwo[ChoicesNum];
  printf("Enter boxes content: ");
  for (int i = 0; i < BoxesNum; i++) {
    scanf("%d", &boxes[i]);
  }
  printf("Enter player 1 choices: ");
  for (int i = 0; i < ChoicesNum; i++) {
    scanf("%d", &userOne[i]);
  }
  printf("Enter player 2 choices: ");
  for (int i = 0; i < ChoicesNum; i++) {
    scanf("%d", &userTwo[i]);
  }
  int userOneScore = 0, userTwoScore = 0;
  calculateScore(boxes, BoxesNum, userOne, userTwo, ChoicesNum, &userOneScore, &userTwoScore);
  printf("Player 1: %d.\nPlayer 2: %d.\n", userOneScore, userTwoScore);
  return 0;
}

void calculateScore(int boxes[], const int BoxesNum, int userOne[], int userTwo[], const int ChoicesNum, int* score1, int* score2) {
  // Get the score of each user
  for (int i = 0; i < BoxesNum; i++){
    bool candy = false;
    bool bomb = false;
    if(boxes[i] == 10 || boxes[i] == -10){
        if(boxes[i] == 10){
            candy = true;
            printf("Found 10 in boxes[%d]\n", i);
        }else{
            bomb = true;
            printf("Found -10 in boxes[%d]\n", i);
        }

        for(int j = 0; j<ChoicesNum; j++){
            bool player1 = false;
            bool player2 = false;

            if(userOne[j] == i || userTwo[j] == i){
                if(userOne[j] == i){
                    player1 = true;
                    printf("Found index %d in player 1\n", i);

                }

                if(userTwo[j] == i){
                    player2 = true;
                    printf("Found index %d in player 2\n", i);
                }

                if(player1 == true && player2 == true){
                    if(candy == true){
                        *score1 = *score1 + 5;
                        *score2 = *score2 + 5;
                        printf("+5 to players 1 and 2 scores");
                    }else{
                        *score1 = *score1 - 10;
                        *score2 = *score2 - 10;
                        printf("-10 from player 1 score.");
                        printf("-10 from player 2 score.");
                    }
                }else if(player1 == true){
                    if(candy == true){
                        *score1 = *score1 + 10;
                        printf("+10 to player 1 score.");
                    }else{
                        *score1 = *score1 - 10;
                        printf("-10 from player 1 score.\n");
                    }
                }else{
                    if(candy == true){
                        *score2 = *score2 + 10;
                        printf("+10 to player 2 score.\n");
                    }else{
                        *score2 = *score2 - 10;
                        printf("-10 from player 2 score.\n");
                    }
                }
            }

        }


    }
  }
}