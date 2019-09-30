#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define R 20
#define C 50
int main()
{
  int i, j;   //INDICI VARI
  int win = 0; //FINE GIOCO
  float t = clock(); //INTERTEMPO PER REFLESH
  int m=6; //MOVIMENTI - INIZIALIZZATO VERSO DESTRA
  int l = 1; //LUNGHEZZA SERPENTE
  int flag = 0; //CIBO MANGIATO IN ITERAZIONE PRECEDENTE
  int tempr, tempc; //VARIABILI PER SCAMBIO POSIZIONI
  char mat[R][C]; //MATRICE
  struct snakes{
    int r;
    int c;
    struct snakes *next;
  }*snake,*coda;


  //GENERA MATRICE
  for (i=0; i<R; i++)
    for (j=0; j<C; j++){
        if (i==0||i==R-1 || j==0 || j==C-1)
            mat[i][j] = '#';
        else
            mat[i][j] = ' ';
    }
    snake = malloc(sizeof(struct snakes));
    coda = snake;
    snake->r = R/2;
    snake->c = 1;

    //SEME PER RANDOM
    srand(time(NULL));
    mat[1+rand()%(R-1)][1+rand()%(C-1)] = 'o';

    while (!win){

        if (clock()>=(t+200)){
            system("color 5f");
            system("cls");
            t = clock();

            //ESECUZIONE CONDIZIONATA A PRESSIONE TASTI
            if(kbhit()){
                m = getch()-48;
            }
            snake = coda;


            if (flag == 0)
            {
                for (i=0; i<l-1; i++){
                    snake->r = snake->next->r;
                    snake->c = snake->next->c;
                    snake = snake->next;
                    mat[snake->r][snake->c] = '*';
                }
            }
            else
            {
                flag = 0;
                mat[1+rand()%R][1+rand()%C] = 'o';
                for (i=0; i<l-1; i++, snake = snake->next)
                {
                    l++;
                    snake->next = malloc(sizeof(struct snakes));
                    tempr = snake->r;
                    tempc = snake->c;
                    snake = snake->next;
                    snake->r = tempr;
                    snake->c = tempc;
                }
            }

            switch (m){

                case 2:
                    snake->r++;
                    break;
                case 4:
                    snake->c--;
                    break;
                case 6:
                    snake->c++;
                    break;
                case 8:
                    snake->r--;
                    break;
            }
            if (mat[snake->r][snake->c] == '#' || mat[snake->r][snake->c] == '*'){
                win = 1;
                continue;
            }
            if (mat[snake->r][snake->c] == 'o')
                flag = 1;

            mat[snake->r][snake->c] = '*';


            //STAMPA
            for (i=0; i<R; i++){
                for (j=0; j<C; j++)
                    printf("%c", mat[i][j]);

                printf("\n");
            }
        }

    }
    return 0;
}
