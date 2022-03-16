/*
 * Orbital simulation view
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#ifndef ORBITALSIMVIEW_H
#define ORBITALSIMVIEW_H

#include "orbitalSim.h"

class OrbitalView
{
public:
    void renderOrbitalSim3D(OrbitalSim *sim);
    void renderOrbitalSim2D(OrbitalSim *sim);

private:
    const char* getISODate(float currentTime);
};

#endif
