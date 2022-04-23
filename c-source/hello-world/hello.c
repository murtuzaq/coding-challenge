#include <stdio.h>

int main(void)
{
    printf("Enter you name:");
    char name[50];
    scanf("%s", name);
    printf("Hello %s", name);
    
    return 0;
}