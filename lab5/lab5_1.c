#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool validateChoices(int choices[], const int ChoicesNum, const int BoxesNum);
void takeUserChoices(int userOne[], int userTwo[], const int ChoicesNum, const int BoxesNum);
void populateBoxes(int boxes[], const int BoxesNum);

int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int boxes[BoxesNum], userOne[ChoicesNum], userTwo[ChoicesNum];
  populateBoxes(boxes, BoxesNum);
  takeUserChoices(userOne, userTwo, ChoicesNum, BoxesNum);
  return 0;
}

void populateBoxes(int boxes[], const int BoxesNum){
    int value = 0;
    for (int i = 0; i < BoxesNum; i++){
        value = rand()%(3-0 + 1) + 0;
        if (value == 0){
            boxes[i] = 0;
        }else if(value == 1){
            boxes[i] = 10;
        }else{
            boxes[i] = -10;
        }
        printf("%d: %d, ", i, boxes[i]);
    }
}

bool validateChoices(int choices[], const int ChoicesNum, const int BoxesNum){
    bool valid = true; 
    for (int i = 0; i < ChoicesNum - 1; i++){
        for (int j = i + 1; j < ChoicesNum; j++){
            if (choices[i] == choices[j]){
                valid = false;
                break;
            }
        }
    }

    for (int k = 0; k < ChoicesNum; k++){
        if (choices[k] > 19){
            valid = false;
            break;
        }
    }

    return valid;
}

void takeUserChoices(int userOne[], int userTwo[], const int ChoicesNum, const int BoxesNum) {
  // Can check if the inputs are distinct and if they are between 1 and BoxesNum
  // - 1
  printf("\n");
  do {
    printf("Player 1, please enter distinct box choices between 0 and 19:");
    for (int choiceInd = 0; choiceInd < ChoicesNum; choiceInd++) {
      scanf("%d", &userOne[choiceInd]);
    }
  } while (!validateChoices(userOne, ChoicesNum, BoxesNum));

  do {
    printf("Player 2, please enter distinct box choices between 0 and 19: ");
    for (int choiceInd = 0; choiceInd < ChoicesNum; choiceInd++) {
      scanf("%d", &userTwo[choiceInd]);
    }
  } while (!validateChoices(userTwo, ChoicesNum, BoxesNum));
}
