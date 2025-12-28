/*
 *  nbody	  Number of particles
 *  pos		  Position of the particles
 *  vel		  Velocity of the particles
 *  f		  Forces acting on each particle
 *  vis           Viscosity coefficient for each particle
 *  mass	  Mass of each particle
 */

struct vec3 {
    double x;
    double y;
    double z;
};

void evolve(int count, double dt, int nbody, double gravity, double central_mass,  
            struct vec3 wind,  
            struct vec3 *pos, struct vec3 *velo, struct vec3 *f,  
            double *mass, double *radius, double *vis,
            int *collisions);
