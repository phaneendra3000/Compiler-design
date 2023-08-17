#include<stdio.h>
int main()
{
    char string[100];
    scanf("%s",&string);
    int i = 0;
    while(string[i+2]!='\0')
    {
        i++;
    }
    if(string[i]== string[i+1])
    {
        printf("ACCEPTED");
    }else{
        printf("REJECTED");
    }
}