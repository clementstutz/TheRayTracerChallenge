#include "pch.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"
#include "Save.h"

TEST(SceneTests, EmptyScene) {
    EXPECT_TRUE(Scene::GetCurrentScene() == nullptr);

    Scene scene;
    EXPECT_TRUE(Scene::GetCurrentScene() == &scene);

    scene.Clear();
    EXPECT_TRUE(Scene::GetCurrentScene() == &scene);

    std::vector<Light*> l;
    std::vector<RayObject*> r;
    EXPECT_EQ(scene.GetLights(), l);
    EXPECT_EQ(scene.GetRayObjects(), r);
}

TEST(SceneTests, constructor_default) {
    Scene scene;
    std::vector<Light*> l;
    std::vector<RayObject*> r;
    EXPECT_EQ(scene.GetLights(), l);
    EXPECT_EQ(scene.GetRayObjects(), r);
}

TEST(SceneTests, accessors) {    
    Scene scene;
    Sphere sphere;
    std::vector<RayObject*> ref1 = scene.GetRayObjects();
    EXPECT_EQ(*ref1[0], sphere);

    Light light(Point(0, 0, -5), Color(1, 1, 1));
    std::vector<Light*> ref2 = scene.GetLights();
    EXPECT_EQ(*ref2[0], light);
}

TEST(SceneTests, Intersections) {
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));*/
    scene.DefaultScene();
    
    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);

    EXPECT_EQ(intersections.size(), 4);
    EXPECT_EQ(intersections[0].getObj(), *scene.GetRayObjects()[0]);
    EXPECT_FLOAT_EQ(intersections[0].getLength(), 4.0f);
    EXPECT_EQ(intersections[1].getObj(), *scene.GetRayObjects()[1]);
    EXPECT_FLOAT_EQ(intersections[1].getLength(), 4.5f);
    EXPECT_EQ(intersections[2].getObj(), *scene.GetRayObjects()[1]);
    EXPECT_FLOAT_EQ(intersections[2].getLength(), 5.5f);
    EXPECT_EQ(intersections[3].getObj(), *scene.GetRayObjects()[0]);
    EXPECT_FLOAT_EQ(intersections[3].getLength(), 6.0f);
}

TEST(SceneTests, hit) {
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));*/
    scene.DefaultScene();

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);

    Intersection hit = scene.Hit(intersections);

    EXPECT_EQ(hit.getObj(), *scene.GetRayObjects()[0]);
    EXPECT_FLOAT_EQ(hit.getLength(), 4.0f);
}

TEST(SceneTests, ShadingIntersectionsOutside) {
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Light light(Point(-10, 10, -10), Color(1, 1, 1));*/
    scene.DefaultScene();

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);
    Computations c = Computations::Prepare(hit, ray);

    Color finalColor = scene.ShadeHit(c);
    EXPECT_EQ(Color(0.38066, 0.47583, 0.2855), finalColor);
}

TEST(SceneTests, ShadingIntersectionsIntside) {
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Light light(Point(0, 0.25, 0), Color(1, 1, 1));*/
    scene.DefaultScene();
    scene.GetLights()[0]->SetPosition(Point(0, 0.25, 0));

    Ray ray(Point(0, 0, 0), Vector(0, 0, 1));

    std::vector<Intersection> intersections = scene.Intersections(ray);
    Intersection hit = scene.Hit(intersections);
    Computations c = Computations::Prepare(hit, ray);

    Color finalColor = scene.ShadeHit(c);
    EXPECT_EQ(Color(0.90498, 0.90498, 0.90498), finalColor);
}

TEST(SceneTests, RayMissColor) {
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Light light(Point(-10, 10, -10), Color(1, 1, 1));*/
    scene.DefaultScene();

    Ray ray(Point(0, 0, -5), Vector(0, 1, 0));

    Color finalColor = scene.ColorAt(ray);
    EXPECT_EQ(Color::black, finalColor);
}

TEST(SceneTests, RayHitColor) {
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Light light(Point(-10, 10, -10), Color(1, 1, 1));*/
    scene.DefaultScene();

    Ray ray(Point(0, 0, -5), Vector(0, 0, 1));

    Color finalColor = scene.ColorAt(ray);
    EXPECT_EQ(Color(0.38066, 0.47583, 0.2855), finalColor);
}

TEST(SceneTests, RayIntersectionBehindColor) {  //NOTE : je n'ai pas compris ce test
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMaterial(Material(Color::white, 1));
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));

    Light light(Point(-10, 10, -10), Color(1, 1, 1));*/
    scene.DefaultScene();
    scene.GetRayObjects()[1]->SetMaterial(Material(Color::white, 1));

    Ray ray(Point(0, 0, 0.75), Vector(0, 0, -1));

    Color finalColor = scene.ColorAt(ray); // Pourquoi ColorAt renvoie la couleur de sphere_2 ?
    std::vector<RayObject*> rayObj = scene.GetRayObjects();
    EXPECT_EQ(rayObj[1]->GetMaterial().GetColor(), finalColor);
}

TEST(SceneTests, RayThroughCenter) {
    Camera camera(201, 101, Utils::GetPI() / 2);
    Scene scene;

    Ray ray = scene.RayForPixel(camera, 100, 50);
    EXPECT_EQ(Point(0, 0, 0), ray.getOrigin());
    EXPECT_EQ(Vector(0, 0, -1), ray.getDirection());
}

TEST(SceneTests, RayThroughCorner) {
    Camera camera(201, 101, Utils::GetPI() / 2);
    Scene scene;

    Ray ray = scene.RayForPixel(camera, 0, 0);
    EXPECT_EQ(Point(0, 0, 0), ray.getOrigin());
    EXPECT_EQ(Vector(0.66519, 0.33259, -0.66851), ray.getDirection());
}

TEST(SceneTests, RayThroughTransformed) {
    Camera camera(201, 101, Utils::GetPI() / 2);
    Scene scene;

    std::cout << "camera.GetTransform() = " << camera.GetTransform() << std::endl;

    //Mat4* transformed = &camera.GetTransform();
    //*transformed = Mat4::RotateYMatrix(Utils::GetPI() / 4.0) * Mat4::TranslateMatrix(0, -2, 5);
    std::cout << "camera.GetTransform() = " << camera.GetTransform() << std::endl;
    //std::cout << "*transformed = " << *transformed << std::endl;
    Ray ray = scene.RayForPixel(camera, 100, 50);

    std::cout << "camera.GetTransform() = " << camera.GetTransform() << std::endl;

    std::cout << ray.getOrigin() << std::endl;
    EXPECT_EQ(Point(0, 2, -5), ray.getOrigin());

    std::cout << ray.getDirection() << std::endl;
    EXPECT_EQ(Vector(std::sqrt(2.0)/2.0, 0, -std::sqrt(2.0) / 2.0), ray.getDirection());
    EXPECT_EQ(1, 2);
}

TEST(SceneTests, RenderWorldWithCamera) {
    Camera camera(11, 11, Utils::GetPI() / 2);
    Scene scene;

    /*Sphere sphere_1;
    sphere_1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere sphere_2;
    sphere_2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));
    Light light(Point(-10, 10, -10), Color(1, 1, 1));*/
    scene.DefaultScene();

    camera.ViewTransform(Point(0, 0, -5), Point(0, 0, 0), Vector(0, 1, 0));
    Canvas canvas = scene.Render(camera);

    EXPECT_EQ(Color(0.38066, 0.47583, 0.2855), canvas.getPixel(5, 5));
    Save::saveCanvas(canvas, "Chapter_7_RenderWorldWithCamera");
}
