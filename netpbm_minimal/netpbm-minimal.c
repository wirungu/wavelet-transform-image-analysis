#include <stdio.h>
#include <netpbm/pam.h>
#include "array.h"
int main(int argc, char **argv)
{
        char *infile = "aya_matsuura.pgm";
        char *outfile = "zz.pgm";
        struct pam pam;
        FILE *fp;
        double **a;
        tuple *row;
        int i, j;
        pm_init (argv[0], 0);
        // initialize the library
        // read image header
        fp = pm_openr (infile);
        pnm_readpaminit (fp, &pam, PAM_STRUCT_SIZE(tuple_type));
        printf("image: %dx%d, depth: %d\n",
               pam.width, pam.height, pam.depth);
        if (!(pam.format == PGM_FORMAT || pam.format == RPGM_FORMAT)) {
                fprintf(stderr, "Sorry, this demo handles PGM images only.\n");
                return EXIT_FAILURE;
        }
        make_matrix(a, pam.height, pam.width);
        // matrix to store image data
        row = pnm_allocpamrow (&pam);
        // tuplerow vector
        for(i = 0; i < pam.height; i++) {
                // read pixel data
                pnm_readpamrow (&pam, row);
                for (j = 0; j < pam.width; j++) {
                        // copy tuplerow into matrix
                        a[i][j] = row [j][0];
                }
        }
        pm_close (fp);
        for (i = 0; i < pam.width && i < pam.height; i++)
                a[i][i] = 0.0;
        // change the ai i pixels to black
        // write image header
        fp = pm_openw (outfile);
        pam.file = fp;
        pam.plainformat = pam.format == PGM_FORMAT ? 1 : 0;
        pnm_writepaminit (&pam);
        for (i = 0; i < pam.height; i++) {
                // write pixel data
                for(j = 0; j < pam.width; j++)
                        row[j][0] = a[i][j];
                pnm_writepamrow (&pam, row);
        }
        pm_close (fp);
        free_matrix(a);
        pnm_freepamrow (row);
        return EXIT_SUCCESS;
}
