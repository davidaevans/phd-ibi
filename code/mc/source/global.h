#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ZEROTOL 1.0e-12     /* Dot pdiscucts below ZEROTOL are deemed zero */
#define MAXO 100            /* Maximum number of connections per disc */


/* Square of a variable */
#define SQ(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))

/* Dot pdiscuct in 2D */
#define DOT(a,b) ((a).x * (b).x + (a).y * (b).y)

/* Acceptance ratio */
#define RATIO(a) ( ((a).acc+(a).rej) > 0 ? 1.0*(a).acc/((a).acc+(a).rej) : 0.0 )

struct vector {             /* Define a 2D vector structure */
   double x;
   double y;
};

struct disc {     /* Define a disc */
   long idx;                /* Index of each disc (0,1,2...) for dereferencing pointers */
   struct vector pos;       /* Position vector */
   // struct vector dir;       /* Unit direction vector of axis */
   //double theta;            /* Polar angle dorresponding to dir */
   // int species;             /* 0 for species 1 or 1 for species 2 */
   double diameter;           /* Diameter of particle */
   // double response;         /* Prefactor for the energy function */
   long cell;               /* Cell in cell-list scheme to which particle belongs */
   struct disc *next;   /* Pointer to next particle in the same cell */
   struct disc *prev;   /* Pointer to previous particle in the same cell */
};

struct disp {               /* Define step size and acceptance ratio statistics */
   double mx;               /* Maximum displacement */
   long acc;                /* Number of accepted steps */
   long rej;                /* Number of rejected steps */
};
 
struct stat {               /* Define statistics counters */
   double sum;
   double sum2;
   long samples;
   double mean;
   double rms;
};

// long seed;                  /* Seed for random number generator */
// #ifndef SEED_DEFINITION
// #define SEED_DEFINITION 1 
extern long seed;                  /* Seed for random number generator */
// #endif