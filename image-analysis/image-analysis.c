#include <math.h>
#include "image-io.h"
#include "array.h"
#include "wavelet.h"
#include <netpbm/pam.h>
#include "xmalloc.h"
#include <stdio.h>

static int prune_matrix(double **a, int m, int n, double rel_err) {
    double max = fabs(a[0][0]);
    double min = fabs(a[0][0]);
    double norm2 = 0.0;
    int zero_count = 0; // Counter for zeroed entries

    // Step 1: Compute max, min, and norm2
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double value = fabs(a[i][j]);
            if (value > max) {
                max = value;
            }
            if (value < min) {
                min = value;
            }
            norm2 += value * value;
        }
    }

    // Step 2: Calculate abs_err2
    double abs_err2 = norm2 * rel_err * rel_err;
    double abs_err = sqrt(abs_err2);

    // Step 3: Bisection algorithm to find threshold
    // Initialize bisection parameters
    double lower = min;
    double upper = max;
    double epsilon = 1e-6; // Tolerance factor for stopping
    double threshold = (lower + upper) / 2.0;

    while ((upper - lower) > epsilon * abs_err) { // Stopping criterion
        // Compute the truncation error for the current threshold
        double truncation_error = 0.0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (fabs(a[i][j]) < threshold) {
                    truncation_error += a[i][j] * a[i][j];
                }
            }
        }

        if (truncation_error > abs_err) {
            // We are truncating too much, adjust the upper bound
            upper = threshold;
        } else {
            // We are truncating too little, adjust the lower bound
            lower = threshold;
        }

        // Update the threshold
        threshold = (lower + upper) / 2.0;
    }

    // Step 4: Set the pixels below the final threshold to zero
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(a[i][j]) <= threshold) {
                a[i][j] = 0.0;
                zero_count++; // Increment zero count
            }
        }
    }

    // Step 5: Return the number of zeroed entries
    return zero_count;
}


static void clip_matrix(double **a, int m, int n, int M) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < 0.0) {
                a[i][j] = 0.0;
            } else if (a[i][j] > M) {
                a[i][j] = (double)M;
            } else {
                a[i][j] = round(a[i][j]);
            }
        }
    }
}
static void reduce_pgm_image(struct image *img, double rel_err)
{
    int m = img->pam.height;
    int n = img->pam.width;
    int M = img->pam.maxval;
    int zero_count;

    haar_transform_matrix(img->g, m, n, WT_FWD);
    zero_count = prune_matrix(img->g, m, n, rel_err);
    haar_transform_matrix(img->g, m, n, WT_REV);
    clip_matrix(img->g, m, n, M);
    fprintf(stderr, "zeroed %d of %d wavelet coefficients, %d remaining\n",
            zero_count, m*n, m*n - zero_count);
}

static void reduce_ppm_image(struct image *img, double rel_err) {
    int m = img -> pam.height;
    int n = img -> pam.width;
    int M = img -> pam.maxval;
    int zero_count;

    double **T;
    make_matrix(T, m, n);

    // Create the composite matrix T
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double r_ij = img -> r[i][j];
            double g_ij = img -> g[i][j];
            double b_ij = img -> b[i][j];
            T[i][j] = sqrt((r_ij * r_ij + g_ij * g_ij + b_ij * b_ij) / 3.0);
        }
    }

    haar_transform_matrix(T, m, n, WT_FWD);
    zero_count = prune_matrix(T, m, n, rel_err);
    haar_transform_matrix(T, m, n, WT_REV);

    // Zero the corresponding entries in r, g, and b matrices
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (T[i][j] == 0.0) {
                img -> r[i][j] = 0.0;
                img -> g[i][j] = 0.0;
                img -> b[i][j] = 0.0;
            }
        }
    }

    clip_matrix(img -> r, m, n, M);
    clip_matrix(img -> g, m, n, M);
    clip_matrix(img -> b, m, n, M);

    free_matrix(T);

    fprintf(stderr, "zeroed %d of %d wavelet coefficients, %d remaining\n",
            zero_count, m * n, m * n - zero_count);
}

void show_usage(char *progname) {
    fprintf(stderr, "Usage: %s rel_err infile outfile\n", progname);
    fprintf(stderr, "0.0 ≤ rel_err ≤ 1.0\n");
    fprintf(stderr, "1. Reads a PGM or PPM image from infile\n");
    fprintf(stderr, "2. Applies the Haar wavelet transform\n");
    fprintf(stderr, "3. Sets as many of the smallest wavelet coefficients to zero\n");
    fprintf(stderr, "   as possible while keeping the relative error\n");
    fprintf(stderr, "   (in the L^2 norm) just under rel_err\n");
    fprintf(stderr, "4. Reconstructs image with the truncated coefficients and\n");
    fprintf(stderr, "   writes to outfile\n");
}


int main(int argc, char **argv)
{
    char *infile, *outfile, *endptr;
    double rel_err;
    if (argc != 4) {
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }
    rel_err = strtod(argv[1], &endptr);
    if (*endptr != '\0' || rel_err < 0.0 || rel_err > 1.0) {
        fprintf(stderr, "*** the rel_err argument should be "
                "between 0.0 and 1.0\n");
        return EXIT_FAILURE;
    }
    infile = argv[2];
    outfile = argv[3];
    pm_init(argv[0], 0);

    struct image *img = read_image(infile);
    struct pam *pam = &img -> pam;
    if (pam->format == PGM_FORMAT || pam->format == RPGM_FORMAT) {
        reduce_pgm_image(img, rel_err);
    } else if (pam->format == PPM_FORMAT || pam->format == RPPM_FORMAT) {
        reduce_ppm_image(img, rel_err);
    } else {
        fprintf(stderr, "*** file %s, line %d: shouldn’t be here\n",
                __FILE__, __LINE__);
        return EXIT_FAILURE;
    }

    write_image(outfile,img);
    free_image(img);
    return EXIT_SUCCESS;
}
