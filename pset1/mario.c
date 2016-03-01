#include<stdio.h>
#include<cs50.h>

int main()
{
int i,j,n,c=1;
printf("Height: ");
n=GetInt();
while(n>23 || n<0)
    { 
    printf("Height between 0 and 23. Try again: ");
    n=GetInt();
    }

    while(n)
    {
    for(i=1;i<n;i++)
        printf(" ");
    for(j=1;j<=c;j++)
        printf("#");
    printf("  ");
    for(j=1;j<=c;j++)
        printf("#");
    printf("\n");
    c++;
    n--;
    }

return 0;
}
