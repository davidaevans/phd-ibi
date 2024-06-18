#include "global.h"
#include "prototypes.h"

/*..............................................................................*/

/*
Dumps a configuration to the supplied file handle.  The director is normalised
to the length of the disc.
*/

// void draw(FILE *outfile, struct vector box, long npart,
//           struct disc *particle)
// {
//    long i;

//    for (i=0; i<npart; i++) {
//       fprintf (outfile,
//          "%15.8le %15.8le 0.0\n",
//          box.x * (particle[i].pos.x - anint(particle[i].pos.x)),
//          box.y * (particle[i].pos.y - anint(particle[i].pos.y)));
//    }
// }

/*..............................................................................*/
// void dumpconfigs(FILE *outfile, struct disc *particle, struct vector box, long ntot, long sweep) 
// {
//    long i;
//    double tmp_angle;
//    /*
//    ITEM: TIMESTEP
//    0
//    ITEM: NUMBER OF ATOMS
//    20000
//    ITEM: BOX BOUNDS pp pp pp
//    0.0000000000000000e+00 1.7386773537360827e+02
//    0.0000000000000000e+00 3.0114775146403002e+02
//    0.0000000000000000e+00 1.7386773537360828e-01
//    ITEM: ATOMS id type xu yu zu 
//    */
//    fprintf(outfile, "SWEEP:\n%ld\n", sweep);
//    fprintf(outfile, "NUMBER OF PARTICLES:\n%ld\n", ntot);
//    fprintf(outfile, "BOX SIZES: (X Y Z)\n%lf %lf\n%lf %lf\n%lf %lf\n",
//             0.0, box.x,
//             0.0, box.y,
//             0.0, 0.0);
//    fprintf(outfile, "ID X Y THETA\n");

//    for (i = 0; i<ntot; i++){
//       if (particle[i].dir.x == 0) {tmp_angle = 0.0;}
//       else {tmp_angle = atan(particle[i].dir.y/particle[i].dir.x);}
      
//       fprintf(outfile, "%ld %lf %lf %.6lf\n",
//       particle[i].idx,
//       particle[i].pos.x,
//       particle[i].pos.y,
//       tmp_angle);
//    }
   
// }

/*..............................................................................*/
void dumpconfigs_LAMMPS(FILE *outfile, struct disc *particle, struct vector box, long npart, long sweep) 
{
   long i;
   /*
   ITEM: TIMESTEP
   0
   ITEM: NUMBER OF ATOMS
   20000
   ITEM: BOX BOUNDS pp pp pp
   0.0000000000000000e+00 1.7386773537360827e+02
   0.0000000000000000e+00 3.0114775146403002e+02
   0.0000000000000000e+00 1.7386773537360828e-01
   ITEM: ATOMS id type xu yu zu 
   */
   fprintf(outfile, "SWEEP:\n%ld\n", sweep);
   fprintf(outfile, "NUMBER OF PARTICLES:\n%ld\n", npart);
   fprintf(outfile, "BOX SIZES: (X Y Z)\n%lf %lf\n%lf %lf\n%lf %lf\n",
            0.0, box.x,
            0.0, box.y,
            0.0, 0.0);
   fprintf(outfile, "ID TYPE X Y Z THETA\n");

   for (i = 0; i<npart; i++){
      fprintf(outfile, "%ld %d %lf %lf %lf\n",
      particle[i].idx,
      1,
      (particle[i].pos.x),
      (particle[i].pos.y),
      0.0);
   }
   
}

// /*..............................................................................*/
// void dumpconfigs_equil(FILE *outfile, struct disc *particle, struct vector box, long ntot, long sweep, struct disp *trans) 
// {
//    long i;
//    double tmp_angle;
//    /*
//    ITEM: TIMESTEP
//    0
//    ITEM: NUMBER OF ATOMS
//    20000
//    ITEM: BOX BOUNDS pp pp pp
//    0.0000000000000000e+00 1.7386773537360827e+02
//    0.0000000000000000e+00 3.0114775146403002e+02
//    0.0000000000000000e+00 1.7386773537360828e-01
//    ITEM: ATOMS id type xu yu zu 
//    */
//    fprintf(outfile, "TRANS_STEP_SIZE:\n%lf %lf\n", trans[0].mx, trans[1].mx);
//    fprintf(outfile, "SWEEP:\n%ld\n", sweep);
//    fprintf(outfile, "NUMBER OF PARTICLES:\n%ld\n", ntot);
//    fprintf(outfile, "BOX SIZES: (X Y Z)\n%lf %lf\n%lf %lf\n%lf %lf\n",
//             -box.x/2, box.x/2,
//             -box.y/2, box.y/2,
//             0.0, 0.0);
//    fprintf(outfile, "ID TYPE X Y Z THETA\n");

//    for (i = 0; i<ntot; i++){
//       if (particle[i].dir.x == 0) {tmp_angle = 0.0;}
//       else {tmp_angle = atan(particle[i].dir.y/particle[i].dir.x);}

//       fprintf(outfile, "%ld %d %lf %lf %lf %.6lf\n",
//       particle[i].idx,
//       1,
//       particle[i].pos.x * box.x,
//       particle[i].pos.y * box.y,
//       0.0,
//       tmp_angle);
//    }
   
// }