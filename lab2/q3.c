#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int main(){
    int N;
    printf("Enter the size of the array : ");
    scanf("%d", &N);

    int a[N];

    int main = INT_MIN;

    FILE *fptr = fopen("q2.txt","w");

    if(fptr == NULL){
        printf("error writng in file\n");
        return 1;
    }


    // for(int i=0;i<N;i++){
    //     a[i] = rand();
    //     fprintf(fptr,"%d",a[i]);
    // }
    // printf("\n");

    int lowerbound = 1;
    int upperbound = 100;
    
    for(int i=0;i<N;i++){
        a[i] = rand()%(upperbound-lowerbound+1)+lowerbound;
        fprintf(fptr,"%d ",a[i]);
    }
}
