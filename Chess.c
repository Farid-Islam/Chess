#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

///Function prototype
void gameStartingMode();/// Game start point
void userTurn(); /// For move turn
void displayChessBoard();/// Chess board print
int searchingAvailable_Loc(int row, int col);/// Troops move location search
void changeMoving();/// Any troops change by available location
void kingMove(); /// King move ( Exceptional )

/// global variable declare
int userInRow,userInCol,cancel_select; /// For cancel troops select
char input;
char Troop[9][9];  /// All troops
char p1[16];/// Player-1 Lost troops collect
char p2[16];/// Player-2 Lost troops collect
int pl_1,pl_2;/// For lost troops count
int avai_Loc_Row[32],avai_Loc_Col[32],x,y,avai_Loc_Count;/// Available troops location collect
int userInRowCollect,userInColCollect; /// Initially select troops row and col collect
int kingmoveRow[8];
int kingmoveCol[8];
int kingMoveAvaiCount,turnCheck; /// For userInput == 'K';

/// Computer turn function prototype
void computerTurn();
int searchingAvailableComputer(int row, int col);/// Troops search available
void randomInput(); /// For randomly input
void changeMovingRandom(int *row, int *col); /// troops location match randomly
void changeMovingComputer(); /// Troops location change

int main()
{
    gameStartingMode();

    while(1)
    {
        userTurn();
        computerTurn();
    }
    return 0;
}

