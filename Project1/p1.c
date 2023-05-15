// Georgia Moore
// Systems Programming
// 1-17-2023
// Tic Tac Clemson
// Creates a game of tic tac clemson for the user to play againest the computer. 
// 2 hours

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//function used to print the tictactoe board
void printGame(char array[]){
        printf("-------------\n");
        printf("| %c | %c | %c | \n", array[0], array[1], array[2]);
        printf("-------------\n");
        printf("| %c | %c | %c | \n", array[3], array[4], array[5]);
        printf("-------------\n");
        printf("| %c | %c | %c | \n", array[6], array[7], array[8]);


}

//function used to determine if the game is over and if there was a winner or tie. 
int winLose(char array[]){
    if (array[0] == array[1] && array[1] == array[2]){
        return 1;
    }
    else if (array[3] == array[4] && array[4] == array[5]){
        return 1;
    }
    else if (array[6] == array[7] && array[7]== array[8]){
        return 1;
    }
    else if (array[0] == array[3] && array[3] == array[6]){
        return 1;
    }
    else if (array[1] == array[4] && array[4] == array[7]){
        return 1;
    }
    else if (array[2] == array[5] && array[5]== array[8]){
        return 1;
    }
    else if (array[0] == array[4] && array[4] == array[8]){
        return 1;
    }
    else if (array[2] == array[4] && array[4] == array[6]){
        return 1;
    }
    else if(array[0]!='1' && array[1]!='2' && array[2]!='3' && array[3]!='4' && array[4]!='5' && 
        array[5]!='6' && array[7]!='8' && array[8]!='9'){
        return 0;
    }
    else {
        return 2;
    }
}

int main(){
    char ans='Y';
    srand(time(NULL));
    //while loop to ensure that the user wants to paly the game
    while(ans=='Y'){  
        char board[9]={'1','2','3','4','5','6','7','8','9'};
        printf("Tic-Tac-Clemson\n");
        printf("(If at any point you would like to exit the game, enter the single character q.) \n");
        printGame(board);
        int userNum;
        //while loop to see if the game is still in play
        while(winLose(board)==2){
            printf("Enter a square 1-9: ");
            if(1!=scanf ("%i", &userNum)){
                    if (getchar() == 'q'){
                    printf ("Terminating the Program\n");
                    exit(0);
                    }
                }
            while (board[userNum-1] == 'C' || board[userNum-1] == 'U'){
                printf("Already Used. Enter a square 1-9: ");
                if(1!=scanf ("%i", &userNum)){
                    if (getchar() == 'q'){
                    printf ("Terminating the program..\n");
                    exit(0);
                    }
                }
                //scanf("%i", &userNum);
            }
            board[userNum-1]='C';
            printGame(board);
            //if loop to determine if the user won.
            if (winLose(board)==1){
                printf("You Won!!!\n");
            }
            //loop to allow the computer to play
            else if (winLose(board)==2){
                int n = rand() % 9 + 1;
                while ((board[n-1] == 'C') || (board[n-1] == 'U')){
                    n = rand() % 9 + 1;
                }
                board[n-1] = 'U';
                printf("Computer choses square %i.\n", n);
                printGame(board);
                if (winLose(board)==1){
                    printf("You Lost. :(\n");
                }
            }
            //loop to determine if there was a tie.
            else if (winLose(board)==0){
                printf("There was a tie.\n");
            } 
        }
        //asking the user if they would like to play again
        printf("Would you like to play again? (Y/N) ");
        scanf(" %c", &ans);
    }
    return 0;
}


