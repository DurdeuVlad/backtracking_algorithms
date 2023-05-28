#include <stdio.h>


typedef struct {
    int v[100];
    int n;
}Sir;



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

int aparePos(Sir a, int n){
    for(int i=0;i<a.n;i++){
        if(a.v[i]==n) return 1;
    }
    return 0;
}


void bt(int n, Sir a, Sir maxime, Sir minime, int k, int pre, int arr[]){
    if(k>=n || k < 0){

        return;
    }
    if(pre==-1){
        bt(n, a, maxime, minime, k+1, k, arr);
        bt(n, a, maxime, minime, k-1, k, arr);
        return;
    }
    if(!aparePos(maxime, k)){
        arr[k]=arr[pre]-1;
        bt(n, a, maxime, minime, k-pre+k, k, arr);
    }
    if(!aparePos(minime, k)){
        arr[k]=arr[pre]+1;
        bt(n, a, maxime, minime, k-pre+k, k, arr);
    }


}



int main() {
    //int n=5, a=2, b=5,
    int arr[100] = {};

    //backtracking(n, a, b, arr, 0);
    int n = 7;
    Sir a = {{1}, 1};
    Sir maxime = {{0, 5}, 2};
    Sir minime = {{2, 6}, 2};
    int k=1;
    arr[k]=1;
    bt(n, a, maxime, minime, k, -1, arr);
    for(int i=0;i<n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
