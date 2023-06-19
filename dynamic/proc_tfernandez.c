#include "../rpc.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    reportable_t parent;

    int n;
    int res;
} my_struct_t;

void *parse_parameters(void *data)
{
    const char *buf = (const char *)(data);

    my_struct_t *d = (my_struct_t *)(malloc(sizeof(my_struct_t)));

    if (d)
    {
        sscanf(buf, "%d", &d->n);
    }

    return (void *)d;
}

int triangular_rec_helper(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n + triangular_rec_helper(n - 1);
    }
}

void *do_work(void *data)
{
    my_struct_t *d = (my_struct_t *)(data);

    d->res = triangular_rec_helper(d->n);

    return data;
}

reportable_t *report(void *data)
{
    my_struct_t *d = (my_struct_t *)(data);

    d->parent.data = (char *)(malloc(255 * sizeof(char)));

    snprintf(d->parent.data, 255, "El numero triangular de %d es %d\n", d->n, d->res);
    d->parent.len = strlen(d->parent.data);

    return (reportable_t *)(data);
}

void clean_up(void *params, void *result, reportable_t *report)
{
    if (report && report->data)
    {
        free(report->data);
    }

    if (params)
    {
        free(params);
    }
}