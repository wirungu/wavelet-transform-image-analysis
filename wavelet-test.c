#include <stdio.h>
#include "array.h"
#include "wavelet.h"

static void test_vector(int n)
{
    double *v;
    make_vector(v, n);
    for (int i = 0; i < n; i++)
        v[i] = 1.0 / (1 + i);
    printf("original vector:\n");
    print_vector("%8.4f ", v, n);
    putchar('\n');
    haar_transform_vector(v, n, WT_FWD);
    printf("transformed vector:\n");
    print_vector("%8.4f ", v, n);
    putchar('\n');
    haar_transform_vector(v, n, WT_REV);
    printf("reconstructed vector:\n");
    print_vector("%8.4f ", v, n);
    putchar('\n');
    free_vector(v);
}

static void test_matrix(int m, int n)
{
    double **a;
    make_matrix(a, m, n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 1.0 / (1 + i + j);

    printf("original matrix:\n");
    print_matrix("%8.4f ", a, m, n);
    putchar('\n');
    haar_transform_matrix(a, m, n, WT_FWD);
    printf("transformed matrix:\n");
    print_matrix("%8.4f ", a, m, n);
    putchar('\n');
    haar_transform_matrix(a, m, n, WT_REV);
    printf("reconstructed matrix:\n");
    print_matrix("%8.4f ", a, m, n);
    putchar('\n');
    free_matrix(a, m);
}

int main(void)
{
    test_vector(8); // test an 8-vector
    test_matrix(4, 8); // test a 4 × 8 matrix
    return 0;
}
