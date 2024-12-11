# Ajouter les fichiers sources à la bibliothèque
add_library(TheRayTracerChallenge
	Tuple.cpp
	Point.cpp
	Vector.cpp
	Utils.cpp
	Color.cpp
	Canvas.cpp
	Save.cpp
	Mat4.cpp
	Camera.cpp
	Computations.cpp
	Intersection.cpp
	Light.cpp
	Material.cpp
	Ray.cpp
	RayObject.cpp
	RayObject_for_Test.cpp
	Scene.cpp
	Sphere.cpp
)

# Inclure les fichiers d'en-tête (pour permettre aux autres projets de les voir)
target_include_directories(TheRayTracerChallenge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
