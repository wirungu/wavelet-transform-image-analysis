 #include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "wavelet.h"

#define SQRT1_2 sqrt(1.0 / 2)

void haar_transform_vector_forward(double *v, int n)
{
    double h = sqrt(n);
    int i, d;
    for (i = 0; i < n; i++)
        v[i] /= h;
    for (d = 1; d < n; d *= 2)
        for (i = 0; i < n; i += 2 * d) {
            double x = SQRT1_2 * (v[i] + v[i + d]);
            double y = SQRT1_2 * (v[i] - v[i + d]);
            v[i] = x;
            v[i + d] = y;
        }
}

void haar_transform_vector_reverse(double *v, int n)
{
    int d, i;
    for (d = n / 2; d >= 1; d /= 2)
        for (i = 0; i < n; i += 2 * d) {
            double x = SQRT1_2 * (v[i] + v[i + d]);
            double y = SQRT1_2 * (v[i] - v[i + d]);
            v[i] = x;
            v[i + d] = y;
        }

    double h = sqrt(n);
    for (i = 0; i < n; i++)
        v[i] *= h;
}

void haar_transform_vector(double *v, int n, int dir)
{
    if (dir == WT_FWD)
        haar_transform_vector_forward(v, n);
    else if (dir == WT_REV)
        haar_transform_vector_reverse(v, n);
    else {
        fprintf(stderr, "*** error in haar_transform_vector(): "
                "the third argument should be one of "
                "WT_FWD or WT_REV\n");
        exit(EXIT_FAILURE);
    }
}

void haar_transform_matrix_forward(double **a, int m, int n)
{
    int i, j;
    double *tmp = (double *)malloc(m * sizeof(double));

    for (i = 0; i < m; i++)
        haar_transform_vector(a[i], n, WT_FWD);

    for (j = 0; j < n; j++) {
        for (i = 0; i < m; i++)
            tmp[i] = a[i][j];
        haar_transform_vector(tmp, m, WT_FWD);
        for (i = 0; i < m; i++)
            a[i][j] = tmp[i];
    }

    free(tmp);
}

void haar_transform_matrix_reverse(double **a, int m, int n)
{
    int i, j;
    double *tmp = (double *)malloc(m * sizeof(double));

    for (j = 0; j < n; j++) {
        for (i = 0; i < m; i++)
            tmp[i] = a[i][j];
        haar_transform_vector(tmp, m, WT_REV);
        for (i = 0; i < m; i++)
            a[i][j] = tmp[i];
    }

    for (i = 0; i < m; i++)
        haar_transform_vector(a[i], n, WT_REV);

    free(tmp);
}

void haar_transform_matrix(double **a, int m, int n, int dir)
{
    if (dir == WT_FWD)
        haar_transform_matrix_forward(a, m, n);
    else if (dir == WT_REV)
        haar_transform_matrix_reverse(a, m, n);
    else {
        fprintf(stderr, "*** error in haar_transform_matrix(): "
                "the fourth argument should be one of "
                "WT_FWD or WT_REV\n");
        exit(EXIT_FAILURE);
    }
}
