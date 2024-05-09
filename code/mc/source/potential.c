#include "global.h"
#include "prototypes.h"

/*..............................................................................*/
double calculate_energy_difference(struct vector vold, long cellold, struct vector vnew, long cellnew,
           struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
           long testp, double **potential, long potential_length, double max_potential_distance, double dr,
           int cells_redundant, long npart, int left_edge) {

    long *cell;
    long i;
    struct disc *test;
    struct vector r_cm;

    double energyold, energynew, deltaE;
    double r2;
    double critval, critval2;

    energyold = energynew = deltaE = 0;


    // Critical value is given by the maximum distance in the loaded potential
    critval = max_potential_distance;
    critval2 = SQ(critval);

    if (!cells_redundant) {

        //absolute energy of old config
        /* Loop over all cells adjacent to particle */
        cell = &neighbour[cellold][0];
        while (*cell >= 0) {
            /* Loop over all particles in cell */
            test = cfirst[*cell];
            while (test) {

                if (testp != test->idx) {
                    r_cm = image(vold, test->pos, box);

                    //calculate pair energy contribution
                    r2 = DOT(r_cm, r_cm);

                    if (r2 <= critval2) {
                        energyold += get_ext_energy(potential, potential_length, r2, max_potential_distance, dr, left_edge);
                    }
                }

            test = test->next;
            }  /* End of loop over particles in adjacent cell */

            cell++;
        }  /* End of loop of adjacent cells */    
        //printf("eo: %lf\n", energyold);
        //absolute energy of new config
        /* Loop over all cells adjacent to particle */
        cell = &neighbour[cellnew][0];
        while (*cell >= 0) {
            /* Loop over all particles in cell */
            test = cfirst[*cell];
            while (test) {

                if (testp != test->idx) {
                    r_cm = image(vnew, test->pos, box);
                    //calculate pair energy contribution
                    r2 = DOT(r_cm, r_cm);
                    if (r2 <= critval2) {
                        //if (r <= 0.09) {printf("%lf\n",sqrt(r));}
                        energynew += get_ext_energy(potential, potential_length, r2, max_potential_distance, dr, left_edge);
                    }
                }

            test = test->next;
            }  /* End of loop over particles in adjacent cell */

            cell++;
        }  /* End of loop of adjacent cells */
    } else {
        // Calculate old and new energies
        for (i = 0; i < npart; i++) {
            if (i == testp){continue;}
            // old energy
            r_cm = image(vold, particle[i].pos, box);
            r2 = DOT(r_cm, r_cm);
            if (r2 <= critval2) {
                energyold += get_ext_energy(potential, potential_length, r2, max_potential_distance, dr, left_edge);
            }

            // new energy
            r_cm = image(vnew, particle[i].pos, box);
            r2 = DOT(r_cm, r_cm);
            if (r2 <= critval2) {
                energyold += get_ext_energy(potential, potential_length, r2, max_potential_distance, dr, left_edge);
            }
        }
    }
    
    //return energy difference
    return energynew - energyold;
}

/*..............................................................................*/

void check_potential(double **potential, long potential_length, double max_potential_distance, double dr, int left_edge) {
   double r, pot;
   FILE *outfile = NULL;

   printf("Checking external potential via interpolation\n");
   fflush(stdout);
   outfile = fopen("interpolated-potential.dat", "w");
   if (!outfile) die ("Could not open file iterpolated-potential.dat");

   r = 0.0;
   while (r < 5.0) {
      
      pot = get_ext_energy(potential, potential_length, SQ(r), max_potential_distance, dr, left_edge);

      fprintf(outfile, "%lf %lf\n", r, pot);

      r += 0.001;
   }

   fclose(outfile);
}  