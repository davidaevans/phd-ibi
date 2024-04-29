// {
// void accumulate(struct stat *q, double x);

// double anint(double arg);

// double axissep2(struct vector r_cm, struct vector dir1, struct vector dir2,
//                 double length1, double length2);

// void baccumulate(struct stat *q, double x, double x2, long n);

// void checkcells(long ntot, long ncells, struct disc **cfirst,
//    long **neighbour, struct disc *particle);

// void die(char string[]);

// void draw(FILE *outfile, struct vector box, long npart,
//           struct disc *particle);

// void equilibrate_theta(long npart, long equilibrate,
//    struct disc *particle, struct disp *step, double fraction,
//    double *length, double *response);

// void fixed_S2(long npart, struct disc *particle, double *sf2);

// long getcell(struct vector pos, long ncellx, long ncelly);

// double linemin(double criterion, double halfl);

// struct vector image(struct vector r1, struct vector r2, struct vector box);

// void init_config(long *npart, struct vector box, double *length, double *response,
//    struct disc *particle, struct vector fixed_dipole);

// void maxstep(struct disp *x, double hi, double lo);

// void move_theta(long npart, struct disc *particle, struct disp *step);

// void normalise(struct vector *);

// int overlap(struct vector r_cm, double diameter1, double diameter2, double shell);

// int pairo(long ntot, long testp, struct disc *particle,
//           struct vector box, struct disc **cfirst, long **neighbour);

// struct vector percolate(long npart, struct disc *particle, double shell,
//                         struct vector box, long *ctot,
//                         struct stat *npc1, struct stat *npc2,
//                         struct disc **cfirst, long **neighbour);

// double pythag(double a, double b);

// int soverlap(struct vector r_cm, struct vector dir1, struct vector dir2,
//              double length1, double length2);

// struct vector spantest(long npart, struct disc *particle, double shell,
//                        struct vector box, long *ctot,
//                        struct stat *npc1, struct stat *npc2,
//                        struct disc **cfirst, long **neighbour);

// double ran2(long *idum);

// void read_options(long *npart, long *ntot, struct vector *box, double *length,
//    long *nsweeps, long *report, long *record, long *movie, double *shell,
//    double *fieldk, long *equilibrate, double *power, double *response,
//    int *periodic, long *adjust, struct disp *trans, struct disp *rot, int *potential,
//    double *kt, double *wellrange, double *welldepth, int *loadconfig, long *extPotentialLength,
//    double *prefactor, double *expprefactor, struct vector *fixed_dipole, double *dipole_strength, 
//    double *dipole_cutoff, double *ljTrunc);

// double discarea(double length, double shell);

// void simulate(long ntot, long *npart, struct vector box, double *length,
//    double *response, long nsweeps, long report, long movie, long adjust,
//    long record, double shell, struct disp *trans, struct disp *rot, int periodic,
//    struct disc *particle, int potential, double kt, double wellrange, double welldepth,
//    double **extPotential, long extPotentialLength, double prefactor, double expprefactor,
//    double extPotentialR0, double extPotentialSpacing, struct vector fixed_dipole, 
//    double dipole_strength, double dipole_cutoff, double ljTrunc);

// long singledisc(long npart, struct disc *particle, long target,
//                struct vector box, int *list);

// double smectic(long npart, struct disc *p, long n);

// void touching(long npart, struct disc *particle, struct vector box,
//               double shell, long *nc, long **conn, long *ctot,
//               struct disc **cfirst, long **neighbour);

// void touching_nopbc(long npart, struct disc *particle, struct vector box,
//               double shell, long *nc, long **conn, long *ctot,
//               struct disc **cfirst, long **neighbour);

// int decision(struct vector vold, long oldcell, struct disc *particle,
//                     int potential, struct vector box, long ntot, long testp,
//                     struct disc **cfirst, long **neighbour, double kt,
//                     double wellrange, double welldepth,
//                     double **extPotential, long extPotentialLength,
//                     double prefactor, double expprefactor,
//                     double extPotentialR0, double extPotentialSpacing,
//                     double dipole_strength, double dipole_cutoff, double ljTrunc);

