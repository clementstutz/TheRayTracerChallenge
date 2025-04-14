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
#include "Plane.h"
#include "SolidColorPattern.h"
#include "StripePattern.h"
#include "GradientPattern.h"
#include "RingPattern.h"
#include "CheckersPattern.h"
#include "RadialGradientPattern.h"
#include "BlendPattern.h"

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

    Point start(0.0, 1.0, 0.0);
    Vector velocity(1.0, 1.8, 0.0);
    velocity.Normalize();
    velocity *= 11.25;
    Projectile projectile(start, velocity);
    Environment environment(Vector(0.0, -0.1, 0.0),
                            Vector(-0.01, 0.0, 0.0));

    while (projectile.m_position.getY() >= 0.0 && currentIteration < maxIteration)
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
    Save::saveCanvas(canvas, "free_fall");
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
        currentLocation = Mat4::RotateZMatrix(2.0 * Utils::GetPI() * (1.0 / maxIterations)) * currentLocation;

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
    transmatrix = Mat4::TranslateMatrix(0, 1, 0);
    //transmatrix = Mat4::ScaleMatrix(0.5, 1, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 1, 0.5);
    //transmatrix = Mat4::RotateMatrix(0.0, 0.0, Utils::GetPI() * 0.25) * Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ShearMatrix(1, 0, 0, 0, 0, 0) * Mat4::ScaleMatrix(1, 0.5, 1);

    int resolution = 100;
    Canvas canvas(resolution, resolution);
    canvas.fillCanvas(Color::black);

    Sphere sphere;
    scene.AddRayObject(sphere);
    sphere.SetMatrix(transmatrix);

    Point camera(0, 0, -5);
    Point wall(0, 0, 10);
    double wallSize = 10.0;
    double increment = wallSize / resolution;
    double half = wallSize / 2;
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
    transmatrix = Mat4::TranslateMatrix(0, 1, 0);
    //transmatrix = Mat4::ScaleMatrix(2, 2, 2);
    //transmatrix = Mat4::ScaleMatrix(0.5, 1, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ScaleMatrix(1, 1, 0.5);
    //transmatrix = Mat4::RotateMatrix(0.0, 0.0, Utils::GetPI() * 0.25) * Mat4::ScaleMatrix(1, 0.5, 1);
    //transmatrix = Mat4::ShearMatrix(1, 0, 0, 0, 0, 0) * Mat4::ScaleMatrix(0.5, 1, 1);

    int resolution = 100;
    Canvas canvas(resolution, resolution);

    Light light(Point(-10, 10, -10), Color::white);

    Sphere sphere;
    Color color(1, 0.2, 1);
    Material material(color, 0.1, 0.9, 0.9);
    sphere.SetMaterial(material);
    sphere.SetMatrix(transmatrix);

    Point camera(0, 0, -5);

    Point wall(0, 0, 10);
    double wallSize = 10.0;

    for (int y = 0; y < resolution; y++) {  // 1: (int y = 0; y < resolution; y++) -or- 2:int y = resolution-1; y >=0; y--
        for (int x = 0; x < resolution; x++) {
            double increment = wallSize / resolution;
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
                                                 sphere.GetNormal(hitPosition, hit));
                canvas.setPixel(x, y, lighting);
            }
        }
    }
    Save::saveCanvas(canvas, "Chapter_6_Challenge");
    cout << "Image created." << endl;
}

