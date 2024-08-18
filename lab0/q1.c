// print n nos using recursion

#include<stdio.h>
#include<stdlib.h>

void recur(int n){
    if(n==0) return;
    else printf("%d ",n);
    n--;
    recur(n);
}

int main(){
    int n;
    printf("enter a no");
    scanf("%d",&n);
    recur(n);
}