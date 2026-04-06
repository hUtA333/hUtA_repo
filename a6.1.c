#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 * strend - Kiem tra xem chuoi t co xuat hien o cuoi chuoi s khong
 * Tham so:
 *   s - chuoi nguon
 *   t - chuoi can tim kiem
 * Tra ve:
 *   1 neu t xuat hien o cuoi s
 *   0 neu nguoc lai
 */
static int32_t strend(const char *s, const char *t)
{
    int32_t len_s;
    int32_t len_t;
    int32_t result = 0;

    if ((s == NULL) || (t == NULL))
    {
        result = 0;
    }
    else
    {
        len_s = (int32_t)strlen(s);
        len_t = (int32_t)strlen(t);

        /* t phai ngan hon hoac bang s */
        if ((len_t <= len_s) && (strcmp(s + (len_s - len_t), t) == 0))
        {
            result = 1;
        }
    }

    return result;
}

int main(void)
{
    const char *s1 = "Hello World";
    const char *t1 = "World";

    const char *s2 = "Hello World";
    const char *t2 = "Hello";

    (void)printf("strend(\"%s\", \"%s\") = %d\n", s1, t1, strend(s1, t1)); /* 1 */
    (void)printf("strend(\"%s\", \"%s\") = %d\n", s2, t2, strend(s2, t2)); /* 0 */

    return 0;
}
