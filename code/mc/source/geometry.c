#include "global.h"
#include "prototypes.h"

/*..............................................................................*/

/*
Returns the cell number for a position in reduced coordinated
(on the unit square -0.5<=x<0.5, -0.5<=y<0.5).
*/

long getcell(struct vector pos, long ncellx, long ncelly, struct vector box)
{
   return (long)( (pos.y/box.y) * ncelly) * ncellx + (long)( (pos.x/box.x) * ncellx);
}

/*..............................................................................*/

/*
Normalise a vector to have unit length.  For speed during heavy use, it is
not checked that the supplied vector has non-zero length.
*/

void normalise(struct vector *u)
{
   double tot;

   tot = sqrt( DOT(*u,*u) );

   (*u).x /= tot;
   (*u).y /= tot;
}

/*..............................................................................*/

/* 
Return area of disc
*/

double discarea(double length) 
{
   return M_PI * SQ(length);
}

/*..............................................................................*/

/* 
Return value of potential via linear interpolation 
*/

double interpolate(double r1, double r2, double v1, double v2, double r_target)
{
   double grad, val;

   //printf("x1: %lf x2: %lf y1: %lf y2: %lf\n", r1, r2, v1, v2);

   grad = (v2-v1)/(r2-r1);

   val = v1 + (r_target-r1) * grad;
   
   return val;
}

/*..............................................................................*/

/* 
Calculate the energy at a given point from external potential.
Assume that the potential is equally spaced and the first value for r is equal to the spacing.

r
*/

double get_ext_energy(double **potential, long potential_length, double r_squared, double max_potential_distance, double dr)
{
   long i;
   double r;
   double r1, r2, v1, v2;
   r = sqrt(r_squared);
   v1 = v2 = r1 =r2 = 0.0;

   if (r > (potential[potential_length-1][0] + dr/2.0)) return 0.0; //TODO: EXTRAPOLATE TO CUTOFF

   i = floor((r-potential[0][0])/dr);
   if (i < 0) {i = 0;}


   if (i == (potential_length - 1)) {i--;}
   if (i > potential_length) {die("Bin error in interpolation");}
   
   r1 = potential[i][0];
   v1 = potential[i][1];
   
   r2 = potential[i+1][0];
   v2 = potential[i+1][1];

   return interpolate(r1, r2, v1, v2, r);
}
