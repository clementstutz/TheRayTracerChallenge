#include "pch.h"
#include "Point.h"
#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"

TEST(IntersectionsTests, constructor) {
    Sphere sphere;
    Intersection intersection(sphere, 1.2f);

    EXPECT_EQ(intersection.getObj(), sphere);
    EXPECT_FLOAT_EQ(intersection.getLength(), 1.2f);
}
