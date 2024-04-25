#include "global.h"
#include "prototypes.h"

void generate_config(struct disc *particle, struct vector box, long npart, double diameter) 
{
    double sx, sy;
    long squaresize;
    long i;
    // FILE *configinit;


    // configinit = NULL;
    // configinit = fopen("config.init", "w");
    // if (configinit == NULL) die("Could not open config.init in generate.c");

    squaresize = ceil(sqrt(npart));

    sx = box.x/(squaresize); 
    sy = box.y/(squaresize);

    if (sx < diameter || sy < diameter) die ("Too many particles for square lattice in generate.c");

    // for (i = 0; i < squaresize; i++){
    //     for (j = 0; j < squaresize; j++) {
    //         if (count < ntot){
    //             fprintf(configinit,
    //             "%le %le\n",
    //             ((i * sx)/box.x),
    //             ((j * sy)/box.y));
    //             count++;
    //         }
    //     }
    // }

    for (i = 0; i < npart; i++) {
        particle[i].pos.x = floor(i/squaresize) * sx;
        particle[i].pos.y = (i % squaresize) * sy;

        particle[i].idx = i;
        particle[i].diameter = diameter;

        particle[i].next = NULL;
        particle[i].prev = NULL;
        particle[i].cell = -1;

    }

    // fclose(configinit);

}