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
#include "Cube.h"

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

void static Chapter_4_TransformChallenge() {//drawCircle
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

void static Chapter_5_Challenge() {
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

void static Chapter_6_Challenge() {
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

void static Chapter_7_Challenge() {
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

void static Chapter_8_Challenge() {
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

void static Chapter_9_Challenge() {
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

void static Chapter_10_1_Challenge() {
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

void static Chapter_10_2_Challenge() {
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

void static Chapter_10_3_Challenge() {
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

void static Chapter_10_4_Challenge() {
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

void static Chapter_11_Challenge_Reflection() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -5),
        Point(0, 1, -1),
        Vector(0, 1, 0));

    int recursion = 2;

    Scene scene;

    Light light(Point(-10, 10, -10), Color::white);

    Material m_1;
    m_1.SetPattern(CheckersPattern());
    Plane floor;
    floor.SetMaterial(m_1);

    GradientPattern pattern_2{ SolidColorPattern(Color::red), SolidColorPattern(Color::white) };
    pattern_2.SetMatrix(Mat4::RotateYMatrix(Utils::GetPI() / 2));
    Material m_2;
    m_2.SetPattern(pattern_2);
    Plane wall;
    wall.SetMaterial(m_2);
    wall.SetMatrix(Mat4::TranslateMatrix(0, 0, 4.1) * Mat4::RotateXMatrix(Utils::GetPI() / 2.0));

    Material m_3;
    m_3.SetReflectivity(1.0);
    Sphere sphere_1;
    sphere_1.SetMaterial(m_3);
    sphere_1.SetMatrix(Mat4::TranslateMatrix(-1, 0.5, -2) * Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Material m_4;
    m_4.SetReflectivity(1.0);
    Sphere sphere_2;
    sphere_2.SetMaterial(m_4);
    sphere_2.SetMatrix(Mat4::TranslateMatrix(1, 1, 0));

    Canvas canvas = scene.Render(camera, recursion);
    Save::saveCanvas(canvas, "Chapter_11_Reflection_" + std::to_string(recursion));
    std::cout << "Image created." << std::endl;
}

void static Chapter_11_Challenge_Transparency() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 0, -3),
        Point(0, 0, 4),
        Vector(0, 1, 0));

    int recursion = 1;

    Scene scene;

    Light light(Point(-10, 10, -10), Color::white);

    StripePattern s1{ SolidColorPattern(Color::white), SolidColorPattern(Color::green) };
    StripePattern s2{ SolidColorPattern(Color::white), SolidColorPattern(Color::green) };
    s1.SetMatrix(Mat4::RotateYMatrix(Utils::GetPI() / 2));
    BlendPattern blend(s1, s2);

    Material m_1;
    m_1.SetPattern(blend);
    Plane wall;
    wall.SetMaterial(m_1);
    wall.SetMatrix(Mat4::RotateXMatrix(Utils::GetPI() / 2.0));

    Material m_2;
    m_2.SetColor(Color::red);
    m_2.SetDiffuse(0.1);
    m_2.SetShininess(300);
    m_2.SetReflectivity(1.0);
    m_2.SetTransparency(0.9);
    m_2.SetRefractiveIndex(RefractiveIndex::Vacuum);

    Sphere sphere;
    sphere.SetMaterial(m_2);
    sphere.SetMatrix(Mat4::TranslateMatrix(0, 0, -0.5));
    sphere.SetCanCastShadows(false);

    Canvas canvas = scene.Render(camera, recursion);
    Save::saveCanvas(canvas, "Chapter_11_Transparency_" + std::to_string(recursion));
    std::cout << "Image created." << std::endl;
}

void static Chapter_11_Challenge_UnderwaterScene() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 4, -10),
        Point(0, -2, 4),
        Vector(0, 1, 0));

    int recursion = 1;

    Scene scene;

    Light light(Point(-10, 10, -10), Color::white);

    Material m_1;
    m_1.SetColor(Color(0.3, 0.7, 0.99));
    m_1.SetDiffuse(0.3);
    m_1.SetReflectivity(0.4);
    m_1.SetTransparency(0.5);
    m_1.SetRefractiveIndex(RefractiveIndex::Water);

    Plane waterSurface;
    waterSurface.SetMaterial(m_1);
    waterSurface.SetCanCastShadows(false);

    Material m_2;
    m_2.SetColor(Color(0.5, 0.25, 0.1));
    m_2.SetDiffuse(0.9);
    m_2.SetReflectivity(0.0);
    m_2.SetTransparency(0.0);
    m_2.SetSpecular(0.0);
    m_2.SetRefractiveIndex(RefractiveIndex::Air);

    Plane waterBed;
    waterBed.SetMaterial(m_2);
    waterBed.SetCanCastShadows(false);
    waterBed.SetMatrix(Mat4::TranslateMatrix(0, -10, 0));

    Sphere sphere_1;
    sphere_1.SetMatrix(Mat4::TranslateMatrix(0, -2.4, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / -15) *
        Mat4::ScaleMatrix(1, 4, 1));

    Canvas canvas = scene.Render(camera, recursion);
    Save::saveCanvas(canvas, "Chapter_11_UnderwaterScene_" + std::to_string(recursion));
    std::cout << "Image created." << std::endl;
}

void static Chapter_12_Challenge_Cube_with_pattern() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2, -10),
        Point(0, 0, 0),
        Vector(0, 1, 0));
    Scene scene;
    Light light(Point(-4, 4, -3), Color::white);

    CheckersPattern pattern{SolidColorPattern(Color::red), SolidColorPattern(Color::cyan)};
    pattern.SetMatrix(Mat4::ScaleMatrix(1, 0.5, 1));
    Material m;
    m.SetPattern(pattern);
    Cube cube;
    cube.SetMaterial(m);
    cube.SetMatrix(Mat4::TranslateMatrix(-2, 0, 0));
    Sphere s;
    s.SetMaterial(m);
    s.SetMatrix(Mat4::TranslateMatrix(2, 0, 0));

    Canvas canvas = scene.Render(camera);
    Save::saveCanvas(canvas, "Chapter_12_Cube");
    std::cout << "Image created." << std::endl;
}

