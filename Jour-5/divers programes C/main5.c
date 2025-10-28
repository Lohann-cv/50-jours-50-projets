#include <stdio.h>

int main()
{

    int choice = 0;
    float pound = 0.0f;
    float kilograms = 0.0f;

    printf("Weight conversion calculator\n");
    printf("1. Kilograms to pounds\n");
    printf("2. Pounds to kilo\n");
    printf("Enter your choice 1 or 2: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        // kilo pound
        printf("Enter your weightin kilogrames: ");
        scanf("%f", &kilograms);
        pound = kilograms * 2.20462;
        printf("%.2f kilograms is equal to %.2f pounds\n", kilograms, pound);
    }
    else if (choice == 2)
    {
        // pounds to kilo
        printf("Enter your weight in pounds: ");
        scanf("%f", &pound);
        kilograms = pound * 2.20462;
        printf("%.2f pounds is equal to %.2f kilo\n", pound, kilograms);
    }
    else
    {
        printf("Invalide choice please enter 1 or 2\n");
    }
}