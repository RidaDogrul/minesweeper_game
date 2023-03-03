#include <stdio.h>
#include <stdlib.h>
#define SIZE_TABLE 8
#define NORMAL 7
#define WIN 1
#define LOST -1
#define CONTINUE 0


//global variables
int subtable[SIZE_TABLE+2][SIZE_TABLE+2];
char table[SIZE_TABLE+2][SIZE_TABLE+2];
int num_mines ,y=0;
int d_count=0;


void create_subtable();
void initialize_table();
void display_subtable();
void display_table();
void place_mines();
int verifymatchwin();
void explore();
int dig(int row, int column);

int main()
{
    int row,column;
    int progress;
    int again;
    char action;
    printf("Welcome to Our Minesweeper Game!\n");
    create_subtable();
    initialize_table();

    do
    {
        display_table();
        printf("\n");

        printf("please enter in this format:    c, row, column   or   d, row, column   or e, row, column\n");
        scanf("%c,%d,%d",&action,&row,&column);
        printf("\n");

        if(action== 'c'){

            progress= dig(row,column);

        }else if(action== 'd'){

            if(num_mines > d_count){

                d_count++;
                table[row][column] = 'D';
                progress=verifymatchwin();
            }


        }else if(action== 'e'){

            if(d_count > 0){

                d_count--;
            }

           table[row][column] = '#';

           progress=dig(row,column);
        }

        if(progress== LOST){

            printf("You lost the game!  \n");
            display_subtable();
            printf("Do you want to replay the game? [1= yes] [0= no] \n");
            scanf("%d" ,&again);
            switch(again){

            case 0:
                printf("Thank you, Have a nice day! \n");

                return 0;
                break;

            case 1:
                d_count=0;
                progress=CONTINUE;
                create_subtable();
                initialize_table();

                break;
                default: printf("You entered an incorrect value\n");
                break;

            }
        }


            if(progress== WIN){

              printf("Congratulations, You did a great job! \n");
              display_subtable();
            printf("Do you want to replay the game? [1= yes] [0= no] \n");
            scanf("%d" ,&again);
            switch(again){

            case 0:
                printf("Thank you, Have a nice day! \n");

                return 0;
                break;

            case 1:
                d_count=0;
                progress=CONTINUE;
                create_subtable();
                initialize_table();

                break;
                default: printf("You entered an incorrect value\n");
                break;
            }
            }


    }while(1);
    return 0;
}

void create_subtable(){

    int i,j , num_mines;

    for(i=0; i <= SIZE_TABLE +1; i++){

        for(j=0; j <= SIZE_TABLE +1; j++){

            subtable[i][j] = 0;

        }

    }
    for(i=0; i <= SIZE_TABLE +1; i++){
        subtable[i][0] = 1;
        subtable[i][SIZE_TABLE +1] = 1;

     }
      for(j=0; j <= SIZE_TABLE +1; j++){
            subtable[0][j] = 1;
            subtable[SIZE_TABLE +1][j] = 1;
        }

        num_mines=NORMAL;
        place_mines();
}

void initialize_table(){

     int i,j;

    for(i=0; i <= SIZE_TABLE +1; i++){

        for(j=0; j <= SIZE_TABLE +1; j++){

            table[i][j] = '#';

        }

    }
    for(i=0; i <= SIZE_TABLE +1; i++){
        table[i][0] = '*';
        table[i][SIZE_TABLE +1] = '*';

     }
      for(j=0; j <= SIZE_TABLE +1; j++){
           table[0][j] = '*';
           table[SIZE_TABLE +1][j] = '*';
        }

}

void display_table(){

    int i,j;
    printf("\n");

    for(i=1; i <= SIZE_TABLE; i++){
            printf("%3d",i);
    }
    printf("\n");


    for(i=1; i <= SIZE_TABLE ; i++){

        for(j=1; j <= SIZE_TABLE ; j++){

            printf("%3c",table[i][j]);

        }
        printf("  |%d",i);
        printf("\n");
    }
    for(i=1; i <= SIZE_TABLE ; i++){
        printf("---");
    }
}


void display_subtable(){
    int i,j;

    printf("\n");

    for(i=1;i<=SIZE_TABLE;i++){
        printf("%3d",i);
    }
    printf("\n");


    for(i=1;i<=SIZE_TABLE;i++){
        printf("---");
    }
    printf("\n");


    for(i=1;i<=SIZE_TABLE;i++){
        for(j=1;j<=SIZE_TABLE;j++){
            printf("%3d",subtable[i][j]);
    }
    printf(" |%d",i);
    printf("\n");
}

    for(i=1;i<=SIZE_TABLE;i++){
        printf("___");
    }
    printf("\n");
}


void place_mines(){

    srand(time(NULL));
    num_mines=NORMAL;
    int i,j,k,p,row,column;

     for(i=1; i <= num_mines ; i++){

            row=1+rand()%SIZE_TABLE;
            column=1+rand()%SIZE_TABLE;
     if(subtable[row][column] == -1)
        i--;
     subtable[row][column] == -1;
     for(k=-1;k<=1;k++){

        for(p=-1;p<=1;p++){

            if(subtable[i][j] == -1){

                if(subtable[row+k][column+p] != -1){
                    subtable[row+k][column+p]++;
                }
            }
       }

     }

}
}
int dig(int row, int column){

    int x=0;

      if(subtable[row][column]== -1){

         x= LOST;
      }else if(subtable[row][column]>0){

        table[row][column] = ('0'+subtable[row][column]);
        x=verifymatchwin();
        x=CONTINUE;
      }
      else{
        explore(row,column);
      }


    return x;

}


void explore(int row,int column){


    int i,j;
    table[row+i][column+j]= '0'+subtable[row+i][column+j];

    for(i=-1;i<=1;i++){

        for(j=-1;j<=1;j++){

            if(subtable[row+i][column+i]>0 && table[row+i][column+j] == '#'){

                table[row+i][column+j]= '0'+subtable[row+i][column+j];

            }
            else if(subtable[row+i][column+j]== 0 &&table[row+i][column+j]== '#'){

                explore(row+i,column+j);
            }
        }
    }


}

int verifymatchwin(){


     int i,j,y=0,status;

     for(i=1;i<=SIZE_TABLE;i++){

        for(j=1;j<=SIZE_TABLE;j++){

                if(table[i][j]== 'D'){
                    if(subtable[i][j] == -1){
                        y++;
                    }
                }
        }
     }



     if(y== NORMAL){

        status=WIN;
     }else

        status=CONTINUE;


     return status;
}
