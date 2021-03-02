/* 
 * This is the head file of a planet.
 * Using this file we can create a planet instance.
 * The planet will be affected by the gravitational force between itself and other planets.
 * This class can calcuate this force and update the position and velocity of the planet based on the force.
 * @author Zhewei Liu. AndrewId: zheweil.
 */
#pragma once
#include <string>
#include <vector>

#include "yspng.h"

using namespace std;

class Planet {
private:
    double xxPos; // The x position of the planet.
    double yyPos; // The y position of the planet.
    double xxVel; // The projection of the velocity in the x direction.
    double yyVel; // The projection of the velocity in the y direction.
    double mass; // The mass of the planet.
    string name; // The name of the planet.
    double color; // The color of the orbit.

public:
    // The constructor of the planet class.
    Planet(string name, double color, double xP, double yP,
        double xV, double yV, double m);

    // Create a copy of the planet.
    Planet(const Planet& origin);

    // Calculate the distance between two planets.
    double calcDistance(const Planet& p);

    // Calculate the force between two planets.
    double calcForceExertedBy(const Planet& p);

    // Calculate the force exerted in the X directions.
    double calcForceExertedByX(const Planet& p);

    // Calculate the force exerted in the X directions.
    double calcForceExertedByY(const Planet& p);

    // Calculate  calculates the net X force exerted by all planets in that array upon the current planet. 
    double calcNetForceExertedByX(const vector<Planet>& planetList);

    // Calculate the net Y force exerted by all planets in that array upon the current planet. 
    double calcNetForceExertedByY(const vector<Planet>& planetList);

    // Update the planet¡¯s velocity and position in a small period of time dt.
    void update(double dt, double fx, double fy);

    // Draw the planet and get the position of the planet.
    void draw(double range, double& x, double& y, int centerX, int centerY);

    // Get the position, velocity, mass and name of the planet.
    double getXPosition() { return xxPos; }
    double getYPosition() { return yyPos; }
    double getXVelocity() { return xxVel; }
    double getYVelocity() { return yyVel; }
    double getMass() { return mass; }
    string getName() { return name; }
    double getColor() { return color; }
};
