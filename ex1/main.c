#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int x, y;
}Point;

void citireFisier(Point *size, char lab[100][100], Point *start, Point *finish){
    FILE * IN = fopen("labirint.in", "r");
    fscanf(IN, "%d %d", &((*size).x), &((*size).y));
    for(int i=0;i<(*size).x;i++){
        fscanf(IN, "%s", lab[i]);
    }

    fscanf(IN,"%d %d", &(*start).x, &(*start).y);

    fscanf(IN,"%d %d", &(*finish).x, &(*finish).y);

    fclose(IN);
}

int comparePoints(Point a, Point b){
    if(a.x==b.x && a.y == b.y)
        return 1;
    return 0;
}

void printStack(Point stack[], int n){
//    for(int i=0;i<n;i++){
//        printf("%d %d\n", stack[i].x, stack[i].y);
//    }
    printf("%d\n", n);

}

int isPointInStack(Point stack[], int n, Point p){
    for(int i=0;i<n;i++){
        if(comparePoints(stack[i], p))
            return 1;
    }
    return 0;
}


void backtracking(Point stack[], int n, Point final, char lab[100][100], Point intersections[], int* interN){
    if(comparePoints(stack[n], final)){
        printf("FOUND A WAY: ");
        printStack(stack, n);
        for(int i=1;i<n-1;i++){
            lab[stack[i].x][stack[i].y] = '0';
        }
        for(int i=0;i<(*interN);i++){
            lab[intersections[i].x][intersections[i].y] = '1';
        }
        *interN = 0;
        return;
    }
    // add all the possible moves to the stack
    int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    for(int i=0;i<4;i++){
        if(i>0 && comparePoints(stack[n], intersections[i-1])){
            printf("FOUND AN INTERSECTION: ");
            printStack(stack, n);
            //add the intersection to the stack
            intersections[*interN] = stack[n];
            (*interN)++;
        }
        Point newPoint;
        newPoint.x = stack[n].x + directions[i][0];
        newPoint.y = stack[n].y + directions[i][1];
        if(newPoint.x>=0 && newPoint.x<100 && newPoint.y>=0 && newPoint.y<100){
            if(lab[newPoint.x][newPoint.y] == '1' && isPointInStack(stack, n, newPoint)==0) {
                stack[n + 1] = newPoint;
                backtracking(stack, n + 1, final, lab, intersections, interN);
            }
        }
    }
    //printf("NO WAY");
    //printStack(stack, n);
}

int main() {
    Point size, start, finish;
    char lab[100][100];
    citireFisier(&size, lab, &start, &finish);
    Point stack[10000];
    stack[0] = start;
    lab[start.x][start.y] = '1';
    lab[finish.x][finish.y] = '1';
    Point intersections[100];
    int interN = 0;

    backtracking(stack, 0, finish, lab, intersections, &interN);
    return 0;
}
