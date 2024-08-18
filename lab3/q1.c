// find CPU time  
#include<time.h>
#include<stdio.h>

int main(){

    double sum = 0;
    double add = 1;
    time_t begin,end;
    time(&begin);//stores surrent time in begin

    int iterations = 1000*1000*1000;
    for(int i=0;i<iterations;i++){
        sum+=add;
        add/=2.0;
    }
    
    time(&end);
    time_t elapsed = end-begin;
    printf("Time measured : %.2d second.\n",elapsed);
    return 0;
}