/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 * 
 * GRUPO 3 - LEVEL 1
 * Santiago Feldman 
 * Angeles Junco
 * 
 * PASOS SIGUIENTES
 * 
 * 1. Utilizamos float para representar las masas, velocidades, aceleraciones y distancias porque estas magnitudes físicas
 * toman valores continuos de los números reales. Float nos permite simular correctamente esa continuidad. Int, por ejemplo, 
 * hubiera tomado valores discretos para las magnitudes. Además utilizamos float y no double, que también permite simular
 * números reales, porque la precisión de float era la suficiente como para crear una simulación "convincente".
 * 
 * 3. La complejidad algorítmica de la simulación es O(n^2) debido a los "for" anidados de las líneas 106 y 113 (en este archivo),
 * que son la "estructura" más compleja del programa.
 * 
 */

#include "orbitalSim.hpp"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743*(pow(10,-11))
#define ASTEROIDS_MEAN_RADIUS 4E11F
#define ASTEROIDS_MEAN_WEIGHT 0X3B9ACA00


OrbitalSim::OrbitalSim(float timeStep)
{
    this->timeStep=timeStep;
    timeElapsed=0;
    numberOfBodies=SOLARSYSTEM_BODYNUM+N_ASTEROID;

    bodies = new OrbitalBody[SOLARSYSTEM_BODYNUM+N_ASTEROID]; 
}

// Gets a random value between min and max
float OrbitalSim::getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

int OrbitalSim::getNumberOfBodies()
{
    return numberOfBodies;
}

float OrbitalSim::getTimeElapsed()
{
    return timeElapsed;
}
// Places an asteroid
//
// centerMass: mass of the most massive object in the star system
void OrbitalSim::placeAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabs(l));
    float phi = getRandomFloat(0, 2 * M_PI);

    // Surprise!
    //phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->setMass(ASTEROIDS_MEAN_WEIGHT);  // Typical asteroid weight: 1 billion tons
    body->setRadius(ASTEROIDS_MEAN_RADIUS); // Typical asteroid radius: 2km
    body->setColor(GRAY);
    body->setPosition ({r * cosf(phi), 0, r * sinf(phi)});
    body->setVelocity ({-v * sinf(phi), vy, v * cosf(phi)});

}

// Make an orbital simulation
void OrbitalSim::makeOrbitalSim(float timeStep)
{
    for(size_t i=0 ; i<SOLARSYSTEM_BODYNUM ; ++i)
    {
        bodies[i].setName(solarSystem[i].name);
        bodies[i].setMass(solarSystem[i].mass);
        bodies[i].setRadius(solarSystem[i].radius);
        bodies[i].setColor(solarSystem[i].color);
        bodies[i].setPosition(solarSystem[i].position);
        bodies[i].setVelocity(solarSystem[i].velocity);
    }
    for(size_t j=SOLARSYSTEM_BODYNUM ; j<numberOfBodies ; ++j)
    {
        placeAsteroid(&bodies[j], bodies[0].getMass());
    }

}

// Simulates a timestep
void OrbitalSim::updateOrbitalSim()
{
    // Calculation of force and acceleration
    for(size_t i=0 ; i<(SOLARSYSTEM_BODYNUM+N_ASTEROID) ; ++i)
    {
        raylib::Vector3 resultantForce;
        resultantForce.x=0;
        resultantForce.y=0;
        resultantForce.z=0;

        for(size_t j=0;j<SOLARSYSTEM_BODYNUM;++j)
        {
            if(i!=j) 
            {
                raylib::Vector3 unitVector=Vector3Subtract(this->bodies[i].getPosition(),this->bodies[j].getPosition());
                float vectorMod = Vector3Length(unitVector);
                unitVector=Vector3Scale(unitVector,1/vectorMod);

                raylib::Vector3 force=Vector3Scale(unitVector,
                              -GRAVITATIONAL_CONSTANT*(this->bodies[i].getMass())*(this->bodies[j].getMass())/(vectorMod*vectorMod));
                resultantForce=Vector3Add(resultantForce,force);
            }
        }

        raylib::Vector3 acceleration;
        acceleration=Vector3Scale(resultantForce, 1/(this->bodies[i].getMass()));

        this->bodies[i].setVelocity(Vector3Add(this->bodies[i].getVelocity(), 
                                 Vector3Scale(acceleration,(this->timeStep))));
        this->bodies[i].setPosition(Vector3Add(this->bodies[i].getPosition(), 
                                 Vector3Scale((this->bodies[i].getVelocity()),(this->timeStep))));
    }

    (this->timeElapsed)+=(this->timeStep);    // Time update
}

void OrbitalBody::setName(std::string name)
{
    this->name=name;
}

void OrbitalBody::setMass(float mass)
{
    this->mass = mass;
}

float OrbitalBody::getMass()   
{
    return mass;
}

void OrbitalBody::setRadius(float radius)
{
    this->radius = radius;
}

float OrbitalBody::getRadius()
{
    return radius;
}

void OrbitalBody::setColor(Color color)
{
    this->color = color;
}

Color OrbitalBody::getColor()
{
    return color;
}

void OrbitalBody::setPosition(raylib::Vector3 position)
{
    this->position = position;
}

raylib::Vector3 OrbitalBody::getPosition()
{
    return position;
}

void OrbitalBody::setVelocity(raylib::Vector3 velocity)
{
    this->velocity = velocity;
}

raylib::Vector3 OrbitalBody::getVelocity()
{
    return velocity;
}

void OrbitalBody::setAcceleration(raylib::Vector3 acceleration)
{
    this->acceleration = acceleration;
}

raylib::Vector3 OrbitalBody::getAcceleration()
{
    return acceleration;
}

OrbitalSim::~OrbitalSim()
{
    delete[] bodies;
}