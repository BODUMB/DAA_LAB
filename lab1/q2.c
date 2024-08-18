#include <stdio.h>

int main(){
    int size=5;
    int arr[size];
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }

    int prefixsum[size];
    prefixsum[0]=arr[0];

    for(int i=1;i<size;i++){
        prefixsum[i]=prefixsum[i-1]+arr[i];
    }
    printf("\n");
    printf("Prefix array:");
    for(int i=0;i<size;i++){
        printf("%d ",prefixsum[i]);
    }
}