#include "global.h"
#include "prototypes.h"

/*..............................................................................*/

/*
Reads the run parameters from the external file "options".  See INSTRUCTIONS
for a list of keywords.
*/

void read_options(long *npart, struct vector *box,
    long *nsweeps, long *dump, long *equilibrate, long *periodic, 
    long *adjust, struct disp *trans, double *kt)
{
    char command[20];
    char error[200];

    FILE *infile;

    /*--- 0. Defaults ---*/
    *adjust = 50;                      /* Sweeps between step size adjustments (equilibration) */
    box->x = box->y -1.0;              /* Box dimensions */
    *equilibrate = 100;                /* Number of equilibration sweeps */
    *npart = 0;                        /* Number of discs species 1 */
    *nsweeps = 0;                      /* Number of accumulation sweeps */
    *dump = 0;                         /* dump config every x sweeps*/
    *periodic = 1;                     /* PBC = 1 */
    seed = 1;                          /* Random number seed */
    *kt = 1.0;                         /* Default kt = 1 for use in metropolis algorithm */
    trans->mx = 0.1;                   /* Initial maximum translation step sizes */


    /*--- 1. Read in values ---*/

    infile = fopen("options-mc", "r");
    if (infile == NULL) die ("Could not open \"options\" file");
    printf ("Reading run options from the \"options\" file\n\n");

    while ( read_line(infile) ) {
        get_string(command, sizeof(command));
        upper_case(command);

        if (*command == '#') {
            continue;

        } else if (strcmp(command, "BOX") == 0) {
            if (!get_double(&(box->x))) die ("Could not read x box dimension after BOX");
            if (!get_double(&(box->y))) die ("Could not read y box dimension after BOX");

        } else if (strcmp(command, "PBC") == 0) {
            if (!get_int(periodic)) die ("Could not read long after PBC");

        } else if (strcmp(command, "EQUILIBRATE") == 0) {
            if (!get_int(equilibrate)) die ("Could not read number of equilibration sweeps after EQUILIBRATE");
        // OPTIONAL
        } else if (strcmp(command, "MAXSTEP") == 0) {
            if (!get_double(&trans->mx)) die ("Could not read max trans step after MAXSEP");
            
        } else if (strcmp(command, "DUMP") == 0) {
            if (!get_int(dump)) die ("Could not read number sweeps between frames after DUMP");
        } else if (strcmp(command, "DISCS") == 0) {
            if (!get_int(npart)) die ("Could not read number of discs after DISCS");

        } else if (strcmp(command, "SEED") == 0) {
            if (!get_int(&seed)) die ("Could not read random number seed after SEED");
            seed = -abs(seed);
        } else if (strcmp(command, "KT") == 0 ) {
            if (!get_double(kt)) die ("Could not read value of kt after KT");      
        } else if (strcmp(command, "SWEEPS") == 0) {
            if (!get_int(nsweeps)) die ("Could not read number of sweeps after SWEEPS");
        } else {
            sprintf (error, "Unrecognised keyword: %s", command);
            die (error);
        }
    }

    fclose(infile);


    /*--- 2. Validity checks ---*/
    if (*npart < 1) {
        die ("The number of discs must be at least 1.");
    }

    if (seed == 0) {
        die ("The random seed must be a negative integer (not zero).");
    }

    if (*kt <= 0.0) {
        die ("The value of kt must be greater than 0.0");
    }

    if ( (box->x < 2.0) || (box->y < 2.0) ) {
        die ("Both box lengths must be at least 2.0");
    }

    if (*dump > *nsweeps) *dump=*nsweeps;



    /*--- 3. Summarize results on standard output ---*/
    
    printf (" Simulation cell dimensions:               %.8lf, %.8lf\n",
        box->x, box->y);
    printf (" KT:                                       %.8lf\n", *kt);
    printf (" Number of discs:                          %ld\n", *npart);
    printf (" Number density:                           %lf\n", *npart/(box->x * box->y));
    printf (" Number of sweeps:\n");
    printf ("    Equilibration:                         %ld\n", *equilibrate);
    printf ("    Main run:                              %ld\n", *nsweeps);
    printf ("    Between saving configurations:         %ld\n", *dump);
    printf (" Initial maximum step size:                %.6le\n", trans->mx);
    printf (" Random number seed:                       %ld\n", seed);
    printf (" PBC:                                      %s\n", *periodic?"Yes":"No");
    printf ("\n");

}

/*..............................................................................*/

/*
Reads in the initial configuration from the file "config.init".  Each line
contains the two components of the position vector and two components of
the direction vector for a disc.  The direction vector is normalised
after being read in.  There is no check for overlaps at this stage.
*/

// void init_config(long *npart, struct vector box, double *length, double *response,
//     struct disc *particle, struct vector fixed_dipole)
// {
//     long i;
//     FILE *infile;

//     infile = fopen("config.init", "r");
//     if (infile == NULL) {
//         fprintf (stderr, "\nERROR: Could not open config.init file.\n\n");
//         exit (1);
//     }

//     for (i=0; i<npart[0]+npart[1]; i++) {
//         if (fscanf(infile, "%le %le",
//             &particle[i].pos.x, &particle[i].pos.y)
//             != 2) {
//             fprintf (stderr,
//                 "ERROR: Could not read coordinates for particle %ld.\n\n", i+1);
//             exit (1);
//         }
//         /* Scale position vector to the unit cube */
//         particle[i].pos.x -= 0.5;
//         particle[i].pos.y -= 0.5;

//         /* Species 1 discs must be listed first */
//         particle[i].idx = i;
//         if (i<npart[0]) {
//             particle[i].species = 0;
//             particle[i].diameter = length[0];
//             particle[i].response = response[0];
//         } else {
//             particle[i].species = 1;
//             particle[i].diameter = length[1];
//             particle[i].response = response[1];
//         }

//         particle[i].dir = fixed_dipole;
//         // printf("dir_x: %lf dir_y: %lf\n", particle[i].dir.x, particle[i].dir.y);
//     }

//     fclose (infile);
//     fflush (stdout);
// }

/*..............................................................................*/
