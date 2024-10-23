#include <cs50.h>
#include <stdio.h>

long AmericanExpress(long number, int count);
long Visa(long number, int count);
long MasterCard(long number, int count);
int CardValidizer(int sum, long number, int count);

int main(void)
{

    long number;
    do {
        number = get_long("Number: ");
    } while (number <= 0);
    long countcheck = number;

    int count=0;
    while (countcheck != 0)
    {
        countcheck /= 10;
        count++;
    }

    //american express
    if(count == 15)
    {
        AmericanExpress(number, count);
        printf("AmericanExpress\n");
    }
    //Visa
    else if(count == 13)
    {
        Visa(number, count);
        printf("Visa\n");
    }
    //mastercard
    else if(count == 16)
    {
        MasterCard(number, count);

    }
    return 0;
}

long AmericanExpress(long number, int count)
{ //15
int sum=0;
    int firstnums = number / 10000000000000;
        if(firstnums == 34 || firstnums == 37)
        {
            CardValidizer(sum, number, count);
        }
            return(0);
}
long Visa(long number, int count)
{ //13
int sum=0;
    int firstnum = number / 1000000000000;
        if(firstnum == 4)
        {
            CardValidizer(sum, number, count);
        }
        return 0;
}
long MasterCard(long number, int count)
{ //16
int sum=0;
    int visacheck = number / 1000000000000000;
    int firstnums = number / 100000000000000;
        if(visacheck == 4)
        {
            CardValidizer(sum, number, count);
                    printf("Visa\n");
        }
        if(firstnums == 51 || firstnums == 52 || firstnums == 53 || firstnums == 54 || firstnums == 55)
        {
            CardValidizer(sum, number, count);
                    printf("Mastercard\n");
        }
        return 0;
}

int CardValidizer(int sum, long number, int count)
{
    int sumOthers = 0;
    int momentary=0;

    for(int i=0; i <count; i++)
    {

        sumOthers += number % 10;
            number /=10;
        momentary += number % 10;
        momentary *=2;
        if(momentary>9){
            sum = sum + momentary%10 + momentary/10;
            //momentary=0;
        }
        else{
            sum +=momentary;
        }
            momentary=0;
            number = number /10;
    }
    sum = sum + sumOthers;
    //printf("%i\n",sum);

    if(sum%10==0){
        printf("Valid ");
    }
    else{printf("invalid\n");

    }

return(0);
}
