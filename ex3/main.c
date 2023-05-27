#include <stdio.h>

typedef struct {
    int x, y;
} Point;

void readFromFile(Point* size, int a[100][100], Point* start){
    FILE *f = fopen("input.txt", "r");
    fscanf(f, "%d %d", &size->x, &size->y);
    for(int i = 0; i < size->x; i++){
        for(int j = 0; j < size->y; j++){
            fscanf(f, "%d", &a[i][j]);
        }
    }
    fscanf(f, "%d,%d", &start->x, &start->y);
    fclose(f);
}

void printSolutionVector(Point solution[100], int n){
    for(int i = 0; i < n; i++){
        printf("%d %d\n", solution[i].x, solution[i].y);
    }
}

int recursiveBackTracking(Point solution[100], int n, Point size, int a[100][100]){
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for(int i = 0; i < 4; i++){
        Point next = {solution[n - 1].x + directions[i][0], solution[n - 1].y + directions[i][1]};
        if(next.x >= 0 && next.x < size.x && next.y >= 0 && next.y < size.y && a[next.x][next.y] < a[solution[n - 1].x][solution[n - 1].y]){
            solution[n] = next;
            return recursiveBackTracking(solution, n + 1, size, a);
        }
    }
    return n;
}


int main() {
    int a[100][100], n = 0;
    Point size, start;
    readFromFile(&size, a, &start);
    Point solution[100];
    solution[n++] = start;
    n = recursiveBackTracking(solution, n, size, a);
    printSolutionVector(solution, n);
    return 0;
}
