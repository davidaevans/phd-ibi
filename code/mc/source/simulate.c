#include "global.h"
#include "prototypes.h"

/*..............................................................................*/

void simulate(long npart, struct vector box, double diameter,
   long nsweeps, long dump, long adjust, struct disp trans, long periodic,
   struct disc *particle, double **potential, double kt, double max_potential_distance, double dr, long potential_length)
{
   static double denom;
   static double longer;           /* Length of the longer of the two disc species */
   long cell;           /* Cell-list cell of a given particle */
   long i, j;
   static long ncellx, ncelly;     /* Number of cell-list cells in each direction */
   static long ncells;  /* Total number of cell-list cells */
   static long **neighbour=NULL;   /* List of neighbouring cells for each cell */
   long next_adjust;    /* Next sweep number for adjusting step sizes */
   long next_frame;     /* Next sweep number for dumping a movie frame */
   long oldcell;        /* For saving original cell of test particle */
   long step;           /* Current step number within sweep */
   long sweep;          /* Current sweep number */
   long testp;          /* Particle for trial move */
   static struct disc **cfirst=NULL;    /* Array of pointers to first particle in cell list */
   struct vector vold;  /* For saving original position or direction vector */
   FILE *dumpfile;       /* Handle for configs file */
   char dumpfilename[60]; /* Buffer for name of configs file */

   sprintf(dumpfilename, "configs-Lx_%.1lf-Ly_%.1lf-npart_%ld-rho_%lf.dat", box.x, box.y, npart, (npart/(box.x*box.y)));

