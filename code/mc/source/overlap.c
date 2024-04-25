#include "global.h"
#include "prototypes.h"

/*..............................................................................*/
 
/*
Determines whether two "2D discs" overlap.  The distance between the axes
below which overlap is defined is supplied as "crit".  For overlap of the cores,
this is 1, but for overlap of conducting shells it may be any non-negative
number.  The vector from the centre of disc 2 to 1, r_cm, (in real,
not scaled coordinates) must be sent as an argument in this version.

Returns 1 if there is an overlap, 0 if not.
*/

int overlap(struct vector r_cm, double diameter1, double diameter2, double shell)
{
   double sep; //scalar separation of two discs
   double thresh; //threshold value for contact of two discs

   sep = DOT(r_cm, r_cm);
   thresh = (diameter1 * shell)/2 + (diameter2 * shell)/2;
   
   if (sep <= SQ(thresh)) {
      //printf("overlap\n");
      return 1;
   } else {
      //printf("no overlap\n");
      return 0;
   }

}

/*..............................................................................*/

/*
Returns the vector pointing from the centre of mass of particle 2 to the
centre of mass of the closest image of particle 1 in 2D.
*/

struct vector image(struct vector r1, struct vector r2, struct vector box)
{
   struct vector r12;

   r12.x = (r1.x - r2.x)/box.x;
   r12.y = (r1.y - r2.y)/box.y;

   r12.x = box.x * (r12.x - anint(r12.x));
   r12.y = box.y * (r12.y - anint(r12.y));

   return r12;
}

/*..............................................................................*/
 
/*
Returns the nearest integer to its argument as a double precision number. e.g.
anint(-0.49) = 0.0 and anint(-0.51) = -1.0. Equivalent to the Fortran intrinsic
ANINT.
*/
 
double anint(double arg)
{
   if (arg < 0) {
      return (double)( (long)(arg-0.5) );
   } else {
      return (double)( (long)(arg+0.5) );
   }
}
                                
/*..............................................................................*/

/*
Determines whether the core of a specified "2D disc" (testp) overlaps
with the core of any other particle.  Returns 1 if an overlap is detected and 0
if not.
*/

int pairo(long ntot, long testp, struct disc *particle,
          struct vector box, struct disc **cfirst, long **neighbour)
{
   long *cell;
   struct disc *test;
   struct vector r_cm;

   /* Loop over all cells adjacent to particle */
   cell = &neighbour[particle[testp].cell][0];
   while (*cell >= 0) {
      /* Loop over all particles in cell */
      test = cfirst[*cell];
      while (test) {

         if (testp != test->idx) {
            //printf("a\n");
            r_cm = image(particle[testp].pos, test->pos, box);
            //compares on hard core overlap - i.e. shell is set to 1
            if ( overlap(r_cm, particle[testp].diameter, test->diameter, 1.0) )
            { return 1; }
         }

      test = test->next;
      }  /* End of loop over particles in adjacent cell */

      cell++;
   }  /* End of loop of adjacent cells */

   return 0;
}

