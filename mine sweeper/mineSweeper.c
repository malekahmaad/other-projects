//324921345
//malek ahmad
#include <stdio.h>
#include "mineSweeper.h"
#include <stdlib.h>
#include <time.h>
#include "colorPrint.h"

//this function i made to give the tile values FALSE to its bools(visible,mine,flagged)
void initTiles(GameBoard *g){
    for(int i=0;i< g->rows;i++){
        for(int j=0;j< g->cols;j++){
            ((g->board)[i][j]).isVisible=FALSE;
            ((g->board)[i][j]).isFlagged=FALSE;    
            ((g->board)[i][j]).isMine=FALSE;    
        }
    }
}

//a function to inialize the board if the level is not (1/2/3) it returns false
//it gives the hidden tiles an inializing value that equals to rows*cols 
//if the cols is 0 or lower it makes it 4 the same thing for the rows 
//the it calls the function that divide the mines and the one that gives the tiles how many mines are around it
bool initBoard(GameBoard *g, int rows, int cols, int level){
    if(level>=1 && level<=3){
        if(cols<=0)
            cols=4;
        else if(cols>20)
            cols=20;    
        if(rows<=0)
            rows=4;
        else if(rows>20)
            rows=20; 
        g->rows=rows;
        g->cols=cols;
        g->board=(Tile**)malloc(rows*sizeof(Tile*));
        for(int i=0;i<rows;i++){
            (g->board)[i]=(Tile*)malloc(cols*sizeof(Tile));
        }
        initTiles(g);
        g->hiddenTiles=rows*cols;
        populateMines(g,level);
        markNumbers(g);
        return TRUE;
    }
    return FALSE;
}

//a function that checks the tile if it visible oor flagged if its not it will see if it has a mine 
//it make is mine clicked =true if its not it should have a num of mines >=0 so it will go  and see 
//if its bigger than zero it will make it visible if its zero it will call itself according to 
//its place to call the ones around it 
//with every successful click the hidden tiles value will decrease by one  
void clickTile(GameBoard *g, int row, int col){
    g->isMineClicked=FALSE;
    if((g->board)[row][col].isVisible==FALSE && (g->board)[row][col].isFlagged==FALSE){
        if((g->board)[row][col].isMine==TRUE)
            g->isMineClicked=TRUE;
        else if((g->board)[row][col].numOfMines>0){
            (g->board)[row][col].isVisible=TRUE;
            g->hiddenTiles-=1;
        }
        else if((g->board)[row][col].numOfMines==0){
            (g->board)[row][col].isVisible=TRUE;
            g->hiddenTiles-=1;
            if(row==0){
                if(col==0){
                    clickTile(g,row+1,col);
                    clickTile(g,row,col+1);
                    clickTile(g,row+1,col+1);
                }
                else if(col==(g->cols)-1){
                    clickTile(g,row+1,col);
                    clickTile(g,row+1,col-1);
                    clickTile(g,row,col-1);
                }
                else{
                    clickTile(g,row+1,col);
                    clickTile(g,row+1,col+1);
                    clickTile(g,row+1,col-1);
                    clickTile(g,row,col-1);
                    clickTile(g,row,col+1);
                }
            }
            else if(row==(g->rows)-1){
                if(col==0){
                    clickTile(g,row-1,col);
                    clickTile(g,row,col+1);
                    clickTile(g,row-1,col+1);
                }
                else if(col==(g->cols)-1){
                    clickTile(g,row-1,col);
                    clickTile(g,row-1,col-1);
                    clickTile(g,row,col-1);
                }
                else{
                    clickTile(g,row-1,col);
                    clickTile(g,row-1,col+1);
                    clickTile(g,row-1,col-1);
                    clickTile(g,row,col-1);
                    clickTile(g,row,col+1);
                }
            }
            else{
                if(col==0){
                    clickTile(g,row-1,col);
                    clickTile(g,row-1,col+1);
                    clickTile(g,row,col+1);
                    clickTile(g,row+1,col+1);
                    clickTile(g,row+1,col);
                }
                else if(col==(g->cols)-1){
                    clickTile(g,row-1,col);
                    clickTile(g,row-1,col-1);
                    clickTile(g,row,col-1);
                    clickTile(g,row+1,col-1);
                    clickTile(g,row+1,col);
                }
                else{
                    clickTile(g,row-1,col);
                    clickTile(g,row-1,col+1);
                    clickTile(g,row-1,col-1);
                    clickTile(g,row,col-1);
                    clickTile(g,row,col+1);
                    clickTile(g,row+1,col);
                    clickTile(g,row+1,col-1);
                    clickTile(g,row+1,col+1);
                }
            }
        }
    }
}

