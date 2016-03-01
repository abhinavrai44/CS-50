#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int main()
{
char *c;
c=GetString();
int l,i;
l=strlen(c);
for(i=0;i<l;i++)
    {
    if((c[i-1]<65 || c[i-1]>122 || (c[i-1]>90 && c[i-1]<97)) && isalpha(c[i+1]) && isalpha(c[i]))
        printf("%c",toupper(c[i]));
    }
printf("\n");
return 0;
}
