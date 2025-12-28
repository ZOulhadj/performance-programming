#include "md.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

void evolve(int count, double dt, int nbody, double gravity, double central_mass,  
            struct vec3 wind,  
            struct vec3 *pos, struct vec3 *velo, struct vec3 *f,  
            double *mass, double *radius, double *vis,
            int *collisions)
{
    int hit_count = 0;
    for (int step = 1; step <= count; ++step) {
        printf("timestep %d\n", step);
        printf("collisions %d\n", hit_count);

        /* set the viscosity term in the force calculation */
        /* add the wind term in the force calculation */
        for (int i = 0; i < nbody; ++i) {
            double px =  pos[i].x, py =  pos[i].y, pz =  pos[i].z;
            double vx = velo[i].x, vy = velo[i].y, vz = velo[i].z;
            
            double Wv = gravity * mass[i] * central_mass;
            double r = sqrt(px*px + py*py + pz*pz);
            double r_pow_3 = r * r * r;

            double fx = -vis[i] * (vx + wind.x);
            double fy = -vis[i] * (vy + wind.y);
            double fz = -vis[i] * (vz + wind.z);

            f[i].x = fx - (Wv * px / r_pow_3);
            f[i].y = fy - (Wv * py / r_pow_3);
            f[i].z = fz - (Wv * pz / r_pow_3);
        }

        // Add pairwise forces
        for (int i = 0; i < nbody; ++i) {
            for (int j = i + 1; j < nbody; ++j) {
                double dx = pos[i].x - pos[j].x;
                double dy = pos[i].y - pos[j].y;
                double dz = pos[i].z - pos[j].z;

                double delta_r = sqrt(dx * dx + dy * dy + dz * dz);
                double size = radius[i] + radius[j];
                double Wv = gravity * mass[i] * mass[j];
                double inv_r3 = 1.0 / (delta_r * delta_r * delta_r);
                double F = Wv * inv_r3;
                double fx = F * dx, fy = F * dy, fz = F * dz;

                double sign = copysign(1.0, size - delta_r);
                hit_count += (sign > 0);

                f[i].x += sign * fx;
                f[i].y += sign * fy;
                f[i].z += sign * fz;
                f[j].x -= sign * fx;
                f[j].y -= sign * fy;
                f[j].z -= sign * fz;
            }
        }

        // update positions and velocities
        for (int i = 0; i < nbody; ++i) {
            pos[i].x += dt * velo[i].x;
            pos[i].y += dt * velo[i].y;
            pos[i].z += dt * velo[i].z;

            velo[i].x += dt * (f[i].x / mass[i]);
            velo[i].y += dt * (f[i].y / mass[i]);
            velo[i].z += dt * (f[i].z / mass[i]);
        }
    }

    *collisions = hit_count;
}