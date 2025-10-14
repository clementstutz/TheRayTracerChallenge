#pragma once
#include <vector>

#include "Ray.h"
#include "Light.h"
#include "Shape.h"
#include "Intersection.h"
#include "Computations.h"
#include "Camera.h"
#include "Canvas.h"

class Scene
{
private :
	static Scene* current; // Pointeur statique vers l'objet Scene
	std::vector<Light*> m_lights;
	std::vector<Shape*> m_shapes;

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Scene();


	// Destructor
	~Scene();


	//Accessors
	static Scene* GetCurrentScene(); // Renvoie l'instance actuelle
	std::vector<Light*> GetLights();
	std::vector<Shape*> GetShapes();


	// Member functions
	friend std::ostream& operator<<(std::ostream& flux, Scene const& scene);
	void DefaultScene();
	static void ResetCurrentScene(); // D�truit l'ancienne instance
	void ClearLights();
	void ClearShapes();
	void Clear();
	void RemoveLight(Light const& light);
	void RemoveShape(Shape const& shape);
	void AddLight(Light& light);
	void AddShape(Shape& shape);
	std::vector<Intersection> Intersections(Ray const& ray);
	Intersection Hit(std::vector<Intersection> const& intersections);
	Ray RayForPixel(Camera const& camera, int x, int y);
	Color ColorAt(Ray const& ray, int remaining = 1);
	Color ShadeHit(Computations const& c, int remaining = 1);
	bool IsShadowed(Point const& point, Light const& light);
	Color ReflectedColor(Computations const& c, int remaining = 1);
	Color RefractedColor(Computations const& c, int remaining = 1);
	double Schlick(Computations const& c);
	Canvas Render(Camera const& camera, int remaining = 1);
};
