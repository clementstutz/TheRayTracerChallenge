#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Canvas.h"
#include "Save.h"
#include "Projectile.h"
#include "Environment.h"

using namespace std;

void static tick(Projectile& proj, Environment& env) {
    proj.m_position = proj.m_position + proj.m_velocity;
    cout << proj.m_position << endl;
    proj.m_velocity = proj.m_velocity + env.m_gravity + env.m_wind;
}

void static runSimulation() {
    int currentIteration = 0;
    int maxIteration = 1000;

    Canvas canvas(900, 550);

    Point start(0.0f, 1.0f, 0.0f);
    Vector velocity(1.0f, 1.8f, 0.0f);
    velocity.Normalize();
    velocity *= 11.25;
    Projectile projectile(start, velocity);
    Environment environment(Vector(0.0f, -0.1f, 0.0f),
                            Vector(-0.01f, 0.0f, 0.0f));

    while (projectile.m_position.getY() >= 0.0f && currentIteration < maxIteration)
    {
        tick(projectile, environment);
        currentIteration++;
        //Draw to canvas
        int x = static_cast<int>(projectile.m_position.getX());
        int y = canvas.getHeight() - static_cast<int>(projectile.m_position.getY());
        canvas.setPixel(x, y, Color::green);
    }

    if (currentIteration == maxIteration)
    {
        cout << "Error, max iteration count exceeded." << endl;
    }

    cout << "--Simulation Results--" << endl;
    cout << projectile.m_position;
    cout << projectile.m_velocity << endl;
    Save::saveCanvas(canvas);
}

int main() {
    runSimulation();
}