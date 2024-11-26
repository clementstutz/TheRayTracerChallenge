#add runner content
add_executable(TheRayTracerChallenge_Runner
	main.cpp
    Environment.cpp
    Projectile.cpp
)

# Inclure les fichiers d'en-tête (en cas de besoin pour les dépendances)
target_include_directories(TheRayTracerChallenge_Runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Lier l'exécutable à la bibliothèque principale
target_link_libraries(TheRayTracerChallenge_Runner TheRayTracerChallenge)