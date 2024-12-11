#pragma once
#include <vector>
#include <memory>
#include "Ray.h"
#include "Light.h"
#include "RayObject.h"
#include "Intersection.h"
#include "Computations.h"
#include "Camera.h"
#include "Canvas.h"

class Scene
{
private :
	static Scene* current; // Pointeur statique vers l'objet Scene
	std::vector<Light*> m_lights;
	std::vector<RayObject*> m_rayObjects;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Scene();
	Scene(std::vector<Light*> lights, std::vector<RayObject*> rayObjects);
	Scene(Scene const& other);
	Scene(Scene&& other) noexcept;

	// Destructors
	~Scene();

	//Accessors
	std::vector<Light*> GetLights();
	std::vector<RayObject*> GetRayObjects();
	static Scene* GetCurrentScene(); // Renvoie l'instance actuelle
	static void ResetCurrentScene(); // Détruit l'ancienne instance

	// Operators
	friend std::ostream& operator<<(std::ostream& flux, Scene const& scene);

	// Member-functions
	//void DefaultScene();
	void ClearLights();
	void ClearRayObjects();
	void Clear();
	void RemoveLight(Light& light);
	void RemoveRayObject(RayObject& rayObject);
	void AddLight(Light& light);
	void AddRayObject(RayObject& rayObject);
	std::vector<Intersection> Intersections(Ray ray);
	Intersection Hit(std::vector<Intersection> intersections);
	
	bool IsShadowed(Point point, Light light);
	Color ShadeHit(Computations c, int remaining = 1);
	Color ColorAt(Ray ray, int remaining = 1);
	Ray RayForPixel(Camera camera, int x, int y);
	Canvas Render(Camera camera, int remaining = 1);
	Color ReflectedColor(Computations c, int remaining = 1);
	Color RefractedColor(Computations c, int remaining = 1);
	float Schlick(Computations c);
};

