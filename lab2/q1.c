#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


int main()
{
    int N;
    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &N);

    int a[N];

    FILE *fptr = fopen("q1.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        free(a); // Free the allocated memory before returning
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(fptr, "%d", &a[i]) != 1) {
            printf("Error reading file.\n");
            fclose(fptr);
            free(a); // Free the allocated memory before returning
            return 1;
        }
    }

    for(int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    FILE *f = fopen("q11.txt","w");
    printf("Enter how mant nos you want to write in disc file from the array");
    int k;
    scanf("%d",&k);

    if(f == NULL){
        printf("error writing in file");
        return 1;
    }

    for (int i = 0; i < k; i++) {
        fprintf(f, "%d ", a[i]);
    }

    fclose(fptr);



}