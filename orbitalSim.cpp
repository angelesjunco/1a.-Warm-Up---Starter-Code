/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 * 
 * GRUPO 3 
 * Santiago Feldman 
 * 
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
    phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->mass = 0X3B9ACA00;  // Typical asteroid weight: 1 billion tons
    body->radius = 0X7D0; // Typical asteroid radius: 2km
    body->color = GRAY;
    body->position = {r * cosf(phi), 0, r * sinf(phi)};
    body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};

}

// Make an orbital simulation
OrbitalSim *makeOrbitalSim(float timeStep)
{
    orbitalsim_t *sim = (orbitalsim_t*) malloc(sizeof(orbitalsim_t));
    if(sim==NULL)
    {
        return NULL;
    }
    sim->p= (orbitalbody_t*) malloc(sizeof(orbitalbody_t)*(SOLARSYSTEM_BODYNUM+N_ASTEROID));
    if(sim->p==NULL)
    {
        free(sim);
        return NULL;
    }
    sim->timeStep=timeStep;
    sim->timeElapsed=0;
    sim->numberOfBodies=SOLARSYSTEM_BODYNUM+N_ASTEROID;
    for(int i=0; i<SOLARSYSTEM_BODYNUM;++i)
    {
        (*sim).p[i].name= (solarSystem[i]).name;
        (*sim).p[i].mass= (solarSystem[i]).mass;
        (*sim).p[i].radius= (solarSystem[i]).radius;
        (*sim).p[i].color= (solarSystem[i]).color;
        (*sim).p[i].position= (solarSystem[i]).position;
        (*sim).p[i].velocity= (solarSystem[i]).velocity;
    }
    for (int x=SOLARSYSTEM_BODYNUM;x<(sim->numberOfBodies);++x)
    {
        placeAsteroid(&sim->p[x], sim->p[0].mass);
    }

    return sim;
}

// Simulates a timestep
void updateOrbitalSim(OrbitalSim *sim)
{
    for(int i=0;i<(SOLARSYSTEM_BODYNUM+N_ASTEROID);++i)
    {
        Vector3 resultantForce;
        resultantForce.x=0;
        resultantForce.y=0;
        resultantForce.z=0;

        for(int j=0;j<SOLARSYSTEM_BODYNUM;++j)
        {
            if(i!=j) 
            {
                Vector3 x=Vector3Subtract( sim->p[i].position ,sim->p[j].position);
                float mod = Vector3Length(x);
                x=Vector3Scale(x,1/mod);

                Vector3 f=Vector3Scale(x,-G*(sim->p[i].mass)*(sim->p[j].mass)/(mod*mod));
                resultantForce=Vector3Add(resultantForce,f);
            }
        }

        Vector3 acc;
        acc=Vector3Scale(resultantForce, 1/(sim->p[i].mass));

        sim->p[i].velocity= Vector3Add(sim->p[i].velocity, Vector3Scale(acc,(sim->timeStep)));
        sim->p[i].position= Vector3Add(sim->p[i].position, Vector3Scale((sim->p[i].velocity),(sim->timeStep)));
    }
    (sim->timeElapsed)+=(sim->timeStep);
}

void freeOrbitalSim(OrbitalSim *sim)
{
    free(sim->p);
    free(sim);
}