void static Chapter7Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 1.5, -5.0),
        Point(0, 1, 0),
        Vector(0, 1, 0));

    Scene scene;

    Light light(Point(-10, 10, -10), Color::white);

    Sphere floor;
    floor.SetMatrix(Mat4::ScaleMatrix(10, 0.01, 10));
    floor.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));
    //floor.SetCanCastShadows(false);

    Sphere leftWall;
    leftWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 5) *
        Mat4::RotateYMatrix(Utils::GetPI() / -4.0) *
        Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::ScaleMatrix(10, 0.01, 10));
    leftWall.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));
    //leftWall.SetCanCastShadows(false);

    Sphere rightWall;
    rightWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 5) *
        Mat4::RotateYMatrix(Utils::GetPI() / 4.0) *
        Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::ScaleMatrix(10, 0.01, 10));
    //rightWall.SetCanCastShadows(false);

    Sphere middle;
    middle.SetMatrix(Mat4::TranslateMatrix(-0.5, 1, 0.5));
    middle.SetMaterial(Material(Color(0.1, 1.0, 0.5), 0.1, 0.7, 0.3));
    middle.SetCanCastShadows(false);

    Sphere right;
    right.SetMatrix(Mat4::TranslateMatrix(1.5, 0.5, -0.5) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));
    right.SetMaterial(Material(Color(0.5, 1.0, 0.1), 0.1, 0.7, 0.3));
    right.SetCanCastShadows(false);

    Sphere left;
    left.SetMatrix(Mat4::TranslateMatrix(-1.5, 0.33, -0.75) *
        Mat4::ScaleMatrix(0.33, 0.33, 0.33));
    left.SetMaterial(Material(Color(1, 0.8, 0.1), 0.1, 0.7, 0.3));
    left.SetCanCastShadows(false);

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_7_PuttingItAllTogether");
    cout << "Image created." << endl;
}

void static Chapter8Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 1.5, -5.0),
        Point(0, 1, 0),
        Vector(0, 1, 0));

    Scene scene;

    Light light(Point(-10, 10, -10), Color::white);

    Sphere floor;
    floor.SetMatrix(Mat4::ScaleMatrix(10, 0.01, 10));
    floor.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));

    Sphere leftWall;
    leftWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 5) *
        Mat4::RotateYMatrix(Utils::GetPI() / -4.0) *
        Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::ScaleMatrix(10, 0.01, 10));

    leftWall.SetMaterial(Material(Color(1, 0.9, 0.9), 0.1, 0.9, 0.0));

    Sphere rightWall;
    rightWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 5) *
        Mat4::RotateYMatrix(Utils::GetPI() / 4.0) *
        Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::ScaleMatrix(10, 0.01, 10));
    //rightWall.SetMaterial(Material(Color(0.1, 1.0, 0.5), 0.1, 0.7, 0.3));

    Sphere middle;
    middle.SetMatrix(Mat4::TranslateMatrix(-0.5, 1, 0.5));
    middle.SetMaterial(Material(Color(0.1, 1.0, 0.5), 0.1, 0.7, 0.3));

    Sphere right;
    right.SetMatrix(Mat4::TranslateMatrix(1.5, 0.5, -0.5) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));
    right.SetMaterial(Material(Color(0.5, 1.0, 0.1), 0.1, 0.7, 0.3));

    Sphere left;
    left.SetMatrix(Mat4::TranslateMatrix(-1.5, 0.33, -0.75) *
        Mat4::ScaleMatrix(0.33, 0.33, 0.33));
    left.SetMaterial(Material(Color(1, 0.8, 0.1), 0.1, 0.7, 0.3));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_8_Chalenge");
    cout << "Image created." << endl;
}

void static Chapter9Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -10),
        Point(0, 2, 4),
        Vector(0, 1, 0));

    Scene scene;

    Light light_1(Point(-5, 5, -5), Color::white);
    Light light_2(Point(5, 0.4, -5), Color(0.6, 0.6, 0.15));

    Plane floor;
    floor.SetMaterial(Material(Color::red));

    Plane wall;
    wall.SetMaterial(Material(Color::blue));
    wall.SetMatrix(Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::TranslateMatrix(0, 0, 4));

    Sphere sphere_1;
    sphere_1.SetMatrix(Mat4::TranslateMatrix(0, 0.5, -3) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::TranslateMatrix(2, 1, -1));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_9_Challenge");
    cout <<"Image created." << endl;
}

void static Chapter10_1Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -10),
        Point(0, 2, 4),
        Vector(0, 1, 0));

    Scene scene;

    Light light_1(Point(-5, 5, -5), Color::white);
    Light light_2(Point(5, 0.4, -5), Color(0.6, 0.6, 0.15));

    Plane floor;
    Material m_1(Color::red);
    m_1.SetPattern(RingPattern(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0))));
    floor.SetMaterial(m_1);

    Plane wall;
    Material m_2(Color::blue);
    m_2.SetPattern(StripePattern(SolidColorPattern(Color(1, 1, 1)), SolidColorPattern(Color(0, 0, 0))));
    wall.SetMaterial(m_2);
    wall.SetMatrix(Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::TranslateMatrix(0, 0, 4));

    Sphere sphere_1;
    Material m_3(Color::blue);
    m_3.SetPattern(CheckersPattern(SolidColorPattern(Color(1, 1, 0)), SolidColorPattern(Color(0, 0, 1))));
    sphere_1.SetMaterial(m_3);
    sphere_1.SetMatrix(Mat4::TranslateMatrix(0, 0.5, -3) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Sphere sphere_2;
    Material m_4(Color::blue);
    m_4.SetPattern(GradientPattern(SolidColorPattern(Color(1, 1, 1)), SolidColorPattern(Color(0, 1, 0))));
    sphere_2.SetMaterial(m_4);
    sphere_2.SetMatrix(Mat4::TranslateMatrix(2, 1, -1));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_10_1_Challenge");
    cout << "Image created." << endl;
}

