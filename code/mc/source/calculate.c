#include "global.h"
#include "prototypes.h"


/*................................................................................*/
//return 0 for reject, 1 for accept
int accept_move(struct vector vold, long oldcell, struct disc *particle,
                struct vector box, long npart, long testp,
                struct disc **cfirst, long **neighbour, double kt,
                double **potential, long potential_length, double max_potential_distance, double dr,
                int cells_redundant)
{
    long newcell;
    double deltaE;
    double diameter;
    struct vector vnew;

    newcell = particle[testp].cell;
    vnew = particle[testp].pos;
    diameter = particle[testp].diameter;
    deltaE = 0;

    deltaE = calculate_energy_difference(vold, oldcell, vnew, newcell, diameter, cfirst, neighbour, box, particle, testp, potential, potential_length, max_potential_distance, dr, cells_redundant, npart);

    return metropolis(deltaE, kt);
}


//return 0 for reject, 1 for accept
int metropolis(double deltaE, double kt) 
{
    double accprob;

    // printf("deltaE: %lf\n", deltaE);
    if (deltaE <=0) {
        // printf("accept\n");
        return 1;
    } else {
        accprob = exp(-deltaE/kt);
        if (ran2(&seed) <= accprob) {
            // printf("accept: %lf\n", accprob);
            return 1;
        }
        // printf("reject\n");
        return 0;
    }
}
