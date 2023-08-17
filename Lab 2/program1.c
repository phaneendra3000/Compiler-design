
#include<stdio.h>

void move(char a,int *currentstate)
{
    if(*currentstate == 10)
    {
        if(a == '1')
        {
            *currentstate = 11;
        }else
        {
            *currentstate = 13;
        }
    }else if(*currentstate == 11)
    {
         if(a == '1')
        {
            *currentstate = 10;
        }else
        {
            *currentstate = 12;
        }
    }else if(*currentstate == 12)
    {
         if(a == '1')
        {
            *currentstate = 13;
        }else
        {
            *currentstate = 11;
        }
    }else if(*currentstate == 13)
    {
         if(a == '1')
        {
            *currentstate = 12;
        }else
        {
            *currentstate = 10;
        }
    }
}
int main() {
   
    char string[100];
    scanf("%s",&string);
    int i = 0;
    int currentstate = 10;
    int q0 = 10;

    while(string[i]!='\0')
    {
        move(string[i],&currentstate);
        
        i++;
    }
    if(currentstate==q0)
    {
        printf("ACCEPTED");
    }else
    {
        printf("REJECTED");
    }
    return 0;
}