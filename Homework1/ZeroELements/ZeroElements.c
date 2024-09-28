#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int zeroCounter(int massive[])
{
    int counter = 0;
    for (int i = 0; i < 10; i++)
    {
        if (massive[i] == 0)
        {
            counter++;
        }
    }
    return counter;
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int massive[10];
    printf("Введите элементы массива:\n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &massive[i]);

    }
    printf("Колличество нулей в массиве:%d", zeroCounter(massive));
}

