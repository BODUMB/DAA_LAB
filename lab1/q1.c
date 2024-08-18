#include <stdio.h>
#include <stdlib.h>

int main(){
    int size = 5;
    int arr[size];
    
    printf("Enter array elemnets:");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    int lar=arr[0];

    for(int i=0;i<size;i++){
        if(arr[i]>lar){
            lar=arr[i];
        }
        
    }
    printf("%d",lar);
    printf("\n");

    int sl=0,pl=0;

    for(int i=0;i<size;i++){
        if(arr[i]<lar){
            pl=sl;
            sl=arr[i];
            
            if(pl>sl){
                sl=pl;
            }
        }
    }
    printf("second largest no. : %d",sl);

    int small = arr[0];
    printf("\n");

    for(int i=0;i<size;i++){
        if(arr[i]<small){
            small = arr[i];
        }
    }

    printf("%d",small);
    printf("\n");

    int ss = arr[0];
    int ps = 0;

    for(int i=0;i<size;i++){
        if(arr[i]>small){
            ps = ss;
            ss = arr[i];
            
            if(ps < ss){
                ss = ps;
            }
        }
    }
    printf("second smallest no. : %d",ss);

}