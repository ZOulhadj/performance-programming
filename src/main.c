#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DECL
#include "md.h"

static double second()
{
    struct timeval tp;
    struct timezone tzp;
    gettimeofday(&tp, &tzp);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
}

// Entry point into the program
int main(int argc, char **argv)
{
    // Main simulation variables
    int nstep = 100;
    int nsave = 5;
    int collisions = 0;
    int nbody = 4 * 1024;
    double gravity = 2.0;
    double central_mass = 1000.0;
    double delta_time   = 0.02;

    struct vec3 wind;
    wind.x = 0.9;
    wind.y = 0.4;
    wind.z = 0.0;

    if (argc > 1) {
        nstep = atoi(argv[1]);
    }

    // Partical forces, positions, velocities
    double *mass   = calloc(nbody, sizeof(double));
    double *radius = calloc(nbody, sizeof(double));
    double *vis    = calloc(nbody, sizeof(double));
    struct vec3 *f      = calloc(nbody, sizeof(struct vec3));
    struct vec3 *pos    = calloc(nbody, sizeof(struct vec3));
    struct vec3 *velo   = calloc(nbody, sizeof(struct vec3));

    // Read the contents of the input.data file into allocated arrays
    FILE *in, *out;
    char name[80];
    in = fopen("input.dat", "r");
    if (!in) {
        perror("input.dat");
        exit(1);
    }

    for (int i = 0; i < nbody; ++i) {
        fscanf(in, "%16le %16le %16le %16le %16le %16le %16le %16le %16le",
            &mass[i], &radius[i], &vis[i],
            &pos[i].x, &pos[i].y, &pos[i].z,
            &velo[i].x, &velo[i].y, &velo[i].z);
    }
    fclose(in);

    
    // Begin the main iteration loop
    double tstart = second();
    for (int i = 1; i <= nsave; ++i) {
        double start = second();

        evolve(nstep, delta_time, nbody, gravity, central_mass, 
               wind, 
               pos, velo, f, 
               mass, radius, vis,
               &collisions);

        double stop = second();
        printf("%d timesteps took %f seconds\n", nstep, stop - start);
        printf("collisions %d\n", collisions);
        fflush(stdout);

        // Write out final result into each timestep specific file
        sprintf(name, "output.dat%03d", i * nstep);
        out = fopen(name, "w");
        if (!out) {
            perror(name);
            exit(1);
        }

        for (int j = 0; j < nbody; ++j) {
            fprintf(out, "%16.8E %16.8E %16.8E %16.8E %16.8E %16.8E %16.8E %16.8E %16.8E\n",
            mass[j], radius[j], vis[j],
            pos[j].x, pos[j].y, pos[j].z,
            velo[j].x, velo[j].y, velo[j].z);
        }
        fclose(out);
    }
    double tstop = second();
    printf("%d timesteps took %f seconds\n", nsave * nstep, tstop - tstart);

    // Free allocated memory
    free(mass);
    free(vis);
    free(radius);
    free(f);
    free(pos);
    free(velo);
}
