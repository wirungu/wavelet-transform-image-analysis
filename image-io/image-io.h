#ifndef H_IMAGE_IO_H
#define H_IMAGE_IO_H
#include <netpbm/pam.h>
struct image {
        struct pam pam;
        double **r;
        double **g;
        double **b;
};
struct image *read_image(char *filename);
void write_image(char *filename, struct image *img);
void free_image(struct image *img);
#endif /∗ H_IMAGE_IO_H */
