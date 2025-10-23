#include <cmath>

#include "Shape.h"
#include "Scene.h"

int Shape::m_currentId = 0;

// Constructors
Shape::Shape() :
	m_id(++m_currentId),
	m_matrix(Mat4()),
	m_invertMat(Mat4()),
	m_material(Material()),
	m_canReceiveShadows(true),
	m_canCastShadows(true),
	m_parent(nullptr) {
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->AddShape(*this);
	}
}

Shape::Shape(Shape const& other) :
	m_id(++m_currentId),
	m_matrix(other.m_matrix),
	m_invertMat(other.m_invertMat),
	m_material(other.m_material),
	m_canReceiveShadows(other.m_canReceiveShadows),
	m_canCastShadows(other.m_canCastShadows),
	m_parent(other.m_parent) {
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->AddShape(*this);
	}
}

Shape::Shape(Shape&& other) noexcept :
	m_id(std::move(other.m_id)),
	m_matrix(std::move(other.m_matrix)),
	m_invertMat(std::move(other.m_invertMat)),
	m_material(std::move(other.m_material)),
	m_canReceiveShadows(std::move(other.m_canReceiveShadows)),
	m_canCastShadows(std::move(other.m_canCastShadows)),
	m_parent(std::move(other.m_parent)) {
	// Reset source object pour �viter des doublons
	other.m_id = 0; // R�initialise l'ID de l'objet source
	other.m_matrix = Mat4();
	other.m_invertMat = Mat4();
	other.m_material = Material();
	other.m_canReceiveShadows = false;
	other.m_canCastShadows = false;
	other.m_parent = nullptr;
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->AddShape(*this);
	}
}


// Destructor
Shape::~Shape() {
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->RemoveShape(*this);
	}
}


// Accessors
int Shape::getNbInstances() {return m_currentId;}

int Shape::GetId() const {return m_id;}

Mat4 Shape::GetMatrix() const {return m_matrix;}

Mat4 Shape::GetInvertMatrix() const { return m_matrix.inverted(); }

Point Shape::GetPosition() const {
	return Point(m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);
}

Material Shape::GetMaterial() const { return m_material; }

bool Shape::CanReceiveShadows() const { return m_canReceiveShadows; }

bool Shape::CanCastShadows() const { return m_canCastShadows; }

Shape* Shape::GetParent() const { return m_parent; }

void Shape::SetMatrix(Mat4 const& mat) {m_matrix = mat;}

void Shape::SetPosition(Point const& p) {
	m_matrix[0][3] = p.getX();
	m_matrix[1][3] = p.getY();
	m_matrix[2][3] = p.getZ();
}

void Shape::SetMaterial(Material const& material) {m_material = material;}

void Shape::SetCanReceiveShadows(bool const& canReceiveShadows) { m_canReceiveShadows = canReceiveShadows; }

void Shape::SetCanCastShadows(bool const& canCastShadows) { m_canCastShadows = canCastShadows; }

void Shape::SetParent(Shape* parent) { m_parent = parent; }


// Member functions
Shape& Shape::operator=(Shape const& other) {
	if (this != &other) {//On v�rifie que l'objet n'est pas le m�me que celui re�u en argument
		m_matrix = other.m_matrix;
		m_invertMat = other.m_invertMat;
		m_material = other.m_material;
		m_canReceiveShadows = other.m_canReceiveShadows;
		m_canCastShadows = other.m_canCastShadows;
		m_parent = other.m_parent;
	}
	return *this;
}

Shape& Shape::operator=(Shape&& other) noexcept {
	if (this != &other) {
		m_matrix = std::move(other.m_matrix);
		m_invertMat = std::move(other.m_invertMat);
		m_material = std::move(other.m_material);
		m_canReceiveShadows = std::move(other.m_canReceiveShadows);
		m_canCastShadows = std::move(other.m_canCastShadows);
		m_parent = std::move(other.m_parent);

		// Reset source object
		other.m_matrix = Mat4();
		other.m_invertMat = Mat4();
		other.m_material = Material();
		other.m_canReceiveShadows = false;
		other.m_canCastShadows = false;
		other.m_parent = nullptr;
	}
	return *this;
}

bool Shape::operator==(Shape const& other) const {
	return (m_id == other.m_id) &&
		   (m_matrix == other.m_matrix) &&
		   (m_material == other.m_material) &&
		   (m_canReceiveShadows == other.m_canReceiveShadows) &&
		   (m_canCastShadows == other.m_canCastShadows) &&
		   (m_parent == other.m_parent);
}

std::ostream& operator<<(std::ostream& flux, Shape const& shape) {
	shape.afficher(flux);
	return flux;
}

void Shape::afficher(std::ostream& flux) const {
	flux << "Shape (id: " << m_id << ")";
}

Ray Shape::RayToObjectSpace(Ray const& ray) const {
	return GetInvertMatrix() * ray;
}

Point Shape::WorldToObject(Point const &worldPoint) const {
	// La copie de worldPoint dans temp pour palier le fait que worldPoint et une ref constant n'est surement pas optimal, mais pour le moment ça marche.
	// TODO : optimiser ça.
	Point temp = worldPoint;
	if (this->GetParent() != nullptr)
	{
		temp = this->GetParent()->WorldToObject(temp);
	}
	return GetInvertMatrix() * temp;
}

Vector Shape::NormalToWorld(Vector const&localNormal) const  {
	Vector worldNormal = GetInvertMatrix().transposed() * localNormal;
	worldNormal.set(worldNormal.getX(), worldNormal.getY(), worldNormal.getZ(), 0.0);	// WARNING : I must do that cause otherwise w is not 0.
	worldNormal.Normalize();

	if (this->GetParent() != nullptr) {
		worldNormal = this->GetParent()->NormalToWorld(worldNormal);
	}
	return worldNormal;
}

Color Shape::Lighting(Point const&position, Light const& light, Vector const& eye, Vector const& normal, bool inShadow) const
{
	Color temp = m_material.GetColor();
	if (m_material.GetPattern() != nullptr) {
		Point objectPoint = WorldToObject(position);
		temp = m_material.GetPattern()->PatternAtObject(objectPoint);
	}

	Color effectiveColor = temp * light.GetIntensity();
	Vector lightVec = (light.GetPosition() - position).Normalize();
	Color ambientColor = temp * m_material.GetAmbient();
	Color diffuseColor;
	Color specularColor;

	if (inShadow)
		return ambientColor;

	double lDotN = lightVec.Dot(normal);
	if (lDotN <= 0) {
		diffuseColor = Color::black;
		specularColor = Color::black;
	}
	else {
		diffuseColor = effectiveColor * m_material.GetDiffuse() * lDotN;
		Vector reflect = Vector::Reflect(-lightVec, normal);
		double rDotE = reflect.Dot(eye);

		if (rDotE <= 0)
			specularColor = Color::black;
		else {
			double factor = std::pow(rDotE, m_material.GetShininess());
			specularColor = light.GetIntensity() * m_material.GetSpecular() * factor;
		}
	}
	return ambientColor + diffuseColor + specularColor;
}
