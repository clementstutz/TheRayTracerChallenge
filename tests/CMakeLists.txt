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