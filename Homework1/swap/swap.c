#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");
    int a, b;
    printf("Введите 2 числа\n");
    scanf("%d", &a);
    scanf("%d", &b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("%d %d", a, b);
}

