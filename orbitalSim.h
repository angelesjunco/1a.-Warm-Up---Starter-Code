/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#define _USE_MATH_DEFINES  /* Enable M_PI definition */

#include <stdlib.h>        /* rand() */
#include <math.h>          /* M_PI */
#include <string>

#include "raylib.h"
#include "raymath.h"

#define N_ASTEROID 1000

class OrbitalBody
{
public:
    OrbitalBody();
    ~OrbitalBody();   
    
    void setName(std::string name);

private:
    const char *name; // Name
    float mass;		  // [kg]
    float radius;	  // [m]
    Color color;	  // raylib color
    Vector3 position; // [m]
    Vector3 velocity; // [m/s]
    Vector3 acceleration;


};

class OrbitalSim
{
public:
    OrbitalSim(float timeStep, int numBodies);
    ~OrbitalSim();

    OrbitalSim *makeOrbitalSim(float timeStep);
    void updateOrbitalSim(OrbitalSim *sim);

    OrbitalBody* bodies;
private:
    float getRandomFloat(float min, float max);
    void placeAsteroid(OrbitalBody body, float centerMass);

    float timeStep;
    float timeElapsed;
    int numberOfBodies;
};




#endif
