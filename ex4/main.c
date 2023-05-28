#include <stdio.h>

void backtracking(int n, int a, int b, int arr[], int k) {
    if(k>=n){
            for(int i=0;i<k;i++){
                printf("%d ", arr[i]);
            }
            printf("\n");
        return;
    }
    if(k==0){
        for(int i=a+1; i<b;i++){
            arr[0] = i;
            backtracking(n, a, b, arr, 1);
        }
        return;
    }
    arr[k]=arr[k-1]-1;
    backtracking(n, a, b, arr, k+1);
    arr[k]=arr[k-1]+1;
    backtracking(n, a, b, arr, k+1);

}


int main() {
    int n=5, a=2, b=5, arr[1000];

    backtracking(n, a, b, arr, 0);

    return 0;
}