   /*=== Initialise cell list on first call ===*/
   if (!cfirst) {
      /* Find cell list dimensions and allocate memory */
      denom = max_potential_distance;
      ncellx = (long)(box.x / (denom));
      ncelly = (long)(box.y / (denom));
      ncells = ncellx * ncelly;
      cfirst = (struct disc **)malloc(sizeof(struct disc *) * ncells);
      neighbour = (long **)malloc(sizeof(long *) * ncells);
      for (i=0; i<ncells; i++) {
         neighbour[i] = (long *)malloc(sizeof(long) * 10);
      }

      printf("Creating neighbour list\n");
      /* Work out neighbouring cells for each cell by pointer */
      /* Interior of box */
      for (i=0; i<ncellx; i++) {
         for (j=0; j<ncelly; j++) {
            neighbour[j*ncellx+i][0] = ((j-1) + (j==0?ncelly:0))*ncellx + ((i-1) + (i==0?ncellx:0));
            neighbour[j*ncellx+i][1] = ((j-1) + (j==0?ncelly:0))*ncellx + i;
            neighbour[j*ncellx+i][2] = ((j-1) + (j==0?ncelly:0))*ncellx + ((i+1) - (i==ncellx-1?ncellx:0));
            neighbour[j*ncellx+i][3] = j*ncellx + ((i-1) + (i==0?ncellx:0));
            neighbour[j*ncellx+i][4] = j*ncellx + i;
            neighbour[j*ncellx+i][5] = j*ncellx + ((i+1) - (i==ncellx-1?ncellx:0));
            neighbour[j*ncellx+i][6] = ((j+1) - (j==ncelly-1?ncelly:0))*ncellx + ((i-1) + (i==0?ncellx:0));
            neighbour[j*ncellx+i][7] = ((j+1) - (j==ncelly-1?ncelly:0))*ncellx + i;
            neighbour[j*ncellx+i][8] = ((j+1) - (j==ncelly-1?ncelly:0))*ncellx + ((i+1) - (i==ncellx-1?ncellx:0));
            neighbour[j*ncellx+i][9] = -1;  /* end token */
         }
      }
      if (!periodic) {
         // printf("OVERWRITING BOUNDARIES WITHOUT PBC\n");
         /* Overwrite periodic results along the boundaries */
         /* Edges */
         for (i=1; i<ncellx-1; i++) {
            /* top */
            neighbour[i][0] = i-1;
            neighbour[i][1] = i;
            neighbour[i][2] = i+1;
            neighbour[i][3] = ncellx + (i-1);
            neighbour[i][4] = ncellx + i;
            neighbour[i][5] = ncellx + (i+1);
            neighbour[i][6] = -1;
            /* bottom */
            neighbour[(ncelly-1)*ncellx + i][0] = (ncelly-2)*ncellx + (i-1);
            neighbour[(ncelly-1)*ncellx + i][1] = (ncelly-2)*ncellx + i;
            neighbour[(ncelly-1)*ncellx + i][2] = (ncelly-2)*ncellx + (i+1);
            neighbour[(ncelly-1)*ncellx + i][3] = (ncelly-1)*ncellx + (i-1);
            neighbour[(ncelly-1)*ncellx + i][4] = (ncelly-1)*ncellx + i;
            neighbour[(ncelly-1)*ncellx + i][5] = (ncelly-1)*ncellx + (i+1);
            neighbour[(ncelly-1)*ncellx + i][6] = -1;
         }
         for (j=1; j<ncelly-1; j++) {
            /* left */
            neighbour[j*ncellx][0] = (j-1)*ncellx;
            neighbour[j*ncellx][1] = (j-1)*ncellx + 1;
            neighbour[j*ncellx][2] = j*ncellx;
            neighbour[j*ncellx][3] = j*ncellx + 1;
            neighbour[j*ncellx][4] = (j+1)*ncellx;
            neighbour[j*ncellx][5] = (j+1)*ncellx + 1;
            neighbour[j*ncellx][6] = -1;
            /* right */
            neighbour[(j+1)*ncellx-1][0] = j*ncellx-2;
            neighbour[(j+1)*ncellx-1][1] = j*ncellx-1;
            neighbour[(j+1)*ncellx-1][2] = (j+1)*ncellx-2;
            neighbour[(j+1)*ncellx-1][3] = (j+1)*ncellx-1;
            neighbour[(j+1)*ncellx-1][4] = (j+2)*ncellx-2;
            neighbour[(j+1)*ncellx-1][5] = (j+2)*ncellx-1;
            neighbour[(j+1)*ncellx-1][6] = -1;
         }
         /* Corners */
         /* Top left */
         neighbour[0][0] = 0;
         neighbour[0][1] = 1;
         neighbour[0][2] = ncellx;
         neighbour[0][3] = ncellx+1;
         neighbour[0][4] = -1;
         /* Top right */
         neighbour[ncellx-1][0] = ncellx-2;
         neighbour[ncellx-1][1] = ncellx-1;
         neighbour[ncellx-1][2] = 2*ncellx-2;
         neighbour[ncellx-1][3] = 2*ncellx-1;
         neighbour[ncellx-1][4] = -1;
         /* Bottom left */
         neighbour[ncellx*(ncelly-1)][0] = ncellx*(ncelly-2);
         neighbour[ncellx*(ncelly-1)][1] = ncellx*(ncelly-2) + 1;
         neighbour[ncellx*(ncelly-1)][2] = ncellx*(ncelly-1);
         neighbour[ncellx*(ncelly-1)][3] = ncellx*(ncelly-1) + 1;
         neighbour[ncellx*(ncelly-1)][4] = -1;
         /* Bottom right */
         neighbour[ncellx*ncelly-1][0] = ncellx*(ncelly-1) - 2;
         neighbour[ncellx*ncelly-1][1] = ncellx*(ncelly-1) - 1;
         neighbour[ncellx*ncelly-1][2] = ncellx*ncelly - 2;
         neighbour[ncellx*ncelly-1][3] = ncellx*ncelly - 1;
         neighbour[ncellx*ncelly-1][4] = - 1;
      }
      
      /* Put the particles in the cells */
      for (i=0; i<npart; i++) { particle[i].next = particle[i].prev = NULL; }
      for (i=0; i<ncells; i++) { cfirst[i] = NULL; }
      for (i=0; i<npart; i++) {
         cell = getcell(particle[i].pos, ncellx, ncelly, box);
         particle[i].cell = cell;
         if (cfirst[cell]) cfirst[cell]->prev = &particle[i];
         particle[i].next = cfirst[cell];
         cfirst[cell] = &particle[i];
      }

      printf ("Cell list grid: %ld x %ld\n\n", ncellx, ncelly);
   }

   /*=== Initialise counters etc. ===*/

   next_adjust = adjust;
   next_frame = dump;

   for (i=0; i<=1; i++) {
      trans.acc = trans.rej = 0.0;
   }

   if (dump > 0) {
      dumpfile = fopen(dumpfilename, "a");
   } else {
      dumpfile = NULL;
   }