void static Chapter10_2Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -10),
        Point(0, 2, 4),
        Vector(0, 1, 0));

    Scene scene;

    Light light_1(Point(-5, 5, -5), Color::white);
    Light light_2(Point(5, 0.4, -5), Color(0.6, 0.6, 0.15));

    Plane floor;
    Material m_1(Color::red);
    m_1.SetPattern(RingPattern(SolidColorPattern(Color(1, 0, 0)), SolidColorPattern(Color(0, 1, 0))));
    floor.SetMaterial(m_1);

    Plane wall;
    Material m_2(Color::blue);
    m_2.SetPattern(RadialGradientPattern());
    wall.SetMaterial(m_2);
    wall.SetMatrix(Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::TranslateMatrix(0, 0, 4));

    Sphere sphere_1;
    Material m_3(Color::blue);
    m_3.SetPattern(RadialGradientPattern());
    sphere_1.SetMaterial(m_3);
    sphere_1.SetMatrix(Mat4::TranslateMatrix(0, 0.5, -3) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Sphere sphere_2;
    Material m_4(Color::blue);
    m_4.SetPattern(RadialGradientPattern());
    sphere_2.SetMaterial(m_4);
    sphere_2.SetMatrix(Mat4::TranslateMatrix(2, 1, -1));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_10_2_Challenge");
    cout << "Image created." << endl;
}

void static Chapter10_3Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -10),
        Point(0, 2, 4),
        Vector(0, 1, 0));

    Scene scene;

    Light light_1(Point(-5, 5, -5), Color::white);
    Light light_2(Point(5, 0.4, -5), Color(0.6, 0.6, 0.15));

    CheckersPattern checkersPattern{ RadialGradientPattern(), SolidColorPattern(Color::green) };
    Plane floor;
    Material m_1(Color::red);
    m_1.SetPattern(checkersPattern);
    floor.SetMaterial(m_1);

    Plane wall;
    Material m_2(Color::blue);
    m_2.SetPattern(checkersPattern);
    wall.SetMaterial(m_2);
    wall.SetMatrix(Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::TranslateMatrix(0, 0, 4));

    Sphere sphere_1;
    Material m_3(Color::blue);
    m_3.SetPattern(checkersPattern);
    sphere_1.SetMaterial(m_3);
    sphere_1.SetMatrix(Mat4::TranslateMatrix(0, 0.5, -3) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Sphere sphere_2;
    Material m_4(Color::blue);
    m_4.SetPattern(checkersPattern);
    sphere_2.SetMaterial(m_4);
    sphere_2.SetMatrix(Mat4::TranslateMatrix(2, 1, -1));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_10_3_Challenge");
    cout << "Image created." << endl;
}

void static Chapter10_4Challenge() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -10),
        Point(0, 2, 4),
        Vector(0, 1, 0));

    Scene scene;

    Light light_1(Point(-5, 5, -5), Color::white);
    Light light_2(Point(5, 0.4, -5), Color(0.6, 0.6, 0.15));

    StripePattern s1{SolidColorPattern(Color::white), SolidColorPattern(Color::green)};
    StripePattern s2{ SolidColorPattern(Color::white), SolidColorPattern(Color::green) };
    s2.SetMatrix(Mat4::RotateYMatrix(Utils::GetPI()/2.0));
    BlendPattern blendPattern(s1, s2, 0.5);

    Plane floor;
    Material m_1(Color::blue);
    m_1.SetPattern(blendPattern);
    floor.SetMaterial(m_1);

    Plane wall;
    Material m_2(Color::blue);
    m_2.SetPattern(blendPattern);
    wall.SetMaterial(m_2);
    wall.SetMatrix(Mat4::RotateXMatrix(Utils::GetPI() / 2.0) *
        Mat4::TranslateMatrix(0, 0, 4));

    Sphere sphere_1;
    Material m_3(Color::blue);
    m_3.SetPattern(blendPattern);
    sphere_1.SetMaterial(m_3);
    sphere_1.SetMatrix(Mat4::TranslateMatrix(0, 0.5, -3) *
        Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Sphere sphere_2;
    Material m_4(Color::blue);
    m_4.SetPattern(blendPattern);
    sphere_2.SetMaterial(m_4);
    sphere_2.SetMatrix(Mat4::TranslateMatrix(2, 1, -1));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_10_4_Challenge");
    cout << "Image created." << endl;
}


