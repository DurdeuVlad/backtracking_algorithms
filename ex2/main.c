#include <stdio.h>
#include <string.h>
#include <malloc.h>


typedef struct Stiva {
    int linie;
    int coloana;
    int valoare;
    struct Stiva * next;
} stiva;

void push(stiva ** top, int linie, int coloana, int valoare) {
    stiva * nou = (stiva *)malloc(sizeof(stiva));

    nou->linie = linie;
    nou->coloana = coloana;
    nou->valoare = valoare;
    nou->next = *top;
    *top = nou;
}

stiva * pop(stiva ** top) {
    stiva * aux = *top;
    *top = (*top)->next;
    return aux;
}

void readMatrix(char matrix[10][10]) {
    int i, j;
    FILE * IN = fopen("matrix.txt", "r");
    if(IN == NULL) {
        printf("Error opening file\n");
        return;
    }
    char aux;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++)
           fscanf(IN, "%c ", &matrix[i][j]);
        fscanf(IN, "\n", aux);
    }
    fclose(IN);
}

void printMatrix(char matrix[10][10]) {
    int i, j;
    for(i = 0; i < 9; i++) {
        for(j = 0; j < 9; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }
}

int checkColumn(char matrix[10][10], int column, char number) {
    int i;
    for(i = 0; i < 10; i++)
        if(matrix[i][column] == number)
            return 0;
    return 1;
}

int checkLine(char matrix[10][10], int line, char number) {
    int i;
    for(i = 0; i < 10; i++)
        if(matrix[line][i] == number)
            return 0;
    return 1;
}

int checkSquare(char matrix[10][10], int line, int column, char number) {
    int i, j;
    for(i = line; i < line + 3; i++)
        for(j = column; j < column + 3; j++)
            if(matrix[i][j] == number)
                return 0;
    return 1;
}


int fillSudokuBacktracking(char matrix[10][10]){
    int i, j, k=0;
    for(i = 0; i < 10; i++)
        for(j = 0; j < 10; j++)
            if(matrix[i][j] == '.'){
                int ok = 0;
                for(k; k <= 9; k++)

                    if(checkLine(matrix, i, k + '0') && checkColumn(matrix, j, k + '0') && checkSquare(matrix, i - i % 3, j - j % 3, k + '0')) {
                        matrix[i][j] = k + '0';
                        ok=1;
                    }
                if(ok==0){
                    if(j==0){
                        i--;
                        j=8;
                    }
                    else
                        j--;
                    k=matrix[i][j]-'0';
                } else
                    k=0;
            }
    return 1;
}


int fillSudokuBacktracking_recursiv(char matrix[10][10], int i, int j){
    int ok, k;
    for(k=1; k <= 9; k++){
        //printf("position %d %d: %d\n", i, j, k);
        if(checkLine(matrix, i, k + '0') && checkColumn(matrix, j, k + '0') && checkSquare(matrix, i - i % 3, j - j % 3, k + '0')) {

            matrix[i][j] = k + '0';
            //printMatrix(matrix);
            //printf("\n\n");
            if(i==8 && j==8)
                return 1;
            if(j==8)
                ok = fillSudokuBacktracking_recursiv(matrix, i+1, 0);
            else
                ok = fillSudokuBacktracking_recursiv(matrix, i, j+1);
            if(ok==1)
                return 1;
            else{
                matrix[i][j]='.';
            }
        }
    }

    return ok;
}



int main() {
    char matrix[10][10];
    readMatrix(matrix);
    printMatrix(matrix);
    printf("\n\n");
    fillSudokuBacktracking_recursiv(matrix, 0, 0);
    printMatrix(matrix);
    return 0;
}
