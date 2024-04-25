void die(char string[]);

void read_options(long *npart, 
                  struct vector *box,
                  double *dr,
                  long *nsweeps,
                  char *filename);


void load(FILE *configfile,
          struct disc *particle,
          long npart,
          struct vector box);

void rdf(struct disc *particle,
         long *rdfhist,
         long npart,
         long numbins,
         double dr,
         double maxsep,
         struct vector box);

void normalise_and_write_rdf(long *rdfhist,
                             long numbins,
                             long nsweeps,
                             long npart,
                             double dr,
                             struct vector box);

double imagesep(struct vector r1, struct vector r2, struct vector box);

double anint(double arg);