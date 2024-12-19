#include <cmath>

#include "RayObject.h"
#include "Scene.h"

int RayObject::m_currentId = 0;

// Constructors
RayObject::RayObject() :
	m_id(++m_currentId),
	m_matrix(Mat4()),
	m_invertMat(Mat4()),
	m_material(Material()),
	m_canReceiveShadows(true),
	m_canCastShadows(true) {
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->AddRayObject(*this);
	}
}

RayObject::RayObject(RayObject const& other) :
	m_id(++m_currentId),
	m_matrix(other.m_matrix),
	m_invertMat(other.m_invertMat),
	m_material(other.m_material),
	m_canReceiveShadows(other.m_canReceiveShadows),
	m_canCastShadows(other.m_canCastShadows) {
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->AddRayObject(*this);
	}
}

RayObject::RayObject(RayObject&& other) noexcept :
	m_id(std::move(other.m_id)),
	m_matrix(std::move(other.m_matrix)),
	m_invertMat(std::move(other.m_invertMat)),
	m_material(std::move(other.m_material)),
	m_canReceiveShadows(std::move(other.m_canReceiveShadows)),
	m_canCastShadows(std::move(other.m_canCastShadows)) {
	// Reset source object pour éviter des doublons
	other.m_id = 0; // Réinitialise l'ID de l'objet source
	other.m_matrix = Mat4();
	other.m_invertMat = Mat4();
	other.m_material = Material();
	other.m_canReceiveShadows = false;
	other.m_canCastShadows = false;
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->AddRayObject(*this);
	}
}


// Destructor
RayObject::~RayObject() {
	if (Scene::GetCurrentScene() != nullptr) {
		//this.SetParent(Scene::GetCurrentScene().root);
		Scene::GetCurrentScene()->RemoveRayObject(*this);
	}
}


// Accessors
int RayObject::getNbInstances() {return m_currentId;}

int RayObject::GetId() const {return m_id;}

Mat4 RayObject::GetMatrix() const {return m_matrix;}

Mat4 RayObject::GetInvertMatrix() const { return m_matrix.inverted(); }

Point RayObject::GetPosition() const {
	return Point(m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);
}

Material RayObject::GetMaterial() const { return m_material; }

bool RayObject::CanReceiveShadows() const { return m_canReceiveShadows; }

bool RayObject::CanCastShadows() const { return m_canCastShadows; }

void RayObject::SetMatrix(Mat4 const& mat) {m_matrix = mat;}

void RayObject::SetPosition(Point const& p) {
	m_matrix[0][3] = p.getX();
	m_matrix[1][3] = p.getY();
	m_matrix[2][3] = p.getZ();
}

void RayObject::SetMaterial(Material const& material) {m_material = material;}

void RayObject::SetCanReceiveShadows(bool const& canReceiveShadows) { m_canReceiveShadows = canReceiveShadows; }

void RayObject::SetCanCastShadows(bool const& canCastShadows) { m_canCastShadows = canCastShadows; }


// Member functions
RayObject& RayObject::operator=(RayObject const& other) {
	if (this != &other) {//On vérifie que l'objet n'est pas le même que celui reçu en argument
		m_matrix = other.m_matrix;
		m_invertMat = other.m_invertMat;
		m_material = other.m_material;
		m_canReceiveShadows = other.m_canReceiveShadows;
		m_canCastShadows = other.m_canCastShadows;
	}
	return *this;
}

RayObject& RayObject::operator=(RayObject&& other) noexcept {
	if (this != &other) {
		m_matrix = std::move(other.m_matrix);
		m_invertMat = std::move(other.m_invertMat);
		m_material = std::move(other.m_material);
		m_canReceiveShadows = std::move(other.m_canReceiveShadows);
		m_canCastShadows = std::move(other.m_canCastShadows);

		// Reset source object
		other.m_matrix = Mat4();
		other.m_invertMat = Mat4();
		other.m_canReceiveShadows = false;
		other.m_canCastShadows = false;
	}
	return *this;
}

bool RayObject::operator==(RayObject const& other) const {
	return (m_id == other.m_id) &&
		   (m_matrix == other.m_matrix) &&
		   (m_canReceiveShadows == other.m_canReceiveShadows) &&
		   (m_canCastShadows == other.m_canCastShadows);
}

std::ostream& operator<<(std::ostream& flux, RayObject const& rayObject) {
	rayObject.afficher(flux);
	return flux;
}

void RayObject::afficher(std::ostream& flux) const {
	flux << "RayObject (id: " << m_id << ")";
}

Ray RayObject::RayToObjectSpace(Ray const& ray) const {
	return GetInvertMatrix() * ray;
}

Point RayObject::WorldToObject(Point const &worldPoint) const {
	/*if (this->GetParent() != null)
	{
		worldPoint = this->GetParent().WorldToObject(worldPoint);
	}*/
	return GetInvertMatrix() * worldPoint;
}

Vector RayObject::NormalToWorld(Vector const&localNormal) const  {
	Vector temp = GetInvertMatrix().transposed() * localNormal;
	Vector worldNormal;
	worldNormal = temp;	// WARNING : I must do that cause otherwise w is not 0.
	worldNormal.Normalize();

	/*if (this.GetParent() != null) {
		worldNormal = this->GetParent().NormalToWorld(worldNormal);
	}*/
	return worldNormal;
}

Color RayObject::Lighting(Point const&position, Light const& light, Vector const& eye, Vector const& normal, bool inShadow) const
{
	Color temp = m_material.GetColor();
	/*if (m_material.m_pattern != null)
	{
		temp = m_material.m_pattern.PatternAtObject(this, position);
	}*/

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