//a function that checks if the tile is visible if its not it makes it flagged
void flagTile(GameBoard *g, int row, int col){
    if((g->board)[row][col].isVisible==FALSE){
        if((g->board)[row][col].isFlagged==TRUE)
            (g->board)[row][col].isFlagged=FALSE;
        else
            (g->board)[row][col].isFlagged=TRUE;
    }
}

//a function that divides the mines into the tiles 
//it decides the total mines number according to the level percent 
//every time it finds the random place with no mine in it it will make it mined and decrease one from the 
//total mines 
//i used the srand(time(NULL)) to get different random values every time i run the program
void populateMines(GameBoard *g, int level){
    if(level==EASY)
        g->totalMines=((g->rows)*(g->cols)*EASY_LEVEL_PERCENT)/100;
    else if(level==MEDIUM)
        g->totalMines=((g->rows)*(g->cols)*MEDIUM_LEVEL_PERCENT)/100;
    else
        g->totalMines=((g->rows)*(g->cols)*HARD_LEVEL_PERCENT)/100;
    srand(time(NULL));
    int place1;
    int place2;
    int mines=g->totalMines;
    while(mines!=0){
        place1=rand()%(g->rows);
        place2=rand()%(g->cols);
        if(((g->board)[place1][place2]).isMine==FALSE){
            ((g->board)[place1][place2]).isMine=TRUE;
            mines=mines-1;
        }
    }
}

//a function that calculates how many mines there are around every tile 
//it checks  the mines around according to the tile place if its in the edge or in the middle
void markNumbers(GameBoard *g){
    for(int i=0;i< g->rows;i++){
        for(int j=0;j< g->cols;j++){
            ((g->board)[i][j]).numOfMines=-1;
            if(((g->board)[i][j]).isMine==FALSE){
                ((g->board)[i][j]).numOfMines=0;
                if(i==0){
                    if(j==0){
                        if(((g->board)[i+1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                    }
                    else if(j==(g->cols)-1){
                        if(((g->board)[i+1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1; 
                    }
                    else{
                        if(((g->board)[i+1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                    }
                }
                else if(i==(g->rows)-1){
                   if(j==0){
                        if(((g->board)[i-1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                    }
                    else if(j==(g->cols)-1){
                        if(((g->board)[i-1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1; 
                    }
                    else{
                        if(((g->board)[i-1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                    } 
                }
                else{
                    if(j==0){
                        if(((g->board)[i+1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;   
                        if(((g->board)[i-1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                    }
                    else if(j==(g->cols)-1){
                        if(((g->board)[i+1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                        if(((g->board)[i-1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                    }
                    else{
                        if(((g->board)[i+1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i+1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i-1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;
                        if(((g->board)[i][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                        if(((g->board)[i+1][j-1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                        if(((g->board)[i-1][j]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                        if(((g->board)[i-1][j+1]).isMine==TRUE)
                            ((g->board)[i][j]).numOfMines+=1;    
                    }
                }
            }
        }
    }
}

//a function that clears the screen and prints the gameboard according to the new change 
//if the tile is flagged it will print it with F if its visible it will print the num of mines 
//it will print the given array(given place) with a different color(cyan) than the others(yellow)
void printBoard(GameBoard *g, int cursorCoords[2]){
    clearScreen();
    char num[3];
    for(int i=0;i< g->rows;i++){
        for(int j=0;j< g->cols;j++){
            if(i==cursorCoords[0] && j==cursorCoords[1]){
                if((g->board)[i][j].isVisible==TRUE){
                    sprintf(num,"%d",(g->board)[i][j].numOfMines);
                    colorPrint(FG_Red ,BG_Cyan ,ATT_Def ,"%c " ,num[0]);//because i wanted the area of the color to be like the other(two chars)
                }
                else {
                    if((g->board)[i][j].isFlagged==TRUE)
                        colorPrint(FG_Red ,BG_Cyan ,ATT_Def ,"F ");
                    else
                        colorPrint(FG_Red ,BG_Cyan ,ATT_Def ,"  ");
                }
            }
            else {
               if((g->board)[i][j].isVisible==TRUE){
                    sprintf(num,"%d",(g->board)[i][j].numOfMines);
                    colorPrint(FG_Red ,BG_Yellow ,ATT_Def ,"%c " ,num[0]);
                }
                else {
                    if((g->board)[i][j].isFlagged==TRUE)
                        colorPrint(FG_Red ,BG_Yellow ,ATT_Def ,"F ");
                    else
                        colorPrint(FG_Red ,BG_Yellow ,ATT_Def ,"  ");
                }
            }
        }
        printf("\n");
    }
}
