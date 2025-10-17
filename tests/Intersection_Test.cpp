#include "pch.h"
#include "Sphere.h"

TEST(IntersectionsTests, constructor) {
    Sphere sphere;
    Intersection intersection(sphere, 1.2);

    EXPECT_EQ(intersection == intersection, true);
    EXPECT_EQ(intersection.IsEmpty(), false);
    EXPECT_EQ(intersection.getObj(), sphere);
    EXPECT_EQ(intersection.getObjPtr(), &sphere);
    EXPECT_FLOAT_EQ(intersection.getLength(), 1.2);
}
