#include <stdio.h>
void appendStatistics(int userChoice[], const int ChoicesNum, int histogram[]);
int frequentBox(int histogram[], const int BoxesNum);
int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int userOne[ChoicesNum], userOneHisto[BoxesNum];
  for (int i = 0; i < BoxesNum; i++) {
    userOneHisto[i] = 0;
  }
  
  int numOfTimes = 0;
  while (numOfTimes <= 5) {
    printf("Enter choices: ");
    for (int i = 0; i < 5; i++) {
      scanf("%d", &userOne[i]);
    }
    appendStatistics(userOne, ChoicesNum, userOneHisto);
    numOfTimes++;
  }
  printf("The smallest and most frequently used box is: %d\n",
         frequentBox(userOneHisto, BoxesNum));
  return 0;
}
void appendStatistics(int userChoice[], const int ChoicesNum, int histogram[]) {
  // Fill in the histogram with the number of times each index was picked
  // Print the histogram

  for (int i = 0; i < 20; i++){
    for (int j = 0; j < ChoicesNum; j++){
        if(userChoice[j] == i){
            histogram[i] += 1;
        }
    }

    printf("%d: %d, ", i, histogram[i]);
  }

  printf("\n");
}

int frequentBox(int histogram[], const int BoxesNum) {
  // Return the index having the maximum number in histogram
  int largest = histogram[19];
  int value = 0;
  for (int i = BoxesNum; i > 0; i--){
    if (histogram[i] >= largest){
        largest = histogram[i];
        value = i;
    }
  }
  return value; 
}