#include "pch.h"
#include "Cube.h"
#include "Ray.h"
#include "Utils.h"

TEST(CubeTests, constructor_default) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cube cube;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cube.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cube.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cube.GetMatrix(), Mat4());
    EXPECT_EQ(cube.GetInvertMatrix(), Mat4());
}

TEST(CubeTests, constructor_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cube cube_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Cube cube_2(cube_1);
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cube_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cube_2.GetPosition(), cube_1.GetPosition());
    EXPECT_EQ(cube_2.GetMatrix(), cube_1.GetMatrix());
    EXPECT_EQ(cube_2.GetInvertMatrix(), cube_1.GetInvertMatrix());

    Cube cube_3 = cube_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(cube_3.GetId() - nbInstanceAlreadyExisting, 3);
    EXPECT_EQ(cube_3.GetPosition(), cube_1.GetPosition());
    EXPECT_EQ(cube_3.GetMatrix(), cube_1.GetMatrix());
    EXPECT_EQ(cube_3.GetInvertMatrix(), cube_1.GetInvertMatrix());
}

TEST(CubeTests, constructor_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();
    std::cout << nbInstanceAlreadyExisting << std::endl;

    Cube cube_1(std::move(Cube()));
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cube_1.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cube_1.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cube_1.GetMatrix(), Mat4());
    EXPECT_EQ(cube_1.GetInvertMatrix(), Mat4());

    Cube cube_2{ Cube() };
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cube_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cube_2.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cube_2.GetMatrix(), Mat4());
    EXPECT_EQ(cube_2.GetInvertMatrix(), Mat4());
}

TEST(CubeTests, affectation_copy) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cube cube_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);

    Cube cube_2;
    cube_2 = cube_1;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);

    EXPECT_EQ(cube_2.GetId() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cube_2.GetPosition(), cube_1.GetPosition());
    EXPECT_EQ(cube_2.GetMatrix(), cube_1.GetMatrix());
    EXPECT_EQ(cube_2.GetInvertMatrix(), cube_1.GetInvertMatrix());
}

TEST(CubeTests, affectation_move) {
    int nbInstanceAlreadyExisting = RayObject::getNbInstances();

    Cube cube;
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cube.GetId() - nbInstanceAlreadyExisting, 1);

    cube = Cube();
    EXPECT_EQ(RayObject::getNbInstances() - nbInstanceAlreadyExisting, 2);
    EXPECT_EQ(cube.GetId() - nbInstanceAlreadyExisting, 1);
    EXPECT_EQ(cube.GetPosition(), Point(0, 0, 0));
    EXPECT_EQ(cube.GetMatrix(), Mat4());
    EXPECT_EQ(cube.GetInvertMatrix(), Mat4());
}

TEST(CubeTests, transformations) {
    Cube cube;
    cube.SetMatrix(Mat4::ScaleMatrix(2.0, 3.0, 4.0));
    Mat4 ref(2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1);
    EXPECT_EQ(cube.GetMatrix(), ref);

    Point position(4, 5, 6);
    cube.SetPosition(position);
    EXPECT_EQ(cube.GetPosition(), position);
    ref = Mat4(2, 0, 0, 4,
        0, 3, 0, 5,
        0, 0, 4, 6,
        0, 0, 0, 1);
    EXPECT_EQ(cube.GetMatrix(), ref);
}

TEST(CubeTests, intersect) {
    Cube cube;

    // Form the right
    Ray ray(Point(5, 0.5, 0), Vector(-1, 0, 0));    
    std::vector<Intersection> intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the left
    ray = Ray(Point(-5, 0.5, 0), Vector(1, 0, 0));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the top
    ray = Ray(Point(0.5, 5, 0), Vector(0, -1, 0));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the bottom
    ray = Ray(Point(0.5, -5, 0), Vector(0, 1, 0));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the back
    ray = Ray(Point(0.5, 0, 5), Vector(0, 0, -1));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the front
    ray = Ray(Point(0.5, 0, -5), Vector(0, 0, 1));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Form the inside
    ray = Ray(Point(0, 0.5, 0), Vector(0, 0, 1));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(-1.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(1.0, intersections[1].getLength());

    // Tangent
    ray = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(2, intersections.size());
    EXPECT_FLOAT_EQ(4.0, intersections[0].getLength());
    EXPECT_FLOAT_EQ(6.0, intersections[1].getLength());

    // Miss
    ray = Ray(Point(-2, 0, 0), Vector(0.2673, 0.5345, 0.8018));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(0, -2, 0), Vector(0.8018, 0.2673, 0.5345));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(0, 0, -2), Vector(0.5345, 0.8018, 0.2673));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(2, 0, 2), Vector(0, 0, -1));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(0, 2, 2), Vector(0, -1, 0));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(2, 2, 0), Vector(-1, 0, 0));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());

    ray = Ray(Point(0, 3, -5), Vector(0, 0, 1));
    intersections = cube.Intersect(ray);
    EXPECT_EQ(0, intersections.size());
}

TEST(CubeTests, get_normal) {
    // Untransformed cube
    Cube cube;

    Vector normal = cube.GetNormal(Point(1, 0.5, -0.8), Intersection());
    EXPECT_EQ(Vector(1, 0, 0), normal);

    normal = cube.GetNormal(Point(-1, -0.2, 0.9), Intersection());
    EXPECT_EQ(Vector(-1, 0, 0), normal);

    normal = cube.GetNormal(Point(-0.4, 1, -0.1), Intersection());
    EXPECT_EQ(Vector(0, 1, 0), normal);

    normal = cube.GetNormal(Point(0.3, -1, -0.7), Intersection());
    EXPECT_EQ(Vector(0, -1, 0), normal);

    normal = cube.GetNormal(Point(-0.6, 0.3, 1), Intersection());
    EXPECT_EQ(Vector(0, 0, 1), normal);

    normal = cube.GetNormal(Point(0.4, 0.4, -1), Intersection());
    EXPECT_EQ(Vector(0, 0, -1), normal);

    normal = cube.GetNormal(Point(1, 1, 1), Intersection());
    EXPECT_EQ(Vector(1, 0, 0), normal);

    normal = cube.GetNormal(Point(-1, -1, -1), Intersection());
    EXPECT_EQ(Vector(-1, 0, 0), normal);

    // Transformed cube
    cube.SetMatrix(Mat4::TranslateMatrix(0, 1, 0) *
        Mat4::RotateZMatrix(Utils::GetPI() / 4.0));
    normal = cube.GetNormal(Point(0, 2.3, -1), Intersection());
    EXPECT_EQ(Vector(0, 0, -1), normal);

    cube.SetMatrix(Mat4::RotateZMatrix(Utils::GetPI() / 4.0) *
        Mat4::RotateYMatrix(Utils::GetPI() / 4.0) *
        Mat4::RotateXMatrix(Utils::GetPI() / 4.0));
    normal = cube.GetNormal(Point(0.5, 0.5, -1.5), Intersection());
    std::cout << normal << std::endl;
    EXPECT_EQ(Vector(0.5, 0.5, sqrt(2) / 2.0), normal);
}
