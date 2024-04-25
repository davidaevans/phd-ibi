#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

#define ZEROTOL 1.0e-12     /* Dot products below ZEROTOL are deemed zero */
#define MAXO 100            /* Maximum number of connections per rod */

/* Square of a variable */
#define SQ(x) ((x) * (x))

/* Dot product in 2D */
#define DOT(a,b) ((a).x * (b).x + (a).y * (b).y)


struct vector {             /* Define a 2D vector structure */
   double x;
   double y;
};

struct disc {              /* Define a disc */
   long idx;               /* Index of each spherocylinder (0,1,2...) for dereferencing pointers */
   struct vector pos;      /* Position vector */
};



