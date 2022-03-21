﻿/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 *
 * Main module
 * 
 */

#include "orbitalSim.hpp"
#include "orbitalSimView.hpp"

#define SECONDS_PER_DAY 86400.0F

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "EDA Orbital Simulation");

    // Camera
    Camera3D camera;
    camera.position = {10.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FREE);

    SetCameraPanControl(MOUSE_BUTTON_LEFT);

    // Orbital simulation
    float fps = 60.0F;							  // frames per second
    float timeMultiplier = 10 * SECONDS_PER_DAY; // Simulation speed: 100 days per real second
    float timeStep = timeMultiplier / fps;

    OrbitalSim sim(timeStep);
    sim.makeOrbitalSim(timeStep);

    OrbitalView view; 

    // Game loop
    while (!WindowShouldClose())
    {
        // Update simulation
        sim.updateOrbitalSim();

        // Camera
        UpdateCamera(&camera);

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        view.renderOrbitalSim3D(&sim);
        DrawGrid(10, 10.0f);
        EndMode3D();

        view.renderOrbitalSim2D(&sim);
        EndDrawing();
    }

    CloseWindow();
   
    return 0;
}