int main() {
    //runSimulation();

    //Chapter4TransformChallenge();

    /*auto debut_5 = std::chrono::high_resolution_clock::now();
    Chapter5Challenge();
    auto fin_5 = std::chrono::high_resolution_clock::now();
    auto duree_5 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_5 - debut_5);
    std::cout << "Durée d'exécution : " << duree_5.count() << " ms" << std::endl;*/

    /*auto debut_6 = std::chrono::high_resolution_clock::now();
    Chapter6Challenge();
    auto fin_6 = std::chrono::high_resolution_clock::now();
    auto duree_6 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_6 - debut_6);
    std::cout << "Durée d'exécution : " << duree_6.count() << " ms" << std::endl;*/

    /*auto debut_7 = std::chrono::high_resolution_clock::now();
    Chapter7Challenge();
    auto fin_7 = std::chrono::high_resolution_clock::now();
    auto duree_7 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_7 - debut_7);
    std::cout << "Durée d'exécution : " << duree_7.count() << " ms" << std::endl;*/

    /*auto debut_8 = std::chrono::high_resolution_clock::now();
    Chapter8Challenge();
    auto fin_8 = std::chrono::high_resolution_clock::now();
    auto duree_8 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_8 - debut_8);
    std::cout << "Durée d'exécution : " << duree_8.count() << " ms" << std::endl;*/

    /*auto debut_9 = std::chrono::high_resolution_clock::now();
    Chapter9Challenge();
    auto fin_9 = std::chrono::high_resolution_clock::now();
    auto duree_9 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_9 - debut_9);
    std::cout << "Durée d'exécution : " << duree_9.count() << " ms" << std::endl;*/

    /*auto debut_9_2 = std::chrono::high_resolution_clock::now();
    Chapter9_2Challenge();
    auto fin_9_2 = std::chrono::high_resolution_clock::now();
    auto duree_9_2 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_9_2 - debut_9_2);
    std::cout << "Durée d'exécution : " << duree_9_2.count() << " ms" << std::endl;*/

    /*auto debut_10_1 = std::chrono::high_resolution_clock::now();
    Chapter10_1Challenge();
    auto fin_10_1 = std::chrono::high_resolution_clock::now();
    auto duree_10_1 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_10_1 - debut_10_1);
    std::cout << "Durée d'exécution : " << duree_10_1.count() << " ms" << std::endl;*/

    /*auto debut_10_2 = std::chrono::high_resolution_clock::now();
    Chapter10_2Challenge();
    auto fin_10_2 = std::chrono::high_resolution_clock::now();
    auto duree_10_2 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_10_2 - debut_10_2);
    std::cout << "Durée d'exécution : " << duree_10_2.count() << " ms" << std::endl;*/

    /*auto debut_10_3 = std::chrono::high_resolution_clock::now();
    Chapter10_3Challenge();
    auto fin_10_3 = std::chrono::high_resolution_clock::now();
    auto duree_10_3 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_10_3 - debut_10_3);
    std::cout << "Durée d'exécution : " << duree_10_3.count() << " ms" << std::endl;*/

    auto debut_10_4 = std::chrono::high_resolution_clock::now();
    Chapter10_4Challenge();
    auto fin_10_4 = std::chrono::high_resolution_clock::now();
    auto duree_10_4 = std::chrono::duration_cast<std::chrono::milliseconds>(fin_10_4 - debut_10_4);
    std::cout << "Durée d'exécution : " << duree_10_4.count() << " ms" << std::endl;
}