// int metropolis(double deltaE, double kt);

// double phs(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp);
   
// double lj(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double ljTrunc);

// double wca(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp);

// double squarewell(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double wellrange, double welldepth);

// void generateconfig(struct vector box, long ntot, double diameter); 

// void dumpconfigs(FILE *outfile, struct disc *particle, struct vector box, long ntot, long sweep); 

// void dumpconfigs_LAMMPS(FILE *outfile, struct disc *particle, struct vector box, long ntot, long sweep);

// void dumpconfigs_equil(FILE *outfile, struct disc *particle, struct vector box, long ntot, long sweep, struct disp *trans);

// double custompotential(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double wellrange, double welldepth);

// void loadconfig_equil(FILE *equilfile, struct disc *particle, long npart, struct disp *trans,
//          struct vector box); 

// double externalpotential(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double **extPotential, long extPotentialLength, double extPotentialR0, double extPotentialSpacing);

// double yukawa(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double prefactor, double expprefactor);

// double split_potential(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double **extPotential, long extPotentialLength, double extPotentialR0, double extPotentialSpacing);
           
// void load_potential(double **extPotential, long extPotentialLength, double *extPotentialSpacing, double *extPotentialR0);

// double interpolate(double r1, double r2, double v1, double v2, double r_target);

// double get_ext_energy(double **extPotential, long extPotentialLength, double r, double extPotentialR0, double extPotentialSpacing);

// void checkPointential(double **extPotential, long extPotentialLength, double extPotentialR0, double extPotentialSpacing);

// double aligned_dipole(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
//            struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
//            long testp, double dipole_strength, double dipole_cutoff);

// /* Prototypes for keywords library */
// int  read_line(FILE *);
// int  get_string(char [], int);
// void upper_case(char []);
// int  get_int(long int *);
// int  get_double(double *);


// void checkWCA();

// void checkLJPotential();
// }

void read_options(long *npart, struct vector *box, double *diameter,
    long *nsweeps, long *dump, long *equilibrate, long *periodic, 
    long *adjust, struct disp *trans, double *kt);

long get_file_length(FILE *fp);

/* Prototypes for keywords library */
int  read_line(FILE *);
int  get_string(char [], int);
void upper_case(char []);
int  get_int(long int *);
int  get_double(double *);

double ran2(long *idum);

void die(char string[]);

double discarea(double length);

void load_potential(long potential_length, double **potential, FILE *potential_file, double *max_potential_distance, double *dr);

void generate_config(struct disc *particle, struct vector box, long npart, double diameter);

void simulate(long npart, struct vector box, double diameter,
    long nsweeps, long dump, long adjust, struct disp *trans, long periodic,
    struct disc *particle, double **potential, double kt, double max_potential_distance, double dr, long potential_length);

long getcell(struct vector pos, long ncellx, long ncelly, struct vector box);

int accept_move(struct vector vold, long oldcell, struct disc *particle,
                struct vector box, long npart, long testp,
                struct disc **cfirst, long **neighbour, double kt,
                double **potential, long potential_length, double max_potential_distance, double dr);

double calculate_energy_difference(struct vector vold, long cellold, struct vector vnew, long cellnew, double diameter,
           struct disc **cfirst, long **neighbour, struct vector box, struct disc *particle, 
           long testp, double **potential, long potential_length, double max_potential_distance, double dr);

struct vector image(struct vector r1, struct vector r2, struct vector box);

double get_ext_energy(double **potential, long potential_length, double r_squared, double max_potential_distance, double dr);

double interpolate(double r1, double r2, double v1, double v2, double r_target);

int metropolis(double deltaE, double kt);

void dumpconfigs_LAMMPS(FILE *outfile, struct disc *particle, struct vector box, long npart, long sweep);

void maxstep(struct disp *x, double hi, double lo);

void accumulate(struct stat *q, double x);

double anint(double arg);

void check_potential(double **potential, long potential_length, double max_potential_distance, double dr);