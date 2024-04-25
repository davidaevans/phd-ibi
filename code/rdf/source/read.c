#include "global.h"
#include "prototypes.h"

/*..............................................................................*/

/*
Reads the run parameters from the external file "options".  See INSTRUCTIONS
for a list of keywords.
*/

void read_options(long *npart, struct vector *box, double *dr, long *nsweeps,char *filename)
{
   int i;
   char command[20];
   char error[200];
   char fname[80]; //name of file where configurations are read from
   FILE *infile = NULL;
   FILE *datafile = NULL; //LAMMPS file


   /* Prototypes for keywords library */
   int  read_line(FILE *);
   int  get_string(char [], int);
   void upper_case(char []);
   int  get_int(long int *);
   int  get_double(double *);


   /*--- 0. Defaults ---*/
   box->x = box->y -1.0;              /* Box dimensions */
   *dr = 0.0;
   *nsweeps = 0;


   /*--- 1. Read in values ---*/

   infile = fopen("options", "r");
   if (infile == NULL) die ("Could not open \"options\" file");
   printf ("Reading run options from the \"options\" file\n\n");

   while ( read_line(infile) ) {
      get_string(command, sizeof(command));
      upper_case(command);

      if (*command == '#') {
         continue;

      } else if (strcmp(command, "FILENAME") == 0) {
         if(!get_string(fname, sizeof(fname))) die ("Could not read filename after FILENAME");
         strcpy(filename, fname);
         //sprintf(error, "fname: %s, filename: %s", fname, filename);
         //die(error);
      } else if (strcmp(command, "BINSIZE") == 0) {
         if (!get_double(dr)) die ("Could not read bin size after BINSIZE");
      } else if (strcmp(command, "SWEEPS") == 0) {
         if (!get_int(nsweeps)) die ("Could not read number of sweeps after SWEEPS");
      } else {
         sprintf (error, "Unrecognised keyword: %s", command);
         die (error);
      }
   }

   fclose(infile);

   datafile = fopen(filename, "r");
   if (datafile == NULL) die ("Could not open configurations file");
   
   for (i = 0; i < 9; i++) {
      read_line(datafile);

      if (i==3) {
         if(!get_int(npart)) die ("Could not read number of particles from LAMMPS configuration file");
      }

      if (i==5) {
         double tmp_xa, tmp_xb;
         if (!get_double(&tmp_xa)) die ("Could not read first box size in x direction from LAMMPS configuration file");
         if (!get_double(&tmp_xb)) die ("Could not read second box size in x direction from LAMMPS configuration file");
         box->x = tmp_xb - tmp_xa;
      }

      if (i==6) {
         double tmp_ya, tmp_yb;
         if (!get_double(&tmp_ya)) die ("Could not read first box size in y direction from LAMMPS configuration file");
         if (!get_double(&tmp_yb)) die ("Could not read second box size in y direction from LAMMPS configuration file");
         box->y = tmp_yb - tmp_ya;
      }
   }

   fclose(datafile);
   
   

   /*--- 2. Validity checks ---*/

   if (*npart < 1) {
      die ("The number of discs must be at least 1.");
   }

   if (*dr <= 0) {
      die ("Bin width has to be greater than 0.");
   }

   if (*nsweeps < 1) {
      die ("Number of sweeps must be at least 1");
   }


   /*--- 3. Summarize results on standard output ---*/
   printf (" Configurations file:                      %s\n", filename);
   printf (" Simulation cell dimensions:               %.8lf, %.8lf\n",
           box->x, box->y);
   printf (" Total number of discs:                    %ld\n", *npart);
   printf (" Total number of sweeps:                   %ld\n", *nsweeps);
   printf (" Bin width:                                %lf\n", *dr);
   printf ("\n");


}

/*..............................................................................*/
