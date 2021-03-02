/* This is the .cpp file of the Planet.h file.
 * @author Zhewei Liu. AndrewId: zheweil.
 */
#include <iostream>
#include <math.h>
#include <vector>
#include "Planet.h"
#include "ysglfontdata.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "yspng.h"

#define G 6.67e-11

Planet::Planet(string name, double color, double xP, double yP, 
    double xV, double yV, double m)
{
    this->name = name;
    this->color = color;
    xxPos = xP;
    yyPos = yP;
    xxVel = xV;
    yyVel = yV;
    mass = m;
}

Planet::Planet(const Planet& origin)
{
    color = origin.color;
    name = origin.name;
    xxPos = origin.xxPos;
    yyPos = origin.yyPos;
    xxVel = origin.xxVel;
    yyVel = origin.yyVel;
    mass = origin.mass;
}

double Planet::calcDistance(const Planet& p)
{
    double distance;
    distance = sqrt(pow((xxPos - p.xxPos), 2) + pow((yyPos - p.yyPos), 2));
    return distance;
}

double Planet::calcForceExertedBy(const Planet& p)
{
    double force;
    force = G * mass * p.mass;
    double distance;
    distance = calcDistance(p);
    force = force / pow(distance, 2);
    return force;
}

double Planet::calcForceExertedByX(const Planet& p)
{
    double dx = p.xxPos - xxPos;
    double distance = calcDistance(p);
    double force = calcForceExertedBy(p);
    double xForce = force * dx / distance;
    return xForce;
}

double Planet::calcForceExertedByY(const Planet& p)
{
    double dy = p.yyPos - yyPos;
    double distance = calcDistance(p);
    double force = calcForceExertedBy(p);
    double yForce = force * dy / distance;
    return yForce;
}

double Planet::calcNetForceExertedByX(const vector<Planet>& planetList)
{
    double xForce = 0;
    for (Planet p: planetList) {
        // The planet will not exert force on itself.
        if (name == p.getName()) { continue; }
        xForce += calcForceExertedByX(p);
    }
    return xForce;
}

double Planet::calcNetForceExertedByY(const vector<Planet>& planetList)
{
    double yForce = 0;
    for (Planet p: planetList) {
        // The planet will not exert force on itself.
        if (name == p.getName()) { continue; }
        yForce += calcForceExertedByY(p);
    }
    return yForce;
}

void Planet::update(double dt, double fx, double fy)
{
    double ax = fx / mass;
    double ay = fy / mass;
    xxVel = xxVel + dt * ax * 1000000; // Here I multiple 1000000 in order to amplify the change.
    yyVel = yyVel + dt * ay * 1000000;
    xxPos = xxPos + dt * xxVel * 1000000;
    yyPos = yyPos + dt * yyVel * 1000000;
}

void Planet::draw(double range, double& x, double& y, int centerX, int centerY)
{
    x = xxPos * 500 / range  + centerX; // In order to fit the size of the window.
    y = centerY - yyPos * 500 / range;
    double planetRed, planetGreen, planetBlue;
    DrawingUtilNG::hsv2rgb(color, 1.0, 1.0, planetRed, planetGreen, planetBlue);
    glColor3f(planetRed, planetGreen, planetBlue);
    // Draw the planet.
    glBegin(GL_QUADS);
    glVertex2f(x - 2, y);
    glVertex2f(x, y + 2);
    glVertex2f(x + 2, y);
    glVertex2f(x,y - 2);
    glEnd();

}






