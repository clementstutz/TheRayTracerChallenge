# Version minimale de CMake requise
cmake_minimum_required(VERSION 3.15)

# Nom du projet
project(TheRayTracerChallenge)

# Configurer la version de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Inclure les sous-répertoires
add_subdirectory(${CMAKE_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/runner)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

# Ajouter les dépendances externes
add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest)
