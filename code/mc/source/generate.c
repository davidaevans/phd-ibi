#include "global.h"
#include "prototypes.h"

void generate_config(struct disc *particle, struct vector box, long npart) 
{
    double sx, sy;
    double hex_lattice_param;
    long squaresize;
    long i, j;
    long ncols, nrows;
    long count;
    // FILE *configinit;
    FILE *testout = NULL;


    // configinit = NULL;
    // configinit = fopen("config.init", "w");
    // if (configinit == NULL) die("Could not open config.init in generate.c");



    // Square Lattice
    // squaresize = ceil(sqrt(npart));

    // sx = box.x/(squaresize); 
    // sy = box.y/(squaresize);

    // for (i = 0; i < npart; i++) {
    //     particle[i].pos.x = floor(i/squaresize) * sx;
    //     particle[i].pos.y = (i % squaresize) * sy;

    //     particle[i].idx = i;

    //     particle[i].next = NULL;
    //     particle[i].prev = NULL;
    //     particle[i].cell = -1;

    // }

    count = 0;
    hex_lattice_param = sqrt(3)/2.0;
    nrows = floor(box.x / (hex_lattice_param * sqrt(3))) - 1;
    ncols = floor(box.y / (hex_lattice_param * 1.5)) - 1;
    // Hexagonal Lattice
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            if (count < npart) {
                particle[count].pos.x = j * hex_lattice_param * sqrt(3);
                particle[count].pos.y = i * hex_lattice_param * 1.5;
                if (j % 2 == 1) particle[count].pos.y += hex_lattice_param * 0.5;
                particle[count].idx = count;
                particle[i].next = NULL;
                particle[i].prev = NULL;
                particle[i].cell = -1;
            }

            // if (particle[count].pos.x < 0.0 || particle[count].pos.x > box.x || particle[count].pos.y < 0.0 || particle[count].pos.y > box.y) {
            //     particle[count].pos.x = fmod(particle[count].pos.x, box.x);
            //     particle[count].pos.y = fmod(particle[count].pos.y, box.y);
            // }
            count++;
        }
    }
    printf("Placed %ld particles\n", count + 1);
    if (count < npart - 1) {printf("Did not place all particles. Placed %ld\n", count+1);}

    testout = fopen("TEST.dat", "w");
    dumpconfigs_LAMMPS(testout, particle, box, npart, 0);
    die ("End of test");

    // fclose(configinit);

}