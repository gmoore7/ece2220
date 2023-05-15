/* Georgia Moore
   Systems Programming
   02-07-2023
   Arrays - 2048
   Purpose Statement: Create the 2048 game to demonstrate understadning of arrays
*/

/* 
     Assumptions:
     Assumes user will enter n, q, or c when prompted after winning.
     Assumes user will enter n or q after losing. 
        

*/

/*   
    Known Bugs:
       If the user clicks the buttons too fast, weird things happen and the game freezes. 
       When user enters invalid data after winning or losing, game continues. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define ROWS 4
#define COLUMNS 4

int score = 0;
int highScore = 0;

void printBoard(int array[ROWS][COLUMNS]){
    printf("*** Score = %d, High Score = %d ***\n", score, highScore);
    printf("----------------------------------\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++) {
            if(j==3){
                if (array[i][j] == 0){
                    printf("|       |\n");
                    printf("----------------------------------\n");
                }
                else {
                        printf("|%7d|\n", array[i][j]);
                        printf("----------------------------------\n");
                }     
            } 
            else{
                if (array[i][j]==0){
                    printf("|       ");
                }
                else {
                printf("|%7d", array[i][j]);
                }
            }
        }
    }
}


void startBoard(int board[ROWS][COLUMNS]){
    printf("\tWelcome to 2048!!\n");
    int i,j;
    for(i = 0; i<ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            board[i][j]=0;
        }
    }

    i = rand() % 4;
    j = rand() % 4;
    board[i][j] = 2;

    i = rand() % 4;
    j = rand() % 4;
    board[i][j] = 2;

}


int removeSpace(int board[ROWS][COLUMNS], char input){
    int j, r, c;
    
    int checkBoard[4][4];
		for(int r = 0;r < 4; r++){
			for(int c = 0;c < 4; c++){
				checkBoard[r][c]=board[r][c];
            }
        
        }

    if(input == 'w' ){
        for(c = 0; c < COLUMNS; c++ ){
            for (r = 0; r < ROWS; r++){
                if(!board[r][c]){
                    for(j = r+1; j < COLUMNS; j++ ){
                        if(board[j][c]){
                            board[r][c]=board[j][c];
                            board[j][c]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (input == 's'){
        for(c = 0; c < COLUMNS; c++ ){
            for (r = 3; r >= 0; r--){
                if (!board[r][c]){
                    for(j = r-1; j >=0; j--){
                        if(board[j][c]){
                            board[r][c]=board[j][c];
                            board[j][c]=0;
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (input == 'a'){
        for (r = 0; r < ROWS; r++){
            for(c = 0; c < COLUMNS; c++ ){
                if (!board[r][c]){
                    for(j = c+1; j < COLUMNS; j++ ){
                        if(board[r][j]){
                            board[r][c]=board[r][j];
                            board[r][j] = 0;
                            break;
                        }
                    }

                }
            }
        }

    }
    else{
        for (r = 0; r < ROWS; r++){
            for(c = 3; c >=0; c-- ){
                if (!board[r][c]){
                    for (j = c-1; j>=0; j--){
                        if (board[r][j]){
                            board[r][c] = board[r][j];
                            board[r][j] = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    for(r = 0; r < ROWS; r++){
        for(c = 0; c < COLUMNS; c++){
            if (checkBoard[r][c] != board[r][c]){
                return 0;
            }
        }
    }

    return 1;
}

int add(int board[ROWS][COLUMNS],char choice){
    int r,c;

    int checkBoard[4][4];
		for(r = 0;r < 4; r++){
			for(c = 0;c < 4; c++){
				checkBoard[r][c]=board[r][c];
            }
        
        }
    
    if (choice == 'w'){
        for(int c = 0; c < COLUMNS; c++ ){
            for (int r = 0; r < ROWS-1; r++){
                if (board[r][c]!=0 && board[r][c]==board[r+1][c]){
                    board[r][c] += board[r+1][c];
                    board[r+1][c]=0;
                    score += board[r][c];
                    if (score > highScore){
                            highScore = score;
                    }
                }
            }
        }
    }
    else if(choice == 's'){
        for(int c = 0; c < COLUMNS; c++ ){
            for (int r = 3; r > 0; r--){
                if (board[r][c]!=0 && board[r][c]==board[r-1][c]){
                    board[r][c] += board[r-1][c];
                    board[r-1][c]=0;
                    score += board[r][c];
                    if (score > highScore)
                        highScore = score;
                }
            }
        }
    }
    else if(choice == 'd'){
        for (int r = 0; r < ROWS; r++){
            for(int c = 3; c > 0; c-- ){
                if (board[r][c]!=0 && board[r][c]==board[r][c-1]){
                    board[r][c] += board[r][c-1];
                    board[r][c-1]=0;
                    score += board[r][c];
                    if (score > highScore)
                        highScore = score;
                }
            }
        }
    }
    else if(choice == 'a'){
        for (int r = 0; r < ROWS; r++){
            for(int c = 0; c < COLUMNS-1; c++ ){
                if (board[r][c]!=0 && board[r][c]==board[r][c+1]){
                    board[r][c] += board[r][c+1];
                    board[r][c+1]=0;
                    score += board[r][c];
                    if (score > highScore)
                        highScore = score;
                }
            }
        }
    }

    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLUMNS; c++){
            if (checkBoard[r][c] != board[r][c]){
                return 0;
            }
        }
    }

    return 1;
}

char gameStatus(int board[ROWS][COLUMNS]){
    int r,c;
    char choice, temp = 'c'; 
    temp = temp +1;
    for (r = 0; r < ROWS; r++){
        for(c = 0; c < COLUMNS; c++){
            if (!board[r][c]){
                return 'x';
            }
            else if(board[r][c] == 2048){
                printf("You Won!! To play again enter the letter n, to continue further enter the letter c or q to quite : ");
                temp = getchar();
                choice = getchar();
                return choice;
            }
        }
    }
    printf("YOU LOST! To play again enter the letter n, to quit type q: ");
    score = 0;
    temp = getchar();
    choice = getchar();
    return choice;
}

void newNum(int board[ROWS][COLUMNS]){
    srand(time(NULL));
    int i,j,k;
		
		do
		{
		    i=rand() % 4;
		    j=rand() % 4;
		    k=rand() % 10;

		}while(board[i][j]);
				
		
			
		if(k<2)
		    board[i][j]=4;

		else
		    board[i][j]=2;
}


void playGame(int board[ROWS][COLUMNS]){
    
    srand(time(NULL));
    
    char choice;
    int tmp2 = 1;
    char temp = 'c';
    int game = 1;
    int contGame = 1;
    temp = temp+1;

    while(game == 1){
        startBoard(board);
        printBoard(board);


        do {printf("w = up, s = down, a = left, d = right: ");
            if(tmp2 == 1){
                choice = getchar();
                tmp2 = 0;
            }
            else{   
                choice = getchar();
                if (choice == '\n'){
                    choice = getchar();
                }
            } 
        } while (!(choice == 'a' || choice == 's' || choice == 'd' || choice == 'w' || choice == 'q'));


        if (choice == 'q'){
                        exit(1);
                }
        
        while(1){
            int i = removeSpace(board, choice);
            int j = add(board, choice);
            int k = removeSpace(board, choice);
            
            if (i == 0 || j == 0 || k == 0){
                newNum(board);
            }
            printBoard(board);


            char stat = gameStatus(board);
            if (contGame == 1){
                if (stat == 'c'){
                    contGame = 0;
                    continue;
                }
                else if (stat == 'q'){
                    exit(1);
                }
            }
            
            if (stat == 'n'){
                score=0;
                break;
            }
            

            
            
            do {printf("w = up, s = down, a = left, d = right: ");
                choice = getchar();
                if (choice == '\n'){
                    choice = getchar();
                }
            } while (!(choice == 'a' || choice == 's' || choice == 'd' || choice == 'w' || choice == 'q'));

            if(choice == 'q'){
                exit(1);
            }
        }
    }
}
    


int main(){
    srand(time(NULL));
    
    int board[ROWS][COLUMNS];

    playGame(board);
   
    return 0;
}