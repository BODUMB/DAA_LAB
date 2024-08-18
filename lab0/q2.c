// add elements of an array using recursion

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sum(int arr[],int n){
    if(n<=0) return 0;
    return (sum(arr,n-1)+arr[n-1]);
}

int main(){
   printf("enter the size of the array:");
   int n;
   scanf("%d",&n);
   printf("enter elements of the array:");
   int arr[n];
   for(int i=0;i<n;i++){
    scanf("%d",&arr[i]);
   }
   printf("Sum of elements of the array: %d",sum(arr,n));
   return 0;
}