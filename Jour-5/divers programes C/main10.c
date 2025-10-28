#include <stdio.h>
#include <string.h>

void happyBirthday(char name[], int age)
{
    printf("\nHappy birthday to you!");
    printf("\nHappy birthday to you!");
    printf("\nHappy birthday dear %s!", name);
    printf("\nHappy birthday to you!");
    printf("\nYou are %d years old!\n", age);
}

int main()
{
    char name[50] = "";
    int age = 0;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';

    printf("Enter your age: ");
    scanf("%i", &age);

    happyBirthday(name, age);
    happyBirthday(name, age);
    happyBirthday(name, age);

    return 0;
}