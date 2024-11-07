/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//324921345
//malek ahmad
#include <stdio.h>
#include "mineSweeper.h"
#include "getch.h"
#include <stdlib.h>
#include <time.h>
//game main
int main()
{   
    GameBoard *c=(GameBoard*)malloc(sizeof(GameBoard));
    printf("enter how many rows do you want: ");
    int rows;
    scanf("%d",&rows);//the user enters a number for rows
    printf("enter how many columns do you want: ");
    int cols;
    scanf("%d",&cols);//the user enters a number for cols 
    printf("which difficulty do you want: ");
    int dificulty;
    scanf("%d",&dificulty);//the user enters which dificulty he wants
    if(initBoard(c, rows, cols, dificulty)==TRUE){//if the dificulty is one of(1\2\3)the program starts the game
        int x[2];
        x[0]=0;
        x[1]=0;
        getch();//this getch i put because when i enter a number in the scanner i need to press enter so the program gives the getch a char=ENTER
        printBoard(c, x);
        char y;
        //infinite loop until the user enters q to quit or wins by getting all the nonmined tiles or losing
        //by pressing a mine 
        for(;;){
            if(c->totalMines==c->hiddenTiles){
                printf("you won, good job");
                break;
            }
            if(c->isMineClicked==TRUE){
                printf("its a trap, you lost.Better luck next time");
                break;
            }
            printf("choose your move: ");
            y=getch();
            if(y==QUIT){
                printf("\nyou quit");
                break;
            }
            if(y==FLAG_TILE){
                flagTile(c,x[0],x[1]);
             }
            if(y==CLICK_TILE){
                clickTile(c,x[0],x[1]);
            }
            //if the user is in the place (0,y) he cant move up just down 
            //if its in the place (row-1,y) he cant move down just up
            //if hes in the middle he can move to the two directions
            if(x[0]==0){
                if(y==DOWN)
                    x[0]+=1;
            }
            else if(x[0]==(c->rows)-1){
                if(y==UP)
                    x[0]-=1;
            }
            else{
                if(y==DOWN)
                    x[0]+=1;
                else if(y==UP)
                    x[0]-=1;    
            }
            //the same job in the x[0] before but for the x[1](columns)
            if(x[1]==0){
                if(y==RIGHT)
                    x[1]+=1;
            }
            else if(x[1]==(c->cols)-1){
                if(y==LEFT)
                    x[1]-=1;
            }
            else{
                if(y==RIGHT)
                    x[1]+=1;
                else if(y==LEFT)
                    x[1]-=1;    
            }
            printBoard(c, x);
        }
    }
    //if the dificulty isnt one from the (1\2\3) it will print that the program doesnt have this dificulty 
    else{
        printf("you entered a wrong dificulty");
    }
    free(c);
}
