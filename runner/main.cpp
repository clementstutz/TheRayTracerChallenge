#include <iostream>
#include <chrono> // Pour std::chrono

#include "Point.h"
#include "Vector.h"
#include "Canvas.h"
#include "Save.h"
#include "Projectile.h"
#include "Environment.h"
#include "Mat4.h"
#include "RayObject.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Scene.h"
#include "Utils.h"
#include "Camera.h"

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

void static Chapter4TransformChallenge() {//drawCircle
    cout << "Chapter 4 Challeng" << endl;
    // Create canvas of set size and width.
    // Creat Transform that first offsets a point by 1/2 canvas size then
    // rotates the objects by 1/12th of 2*pi through 12 iterations.
    // At each location draw on the canvas a circle.
    int circleRadius = 5;
    Canvas canvas(100, 100);
    Point currentLocation;

    // Offset 1/3 distance of canvas size.
    currentLocation = Mat4::TranslateMatrix(canvas.getWidth() * 0.3, 0.0, 0.0) * currentLocation;   // Rayon du cadrent de l'horloge par rapport à la taille du canvas.

    // Rotate loop.
    int maxIterations = 12;
    for (int r = 0; r < maxIterations; r++)
    {
        currentLocation = Mat4::RotateZMatrix(2.0 * Utils::PI * (1.0 / maxIterations)) * currentLocation;

        // Offset current location so that it is centered in the image by 1/2 width and height through translation.
        Point screenSpaceLocation = Mat4::TranslateMatrix(canvas.getWidth() * 0.5, canvas.getHeight() * 0.5, 0.0) * currentLocation;

        cout << "Point : " << r << endl;
        cout << screenSpaceLocation << endl;;

        // Draw circle at current location.
        Color color(1, 0, 0);
        canvas.drawCircle((int)screenSpaceLocation.getX(), (int)screenSpaceLocation.getY(), circleRadius, color);
    }
    Save::saveCanvas(canvas, "Chapter_4_TransformChallenge");
}

void static Chapter5Challenge() {
    cout << "Chapter 5 Challeng" << endl;
    Scene scene;
    Mat4 transmatrix;
    //transmatrix = Mat4::ScaleMatrix(0.5, 1, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 1, 0.5);
    //transmatrix = Mat4::RotateMatrix(0.0, 0.0, Utils::PI * 0.25) * Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ShearMatrix(1, 0, 0, 0, 0, 0) * Mat4::ScaleMatrix(1, 0.5, 1);

    int resolution = 100;
    Canvas canvas(resolution, resolution);
    canvas.fillCanvas(Color::black);

    Sphere sphere;
    scene.AddRayObject(sphere);
    sphere.SetMatrix(transmatrix);

    Point camera(0, 0, -5);
    Point wall(0, 0, 10);
    float wallSize = 10.0;
    float increment = wallSize / resolution;
    float half = wallSize / 2;
    for (int y = 0; y < resolution; y++) {
        for (int x = 0; x < resolution; x++) {
            Vector temp = wall - Point(half - x * increment, half - y * increment, wall.getZ());
            Point currentWallPixel(temp.getX(), temp.getY(), temp.getZ());
            Vector direction = (currentWallPixel - camera).Normalize();
            Ray ray(camera, direction);
            Intersection hit = scene.Hit(scene.Intersections(ray));
            if (hit.getObjPtr() != nullptr) {
                canvas.setPixel(x, y, Color::red);
            }
        }
    }
    Save::saveCanvas(canvas, "Chapter_5_Challenge");
    cout << "Image created." << endl;
}

