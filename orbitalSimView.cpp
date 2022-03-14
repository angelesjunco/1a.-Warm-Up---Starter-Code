/*
 * Orbital simulation view
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 */

#include <time.h>

#include "orbitalSimView.h"

const char* getISODate(float currentTime) {
    // Epoch: 2022-01-01
    struct tm epoch_tm = { 0, 0, 0, 1, 0, 122 };
    time_t epoch = mktime(&epoch_tm);

    // Convert epoch time to local time
    time_t local_time = epoch + (time_t)currentTime;

    // Print ISO date for local time
    struct tm* local_tm = localtime(&local_time);
    return TextFormat("Date: %04d-%02d-%02d", 1900 + local_tm->tm_year, local_tm->tm_mon + 1, local_tm->tm_mday);
}

void renderOrbitalSim3D(OrbitalSim *sim)
{
    for(size_t i=0;i<9;++i)
    {
        Vector3 scaledPos=Vector3Scale(sim->p[i].position, pow(10,-11));
        DrawSphere(scaledPos, 0.005F*logf(sim->p[i].radius), sim->p[i].color);
        DrawPoint3D(scaledPos, sim->p[i].color);
    }
}

void renderOrbitalSim2D(OrbitalSim *sim)
{
    DrawFPS(40,40);
}
