/**
* @file reversi.c
* @author <-- Your name here-->
* @brief This file is used for APS105 Lab 8. 2023W version
* @date 2023-03-14
*
*/
#if !defined(TESTER_P1) && !defined(TESTER_P2)
#include "reversi.h"
#include <stdio.h>
#include <stdbool.h>
#endif

int humanPlays(char board[26][26], int n, char turn, char *row, char *col);

void printBoard(char board[][26], int n);

int convertRow(char moveRow, char board[][26]);

char convertNum(int i, char board[][26], int n);

bool positionInBounds(int n, int row, int col);

bool checkLegalInDirection(char board[][26], int n, int row, int col,
char colour, int deltaRow, int deltaCol);

int makeMove(char board[26][26], int n, char turn, int *row, int *col);

int decision(char board[][26], int n, char humanColour, char computerColour, char playColour);

int computerPlays(char board[][26], int n, char playColour, char movesComputer[26][3]);

int avaliableMoves(char board[][26], int n, char colour, char movesW[26][3]);

int countingBoard(char moveColour, char moveRow, char moveCol, char board[][26], int n);

void changeBoard(char moveColour, char moveRow, char moveCol, char board[][26], int n);

void updateValues(int *row, int *col, int deltaRow, int deltaCol);

bool validateMove(char moveRow, char moveCol, char movesW[][3]);

bool checkFullBoard(char board[][26], int n);

char findWinner(char board[][26], int n);






#ifndef TESTER_P2

int main(void) {
  int n = 0;
  //create board 
  printf("Enter the board dimension: ");
  scanf(" %d", &n);

 char board[26][26];

//set up board 
 for (int row = 0; row < (n); row++){
  for (int col = 0; col < (n); col++){
    if (row == (n/2 -1) && col == (n/2 -1)){
      board[row][col] = 'W';
    } else if (row == (n/2-1) && col == n/2){
      board[row][col] = 'B';
    } else if (row == n/2 && col == (n/2-1)){
      board[row][col] = 'B';
    } else if (row == n/2 && col == n/2){
      board[row][col] = 'W';
    } else {
      board[row][col] = 'U';
    }
  }
  }

    //choose player 
    char computerColour = ' ', humanColour = ' '; 
    printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);

    if (computerColour == 'W'){
        humanColour = 'B';
    }else{
        //computer is black 
        humanColour = 'W';
    }
    //print board
    printBoard(board, n);

    int validGame1 = 1, validGame2 = 1; 
    bool fullBoard = checkFullBoard(board, n);
    bool declared = false;

    while (validGame1 == 1 && validGame2 == 1 && fullBoard == true){
      
      //first player goes 
      validGame1 = decision(board, n, humanColour, computerColour, 'B');
      fullBoard = checkFullBoard(board, n);
      if (validGame1 == 1 && fullBoard == true){
        printBoard(board, n);
        validGame2 = decision(board, n, humanColour, computerColour, 'W');
        if(validGame2 == 1){
          printBoard(board, n);
        }else if(validGame2 == 0){
          printf("Invalid move.\nB player wins.");
           declared = true;
        }else{
          printf("W player has no valid move.\n");
          while(decision(board, n, humanColour, computerColour, 'W') != 1 && (fullBoard == true)){
            validGame1 = decision(board, n, humanColour, computerColour, 'B');
            if(validGame1 == 1){
              printBoard(board, n);
            }else if(validGame2 == 0){
              printf("Invalid move.\nW player wins.");
               declared = true;
            }else{
              break;
            }
            fullBoard = checkFullBoard(board, n);
          }
        }
      }else if(validGame1 == 0){
        printf("Invalid move.\nW player wins.");
         declared = true;
      }else if (validGame1 == 2 && fullBoard == true){
        printf("B player has no valid moves.\n");
        while(decision(board, n, humanColour, computerColour, 'B') != 1 && (fullBoard == true)){
            validGame1 = decision(board, n, humanColour, computerColour, 'W');
            if(validGame1 == 1){
              printBoard(board, n);
            }else if(validGame2 == 0){
              printf("Invalid move.\n B player wins.");
               declared = true;
            }else{
              break;
            }
            fullBoard = checkFullBoard(board, n);
          }

      }
    }

    char winner = findWinner(board, n);

    if(declared == false){
        printf("%c player wins.", winner);
    }
  

  return 0;
}