   /*=== The simulation ===*/
   for (sweep = 1; sweep <= nsweeps; sweep++) {
      if(sweep%1000 == 0) printf("Sweep: %ld\n",sweep);

      /*=== One translation per particle on average ===*/
      for (step=0; step<npart; step++) {
         testp = (long)(ran2(&seed) * npart);

   
         /* Translation step */
         vold = particle[testp].pos;
         
         oldcell = particle[testp].cell;
         particle[testp].pos.x += (ran2(&seed) - 0.5) * 2.0 * trans.mx + box.x;
         particle[testp].pos.y += (ran2(&seed) - 0.5) * 2.0 * trans.mx + box.y;

         particle[testp].pos.x = fmod(particle[testp].pos.x, box.x);
         particle[testp].pos.y = fmod(particle[testp].pos.y, box.y);


         

         // if (particle[testp].pos.x > 0.5) particle[testp].pos.x-=1.0;
         // if (particle[testp].pos.x < -0.5) particle[testp].pos.x+=1.0;
         // if (particle[testp].pos.y > 0.5) particle[testp].pos.y-=1.0;
         // if (particle[testp].pos.y < -0.5) particle[testp].pos.y+=1.0;

         cell = getcell(particle[testp].pos, ncellx, ncelly, box);

         if (cell != oldcell) {
            /* Remove particle from original cell */
            if (particle[testp].prev) {
               (particle[testp].prev)->next = particle[testp].next;
            } else {
               cfirst[oldcell] = particle[testp].next;
               if (cfirst[oldcell]) cfirst[oldcell]->prev = NULL;
            }
            if (particle[testp].next) {
               (particle[testp].next)->prev = particle[testp].prev;
            }
            /* Insert particle into new cell */
            particle[testp].cell = cell;
            if (cfirst[cell]) cfirst[cell]->prev = &particle[testp];
            particle[testp].next = cfirst[cell];
            particle[testp].prev = NULL;
            cfirst[cell] = &particle[testp];
         }
         //printf("predecision\n");
	      fflush(stdout);
         if (!accept_move(vold, oldcell, particle, box, npart, testp, cfirst, neighbour, kt, potential, potential_length, max_potential_distance, dr) ) {
            /* Reject due to overlap */
            particle[testp].pos = vold;
            trans.rej++;
            if (cell != oldcell) {
               /* Remove particle from trial cell, given that it must be the first one in the cell */
               if (particle[testp].next) (particle[testp].next)->prev = NULL;
               cfirst[cell] = particle[testp].next;
               /* Reinsert particle into original cell */
               particle[testp].cell = oldcell;
               if (cfirst[oldcell]) cfirst[oldcell]->prev = &particle[testp];
               particle[testp].next = cfirst[oldcell];
               particle[testp].prev = NULL;
               cfirst[oldcell] = &particle[testp];
            }
         } else {
            /* Accept */
            trans.acc++;
         }
         

      }

      /*=== Adjust step sizes during equilibration ===*/
      if (sweep == next_adjust) {
         maxstep(&trans, longer, 0.001);
         next_adjust += adjust;
      }


      /* Writing of movie frame */
      if (sweep == next_frame) {
         dumpconfigs_LAMMPS(dumpfile, particle, box, npart, sweep);
         fflush(dumpfile);
         next_frame += dump;
      }

   }
   /**** End of sweeps loop ****/

   if (dumpfile) fclose (dumpfile);
}

/*..............................................................................*/

/*
Adjusts the maximum displacement within the specified limits and resets the
acceptance counters to zero.
*/
 
void maxstep(struct disp *x, double hi, double lo)
{
   if (RATIO(*x) < 0.5) {
      (*x).mx *= 0.95;
   } else {
      (*x).mx *= 1.05;
   }
 
   if ( (*x).mx > hi ) (*x).mx = hi;
   if ( (*x).mx < lo ) (*x).mx = lo;
 
   (*x).acc = (*x).rej = 0;
}

/*..............................................................................*/

/*
Accumulate a value into the statistics and update the mean and rms values.
*/
void accumulate(struct stat *q, double x)
{
   (*q).sum += x;
   (*q).sum2 += x*x;
   (*q).samples++;
   (*q).mean = (*q).sum / (*q).samples;
   (*q).rms = sqrt(fabs((*q).sum2 / (*q).samples -
                        (*q).sum * (*q).sum / (*q).samples / (*q).samples));
}

/*................................................................................*/

/*
Debugging tool to check that cell lists are consistent.
*/

void checkcells(long ntot, long ncells, struct disc **cfirst,
   long **neighbour, struct disc *particle)
{
   long i;
   static int *seen=NULL;
   struct disc *test;

   if (!seen) seen = (int *)malloc(ntot * sizeof(int));

   /* Check that all particles appear exactly once in the cell list */
   for (i=0; i<ntot; i++) seen[i]=0;
   for (i=0; i<ncells; i++) {
      test = cfirst[i];
      while (test) {
         seen[test->idx]++;
         test = test->next;
      }
   }
   for (i=0; i<ntot; i++) {
      if (seen[i] == 0) {
         printf ("CELL LIST ERROR: Particle %ld does not appear in any cell list\n", i);
         exit(1);
      }
      if (seen[i] > 1) {
         printf ("CELL LIST ERROR: Particle %ld appears in more than one cell list\n", i);
         exit(1);
      }
   }

   /* Check consistency of prev<->next relations */
   for (i=0; i<ntot; i++) {
      if (particle[i].next) {
         if ( (particle[i].next)->prev != &particle[i] ) {
            printf ("CELL LIST ERROR: i->next->prev != i for i=%ld\n", i);
            exit(1);
         }
      }
      if (particle[i].prev) {
         if ( (particle[i].prev)->next != &particle[i] ) {
            printf ("CELL LIST ERROR: i->prev->next != i for i=%ld\n", i);
            exit(1);
         }
      }
   }
}