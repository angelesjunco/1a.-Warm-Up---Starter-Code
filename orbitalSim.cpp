/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#include "orbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743E-11F
#define ASTEROIDS_MEAN_RADIUS 4E11F

// Gets a random value between min and max
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

// Places an asteroid
//
// centerMass: mass of the most massive object in the star system
void placeAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabs(l));
    float phi = getRandomFloat(0, 2 * M_PI);

    // Surprise!
    // phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    // body->mass = 1E12F;  // Typical asteroid weight: 1 billion tons
    // body->radius = 2E3F; // Typical asteroid radius: 2km
    // body->color = GRAY;
    // body->position = {r * cosf(phi), 0, r * sinf(phi)};
    // body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};
}

// Make an orbital simulation
OrbitalSim *makeOrbitalSim(float timeStep)
{
    orbitalsim_t *sim = (orbitalsim_t*) malloc(sizeof(orbitalsim_t));
    if(sim==NULL)
    {
        return NULL;
    }
    sim->p= (orbitalbody_t*) malloc(sizeof(orbitalbody_t)*9);
    if(sim->p==NULL)
    {
        free(sim);
        return NULL;
    }
    sim->timeStep=timeStep;
    sim->timeElapsed=0;
    sim->numberOfBodies=9;
    int i;
    for(i=0;i<9;++i)
    {
        (*sim).p[i].name= (solarSystem[i]).name;
        (*sim).p[i].mass= (solarSystem[i]).mass;
        (*sim).p[i].radius= (solarSystem[i]).radius;
        (*sim).p[i].color= (solarSystem[i]).color;
        (*sim).p[i].position= (solarSystem[i]).position;
        (*sim).p[i].velocity= (solarSystem[i]).velocity;
    }
    return sim;
}

// Simulates a timestep
void updateOrbitalSim(OrbitalSim *sim)
{
    int i, j;
    for(i=0;i<9;++i)
    {
        Vector3 resultantForce;
        resultantForce.x=0;
        resultantForce.y=0;
        resultantForce.z=0;

        for(j=0;j<9;++j)
        {
            if(i==j) 
            {
                continue;
            }
            Vector3 x=Vector3Subtract( sim->p[i].position ,sim->p[j].position);
            float mod = Vector3Length(x);
            x=Vector3Scale(x,1/mod);

            Vector3 f=Vector3Scale(x,-G*(sim->p[i].mass)*(sim->p[j].mass)/(mod*mod));
            resultantForce=Vector3Add(resultantForce,f);
        }

        Vector3 acc;
        acc=Vector3Scale(resultantForce, 1/(sim->p[i].mass));

        sim->p[i].velocity= Vector3Add(sim->p[i].velocity, Vector3Scale(acc,(sim->timeStep)));
        sim->p[i].position= Vector3Add(sim->p[i].position, Vector3Scale((sim->p[i].velocity),(sim->timeStep)));

    }
}

void freeOrbitalSim(OrbitalSim *sim)
{
    free(sim->p);
    free(sim);
}
