#include "global.h"
#include "prototypes.h"

// Calculates the number of lines in a file and then resets the pointer back to the start
long get_file_length(FILE *fp){
    long lines = 0;
    int ch;
    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n')
        {
            lines++;
        }
    }
    rewind(fp);
    return lines;
}

void load_potential(long potential_length, double **potential, FILE *potential_file, double *max_potential_distance, double *dr) {
    long i;
    double r0;

    // Load potential from file
    for (i = 0; i < potential_length; i++) {
        if (read_line(potential_file)) {
            if (!get_double(&(potential[i][0]))) die ("Could not read value of position when loading potential.");
            if (!get_double(&(potential[i][1]))) die ("Could not read value of potential when loading potential.");
        } else {
            die("Error reading line in potential file");
        }
    }

    *dr = (double) (potential[1][0] - potential[0][0]);
    *max_potential_distance = potential[(potential_length)-1][0];
    r0 = *dr/2;

    printf("Spacing in r: %lf\n", *dr);
    printf("Maximum separation: %lf\n", *max_potential_distance);
    printf("Expected first bin r: %lf\n", r0);
    printf("Actual first bin r: %lf\n\n", potential[0][0]);

    if (fabs(potential[0][0] - r0) > 0.0001) die ("Potential should be at bin centres.");

}