void static Chapter_12_Challenge_CubeRoom() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2.2, -5),
        Point(0, 1, 4),
        Vector(0, 1, 0));

    int recursion = 5;

    Scene scene;

    Light light(Point(-4, 4, -3), Color::white);

    //Create a cube room
    //Floor
    CheckersPattern floor_pattern{ SolidColorPattern(Color::white), SolidColorPattern(Color::black) };
    floor_pattern.SetMatrix(Mat4::ScaleMatrix(0.1, 1, 0.1));
    Material floor_m;
    floor_m.SetReflectivity(0.2);
    floor_m.SetPattern(floor_pattern);
    Plane floor;
    floor.SetMaterial(floor_m);
    floor.SetMatrix(Mat4::TranslateMatrix(0, 0.1, 0) * Mat4::ScaleMatrix(10, 0.1, 10));

    //Ceiling
    Material ceiling_m(Color(0.9, 0.9, 0.95));
    Cube ceiling;
    ceiling.SetMaterial(ceiling_m);
    ceiling.SetMatrix(Mat4::TranslateMatrix(0, 5, 0) * Mat4::ScaleMatrix(10, 0.1, 10));

    //Back  Wall
    Material backWall_m(Color(0.6, 0.1, 0.05));
    backWall_m.SetReflectivity(0);
    Cube backWall;
    backWall.SetMaterial(backWall_m);
    backWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 0) * Mat4::ScaleMatrix(5, 5, 6));

    //Mirror
    Material mirror_m(Color::black);
    mirror_m.SetShininess(300);
    mirror_m.SetReflectivity(1);
    Cube mirror;
    mirror.SetMaterial(mirror_m);
    mirror.SetMatrix(Mat4::TranslateMatrix(0, 2, 5.9) * Mat4::ScaleMatrix(2, 1, 0.005));

    //Table
    Material table_m(Color(0.6471, 0.3843, 0.2196));
    Cube tableTop;
    tableTop.SetMaterial(table_m);
    tableTop.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) * Mat4::ScaleMatrix(2, 0.1, 1));

    Cube leg1;
    leg1.SetMaterial(table_m);
    leg1.SetMatrix(Mat4::TranslateMatrix(-1.7, 0, -0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    Cube leg2;
    leg2.SetMaterial(table_m);
    leg2.SetMatrix(Mat4::TranslateMatrix(1.7, 0, -0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    Cube leg3;
    leg3.SetMaterial(table_m);
    leg3.SetMatrix(Mat4::TranslateMatrix(1.7, 0, 0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    Cube leg4;
    leg4.SetMaterial(table_m);
    leg4.SetMatrix(Mat4::TranslateMatrix(-1.7, 0, 0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    //Sphere
    Material sphere_1_m;
    sphere_1_m.SetRefractiveIndex(RefractiveIndex::Glass);
    sphere_1_m.SetDiffuse(0);
    sphere_1_m.SetTransparency(1);
    Sphere sphere1;
    sphere1.SetMaterial(sphere_1_m);
    sphere1.SetMatrix(Mat4::TranslateMatrix(0.7, 1.5, 0) * Mat4::ScaleMatrix(0.4, 0.4, 0.4));
    sphere1.SetCanCastShadows(false);

    Material sphere_2_m(Color(0, 0.1, 0));
    sphere_2_m.SetDiffuse(0.2);
    sphere_2_m.SetShininess(100);
    sphere_2_m.SetReflectivity(1);
    sphere_2_m.SetTransparency(0.2);
    sphere_2_m.SetRefractiveIndex(RefractiveIndex::Vacuum);
    Sphere sphere2;
    sphere2.SetMaterial(sphere_2_m);
    sphere2.SetMatrix(Mat4::TranslateMatrix(-0.7, 1.5, 0) * Mat4::ScaleMatrix(0.4, 0.4, 0.4));

    Canvas canvas = scene.Render(camera, recursion);
    Save::saveCanvas(canvas, "Chapter_12_CubeRoom_" + std::to_string(recursion));
    std::cout << "Image created." << std::endl;
}

void static Chapter_12_Challenge_CubeRoom_better() {
    Camera camera(500, 300, Utils::GetPI() / 3.0);
    camera.ViewTransform(Point(0, 2.2, -5),
        Point(0, 1, 4),
        Vector(0, 1, 0));

    int recursion = 5;

    Scene scene;

    Light light(Point(-4, 4, -3), Color::white);

    //Create a cube room
    //Floor
    CheckersPattern floor_pattern{ SolidColorPattern(Color::white), SolidColorPattern(Color::black) };
    floor_pattern.SetMatrix(Mat4::ScaleMatrix(0.2, 0.2, 0.2));
    Material floor_m;
    floor_m.SetReflectivity(0.2);
    floor_m.SetPattern(floor_pattern);
    Cube floor;
    floor.SetMaterial(floor_m);
    floor.SetMatrix(Mat4::TranslateMatrix(0, 0.1, 0) * Mat4::ScaleMatrix(10, 0.1, 10));

    //Ceiling
    Material ceiling_m(Color(0.9, 0.9, 0.95));
    Cube ceiling;
    ceiling.SetMaterial(ceiling_m);
    ceiling.SetMatrix(Mat4::TranslateMatrix(0, 5, 0) * Mat4::ScaleMatrix(10, 0.1, 10));

    //Back  Wall
    Material backWall_m(Color(0.6, 0.1, 0.05));
    backWall_m.SetReflectivity(0);
    Cube backWall;
    backWall.SetMaterial(backWall_m);
    backWall.SetMatrix(Mat4::TranslateMatrix(0, 0, 0) * Mat4::ScaleMatrix(5, 5, 6));

    //Mirror
    Material mirror_m(Color::black);
    mirror_m.SetShininess(300);
    mirror_m.SetReflectivity(1);
    Cube mirror;
    mirror.SetMaterial(mirror_m);
    mirror.SetMatrix(Mat4::TranslateMatrix(0, 2, 5.9) * Mat4::ScaleMatrix(2, 1, 0.005));

    //Table
    Material table_m(Color(0.6471, 0.3843, 0.2196));
    Cube tableTop;
    tableTop.SetMaterial(table_m);
    tableTop.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) * Mat4::ScaleMatrix(2, 0.1, 1));

    Cube leg1;
    leg1.SetMaterial(table_m);
    leg1.SetMatrix(Mat4::TranslateMatrix(-1.7, 0, -0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    Cube leg2;
    leg2.SetMaterial(table_m);
    leg2.SetMatrix(Mat4::TranslateMatrix(1.7, 0, -0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    Cube leg3;
    leg3.SetMaterial(table_m);
    leg3.SetMatrix(Mat4::TranslateMatrix(1.7, 0, 0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    Cube leg4;
    leg4.SetMaterial(table_m);
    leg4.SetMatrix(Mat4::TranslateMatrix(-1.7, 0, 0.9) * Mat4::ScaleMatrix(0.1, 1, 0.1));

    //Sphere
    Material sphere_1_m;
    sphere_1_m.SetRefractiveIndex(RefractiveIndex::Glass);
    sphere_1_m.SetDiffuse(0);
    sphere_1_m.SetTransparency(1);
    Sphere sphere1;
    sphere1.SetMaterial(sphere_1_m);
    sphere1.SetMatrix(Mat4::TranslateMatrix(0.9, 1.5, 0) * Mat4::ScaleMatrix(0.4, 0.4, 0.4));
    sphere1.SetCanCastShadows(false);

    Material sphere_2_m(Color(0, 0.1, 0));
    sphere_2_m.SetDiffuse(0.2);
    sphere_2_m.SetShininess(100);
    sphere_2_m.SetReflectivity(1);
    sphere_2_m.SetTransparency(0.2);
    sphere_2_m.SetRefractiveIndex(RefractiveIndex::Vacuum);
    Sphere sphere2;
    sphere2.SetMaterial(sphere_2_m);
    sphere2.SetMatrix(Mat4::TranslateMatrix(-0.9, 1.5, 0) * Mat4::ScaleMatrix(0.4, 0.4, 0.4));

    Canvas canvas = scene.Render(camera, recursion);
    Save::saveCanvas(canvas, "Chapter_12_CubeRoom_better_" + std::to_string(recursion));
    std::cout << "Image created." << std::endl;
}

int main() {
    //runSimulation();

    //Chapter4TransformChallenge();

    auto debut = std::chrono::high_resolution_clock::now();
    auto fin = std::chrono::high_resolution_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_5_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_6_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_7_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_8_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_9_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_10_1_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_10_2_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_10_3_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_10_4_Challenge();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    //There is noise in the reflections.
    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_11_Challenge_Reflection();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_11_Challenge_Transparency();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_11_Challenge_UnderwaterScene();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_12_Challenge_Cube_with_pattern();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/

    /*debut = std::chrono::high_resolution_clock::now();
    Chapter_12_Challenge_CubeRoom();
    fin = std::chrono::high_resolution_clock::now();
    duree = std::chrono::duration_cast<std::chrono::milliseconds>(fin - debut);
    std::cout << "Durée d'exécution : " << duree.count() << " ms" << std::endl;*/
}