char findWinner(char board[][26], int n){
  int bCounter = 0; 
  int wCounter = 0;
  for(int i = 0; i < n + 1; i++){
    for(int j = 0; j < n + 1; j++){
      if(board[i][j] == 'W'){
        wCounter++;
      }else{
        bCounter++;
      }
    }
  }

  if (bCounter > wCounter){
    return 'B';
  }else{
    return 'W';
  }
}

bool checkFullBoard(char board[][26], int n){
  char value = 'U';
  bool fullBoard = false;
  for(int i = 0; i < n + 1; i++){
    for(int j = 0; j < n + 1; j++){
      if(board[i][j] == 'U'){
        fullBoard = true;
      }
    }
  }
  return fullBoard;
}

int decision(char board[][26], int n, char humanColour, char computerColour, char playColour){
  int legal = 1;
    if (playColour == computerColour){
        char movesComputer[26][3];
        legal = computerPlays(board, n, playColour, movesComputer);
    }else{
        char row, col; 
        printf("Enter move for colour %c (RowCol): ", playColour);
        scanf(" %c %c", &row, &col);

        legal = humanPlays(board, n, playColour, &row, &col);
        if (legal == 1){
          changeBoard(playColour, row, col, board, n);
        }
    }

    return legal;

}

int humanPlays(char board[26][26], int n, char turn, char *row, char *col){
  char movesHuman[26][3];
  int length = avaliableMoves(board, n, turn, movesHuman);

  if(length != 0){
    for (int i = 0; i<length; i++){
      if(movesHuman[i][0] == *row && movesHuman[i][1] == *col){
        return 1;
      }
    }
    return 0;
  }else{
    return 2;
  }
  
}

int computerPlays(char board[][26], int n, char playColour, char movesComputer[26][3]){
    //moves is the number of moves avaliable for the user to make 
    int moves = avaliableMoves(board, n, playColour, movesComputer);
    
    int moveChanges[moves];
    int length = 0;
    //get number of tiles moved for making particular move change 
    for (int i = 0; i < moves; i++){
        moveChanges[i] = countingBoard(playColour, movesComputer[i][0], movesComputer[i][1], board, n);
        length ++;
    }

    //get the number of the move that makes the most tile changes 
    int largestIndex = 0;
    for (int i = length -1 ; i >= 0 ; i--){
      if (moveChanges[largestIndex] <= moveChanges[i]){
        largestIndex = i; 
      }
    }

    if (moves == 0){
      return 2;
    }else{
      printf("Computer places %c at %c%c.\n", playColour, movesComputer[largestIndex][0], movesComputer[largestIndex][1]);
      changeBoard(playColour, movesComputer[largestIndex][0], movesComputer[largestIndex][1], board, n);
      return 1;
    }

    

}

