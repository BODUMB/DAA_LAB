// find the time taken using cycles
#include<stdio.h>
#include<time.h>


int main(){
double sum = 0;
double add = 1;
clock_t start = clock();

// clock_t end = clock();

int iterations = 1000*1000*1000;
for(int i=0;i<iterations;i++){
        sum+=add;
        add/=2.0;
    }

clock_t end = clock();
end = clock()-start;
double time_taken = ((double)end)/CLOCKS_PER_SEC;
printf("result:%.20f\n",time_taken);
return 0;
}