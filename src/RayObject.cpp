#include "RayObject.h"
#include "Scene.h"

int RayObject::m_currentId = 0;

// Constructors
RayObject::RayObject() {
	m_id = ++m_currentId;
	m_matrix = Mat4();
	m_invertMat = m_matrix.inverted();
	m_material = Material();
	m_canReceiveShadows = true;
	m_canCastShadows = true;

	if (Scene::GetCurrentScene() != nullptr) {
		Scene::GetCurrentScene()->AddRayObject(*this);
	}
}

RayObject::RayObject(RayObject const& other) {
	m_id = ++m_currentId;
	m_matrix = other.m_matrix;
	m_invertMat = other.m_invertMat;
	m_canReceiveShadows = other.m_canReceiveShadows;
	m_canCastShadows = other.m_canCastShadows;
	if (Scene::GetCurrentScene() != nullptr) {
		Scene::GetCurrentScene()->AddRayObject(*this);
	}
}

RayObject::RayObject(RayObject&& other) noexcept :
	m_id(other.m_id),
	m_matrix(other.m_matrix),
	m_invertMat(other.m_invertMat),
	m_canReceiveShadows(other.m_canReceiveShadows),
	m_canCastShadows(other.m_canCastShadows) {
	// R�initialise l'objet source pour �viter des doublons
	other.m_id = 0; // R�initialise l'ID de l'objet source
	other.m_matrix = Mat4();
	other.m_invertMat = Mat4();
	other.m_canReceiveShadows = false;
	other.m_canCastShadows = false;
	if (Scene::GetCurrentScene() != nullptr) {
		Scene::GetCurrentScene()->AddRayObject(*this);
	}
}


// Destructor
RayObject::~RayObject() {}


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

void RayObject::SetMatrix(Mat4 mat) {m_matrix = mat;}

void RayObject::SetPosition(Point p) {
	m_matrix[0][3] = p.getX();
	m_matrix[1][3] = p.getY();
	m_matrix[2][3] = p.getZ();
}

void RayObject::SetMaterial(Material material) {m_material = material;}


// Operators
RayObject& RayObject::operator=(RayObject const& other) {
	if (this != &other) {//On v�rifie que l'objet n'est pas le m�me que celui re�u en argument
		m_matrix = other.m_matrix;
		m_invertMat = other.m_invertMat;
		m_canReceiveShadows = other.m_canReceiveShadows;
		m_canCastShadows = other.m_canCastShadows;
	}
	return *this;
}

RayObject& RayObject::operator=(RayObject&& other) noexcept {
	if (this != &other) {
		m_matrix = other.m_matrix;
		m_invertMat = other.m_invertMat;
		m_canReceiveShadows = other.m_canReceiveShadows;
		m_canCastShadows = other.m_canCastShadows;

		// R�initialise l'objet source
		other.m_id = 0;
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


// Member-functions
void RayObject::afficher(std::ostream& flux) const {
	flux << "RayObject (id: " << m_id << ")";
}

Ray RayObject::RayToObjectSpace(Ray& ray) const {
	return GetInvertMatrix() * ray;
}

Point RayObject::WorldToObject(Point const &worldPoint) const {
	/*if (this->GetParent() != null)
	{
		worldPoint = this->GetParent().WorldToObject(worldPoint);
	}*/
	return GetInvertMatrix() * worldPoint;
}

Vector RayObject::NormalToWorld(Vector &localNormal) const  {
	Vector temp = (GetInvertMatrix().transposed()) * localNormal;
	Vector worldNormal;
	worldNormal = temp;	// WARNING : I must do that cause otherwise w is not 0.
	worldNormal.Normalize();

	/*if (this.GetParent() != null) {
		worldNormal = this->GetParent().NormalToWorld(worldNormal);
	}*/
	return worldNormal;
}

Color RayObject::Lighting(Point position, Light light, Vector eye, Vector normal, bool inShadow) const
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

	float lDotN = lightVec.Dot(normal);
	if (lDotN <= 0) {
		diffuseColor = Color::black;
		specularColor = Color::black;
	}
	else {
		diffuseColor = effectiveColor * m_material.GetDiffuse() * lDotN;
		Vector reflect = Vector::Reflect(-lightVec, normal);
		float rDotE = reflect.Dot(eye);

		if (rDotE <= 0)
			specularColor = Color::black;
		else {
			float factor = pow(rDotE, m_material.GetShininess());
			specularColor = light.GetIntensity() * m_material.GetSpecular() * factor;
		}
	}
	return ambientColor + diffuseColor + specularColor;
}