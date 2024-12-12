#pragma once
#include <vector>
#include "Mat4.h"
#include "Ray.h"
#include "Point.h"
#include "Vector.h"
#include "Material.h"
#include "Light.h"

// Déclaration anticipée de classes
class Intersection;

class RayObject
{
protected:
	static int m_currentId;
	int m_id;
	Mat4 m_matrix;
	Mat4 m_invertMat;	//NOTE : Useless because I would have to recalculate the inverse for EACH modification of the matrix
	Material m_material;
	bool m_canReceiveShadows;   // WARNING : A déplacer dans materiaux, car sinon je ne peux pas définir un mtx Glassy() qui ne peux caster des ombres !
	bool m_canCastShadows;      // WARNING : A déplacer dans materiaux

	virtual void afficher(std::ostream& flux) const;

public:
	// Constructors
	RayObject();
	RayObject(RayObject const& other);
	RayObject(RayObject&& other) noexcept;

	// Destructor
	virtual ~RayObject();// = default;

	// Accessors
	int static getNbInstances() ;
	int GetId() const;
	Mat4 GetMatrix() const;
	Mat4 GetInvertMatrix() const;
	Point GetPosition() const;
	Material GetMaterial() const;
	bool CanReceiveShadows() const;
	bool CanCastShadows() const;
	void SetMatrix(Mat4 const&mat);
	void SetPosition(Point const& p);
	void SetMaterial(Material const& material);
	
	// Member functions
	RayObject& operator=(RayObject const& other);
	RayObject& operator=(RayObject&& other) noexcept;
	bool operator==(RayObject const& other) const;
	friend std::ostream& operator<<(std::ostream& flux, RayObject const& rayObject);
	Ray RayToObjectSpace(Ray const& ray) const;
	virtual std::vector<Intersection> Intersect(Ray const& ray) = 0;
	virtual Vector GetNormal(Point const& worldPoint, Intersection const& i) const = 0;
	Point WorldToObject(Point const &worldPoint) const;
	virtual Vector CalculateLocalNormal(Point const& localPoint, Intersection const& i) const = 0;
	Vector NormalToWorld(Vector const&localNormal) const;
	Color Lighting(Point const& position, Light const& light, Vector const& eye, Vector const& normal, bool inShadow = false) const;
};