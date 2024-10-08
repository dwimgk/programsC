#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int change;
    int coincount=0;
    do {
        change = get_int("Change owed: ");
    } while (change < 0);

    do {
        //quarter
        if(change-25 >=0 ){
            change=change-25;
            coincount++;
        }
        //dimes
        else if(change-10>=0){
            change-=10;
            coincount++;
        }
        //nickel
        else if(change-5>=0){
            change-=5;
            coincount++;
        }
        //penny
        else if(change-1>=0){
            change-=1;
            coincount++;
        }

    } while (change > 0);
    printf("Change returned fully\n");
    printf("Coins used: %d\n", coincount);
}
