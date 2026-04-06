#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>    /* Them: int32_t */

#define STACK_SIZE 100U

static double  g_stack[STACK_SIZE];
static int32_t g_top = -1;

static int32_t stack_push(double val)
{
    int32_t result = 0;

    if (g_top >= ((int32_t)STACK_SIZE - 1))
    {
        (void)fprintf(stderr, "Loi: Stack day!\n");
        result = -1;
    }
    else
    {
        g_top++;
        g_stack[g_top] = val;
        result = 0;
    }

    return result;
}

static int32_t stack_pop(double *out)
{
    int32_t result = 0;

    if (g_top < 0)
    {
        (void)fprintf(stderr, "Loi: Stack rong!\n");
        result = -1;
    }
    else
    {
        *out = g_stack[g_top];
        g_top--;
        result = 0;
    }

    return result;
}

static int32_t is_operator(const char *token)
{
    int32_t result = 0;

    if ((strcmp(token, "+") == 0) ||
        (strcmp(token, "-") == 0) ||
        (strcmp(token, "*") == 0) ||
        (strcmp(token, "/") == 0))
    {
        result = 1;
    }

    return result;
}

int main(int argc, char *argv[])
{
    int32_t i;
    double  a;
    double  b;
    double  res;
    double  final_result;

    if (argc < 2)
    {
        (void)fprintf(stderr, "Cu phap: expr <bieu_thuc_RPN>\n");
        (void)fprintf(stderr, "Vi du:   expr 2 3 4 + *\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        if (is_operator(argv[i]) != 0)
        {
            if ((stack_pop(&b) != 0) || (stack_pop(&a) != 0))
            {
                return 1;
            }

            if      (strcmp(argv[i], "+") == 0) { res = a + b; }
            else if (strcmp(argv[i], "-") == 0) { res = a - b; }
            else if (strcmp(argv[i], "*") == 0) { res = a * b; }
            else
            {
                if ((b > -1e-9) && (b < 1e-9))
                {
                    (void)fprintf(stderr, "Loi: Chia cho 0!\n");
                    return 1;
                }
                res = a / b;
            }

            if (stack_push(res) != 0)
            {
                return 1;
            }
        }
        else
        {
            if (stack_push(atof(argv[i])) != 0)
            {
                return 1;
            }
        }
    }

    if (stack_pop(&final_result) != 0)
    {
        return 1;
    }

    (void)printf("Ket qua: %.6g\n", final_result);

    return 0;
}