void changeBoard(char moveColour, char moveRow, char moveCol, char board[][26], int n){
  int numRow = convertRow(moveRow, board);
  int numCol = convertRow(moveCol, board);

  board[numRow][numCol] = moveColour;
  char anticolour;
  bool continuation;
  int counter = 0;
  if(moveColour == 'W'){
    anticolour = 'B';
  }else{
    anticolour = 'W';
  }

  for (int i = -1; i <= 1; i++){
    numRow = convertRow(moveRow, board);
    numCol = convertRow(moveCol, board);
    for(int j = -1; j <= 1; j++){
      counter = 0;
      if(i != 0 || j != 0){
        continuation = checkLegalInDirection(board, n, numRow, numCol, anticolour, i, j);
      
        if (continuation == true){
          while (continuation == true){
            if (j == 0){
              //board[numRow + i + counter*(i)][numCol + j + j*counter] = moveColour;
              continuation = checkLegalInDirection(board, n, numRow + i + counter*(i), numCol + j + j*counter, anticolour, i, j);
            }else{
              //board[numRow - i - counter*i][numCol + j + counter*j] = moveColour;
              continuation = checkLegalInDirection(board, n, numRow - i - counter*i, numCol + j + counter*j, anticolour, i, j);
            }
            counter++;
          }
          int initalRow = 0, initalCol = 0;
          counter--;
          if (j == 0){
            initalRow = numRow + i + counter*i;
            initalCol = numCol + j + counter*j;
          }else{
            initalRow = numRow - i - counter*i;
            initalCol = numCol + j + counter*j;
          }
          
          updateValues(&initalRow, &initalCol, i, j);
          bool valid = positionInBounds(n, initalRow, initalCol);
          
          //have to make it && to work on computer but || to work on examify
          if(valid == true && board[initalRow][initalCol] == moveColour){
            counter = 0;
            continuation = true;
            while (continuation == true){
              if (j == 0){
                board[numRow + i + counter*(i)][numCol + j + j*counter] = moveColour;
                continuation = checkLegalInDirection(board, n, numRow + i + counter*(i), numCol + j + j*counter, anticolour, i, j);
              }else{
                board[numRow - i - counter*i][numCol + j + counter*j] = moveColour;
                continuation = checkLegalInDirection(board, n, numRow - i - counter*i, numCol + j + counter*j, anticolour, i, j);
              }
              counter++;
          }
          }
          
        }
      }
    }
  }
}



int avaliableMoves(char board[][26], int n, char colour, char movesColour[26][3]){

  int countPositions = 0;
  int index = 0;
  int moves[26][2];
  char anticolour; 
  if (colour == 'W'){
    anticolour = 'B';
  }else{
    anticolour = 'W';
  }
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
   
      if(board[row][col] == 'U'){
        for (int i = -1; i <= 1; i++){
          for (int j = -1; j <= 1; j++){
            int counter = 0;
            bool finding = false; 
            if(i != 0 || j != 0){
              finding = checkLegalInDirection(board, n, row, col, anticolour, i, j);
              
              if (finding == true){ 
                while (finding == true){
                  if (j == 0){
                    finding = checkLegalInDirection(board, n, row + i + counter*(i), col + j + j*counter, anticolour, i, j);
                  }else{
                    finding = checkLegalInDirection(board, n, row - i - counter*i, col + j + counter*j, anticolour, i, j);
                  }
                  counter++;
                }
                
              
              bool valid = false;
              if(j==0){
                valid = positionInBounds(n, row + i + counter*(i), col + j + j*counter);
              }else{
                valid = positionInBounds(n, row - i - counter*i, col + j + counter*j);
              }
              if (valid == true){
                if ( j == 0){
                  finding = checkLegalInDirection(board, n, row + i + (counter-1)*(i), col + j + j*(counter-1), colour, i, j);
                }else{
                  finding = checkLegalInDirection(board, n, row - i - (counter-1)*i, col + j + (counter-1)*j, colour, i, j);
                }
                if (finding == true){
                    bool checking = true; 
                    for (int i = 0; i <= index; i++){
                        if(moves[i][0] == row && moves[i][1] == col){
                            checking = false;
                        }
                    }
                    if(checking == true){
                        countPositions++;
                        moves[index][0] = row;
                        moves[index][1] = col;
                        index++;
                    }
                  
                  
                }
              }
              }
            }
          }
        }
      }
  }

    }
  //moves array has been filled 
  for (int i = 0; i < index; i++){
    
    char rowNum = convertNum(moves[i][0], board, n);
    char colNum = convertNum(moves[i][1], board, n);
    movesColour[i][0] = rowNum;
    movesColour[i][1] = colNum;
    
  }

    return countPositions;

}
int countingBoard(char moveColour, char moveRow, char moveCol, char board[][26], int n){
  int numRow = convertRow(moveRow, board);
  int numCol = convertRow(moveCol, board);
  int countMoves = 0;
  bool equalB, equalW = false;

 //board[numRow][numCol] = moveColour;
  char anticolour;
  bool continuation;
  int counter = 0;
  if(moveColour == 'W'){
    anticolour = 'B';
  }else{
    anticolour = 'W';
  }

  for (int i = -1; i <= 1; i++){
    numRow = convertRow(moveRow, board);
    numCol = convertRow(moveCol, board);
    for(int j = -1; j <= 1; j++){
      counter = 0;
      if(i != 0 || j != 0){
        continuation = checkLegalInDirection(board, n, numRow, numCol, anticolour, i, j);
      
        if (continuation == true){
          while (continuation == true){
            if (j == 0){
              //board[numRow + i + counter*(i)][numCol + j + j*counter] = moveColour;
              continuation = checkLegalInDirection(board, n, numRow + i + counter*(i), numCol + j + j*counter, anticolour, i, j);
            }else{
              //board[numRow - i - counter*i][numCol + j + counter*j] = moveColour;
              continuation = checkLegalInDirection(board, n, numRow - i - counter*i, numCol + j + counter*j, anticolour, i, j);
            }
            counter++;
          }
          int initalRow = 0, initalCol = 0;
          counter--;
          if (j == 0){
            initalRow = numRow + i + counter*i;
            initalCol = numCol + j + counter*j;
          }else{
            initalRow = numRow - i - counter*i;
            initalCol = numCol + j + counter*j;
          }
          
          updateValues(&initalRow, &initalCol, i, j);
          bool valid = positionInBounds(n, initalRow, initalCol);
          
          //have to make it && to work on computer but || to work on examify
          if(valid == true && board[initalRow][initalCol] == moveColour){
            counter = 0;
            continuation = true;
            while (continuation == true){
              countMoves++;
              if (j == 0){
                //board[numRow + i + counter*(i)][numCol + j + j*counter] = moveColour;
                continuation = checkLegalInDirection(board, n, numRow + i + counter*(i), numCol + j + j*counter, anticolour, i, j);
              }else{
                //board[numRow - i - counter*i][numCol + j + counter*j] = moveColour;
                continuation = checkLegalInDirection(board, n, numRow - i - counter*i, numCol + j + counter*j, anticolour, i, j);
              }
              counter++;
          }
          }
          
        }
      }
    }
  }
  
  return countMoves;
}

