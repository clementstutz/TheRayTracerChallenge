# Ajouter un exécutable pour les tests
add_executable(TheRayTracerChallenge_Tests
	pch.cpp
	Tuple_Test.cpp
	Point_Test.cpp
	Vector_Test.cpp
	Color_Test.cpp
	Canvas_Test.cpp
	Save_Test.cpp
	Mat4_Test.cpp
	Camera_Test.cpp
	Computations_Test.cpp
	Intersection_Test.cpp
	Light_Test.cpp
	Material_Test.cpp
	Ray_Test.cpp
	RayObject_Test.cpp
	Scene_Test.cpp
	Sphere_Test.cpp
	Utils_Test.cpp
	BlendPattern_Test.cpp
	CheckersPattern_Test.cpp
	Cube_Test.cpp
	GradientPattern_Test.cpp
	Pattern_Test.cpp
	Plane_Test.cpp
	RadialGradientPattern_Test.cpp
	RingPattern_Test.cpp
	SolidColorPattern_Test.cpp
	StripePattern_Test.cpp
	Cone_Test.cpp
	Cylinder_Test.cpp
)

# Lier les bibliothèques nécessaires
target_link_libraries(TheRayTracerChallenge_Tests
    TheRayTracerChallenge
    gtest
    gtest_main
)

# Activer les tests
enable_testing()
add_test(NAME AllTests COMMAND TheRayTracerChallenge_Tests)
