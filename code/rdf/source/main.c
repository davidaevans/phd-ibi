#include "global.h"
#include "prototypes.h"

/*..............................................................................*/

int main()
{
   char filename[80];          /*Name of file where LAMMPS configs are */

   long i;
   long npart;                 /* Number of particles */
   long nsweeps;
   long numbins;
   long *rdfhist;
   double maxsep;
   double shorter;
   double dr;
   struct disc *particle;  /* Configuration of entire system */
   struct vector box;          /* Simulation cell dimensions */
   FILE *configs = NULL;   /* file for LAMMPS data */


   printf ("\nRDF in 2D");
   printf ("\n--------------------------\n\n");
   
   /* Get user parameters */
   read_options(&npart, &box, &dr, &nsweeps, filename);

   // Set up RDF variables
   numbins = 0;
   maxsep = 0;
   rdfhist = NULL;

   shorter = box.y > box.x ? box.x : box.y;
   maxsep = shorter/2;
   numbins = maxsep/dr + 1;
   rdfhist = (long *)malloc(numbins * sizeof(long));
   //set all elements to zero as no guarantee they will all be accessed
   for (i=0;i<numbins;i++) rdfhist[i] = 0;

   /* Set aside memory for the configuration */
   particle = (struct disc *)malloc(npart * sizeof(struct disc));


   for (i=0; i<npart; i++) { particle[i].idx=i; }

   // OPEN CONFIG FILE
   configs = fopen(filename, "r");
   if (!configs) die ("Could not open LAMMPS datafile.");

   for (i=0;i<nsweeps;i++){
      load(configs, particle,npart, box);
      rdf(particle, rdfhist, npart, numbins, dr, maxsep, box);
   }
   fclose(configs);
   normalise_and_write_rdf(rdfhist, numbins, nsweeps, npart, dr, box);



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
