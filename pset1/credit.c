#include<cs50.h>
#include<stdio.h>

int main()
{
long long int n,z,z2,z3;
int r,x,c=0,s=0;
printf("Number: ");
n=GetLongLong();
z=n;
while(z>=100)
    {
        z=z/10;
        c++;
    }
c+=2;
z2=n/10;
z3=n;
while(z2)
    {
    r=z2%10;
    if(r>4)
        {
        r*=2;
        while(r)
            {
            x=r%10;
            s+=x;
            r/=10;
            }
        }
    else
    s+=(r*2);
    z2/=100;
    }
while(z3)
    {
    r=z3%10;
    s+=r;
    z3/=100;
    }
if(s%10==0) 
    {
    if(c==15 && (z==34 || z==37))
        printf("AMEX\n");
    else if (c==16 && (z==51 || z==52 || z==53 || z==54 || z==55))
        printf("MASTERCARD\n");
    else if((c==13 || c==16) && (z/10==4))
        printf("VISA\n");
    else printf("INVALID\n");
    }
else printf("INVALID\n");
return 0;
}
