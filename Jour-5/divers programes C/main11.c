#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

int main()
{

    int rows = 0;
    int columns = 0;
    char symbol = '\0';

    printf("Enter the # of rows: ");
    scanf("%d", &rows);

    printf("Enter the # of columns: ");
    scanf("%d", &columns);

    printf("Enter symbol to use: ");
    scanf(" %c", &symbol);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%c", symbol);
        }
        printf("\n");
    }

    return 0;
}