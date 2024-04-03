#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// 判斷是否為刮號以外的運算元
int is_operator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
}

// 回傳運算元的階級
int priority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// 遇到運算元後丟出兩個數字出來計算
double cal(char op, double c1, double c2)
{
    switch (op)
    {
    case '+':
        return c1 + c2;
    case '-':
        return c1 - c2;
    case '*':
        return c1 * c2;
    case '/':
        return c1 / c2;
    case '%':
        return fmod(c1, c2);
    case '^':
        return pow(c1, c2);
    default:
        return 0;
    }
}

// 傳入infix後輸出結果
double result(char infix[MAX])
{

    int operand_top = 0;  // 運算子的頂端
    int operator_top = 0; // 運算元的頂端
    int index = 0;        // infix的索引值
    double ope_rand[MAX]; // 用來存放運算子的堆疊
    char ope_rator[MAX];  // 用來存放運算元的堆疊

    while (index < strlen(infix) - 1)
    {

        // 判斷數字
        if (isdigit(infix[index]))
        {

            // 用atof將指向字串infix的第index的位址傳入，將可分辨的數字字元轉浮點數，存入運算子堆疊
            ope_rand[operand_top++] = atof(infix + index);

            index++;

            // 略過已讀過的數字
            while (infix[index] == '.' || isdigit(infix[index]))
            {
                index++;
            }
        }

        // 判斷+-*/%^
        else if (is_operator(infix[index]))
        {

            // 當運算元堆疊中，運算元的階級>=infix中運算元的階級
            while (priority(ope_rator[operator_top - 1]) >= priority(infix[index]))
            {

                // 先將最上層的兩個運算子和一個運算元拿出來運算
                double operand2 = ope_rand[--operand_top]; // 先--是因為前面存入都有++
                double operand1 = ope_rand[--operand_top];
                char op = ope_rator[--operator_top];

                // 運算結果放回運算子最上層堆疊
                ope_rand[operand_top++] = cal(op, operand1, operand2);
            }

            // 處理完後將運算子存入運算子堆疊
            if (operator_top >= 0)
            {
                ope_rator[operator_top++] = infix[index];
            }

            index++;
        }

        // 當遇到'('直接存入運算子堆疊
        else if (infix[index] == '(')
        {
            ope_rator[operator_top++] = infix[index];

            index++;
        }

        // 當遇到')'，將運算子堆疊中的運算元拿出來運算，直到遇到'('
        else if (infix[index] == ')')
        {
            while (ope_rator[operator_top - 1] != '(')
            {
                double operand2 = ope_rand[--operand_top];
                double operand1 = ope_rand[--operand_top];
                char op = ope_rator[--operator_top];

                ope_rand[operand_top++] = cal(op, operand1, operand2);
            }

            // 把'('移除
            operator_top--;

            index++;
        }
    }

    // 把剩下的運算做完
    while (operator_top > 0)
    {

        double operand2 = ope_rand[--operand_top];
        double operand1 = ope_rand[--operand_top];
        char op = ope_rator[--operator_top];

        ope_rand[operand_top++] = cal(op, operand1, operand2);
    }

    // 運算結果會在運算子堆疊[0]
    return ope_rand[0];
}

int main()
{

    char infix[MAX];

    while (1)
    {
        printf("Enter:\n");
        fgets(infix, MAX, stdin); // fgets(char *s, int n, FILE *stream)
        printf("Result:\n%g\n\n", result(infix));
    }
    return 0;
}