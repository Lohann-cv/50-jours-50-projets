#include <stdio.h>

int main()
{

    char choice = '\0';
    float fahrenheit = 0.0f;
    float celsius = 0.0f;

    printf("Temperature conversion program\n");
    printf("C. Celsius to fahrenheit\n");
    printf("F. Fahrenheit to celsius\n");
    printf("Is the temp in Celsius (C) or Fahrenheit (F) ?: ");
    scanf("%c", &choice);

    if (choice == 'C')
    {
        // C to F
        printf("Enter the temp in Celsius: ");
        scanf("%f", &celsius);
        fahrenheit = (celsius * 9 / 5) + 32;
        printf("%.1f Celsius is equal to %.1f farehent", celsius, fahrenheit);
    }
    else if (choice == 'F')
    {
        // Fto C
        printf("Enter the temp in Farenheit: ");
        scanf("%f", &fahrenheit);
        celsius = (fahrenheit - 32) * 5 / 9;
        printf("%.1f farhenti is equal to %.1f celsius", fahrenheit, celsius);
    }
    else
    {
        printf("Invalide choice ! Please select C or F\n");
    }
}