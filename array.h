#ifndef H_ARRAY_H
#define H_ARRAY_H
#include "xmalloc.h"

#define make_vector(v,n) ((v) = xmalloc((n) * sizeof *(v)))
#define free_vector(v) do { free(v); v = NULL; } while (0)

#define make_matrix(a, m, n) do {                               \
        size_t make_matrix_loop_counter;                        \
        make_vector(a, (m) + 1);                                \
        for (make_matrix_loop_counter = 0;                      \
             make_matrix_loop_counter < (m);                    \
             make_matrix_loop_counter++)                        \
            make_vector((a)[make_matrix_loop_counter], (n));    \
        (a)[m] = NULL;                                          \
    } while (0)

#define free_matrix(a, m) do {                                 \
    if ((a) != NULL) {                                        \
        size_t make_matrix_loop_counter;                      \
        for (make_matrix_loop_counter = 0;                    \
             (a)[make_matrix_loop_counter] != NULL;           \
             make_matrix_loop_counter++)                      \
            free_vector((a)[make_matrix_loop_counter]);       \
        free_vector(a);                                       \
        a = NULL;                                             \
    }                                                         \
} while (0)

#define print_vector(format, v, n) do {                      \
    for (int print_vector_i = 0; print_vector_i < (n); print_vector_i++) { \
        printf(format, (v)[print_vector_i]);                 \
    }                                                        \
    putchar('\n');                                           \
} while (0)

#define print_matrix(format, a, m, n) do {                   \
    for (int print_matrix_i = 0; print_matrix_i < (m); print_matrix_i++) { \
        for (int print_matrix_j = 0; print_matrix_j < (n); print_matrix_j++) { \
            printf(format, (a)[print_matrix_i][print_matrix_j]); \
        }                                                    \
        putchar('\n');                                       \
    }                                                        \
} while (0)

#endif // H_ARRAY_H
