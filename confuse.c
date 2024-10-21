#include <stdio.h>
#include <stdlib.h>

#define ROWS 6+1
#define COLS 6+1

FILE *mapf ;
char map[ROWS][COLS];
int srow, scol, erow, ecol; // เอาไว้เก็บพิกัด จุดเริ่มกับ จุดจบ
int currentrow, currentcol;
char FDirection = 'E'; // N E S W ทิดทางของด้านหน้า
char LFDirection;      // เอามาเก็บตัวแปรชั่วคราว
struct checkpoint{ // ไว้เก็บจุดที่มีแยก
    int row;
    int col;
    char Fdirection;
};
struct checkpoint cp[50]; // มี checkpoint 50 จุด
int cpcount =0; // จุดเซฟที่เท่าไหร่

#define Lcell map[currentrow][currentcol + 1]
#define Rcell map[currentrow][currentcol - 1]
#define Bcell map[currentrow + 1][currentcol]
#define Tcell map[currentrow - 1][currentcol]

int  main(){

    mapf = fopen("maptest.txt", "r");

    // Read the map from the file into the array
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            char ch = fgetc(mapf); // อ่านค่าทีละตัว
            map[r][c] = ch;        // มาเก็บใส่ Array
            if (ch == 's')
            {
                srow = r;
                scol = c;
            }
            if( ch == 'E'){
                erow = r;
                ecol = c;
            }
            
        }
    }


    
    // start map[srow][scol];
    currentcol = scol;
    currentrow = srow;
    // while ((map[currentrow][currentcol + 1] != 'E') &&
    //        (map[currentrow][currentcol - 1] != 'E') &&
    //        (map[currentrow + 1][currentcol] != 'E') &&
    //        (map[currentrow - 1][currentcol] != 'E'))
    for(int i =0 ; i <10; i++)
    {

        // check ถ้าเจอแยก
        int countway;
        if(Tcell == ' '){ countway++;}
        if(Bcell == ' '){ countway++;}
        if(Rcell == ' '){ countway++;}
        if(Lcell == ' '){ countway++;}
        if (countway >= 2)
        {
            cp[cpcount].row = currentrow;
            cp[cpcount].col = currentcol;
            cp[cpcount].Fdirection = FDirection;
            cpcount++;
        }
        

        // ถ้าเจอทางตัน
        if ((FDirection == 'N' && Lcell == ' ' && Tcell == ' ' && Rcell == ' ') ||
            (FDirection == 'E' && Tcell == ' ' && Rcell == ' ' && Bcell == ' ') ||
            (FDirection == 'S' && Rcell == ' ' && Bcell == ' ' && Lcell == ' ') ||
            (FDirection == 'W' && Tcell == ' ' && Lcell == ' ' && Bcell == ' '))
        {
            // ลบเส้นเก่าออก
            // กลับไปเชคพอยน์เก่า
            currentcol = cp[cpcount-1].col;
            currentrow = cp[cpcount-1].row;
            FDirection = 'W';
        }
        

        
        if (Rcell == ' ' && FDirection == 'E')
        {
            Rcell = '+';
            currentcol++;
        }
        else if (Lcell == ' ' && FDirection == 'W')
        {
            Lcell = '+';
            currentcol--;
        }
        else if (Tcell == ' ' && FDirection == 'N')
        {
            Tcell = '+';
            currentrow--;
            if (Tcell != ' ')
            {
                LFDirection = FDirection;
                FDirection = ' ';
            }
        }
        else if (Bcell == ' ' && FDirection == 'S')
        {
            map[currentrow + 1][currentcol] = '+';
            currentrow++;
        }


        // ถ้าเกิดชนกำแพง ให้เชคขวาก่อน
        if (FDirection == ' ' && LFDirection == 'N')
        { // ชนกำแพงเหนือ
            if (Rcell == ' ')
            {
                FDirection = 'E';
            }
            else if (Lcell == ' ')
            {
                FDirection = 'W';
            }
        } 

    }

    
    
    
    

    // Print the map to verify
    printf("Map stored in the array:\n");
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS - 1; c++)
        {
            printf("%c", map[r][c]); // Print the stored map
        }
        printf("\n");
    }

    return 0;
}
