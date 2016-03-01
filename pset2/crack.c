#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include<crypt.h>
#include<string.h>
#define _XOPEN_SOURCE
#include<unistd.h>

char alphabet[] = {"abcdefghijklmnopqrstuvwxyz0123456789"};
static const int alphabetSize = sizeof(alphabet) - 1;
const int maxpass=8;

int seconds;

void crypto(char *word, char *pass, char *salt)
    {
    if(strcmp(crypt(word,salt),pass)==0)
        {
        printf("\nCracking Succesful..:-)");
        printf("\nPassword :%s",word);
        printf("\nProgram executed in %d seconds.\n", (int) time(NULL) - seconds);
        exit(1);
        }
    }

void dictionary(char *pass,char *salt)
    {
    char word[20];
    memset(word, 0, 9);
    FILE *f;
    f=fopen("/usr/share/dict/words", "r"); 
    if (!f)
        {
        printf("Error opening the dictionary file.\n");y
        exit(1);
        }
    else
        {
        while (fgets(word,8,f))
            {
            crypto(word,pass,salt);
            }
        }
    }

void bruteImpl(char* word, int index, int maxDepth, char* pass, char *salt) 
{
    int i;
    for ( i = 0; i < alphabetSize; ++i)
    {
        word[index] = alphabet[i];

        if (index == maxDepth - 1) 
            {
            crypto(word,pass,salt);
            }
        else bruteImpl(word, index + 1, maxDepth, pass, salt);
    }
}

void brute(char* pass, char* salt)
    {
    char word[10];
    int i;
    for ( i = 1;i<=8;i++)
        {
        memset(word, 0, 9);
        bruteImpl(word, 0, i, pass, salt);
        }
    }

int main(int argc, char* argv[])
{
int c;
char salt[2];
if(argc!=2)
        {
        printf("Wrong input.....:(\n");
        exit(1);
        }
else
    {
    seconds = time(NULL);
    strncpy(salt, argv[1], 2);
    printf("Dictionary attack........");
    dictionary(argv[1],salt);
    printf("\nDictionary attack failed :-(");
    printf("\nStarting Brute Force Attack..");
    brute(argv[1],salt);
    printf("\nPassword could not be broken :-(\n");
    }
    
return 0;
}
