#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// �P�_�O�_�����H�~���B�⤸
int is_operator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
}

// �^�ǹB�⤸������
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

// �J��B�⤸���X��ӼƦr�X�ӭp��
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

// �ǤJinfix���X���G
double result(char infix[MAX])
{

    int operand_top = 0;  // �B��l������
    int operator_top = 0; // �B�⤸������
    int index = 0;        // infix�����ޭ�
    double ope_rand[MAX]; // �ΨӦs��B��l�����|
    char ope_rator[MAX];  // �ΨӦs��B�⤸�����|

    while (index < strlen(infix) - 1)
    {

        // �P�_�Ʀr
        if (isdigit(infix[index]))
        {

            // ��atof�N���V�r��infix����index����}�ǤJ�A�N�i���몺�Ʀr�r����B�I�ơA�s�J�B��l���|
            ope_rand[operand_top++] = atof(infix + index);

            index++;

            // ���L�wŪ�L���Ʀr
            while (infix[index] == '.' || isdigit(infix[index]))
            {
                index++;
            }
        }

        // �P�_+-*/%^
        else if (is_operator(infix[index]))
        {

            // ��B�⤸���|���A�B�⤸������>=infix���B�⤸������
            while (priority(ope_rator[operator_top - 1]) >= priority(infix[index]))
            {

                // ���N�̤W�h����ӹB��l�M�@�ӹB�⤸���X�ӹB��
                double operand2 = ope_rand[--operand_top]; // ��--�O�]���e���s�J����++
                double operand1 = ope_rand[--operand_top];
                char op = ope_rator[--operator_top];

                // �B�⵲�G��^�B��l�̤W�h���|
                ope_rand[operand_top++] = cal(op, operand1, operand2);
            }

            // �B�z����N�B��l�s�J�B��l���|
            if (operator_top >= 0)
            {
                ope_rator[operator_top++] = infix[index];
            }

            index++;
        }

        // ��J��'('�����s�J�B��l���|
        else if (infix[index] == '(')
        {
            ope_rator[operator_top++] = infix[index];

            index++;
        }

        // ��J��')'�A�N�B��l���|�����B�⤸���X�ӹB��A����J��'('
        else if (infix[index] == ')')
        {
            while (ope_rator[operator_top - 1] != '(')
            {
                double operand2 = ope_rand[--operand_top];
                double operand1 = ope_rand[--operand_top];
                char op = ope_rator[--operator_top];

                ope_rand[operand_top++] = cal(op, operand1, operand2);
            }

            // ��'('����
            operator_top--;

            index++;
        }
    }

    // ��ѤU���B�ⰵ��
    while (operator_top > 0)
    {

        double operand2 = ope_rand[--operand_top];
        double operand1 = ope_rand[--operand_top];
        char op = ope_rator[--operator_top];

        ope_rand[operand_top++] = cal(op, operand1, operand2);
    }

    // �B�⵲�G�|�b�B��l���|[0]
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