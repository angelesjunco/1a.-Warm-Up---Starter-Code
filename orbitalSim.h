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

#include "raylib.h"
#include "raymath.h"



struct OrbitalBody
{
    // Your code goes here...
};

struct OrbitalSim
{
    // Your code goes here...
};

OrbitalSim *makeOrbitalSim(float timeStep);
void updateOrbitalSim(OrbitalSim *sim);
void freeOrbitalSim(OrbitalSim *sim);

#endif
