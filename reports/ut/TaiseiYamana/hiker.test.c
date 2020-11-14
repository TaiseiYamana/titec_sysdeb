#include "hiker.h"
#include <assert.h>
#include <stdio.h>

#define doornum 100
#define stepnum 3
static void test_flip(void)
{
  int door[doornum] = {0};
  int result[doornum] = {1,0,0,0,1,1,1,0,0,0};
  
  for(int i = 1 ;i <= stepnum;i++)
  flip(door ,doornum,i);
    
    
  for(int i = 0; i < doornum;i++)
      assert(door[i] == result[i]);
}
static void test_sum_door(void)
{
    int door[doornum] = {1,0,0,0,1,1,1,0,0,0};
    int sum;
    sum = sum_door(door,doornum);
    assert(4 == sum);
}
static void life_the_universe_and_everything(void)
{
    assert(answer() == 42);
}
int main(void)
{
    //life_the_universe_and_everything();
    //test_flip();
    //test_sum_door();
    //puts("All tests passed");
    
    int door[doornum] = {0};
    int sum;
    
    for(int i = 1 ;i <= stepnum;i++)
        flip(door ,doornum,i);
    
    sum = sum_door(door,doornum);
    
    printf("Opened Door: %d\n",sum);
}
