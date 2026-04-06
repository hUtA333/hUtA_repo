#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>    /* Them: int32_t */
#include <stddef.h>    /* Them: size_t  */

#define MAX_LINES   1000
#define MAX_LEN     256
#define MAX_FIELDS  10

typedef struct
{
    int32_t field_index;
    int32_t numeric;
    int32_t fold_case;
    int32_t reverse;
    char    delimiter;
} FieldOption;

static FieldOption        g_options[MAX_FIELDS];
static int32_t            g_num_options = 0;
static const FieldOption *g_current_opt = NULL;

static void get_field(const char *line, int32_t field_idx,
                      char delim, char *out, int32_t out_size)
{
    int32_t current_field = 0;
    int32_t i             = 0;
    int32_t j             = 0;

    while ((line[i] != '\0') && (current_field < field_idx))
    {
        if (line[i] == delim)
        {
            current_field++;
        }
        i++;
    }

    while ((line[i] != '\0') && (line[i] != delim) && (j < (out_size - 1)))
    {
        out[j] = line[i];
        j++;
        i++;
    }
    out[j] = '\0';
}

static int32_t compare_lines(const char *a, const char *b,
                              const FieldOption *opt)
{
    char    fa[MAX_LEN];
    char    fb[MAX_LEN];
    int32_t cmp = 0;
    int32_t ia  = 0;
    int32_t ib  = 0;

    get_field(a, opt->field_index, opt->delimiter, fa, (int32_t)sizeof(fa));
    get_field(b, opt->field_index, opt->delimiter, fb, (int32_t)sizeof(fb));

    if (opt->numeric != 0)
    {
        double da = atof(fa);
        double db = atof(fb);
        if      (da < db) { cmp = -1; }
        else if (da > db) { cmp =  1; }
        else              { cmp =  0; }
    }
    else if (opt->fold_case != 0)
    {
        while ((fa[ia] != '\0') && (fb[ib] != '\0'))
        {
            int32_t ca = (int32_t)tolower((unsigned char)fa[ia]);
            int32_t cb = (int32_t)tolower((unsigned char)fb[ib]);
            if (ca != cb) { cmp = ca - cb; break; }
            ia++;
            ib++;
        }
        if (cmp == 0)
        {
            cmp = (int32_t)tolower((unsigned char)fa[ia])
                - (int32_t)tolower((unsigned char)fb[ib]);
        }
    }
    else
    {
        cmp = strcmp(fa, fb);
    }

    if (opt->reverse != 0)
    {
        cmp = -cmp;
    }

    return cmp;
}

static int qsort_compare(const void *a, const void *b)
{
    const char *sa = *(const char * const *)a;
    const char *sb = *(const char * const *)b;
    return (int)compare_lines(sa, sb, g_current_opt);
}

int main(void)
{
    static const char *lines[] = {
        "banana 3",
        "apple 1",
        "cherry 2"
    };
    int32_t     n = 3;
    int32_t     i;
    FieldOption opt_num;

    opt_num.field_index = 1;
    opt_num.numeric     = 1;
    opt_num.fold_case   = 0;
    opt_num.reverse     = 0;
    opt_num.delimiter   = ' ';

    g_current_opt = &opt_num;
    qsort((void *)lines, (size_t)n, sizeof(char *), qsort_compare);

    (void)printf("=== Sap xep theo so (truong 1) ===\n");
    for (i = 0; i < n; i++)
    {
        (void)printf("%s\n", lines[i]);
    }

    return 0;
}