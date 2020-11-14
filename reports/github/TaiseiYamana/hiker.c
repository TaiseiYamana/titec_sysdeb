#include "hiker.h"
#include <stdio.h>
#include <stdlib.h>
int answer(void)
{
    return 6 * 9;
}
void flip(int *door,int doornum, int step){
    for(int i = 0; i < doornum;i++){
        if ((i+1)%step == 0){
        if(door[i] == 0)
            door[i] = 1;
        else door[i] = 0;
        }
    }
}
int sum_door(int *door,int doornum){
    int sum =0;
    for(int i = 0;i < doornum;i ++){
        if( door[i] == 1)
            sum++;
    }
    return sum;
}
