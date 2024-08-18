#include<stdio.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void Rotate_right(int *p1, int p2){
    if (p2 > 1) {
        // Swap the first element with the p2-th element
        EXCHANGE(&p1[0], &p1[p2-1]);
        
        // Now, shift the elements from index 1 to p2-2 to the right
        for (int i = p2-2; i > 0; i--) {
            EXCHANGE(&p1[i], &p1[i+1]);
        }
    }
}

int main(){
    printf("enter the size of the array");
    int n;
    scanf("%d",&n);

    printf("enter the elements of the array:");
    int A[n];
    for(int i=0;i<n;i++){
        scanf("%d",&A[i]);
    }

    printf("\n");

    printf("Before ROTATE: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }

    int p2;
    printf("enter the element position which is to be rotated");
    scanf("%d",&p2);

    Rotate_right(A,p2);

     printf("After ROTATE: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;



}