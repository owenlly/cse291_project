#include<stdio.h>
int main ()
{
    int a = 1, b = 2, c = 3;
    int i;
    i = a*a*a + b*b*b + c*c*c + a*b*c;
    if (i < 0) {
        i++;
        i = i*i;
    }
    else {
        i = i*i;
    }
    printf("i = %d\n", i);
}