void userTurn()
{

    while(1)
    {

        int gameReset = 0;
        avai_Loc_Row[32],avai_Loc_Col[32],x = 0,y = 0,avai_Loc_Count = 0,kingMoveAvaiCount = 0;

        while(1)
        {
            system("cls");
            displayChessBoard();
            printf("Enter your turn : ");

            userInRow = (int)_getch() - 48;
            printf("%d",userInRow);

            if(userInRow == 34 || userInRow == 66)
            {
                gameReset = 1;
                break;
            }

            userInCol = (int)_getch() - 48;
            printf("%d",userInCol);

            if(userInCol == 34 || userInCol == 66)
            {
                gameReset = 1;
                break;
            }

            input = Troop[userInRow][userInCol];


            if(input == 'K' || input == 'P' || input == 'R' || input == 'N' || input == 'B' || input == 'Q')
            {
                if(input == 'K')
                {
                    turnCheck = 1;
                    kingMove();
                }

                break;
            }
            else
                continue;

        }
        if(gameReset)
        {
            gameStartingMode();
            continue;
        }

        /// Troops checking starting point...

        if(input == 'K')
        {
            printf("\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;
            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 8; loop++)
            {
                if(loop == 1)
                {
                    row--;
                    col--;
                }
                else if(loop == 2)
                    col++;
                else if(loop == 3)
                    col++;
                else if(loop == 4)
                {
                    row = userInRow;
                    col = userInCol - 1;
                }
                else if(loop == 5)
                    col += 2;
                else if(loop == 6)
                {
                    row = userInRow + 1;
                    col = userInCol - 1;
                }
                else if(loop == 7)
                    col++;
                else if(loop == 8)
                    col++;

                if(row < 1 || 8 < row || col < 1 || 8 < col)
                    continue;

                searchingAvailable_Loc(row,col);

            }

            if(avai_Loc_Count == 0)
            {
                printf("Moving block...\nTryAgain...");
                _getch();
                continue;
            }

            changeMoving();

            if(cancel_select == 51 || cancel_select == 19)  ///  For cancel move turn
                continue;


        }  /// K moving...last brace:

        else if(input == 'P')
        {
            printf("\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            if(Troop[--userInRow][--userInCol] == '0' || Troop[userInRow][userInCol] == 'q' || Troop[userInRow][userInCol] == 'r' || Troop[userInRow][userInCol] == 'b' || Troop[userInRow][userInCol] == 'n')
            {
                avai_Loc_Row[x++] = userInRow;
                avai_Loc_Col[y++] = userInCol;
                avai_Loc_Count++;
            }

            if(Troop[userInRow][++userInCol] == ' ')
            {
                avai_Loc_Row[x++] = userInRow;
                avai_Loc_Col[y++] = userInCol;
                Troop[userInRow][userInCol] = '*';
                avai_Loc_Count++;

                if(userInRowCollect == 7)
                {
                    if(Troop[--userInRow][userInCol] == ' ')
                    {
                        avai_Loc_Row[x++] = userInRow;
                        avai_Loc_Col[y++] = userInCol;
                        Troop[userInRow][userInCol] = '*';
                        avai_Loc_Count++;
                        userInRow++;
                    }
                }
            }
            if(Troop[userInRow][++userInCol] == '0' || Troop[userInRow][userInCol] == 'q' || Troop[userInRow][userInCol] == 'r' || Troop[userInRow][userInCol] == 'b' || Troop[userInRow][userInCol] == 'n')
            {
                avai_Loc_Row[x++] = userInRow;
                avai_Loc_Col[y++] = userInCol;
                avai_Loc_Count++;
            }

            if(avai_Loc_Count == 0)
            {
                printf("Moving block...\nTryAgain...");
                _getch();
                continue;
            }

            changeMoving();

            if(cancel_select == 51 || cancel_select == 19)
                continue;

        }  /// P moving...last brace:

        else if(input == 'R')
        {
            printf("\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 4; loop++)
            {
                if(loop == 1)
                {
                    for(row = userInRow - 1; row >= 1; row--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 2)
                {
                    for(row = userInRow + 1; row <= 8; row++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 3)
                {
                    row = userInRow;
                    for(col = userInCol - 1; col >= 1; col--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 4)
                {
                    for(col = userInCol + 1; col <= 8; col++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

            }

            if(avai_Loc_Count == 0)
            {
                printf("Moving block...\nTryAgain...");
                _getch();
                continue;
            }

            changeMoving();

            if(cancel_select == 51 || cancel_select == 19)
                continue;



        }/// R moving.. last brace:

        else if(input == 'N')
        {
            printf("\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 8; loop++)
            {
                if(loop == 1)
                {
                    row = userInRow - 2;
                    col = userInCol - 1;
                }
                else if(loop == 2)
                {
                    row = userInRow - 2;
                    col = userInCol + 1;
                }
                else if(loop == 3)
                {
                    row = userInRow - 1;
                    col = userInCol + 2;
                }
                else if(loop == 4)
                {
                    row = userInRow + 1;
                    col = userInCol + 2;
                }
                else if(loop == 5)
                {
                    row = userInRow + 2;
                    col = userInCol + 1;
                }
                else if(loop == 6)
                {
                    row = userInRow + 2;
                    col = userInCol - 1;
                }
                else if(loop == 7)
                {
                    row = userInRow + 1;
                    col = userInCol - 2;
                }
                else if(loop == 8)
                {
                    row = userInRow - 1;
                    col = userInCol - 2;
                }
                if(row < 1 || 8 < row || col < 1 || 8 < col)
                    continue;

                searchingAvailable_Loc(row,col);

            }


            if(avai_Loc_Count == 0)
            {
                printf("Moving block...\nTryAgain...");
                _getch();
                continue;
            }

            changeMoving();

            if(cancel_select == 51 || cancel_select == 19)
                continue;


        }/// N Moving..last brace:

        else if(input == 'B')
        {
            printf("\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row,col,loop;
            for(loop = 1; loop <= 4; loop++)
            {
                if(loop == 1)
                {
                    for(row = userInRow - 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;

                    }
                }

                else if(loop == 2)
                {
                    for(row = userInRow + 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 3)
                {
                    for(row = userInRow - 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 4)
                {
                    for(row = userInRow + 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

            }

            if(avai_Loc_Count == 0)
            {
                printf("Moving block...\nTryAgain...");
                _getch();
                continue;
            }

            changeMoving();

            if(cancel_select == 51 || cancel_select == 19)
                continue;


        }/// B moving.. last brace:

        else if(input == 'Q')
        {
            printf("\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 8; loop++)
            {

                if(loop == 1)
                {
                    for(row = userInRow - 1; row >= 1; row--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 2)
                {
                    for(row = userInRow + 1; row <= 8; row++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 3)
                {
                    row = userInRow;
                    for(col = userInCol - 1; col >= 1; col--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 4)
                {
                    for(col = userInCol + 1; col <= 8; col++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }
                else if(loop == 5)
                {
                    for(row = userInRow - 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;

                    }
                }

                else if(loop == 6)
                {
                    for(row = userInRow + 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 7)
                {
                    for(row = userInRow - 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col++)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 8)
                {
                    for(row = userInRow + 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col--)
                    {
                        int result = searchingAvailable_Loc(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

            }



            if(avai_Loc_Count == 0)
            {
                printf("Moving block...\nTryAgain...");
                _getch();
                continue;
            }

            changeMoving();

            if(cancel_select == 51 || cancel_select == 19)
                continue;


        }/// Q moving.. last brace:

        break;
    }

    return;

} /// Your turn End:


/// Game starting point

void gameStartingMode()
{
    Troop[1][1] = 'r';
    Troop[1][2] = 'n';
    Troop[1][3] = 'b';
    Troop[1][4] = 'q';
    Troop[1][5] = 'k';
    Troop[1][6] = 'b';
    Troop[1][7] = 'n';
    Troop[1][8] = 'r';
    Troop[2][1] = '0';
    Troop[2][2] = '0';
    Troop[2][3] = '0';
    Troop[2][4] = '0';
    Troop[2][5] = '0';
    Troop[2][6] = '0';
    Troop[2][7] = '0';
    Troop[2][8] = '0';
    Troop[3][1] = ' ';
    Troop[3][2] = ' ';
    Troop[3][3] = ' ';
    Troop[3][4] = ' ';
    Troop[3][5] = ' ';
    Troop[3][6] = ' ';
    Troop[3][7] = ' ';
    Troop[3][8] = ' ';
    Troop[4][1] = ' ';
    Troop[4][2] = ' ';
    Troop[4][3] = ' ';
    Troop[4][4] = ' ';
    Troop[4][5] = ' ';
    Troop[4][6] = ' ';
    Troop[4][7] = ' ';
    Troop[4][8] = ' ';
    Troop[5][1] = ' ';
    Troop[5][2] = ' ';
    Troop[5][3] = ' ';
    Troop[5][4] = ' ';
    Troop[5][5] = ' ';
    Troop[5][6] = ' ';
    Troop[5][7] = ' ';
    Troop[5][8] = ' ';
    Troop[6][1] = ' ';
    Troop[6][2] = ' ';
    Troop[6][3] = ' ';
    Troop[6][4] = ' ';
    Troop[6][5] = ' ';
    Troop[6][6] = ' ';
    Troop[6][7] = ' ';
    Troop[6][8] = ' ';
    Troop[7][1] = 'P';
    Troop[7][2] = 'P';
    Troop[7][3] = 'P';
    Troop[7][4] = 'P';
    Troop[7][5] = 'P';
    Troop[7][6] = 'P';
    Troop[7][7] = 'P';
    Troop[7][8] = 'P';
    Troop[8][1] = 'R';
    Troop[8][2] = 'N';
    Troop[8][3] = 'B';
    Troop[8][4] = 'Q';
    Troop[8][5] = 'K';
    Troop[8][6] = 'B';
    Troop[8][7] = 'N';
    Troop[8][8] = 'R';

    ///p1_LostTroops

    p1[1] = ' ';
    p1[2] = ' ';
    p1[3] = ' ';
    p1[4] = ' ';
    p1[5] = ' ';
    p1[6] = ' ';
    p1[7] = ' ';
    p1[8] = ' ';
    p1[9] = ' ';
    p1[10] = ' ';
    p1[11] = ' ';
    p1[12] = ' ';
    p1[13] = ' ';
    p1[14] = ' ';
    p1[15] = ' ';

    ///p2_LostTroops

    p2[1] = ' ';
    p2[2] = ' ';
    p2[3] = ' ';
    p2[4] = ' ';
    p2[5] = ' ';
    p2[6] = ' ';
    p2[7] = ' ';
    p2[8] = ' ';
    p2[9] = ' ';
    p2[10] = ' ';
    p2[11] = ' ';
    p2[12] = ' ';
    p2[13] = ' ';
    p2[14] = ' ';
    p2[15] = ' ';

    /// This two variable are working for Lost troops count
    pl_1 = 1;
    pl_2 = 1;

}


void displayChessBoard()  /// Chess board print getch()
{
    printf("\n\n\t\t\t\t\t\t\tYou\t: Lost troops: %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n\n",p1[1],p1[2],p1[3],p1[4],p1[5],p1[6],p1[7],p1[8],p1[9],p1[10],p1[11],p1[12],p1[13],p1[14],p1[15]);
    printf("\t\t\t\t\t\t\tComputer: Lost troops: %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n",p2[1],p2[2],p2[3],p2[4],p2[5],p2[6],p2[7],p2[8],p2[9],p2[10],p2[11],p2[12],p2[13],p2[14],p2[15]);
    printf("\t\t\t  -----Chess-----\n\n");
    printf("\t     1     2     3     4     5     6     7     8\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t1 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[1][1],Troop[1][2],Troop[1][3],Troop[1][4],Troop[1][5],Troop[1][6],Troop[1][7],Troop[1][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t2 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[2][1],Troop[2][2],Troop[2][3],Troop[2][4],Troop[2][5],Troop[2][6],Troop[2][7],Troop[2][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t3 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[3][1],Troop[3][2],Troop[3][3],Troop[3][4],Troop[3][5],Troop[3][6],Troop[3][7],Troop[3][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t4 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[4][1],Troop[4][2],Troop[4][3],Troop[4][4],Troop[4][5],Troop[4][6],Troop[4][7],Troop[4][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t5 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[5][1],Troop[5][2],Troop[5][3],Troop[5][4],Troop[5][5],Troop[5][6],Troop[5][7],Troop[5][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t6 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[6][1],Troop[6][2],Troop[6][3],Troop[6][4],Troop[6][5],Troop[6][6],Troop[6][7],Troop[6][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t7 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[7][1],Troop[7][2],Troop[7][3],Troop[7][4],Troop[7][5],Troop[7][6],Troop[7][7],Troop[7][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t8 .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .  %c  .\n",Troop[8][1],Troop[8][2],Troop[8][3],Troop[8][4],Troop[8][5],Troop[8][6],Troop[8][7],Troop[8][8]);
    printf("\t  .     .     .     .     .     .     .     .     .\n");
    printf("\t  .................................................\n");
}

/// This function working for location search for every troops

int searchingAvailable_Loc(int row, int col)
{
    int loop;
    for(loop = 0; loop < kingMoveAvaiCount; loop++)
    {
        if(kingmoveRow[loop] == row && kingmoveCol[loop] == col)
            return 1;
    }

    if(Troop[row][col] == ' ' || Troop[row][col] == '0' || Troop[row][col] == 'q' || Troop[row][col] == 'r' || Troop[row][col] == 'b' || Troop[row][col] == 'n')
    {
        if(Troop[row][col] == ' ')
        {
            avai_Loc_Row[x++] = row;
            avai_Loc_Col[y++] = col;
            Troop[row][col] = '*';
            avai_Loc_Count++;
            return 1;
        }
        else
        {
            avai_Loc_Row[x++] = row;
            avai_Loc_Col[y++] = col;
            avai_Loc_Count++;
            return 0;
        }

    }
    else
        return 0;
}

///  This function working for troops location change

void changeMoving()
{
    printf("\n");

    system("cls");
    displayChessBoard();
    int l;
    for(l = 0; l < avai_Loc_Count; l++)
    {
        if(Troop[avai_Loc_Row[l]][avai_Loc_Col[l]] == '*')
            Troop[avai_Loc_Row[l]][avai_Loc_Col[l]] = ' ';
    }
    printf("Available: ");
    for(l = 0; l < avai_Loc_Count; l++)
        printf("(%d,%d)  ",avai_Loc_Row[l],avai_Loc_Col[l]);
    printf("\n");
    printf("Enter move location : ");
    while(1)
    {
        int row,col,ck = 0;
        row = (int)_getch() - 48;
        cancel_select = row;
        printf("%d,",row);
        if(cancel_select == 51 || cancel_select == 19)
            break;
        col = (int)_getch() - 48;
        printf("%d  ",col);

        for(l = 0; l < avai_Loc_Count; l++)
        {
            if(row == avai_Loc_Row[l] && col == avai_Loc_Col[l])
            {
                if(Troop[avai_Loc_Row[l]][avai_Loc_Col[l]] != ' ')
                    p2[pl_2++] = Troop[avai_Loc_Row[l]][avai_Loc_Col[l]];

                if(Troop[userInRowCollect][userInColCollect] == 'K')
                    Troop[row][col] = 'K';
                else if(Troop[userInRowCollect][userInColCollect] == 'P')
                    Troop[row][col] = 'P';
                else if(Troop[userInRowCollect][userInColCollect] == 'R')
                    Troop[row][col] = 'R';
                else if(Troop[userInRowCollect][userInColCollect] == 'N')
                    Troop[row][col] = 'N';
                else if(Troop[userInRowCollect][userInColCollect] == 'B')
                    Troop[row][col] = 'B';
                else if(Troop[userInRowCollect][userInColCollect] == 'Q')
                    Troop[row][col] = 'Q';

                Troop[userInRowCollect][userInColCollect] = ' ';
                ck = 1;
                break;
            }
        }
        if(ck)
            break;
    }

    printf("\n");
}

void kingMove()
{
    int row,col,ck = 0;

    for(row = 1; row <= 8; row++)
    {
        for(col = 1; col <= 8; col++)
        {
            if(turnCheck)
            {
                if(Troop[row][col] == 'k')
                {
                    ck = 1;
                    break;
                }
            }
            else
            {
                if(Troop[row][col] == 'K')
                {
                    ck = 1;
                    break;
                }
            }

        }
        if(ck)
            break;
    }

    int r = row,c = col,loop,a = 0,b = 0;

    for(loop = 1; loop <= 8; loop++)
    {
        if(loop == 1)
        {
            r--;
            c--;
        }
        else if(loop == 2)
            c++;
        else if(loop == 3)
            c++;
        else if(loop == 4)
        {
            r = row;
            c = col - 1;
        }
        else if(loop == 5)
            c += 2;
        else if(loop == 6)
        {
            r = row + 1;
            c = col - 1;
        }
        else if(loop == 7)
            c++;
        else if(loop == 8)
            c++;

        if(r < 1 || 8 < r || c < 1 || 8 < c)
            continue;

        kingMoveAvaiCount++;
        kingmoveRow[a++] = r;
        kingmoveCol[b++] = c;

    }

}

/// Computer turn part:


void computerTurn()
{
    while(1)
    {
        avai_Loc_Row[32],avai_Loc_Col[32],x = 0,y = 0,avai_Loc_Count = 0,kingMoveAvaiCount = 0;
        char input;

        system("cls");
        displayChessBoard();
        printf("Computer thinking...\nPlease wait!");

        while(1)
        {
            randomInput();

            input = Troop[userInRow][userInCol];

            if(input == 'k' || input == '0' || input == 'r' || input == 'n' || input == 'b' || input == 'q')
            {
                if(input == 'k')
                {
                    turnCheck = 0;
                    kingMove();
                }
                break;
            }
            else
            {
                continue;
            }
        }

        /// Troops checking start point...

        if(input == 'k')
        {
            printf("\n\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;
            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 8; loop++)
            {
                if(loop == 1)
                {
                    row--;
                    col--;
                }
                else if(loop == 2)
                    col++;
                else if(loop == 3)
                    col++;
                else if(loop == 4)
                {
                    row = userInRow;
                    col = userInCol - 1;
                }
                else if(loop == 5)
                    col += 2;
                else if(loop == 6)
                {
                    row = userInRow + 1;
                    col = userInCol - 1;
                }
                else if(loop == 7)
                    col++;
                else if(loop == 8)
                    col++;

                if(row < 1 || 8 < row || col < 1 || 8 < col)
                    continue;

                searchingAvailableComputer(row,col);
            }

            if(avai_Loc_Count == 0)
                continue;

            changeMovingComputer();

        }  /// k moving...last brace:

        else if(input == '0')
        {
            printf("\n\n");
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            if(Troop[++userInRow][++userInCol] == 'P' || Troop[userInRow][userInCol] == 'Q' || Troop[userInRow][userInCol] == 'R' || Troop[userInRow][userInCol] == 'B' || Troop[userInRow][userInCol] == 'N')
            {
                avai_Loc_Row[x++] = userInRow;
                avai_Loc_Col[y++] = userInCol;
                avai_Loc_Count++;
            }
            if(Troop[userInRow][--userInCol] == ' ')
            {
                avai_Loc_Row[x++] = userInRow;
                avai_Loc_Col[y++] = userInCol;
                avai_Loc_Count++;
                Troop[userInRow][userInCol] = '*';

                if(userInRowCollect == 2)
                {
                    if(Troop[++userInRow][userInCol] == ' ')
                    {
                        avai_Loc_Row[x++] = userInRow;
                        avai_Loc_Col[y++] = userInCol;
                        avai_Loc_Count++;
                        Troop[userInRow][userInCol] = '*';
                        userInRow--;
                    }
                }
            }
            if(Troop[userInRow][--userInCol] == 'P' || Troop[userInRow][userInCol] == 'Q' || Troop[userInRow][userInCol] == 'R' || Troop[userInRow][userInCol] == 'B' || Troop[userInRow][userInCol] == 'N')
            {
                avai_Loc_Row[x++] = userInRow;
                avai_Loc_Col[y++] = userInCol;
                avai_Loc_Count++;
            }

            if(avai_Loc_Count == 0)
                continue;

            changeMovingComputer();

        }  /// 0 moving...last brace:

        else if(input == 'r')
        {
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 4; loop++)
            {
                if(loop == 1)
                {
                    for(row = userInRow - 1; row >= 1; row--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 2)
                {
                    for(row = userInRow + 1; row <= 8; row++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 3)
                {
                    row = userInRow;
                    for(col = userInCol - 1; col >= 1; col--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 4)
                {
                    for(col = userInCol + 1; col <= 8; col++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

            }

            if(avai_Loc_Count == 0)
                continue;

            changeMovingComputer();

        }/// r moving.. last brace:

        else if(input == 'n')
        {
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 8; loop++)
            {
                if(loop == 1)
                {
                    row = userInRow - 2;
                    col = userInCol - 1;
                }
                else if(loop == 2)
                {
                    row = userInRow - 2;
                    col = userInCol + 1;
                }
                else if(loop == 3)
                {
                    row = userInRow - 1;
                    col = userInCol + 2;
                }
                else if(loop == 4)
                {
                    row = userInRow + 1;
                    col = userInCol + 2;
                }
                else if(loop == 5)
                {
                    row = userInRow + 2;
                    col = userInCol + 1;
                }
                else if(loop == 6)
                {
                    row = userInRow + 2;
                    col = userInCol - 1;
                }
                else if(loop == 7)
                {
                    row = userInRow + 1;
                    col = userInCol - 2;
                }
                else if(loop == 8)
                {
                    row = userInRow - 1;
                    col = userInCol - 2;
                }
                if(row < 1 || 8 < row || col < 1 || 8 < col)
                    continue;

                searchingAvailableComputer(row,col);

            }

            if(avai_Loc_Count == 0)
                continue;

            changeMovingComputer();

        }/// n Moving..last brace:

        else if(input == 'b')
        {
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row,col,loop;
            for(loop = 1; loop <= 4; loop++)
            {
                if(loop == 1)
                {
                    for(row = userInRow - 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;

                    }
                }

                else if(loop == 2)
                {
                    for(row = userInRow + 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 3)
                {
                    for(row = userInRow - 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 4)
                {
                    for(row = userInRow + 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

            }

            if(avai_Loc_Count == 0)
                continue;

            changeMovingComputer();

        }/// b moving.. last brace:

        else if(input == 'q')
        {
            userInRowCollect = userInRow;
            userInColCollect = userInCol;

            int row = userInRow,col = userInCol,loop;
            for(loop = 1; loop <= 8; loop++)
            {
                if(loop == 1)
                {
                    for(row = userInRow - 1; row >= 1; row--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 2)
                {
                    for(row = userInRow + 1; row <= 8; row++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 3)
                {
                    row = userInRow;
                    for(col = userInCol - 1; col >= 1; col--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 4)
                {
                    for(col = userInCol + 1; col <= 8; col++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }
                else if(loop == 5)
                {
                    for(row = userInRow - 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;

                    }
                }

                else if(loop == 6)
                {
                    for(row = userInRow + 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 7)
                {
                    for(row = userInRow - 1,col = userInCol + 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row--,col++)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

                else if(loop == 8)
                {
                    for(row = userInRow + 1,col = userInCol - 1; row >= 1 && 8 >= row && col >= 1 && 8 >= col; row++,col--)
                    {
                        int result = searchingAvailableComputer(row,col);
                        if(result)
                            continue;
                        else
                            break;
                    }
                }

            }

            if(avai_Loc_Count == 0)
            {
                continue;
            }

            changeMovingComputer();

        }/// q moving.. last brace:

        break;
    }

    return;


}/// Computer turn end point.getch()

/// This function is working troops location search

int searchingAvailableComputer(int row, int col)
{
    int l;
    for(l = 0; l < kingMoveAvaiCount; l++)
    {
        if(kingmoveRow[l] == row && kingmoveCol[l] == col)
            return 1;
    }

    if(Troop[row][col] == ' ' || Troop[row][col] == 'P' || Troop[row][col] == 'Q' || Troop[row][col] == 'R' || Troop[row][col] == 'B' || Troop[row][col] == 'N')
    {
        if(Troop[row][col] == ' ')
        {
            Troop[row][col] = '*';
            avai_Loc_Row[x++] = row;
            avai_Loc_Col[y++] = col;
            avai_Loc_Count++;
            return 1;
        }
        else
        {
            avai_Loc_Row[x++] = row;
            avai_Loc_Col[y++] = col;
            avai_Loc_Count++;
            return 0;
        }

    }
    else
        return 0;
}

/// This function is working troops move change

void changeMovingComputer()
{
    system("cls");
    displayChessBoard();
    printf("Computer turn : %d , %d\n",userInRowCollect,userInColCollect);
    int l;
    for(l = 0; l < avai_Loc_Count; l++)
    {
        if(Troop[avai_Loc_Row[l]][avai_Loc_Col[l]] == '*')
            Troop[avai_Loc_Row[l]][avai_Loc_Col[l]] = ' ';
    }
    printf("Available: ");
    for(l = 0; l < avai_Loc_Count; l++)
        printf("(%d,%d)  ",avai_Loc_Row[l],avai_Loc_Col[l]);
    printf("\nPlease press Enter : ");
    _getch();
    while(1)
    {
        int row,col,ck = 0;
        changeMovingRandom(&row,&col);
        //printf("move random = %d , %d \n",row,col);
        //getch();
        //continue;

        for(l = 0; l < avai_Loc_Count; l++)
        {
            if(row == avai_Loc_Row[l] && col == avai_Loc_Col[l])
            {
                if(Troop[avai_Loc_Row[l]][avai_Loc_Col[l]] != ' ')
                    p1[pl_1++] = Troop[avai_Loc_Row[l]][avai_Loc_Col[l]];

                if(Troop[userInRowCollect][userInColCollect] == 'k')
                    Troop[row][col] = 'k';
                else if(Troop[userInRowCollect][userInColCollect] == '0')
                    Troop[row][col] = '0';
                else if(Troop[userInRowCollect][userInColCollect] == 'r')
                    Troop[row][col] = 'r';
                else if(Troop[userInRowCollect][userInColCollect] == 'n')
                    Troop[row][col] = 'n';
                else if(Troop[userInRowCollect][userInColCollect] == 'b')
                    Troop[row][col] = 'b';
                else if(Troop[userInRowCollect][userInColCollect] == 'q')
                    Troop[row][col] = 'q';

                Troop[userInRowCollect][userInColCollect] = ' ';
                ck = 1;
                break;
            }
        }
        if(ck)
            break;
    }

}

void randomInput()
{
    /// For random input
    srand(time(NULL));

    int cm,cmTurn[3],z = 0;
    for(cm = 1; cm <= 2; cm++)
        cmTurn[z++] = (rand() % 8) + 1;
    userInRow = cmTurn[0];
    userInCol = cmTurn[1];

    return;

}

/// This function is working troops move randomly

void changeMovingRandom(int *row, int *col)
{
    int cm,cmTurn[3],z = 0;
    for(cm = 1; cm <= 2; cm++)
        cmTurn[z++] = (rand() % 8) + 1;
    *row = cmTurn[0];
    *col = cmTurn[1];

    return;
}

