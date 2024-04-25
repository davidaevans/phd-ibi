#include "global.h"
#include "prototypes.h"
long seed;
/*..............................................................................*/

int main()
{
    double diameter;             /* Diameter of disks */
    double kt;                  /* kt for use in metropolist algorithm */
    double **potential;       /* Array of external potential */
    double max_potential_distance; /* Max distance for potential */
    double dr;                 /* Bin width of potential and */
    long periodic;               /* 1=wrapping criterion, 0=spanning */
    long adjust;                /* Number of sweeps between step size adjustments */
    long equilibrate;           /* Number of equilibration sweeps */
    long dump;                 /* Number of sweeps between movie frames */
    long npart;                /* Number of particles */
    long nsweeps;               /* Number of pdiscuction sweeps */
    long i;                     /* Iterator */
    long potential_length;     /* Number of points in potential */
    struct disp trans;         /* Maximum (unscaled) translation step */
    struct disc *particle;      /* Configuration of entire system */
    struct vector box;          /* Simulation cell dimensions */
    FILE *equilfile;            /* File to write equilibrated config too */
    FILE *potential_file = NULL;

    // equilfile = fopen("config.equil", "w+");
    // if (equilfile == NULL) die ("Could not open config.equil");

    printf ("\nMC Simulation of 2D Discs");
    printf ("\n--------------------------\n\n");

    /* Get user parameters */
    read_options(&npart, &box, &diameter, &nsweeps, &dump, &equilibrate, &periodic, &adjust, &trans, &kt);

    /* Set aside memory for the configuration */
    particle = (struct disc *)malloc(npart * sizeof(struct disc));

    // Load potential from "potential.dat"
    potential_file = fopen("potential.dat", "r");
    if (!potential_file) die ("Could not open 'potential.dat' for reading");

    potential_length = get_file_length(potential_file);

    potential = (double **) malloc(sizeof(double *) * potential_length);
    for (i = 0; i < potential_length; i++){
        // two elements: r V(r)
        potential[i] = (double *) malloc(sizeof(double) * 2);
        potential[i][0] = potential[i][1] = 0.0;
    }

    printf("Loading potential\n");
    max_potential_distance = dr = 0.0;
    load_potential(potential_length, potential, potential_file, &max_potential_distance, &dr);
    check_potential(potential, potential_length, max_potential_distance, dr);

    generate_config(particle, box, npart, diameter);

    // init_config(npart, box, diameter, response, particle, fixed_dipole);

    printf ("Beginning cell set-up and equilibration\n\n");
    simulate(npart, box, diameter, equilibrate, 0, adjust,
        trans, periodic, particle, potential, kt, max_potential_distance, dr, potential_length);

    printf ("Equilibrated step size: %.6le\n", trans.mx);
    
    // printf ("Writing equilibrated configuration to config.equil\n");
//     dumpconfigs_equil(equilfile, particle, box, npart, 0, trans);
//     printf ("\n");
//     fclose(equilfile);


   printf ("Beginning main run\n\n");
   fflush (stdout);
   simulate(npart, box, diameter, nsweeps, dump, 0,
        trans, periodic, particle, potential, kt, max_potential_distance, dr, potential_length);
   printf("Acceptance Ratios:\n");
   printf("acc: %ld\n", trans.acc);
   printf("rej: %ld\n", trans.rej);
   printf("acc - species 1: %lf\n", RATIO(trans));
    printf ("\nDone\n\n");

    return 0;
}

/*..............................................................................*/

/*
Print error message and exit.
*/

void die(char string[])
{
   fprintf (stderr, "\nERROR: %s\n\n", string);
   exit (1);
}

/*................................................................................*/