char convertNum(int num, char board[][26], int n){
  char letter = 'a' + num;
  return (letter);
}

int convertRow(char moveRow, char board[][26]){
  int number = moveRow - 'a';
  
  return number;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
  int initalRow = 0, initalCol = 0;
  initalRow = row;
  initalCol = col;
  updateValues(&initalRow, &initalCol, deltaRow, deltaCol);
  bool valid = positionInBounds(n, initalRow, initalCol);

  if (valid == true){
    if (board[initalRow][initalCol] == colour){
      return true;
    }else{
      return false;
    }
  }else{
    return false;
  }
}

void printBoard(char board[][26], int n) {
  printf("  ");
  for (int i = 0; i < n; i++){
    char letter = 'a' + i;
    printf("%c", letter);
  }
  printf("\n");
  for(int row = 0; row < n; row++){
    char letter = 'a' + row;
    printf("%c ", letter); 
    for (int col = 0; col < n; col++){
      printf("%c", board[row][col]);
      
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col){
  if (row < 0 || row > n){
    return false;
  }else if(col < 0 || col > n){
    return false;
  }else{
    return true;
  }
}

void updateValues(int *row, int*col, int deltaRow, int deltaCol){
  if(deltaRow == 1 && deltaCol == 0){
    (*row)++;
  }else if(deltaRow == -1 && deltaCol == 0){
    (*row)--;
  }else if(deltaRow == 0 && deltaCol == 1){
    (*col)++;
  }else if(deltaRow == 0 && deltaCol == -1){
    (*col)--;
  }else if(deltaRow == -1 && deltaCol == 1){
    (*row)++;
    (*col)++;
  }else if(deltaRow == -1 && deltaCol == -1){
    (*row)++;
    (*col)--;
  }else if(deltaRow == 1 && deltaCol == 1){
    (*row)--;
    (*col)++;
  }else if(deltaRow == 1 && deltaCol == -1){
    (*row)--;
    (*col)--;
  }
}

bool validateMove(char moveRow, char moveCol, char movesW[][3]){
  for (int i = 0; i < 26; i++){
    if('a' + i == moveRow){
      if('a' + i == moveCol){
        return true;
      }
    }
  }
  
  return false;
}

#endif