void static Chapter6Challenge() {
    cout << "Chapter 6 Challeng" << endl;
    Scene scene;
    Mat4 transmatrix;
    //transmatrix = Mat4::ScaleMatrix(0.5, 1, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 1, 0.5);
    //transmatrix = Mat4::RotateMatrix(0.0, 0.0, Utils::PI * 0.25) * Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ShearMatrix(1, 0, 0, 0, 0, 0) * Mat4::ScaleMatrix(0.5, 1, 1);

    int resolution = 100;
    Canvas canvas(resolution, resolution);
    canvas.fillCanvas(Color::black);

    Light light(Point(-10, 10, -10), Color::white);

    Sphere sphere;
    scene.AddRayObject(sphere);
    Color color(1, 0.2, 1);
    Material material(color, 0.1, 0.9, 0.9);
    sphere.SetMaterial(material);
    sphere.SetMatrix(transmatrix);

    Point camera(0, 0, -5);

    Point wall(0, 0, 10);
    float wallSize = 10.0;

    for (int y = 0; y < resolution; y++) {
        for (int x = 0; x < resolution; x++) {
            float increment = wallSize / resolution;
            Vector temp = wall - Point((wallSize * 0.5) - x * increment,
                                       (wallSize * 0.5) - y * increment,
                                       wall.getZ());
            Point currentWallPixel(temp.getX(), temp.getY(), temp.getZ());
            
            Vector direction = (currentWallPixel - camera).Normalize();
            Ray ray(camera, direction);

            Intersection hit = scene.Hit(scene.Intersections(ray));

            if (hit.getObjPtr() != nullptr) {
                Point hitPosition = ray.position(hit.getLength());
                Color lighting = sphere.Lighting(hitPosition,
                                                 light,
                                                 -ray.getDirection(),
                                                 sphere.GetNormal(hitPosition,
                                                 hit));
                canvas.setPixel(x, y, lighting);
            }
        }
    }
    Save::saveCanvas(canvas, "Chapter_6_Challenge");
    cout << "Image created." << endl;
}

void static Chapter7Challenge() {
    Scene scene;

    Sphere floor;
    floor.SetMatrix(Mat4::ScaleMatrix(10, 0.01, 10));
    floor.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));

    Sphere leftWall;
    leftWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 5) *
        Mat4::RotateYMatrix(Utils::PI / -4.0) *
        Mat4::RotateXMatrix(Utils::PI / 2.0) *
        Mat4::ScaleMatrix(10, 0.01, 10));
    leftWall.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));
    //leftWall.material.color = new Color(0, 1, 0);

    Sphere rightWall;
    rightWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 5) *
        Mat4::RotateYMatrix(Utils::PI / 4.0) *
        Mat4::RotateXMatrix(Utils::PI / 2.0) *
        Mat4::ScaleMatrix(10, 0.01, 10));
    rightWall.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));
    //rightWall.material.color = new Color(0, 0, 1);

    Sphere middle;
    middle.SetMatrix(Mat4::TranslateMatrix(-0.5, 1, 0.5));
    middle.SetMaterial(Material(Color(0.1, 1.0, 0.5), 0.1, 0.7, 0.3));

    Sphere right;
    right.SetMatrix(Mat4::TranslateMatrix(1.5, 0.5, -0.5) * Mat4::ScaleMatrix(0.5, 0.5, 0.5));
    right.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));
    right.SetMatrix(Mat4::TranslateMatrix(1.5, 0.5, -0.5));
    right.SetMaterial(Material(Color(0.5, 1.0, 0.1), 0.1, 0.7, 0.3));

    Sphere left;
    left.SetMatrix(Mat4::TranslateMatrix(-1.5, 0.33, -0.75) *
        Mat4::ScaleMatrix(0.5, 0.4, 0.5));
    left.SetMaterial(Material(Color(1, 0.8, 0.1), 0.1, 0.7, 0.3));

    Light light(Point(-10, 10, -10), Color::white);

    Camera camera(100, 75, Utils::PI / 18.0);

    camera.ViewTransform(Point(0, 1.5, -5.0), Point(0, 1, 0), Vector(0, 1, 0));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_7_PuttingItAllTogether");
    scene.Clear();
    cout << "Image created." << endl;
}

int main() {
    //runSimulation();

    Chapter4TransformChallenge();

    auto debut_5 = std::chrono::high_resolution_clock::now(); // Début du timer
    Chapter5Challenge();
    auto fin_5 = std::chrono::high_resolution_clock::now(); // Fin du timer
    auto duree_5 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_5 - debut_5);
    std::cout << "Durée d'exécution : " << duree_5.count() << " ms" << std::endl;

    auto debut_6 = std::chrono::high_resolution_clock::now(); // Début du timer
    Chapter6Challenge();
    auto fin_6 = std::chrono::high_resolution_clock::now(); // Fin du timer
    auto duree_6 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_6 - debut_6);
    std::cout << "Durée d'exécution : " << duree_6.count() << " ms" << std::endl;

    auto debut_7 = std::chrono::high_resolution_clock::now(); // Début du timer
    Chapter7Challenge();
    auto fin_7 = std::chrono::high_resolution_clock::now(); // Fin du timer
    auto duree_7 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_7 - debut_7);
    std::cout << "Durée d'exécution : " << duree_7.count() << " ms" << std::endl;

}