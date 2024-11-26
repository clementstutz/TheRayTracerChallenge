#include "Mat4.h"
#include "Utils.h"

// Constructeurs
Mat4::Mat4(float m00, float m01, float m02, float m03,
		   float m10, float m11, float m12, float m13,
		   float m20, float m21, float m22, float m23,
		   float m30, float m31, float m32, float m33) {
	m_mat[0][0] = m00;
	m_mat[0][1] = m01;
	m_mat[0][2] = m02;
	m_mat[0][3] = m03;

	m_mat[1][0] = m10;
	m_mat[1][1] = m11;
	m_mat[1][2] = m12;
	m_mat[1][3] = m13;

	m_mat[2][0] = m20;
	m_mat[2][1] = m21;
	m_mat[2][2] = m22;
	m_mat[2][3] = m23;

	m_mat[3][0] = m30;
	m_mat[3][1] = m31;
	m_mat[3][2] = m32;
	m_mat[3][3] = m33;
}

Mat4::Mat4(Mat4 const& other) {
	m_mat[0][0] = other.m_mat[0][0];
	m_mat[0][1] = other.m_mat[0][1];
	m_mat[0][2] = other.m_mat[0][2];
	m_mat[0][3] = other.m_mat[0][3];

	m_mat[1][0] = other.m_mat[1][0];
	m_mat[1][1] = other.m_mat[1][1];
	m_mat[1][2] = other.m_mat[1][2];
	m_mat[1][3] = other.m_mat[1][3];

	m_mat[2][0] = other.m_mat[2][0];
	m_mat[2][1] = other.m_mat[2][1];
	m_mat[2][2] = other.m_mat[2][2];
	m_mat[2][3] = other.m_mat[2][3];

	m_mat[3][0] = other.m_mat[3][0];
	m_mat[3][1] = other.m_mat[3][1];
	m_mat[3][2] = other.m_mat[3][2];
	m_mat[3][3] = other.m_mat[3][3];
}

Mat4& Mat4::operator=(Mat4 const& other) {
	if (this != &other) {	//On vérifie que l'objet n'est pas le même que celui reçu en argument
		m_mat[0][0] = other.m_mat[0][0];
		m_mat[0][1] = other.m_mat[0][1];
		m_mat[0][2] = other.m_mat[0][2];
		m_mat[0][3] = other.m_mat[0][3];

		m_mat[1][0] = other.m_mat[1][0];
		m_mat[1][1] = other.m_mat[1][1];
		m_mat[1][2] = other.m_mat[1][2];
		m_mat[1][3] = other.m_mat[1][3];

		m_mat[2][0] = other.m_mat[2][0];
		m_mat[2][1] = other.m_mat[2][1];
		m_mat[2][2] = other.m_mat[2][2];
		m_mat[2][3] = other.m_mat[2][3];

		m_mat[3][0] = other.m_mat[3][0];
		m_mat[3][1] = other.m_mat[3][1];
		m_mat[3][2] = other.m_mat[3][2];
		m_mat[3][3] = other.m_mat[3][3];
	}
	return *this;
}

// Accesseurs
float(&Mat4::operator[](int row))[4]{
	if (row < 0 || row >= 4) {
		throw std::out_of_range("Index hors limites pour Mat4.");
	}
	return m_mat[row];
}

const float(&Mat4::operator[](int row) const)[4]{
	if (row < 0 || row >= 4) {
		throw std::out_of_range("Index hors limites pour Mat4.");
	}
	return m_mat[row];
}

// Opérateurs
bool Mat4::operator==(Mat4 const& other) const {
	return Utils::FE(m_mat[0][0], other.m_mat[0][0]) && Utils::FE(m_mat[0][1], other.m_mat[0][1]) && Utils::FE(m_mat[0][2], other.m_mat[0][2]) && Utils::FE(m_mat[0][3], other.m_mat[0][3]) &&
		Utils::FE(m_mat[1][0], other.m_mat[1][0]) && Utils::FE(m_mat[1][1], other.m_mat[1][1]) && Utils::FE(m_mat[1][2], other.m_mat[1][2]) && Utils::FE(m_mat[1][3], other.m_mat[1][3])&&
		Utils::FE(m_mat[2][0], other.m_mat[2][0]) && Utils::FE(m_mat[2][1], other.m_mat[2][1]) && Utils::FE(m_mat[2][2], other.m_mat[2][2]) && Utils::FE(m_mat[2][3], other.m_mat[2][3])&&
		Utils::FE(m_mat[3][0], other.m_mat[3][0]) && Utils::FE(m_mat[3][1], other.m_mat[3][1]) && Utils::FE(m_mat[3][2], other.m_mat[3][2]) && Utils::FE(m_mat[3][3], other.m_mat[3][3]);
}

Mat4& Mat4::operator*=(Mat4 const& other) {
    float a00 = m_mat[0][0] * other.m_mat[0][0] + m_mat[0][1] * other.m_mat[1][0] +
                m_mat[0][2] * other.m_mat[2][0] + m_mat[0][3] * other.m_mat[3][0];
    float a01 = m_mat[0][0] * other.m_mat[0][1] + m_mat[0][1] * other.m_mat[1][1] +
                m_mat[0][2] * other.m_mat[2][1] + m_mat[0][3] * other.m_mat[3][1];
    float a02 = m_mat[0][0] * other.m_mat[0][2] + m_mat[0][1] * other.m_mat[1][2] +
                m_mat[0][2] * other.m_mat[2][2] + m_mat[0][3] * other.m_mat[3][2];
    float a03 = m_mat[0][0] * other.m_mat[0][3] + m_mat[0][1] * other.m_mat[1][3] +
                m_mat[0][2] * other.m_mat[2][3] + m_mat[0][3] * other.m_mat[3][3];

    float a10 = m_mat[1][0] * other.m_mat[0][0] + m_mat[1][1] * other.m_mat[1][0] +
                m_mat[1][2] * other.m_mat[2][0] + m_mat[1][3] * other.m_mat[3][0];
    float a11 = m_mat[1][0] * other.m_mat[0][1] + m_mat[1][1] * other.m_mat[1][1] +
                m_mat[1][2] * other.m_mat[2][1] + m_mat[1][3] * other.m_mat[3][1];
    float a12 = m_mat[1][0] * other.m_mat[0][2] + m_mat[1][1] * other.m_mat[1][2] +
                m_mat[1][2] * other.m_mat[2][2] + m_mat[1][3] * other.m_mat[3][2];
    float a13 = m_mat[1][0] * other.m_mat[0][3] + m_mat[1][1] * other.m_mat[1][3] +
                m_mat[1][2] * other.m_mat[2][3] + m_mat[1][3] * other.m_mat[3][3];

    float a20 = m_mat[2][0] * other.m_mat[0][0] + m_mat[2][1] * other.m_mat[1][0] +
                m_mat[2][2] * other.m_mat[2][0] + m_mat[2][3] * other.m_mat[3][0];
    float a21 = m_mat[2][0] * other.m_mat[0][1] + m_mat[2][1] * other.m_mat[1][1] +
                m_mat[2][2] * other.m_mat[2][1] + m_mat[2][3] * other.m_mat[3][1];
    float a22 = m_mat[2][0] * other.m_mat[0][2] + m_mat[2][1] * other.m_mat[1][2] +
                m_mat[2][2] * other.m_mat[2][2] + m_mat[2][3] * other.m_mat[3][2];
    float a23 = m_mat[2][0] * other.m_mat[0][3] + m_mat[2][1] * other.m_mat[1][3] +
                m_mat[2][2] * other.m_mat[2][3] + m_mat[2][3] * other.m_mat[3][3];

    float a30 = m_mat[3][0] * other.m_mat[0][0] + m_mat[3][1] * other.m_mat[1][0] +
                m_mat[3][2] * other.m_mat[2][0] + m_mat[3][3] * other.m_mat[3][0];
    float a31 = m_mat[3][0] * other.m_mat[0][1] + m_mat[3][1] * other.m_mat[1][1] +
                m_mat[3][2] * other.m_mat[2][1] + m_mat[3][3] * other.m_mat[3][1];
    float a32 = m_mat[3][0] * other.m_mat[0][2] + m_mat[3][1] * other.m_mat[1][2] +
                m_mat[3][2] * other.m_mat[2][2] + m_mat[3][3] * other.m_mat[3][2];
    float a33 = m_mat[3][0] * other.m_mat[0][3] + m_mat[3][1] * other.m_mat[1][3] +
                m_mat[3][2] * other.m_mat[2][3] + m_mat[3][3] * other.m_mat[3][3];

    m_mat[0][0] = a00;
    m_mat[0][1] = a01;
    m_mat[0][2] = a02;
    m_mat[0][3] = a03;

    m_mat[1][0] = a10;
    m_mat[1][1] = a11;
    m_mat[1][2] = a12;
    m_mat[1][3] = a13;

    m_mat[2][0] = a20;
    m_mat[2][1] = a21;
    m_mat[2][2] = a22;
    m_mat[2][3] = a23;

    m_mat[3][0] = a30;
    m_mat[3][1] = a31;
    m_mat[3][2] = a32;
    m_mat[3][3] = a33;

    return *this;
}

void Mat4::transpose() {
	std::swap(m_mat[0][1], m_mat[1][0]);
	std::swap(m_mat[0][2], m_mat[2][0]);
	std::swap(m_mat[0][3], m_mat[3][0]);
	std::swap(m_mat[1][2], m_mat[2][1]);
	std::swap(m_mat[1][3], m_mat[3][1]);
	std::swap(m_mat[2][3], m_mat[3][2]);
}

Mat4 Mat4::transposed() const {
	Mat4 temp(*this);
	temp.transpose();
	return temp;
}

float Mat4::det() {
	float a = m_mat[2][2] * m_mat[3][3] - m_mat[2][3] * m_mat[3][2];
	float b = m_mat[2][1] * m_mat[3][3] - m_mat[2][3] * m_mat[3][1];
	float c = m_mat[2][1] * m_mat[3][2] - m_mat[2][2] * m_mat[3][1];
	float d = m_mat[1][1] * a - m_mat[1][2] * b + m_mat[1][3] * c;

	float e = m_mat[2][0] * m_mat[3][3] - m_mat[2][3] * m_mat[3][0];
	float f = m_mat[2][0] * m_mat[3][2] - m_mat[2][2] * m_mat[3][0];
	float g = m_mat[1][0] * a - m_mat[1][2] * e + m_mat[1][3] * f;

	float h = m_mat[2][0] * m_mat[3][1] - m_mat[2][1] * m_mat[3][0];
	float i = m_mat[1][0] * b - m_mat[1][1] * e + m_mat[1][3] * h;

	float j = m_mat[1][0] * c - m_mat[1][1] * f + m_mat[1][2] * h;

	return m_mat[0][0] * d - m_mat[0][1] * g + m_mat[0][2] * i - m_mat[0][3] * j;
}

void Mat4::invert() {
	float det = this->det();
	if (Utils::FE(det, 0.0)) {
		throw std::runtime_error("La matrice n'est pas inversible.");
	}
	float invDet = 1.0f / det;

	// Pré-calcul des termes communs pour les mineurs
	float minor0 = m_mat[2][2] * m_mat[3][3] - m_mat[2][3] * m_mat[3][2];
	float minor1 = m_mat[2][1] * m_mat[3][3] - m_mat[2][3] * m_mat[3][1];
	float minor2 = m_mat[2][1] * m_mat[3][2] - m_mat[2][2] * m_mat[3][1];
	float minor3 = m_mat[2][0] * m_mat[3][3] - m_mat[2][3] * m_mat[3][0];
	float minor4 = m_mat[2][0] * m_mat[3][2] - m_mat[2][2] * m_mat[3][0];
	float minor5 = m_mat[2][0] * m_mat[3][1] - m_mat[2][1] * m_mat[3][0];

	float minor6 = m_mat[1][2] * m_mat[3][3] - m_mat[1][3] * m_mat[3][2];
	float minor7 = m_mat[1][1] * m_mat[3][3] - m_mat[1][3] * m_mat[3][1];
	float minor8 = m_mat[1][1] * m_mat[3][2] - m_mat[1][2] * m_mat[3][1];
	float minor9 = m_mat[1][0] * m_mat[3][3] - m_mat[1][3] * m_mat[3][0];
	float minor10 = m_mat[1][0] * m_mat[3][2] - m_mat[1][2] * m_mat[3][0];
	float minor11 = m_mat[1][0] * m_mat[3][1] - m_mat[1][1] * m_mat[3][0];

	float minor12 = m_mat[1][2] * m_mat[2][3] - m_mat[1][3] * m_mat[2][2];
	float minor13 = m_mat[1][1] * m_mat[2][3] - m_mat[1][3] * m_mat[2][1];
	float minor14 = m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1];
	float minor15 = m_mat[1][0] * m_mat[2][3] - m_mat[1][3] * m_mat[2][0];
	float minor16 = m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0];
	float minor17 = m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0];

	// Calcul des cofacteurs
	float a00 =  (m_mat[1][1] * minor0 - m_mat[1][2] * minor1 + m_mat[1][3] * minor2) * invDet;
	float a01 = -(m_mat[1][0] * minor0 - m_mat[1][2] * minor3 + m_mat[1][3] * minor4) * invDet;
	float a02 =  (m_mat[1][0] * minor1 - m_mat[1][1] * minor3 + m_mat[1][3] * minor5) * invDet;
	float a03 = -(m_mat[1][0] * minor2 - m_mat[1][1] * minor4 + m_mat[1][2] * minor5) * invDet;

	float a10 = -(m_mat[0][1] * minor0 - m_mat[0][2] * minor1 + m_mat[0][3] * minor2) * invDet;
	float a11 =  (m_mat[0][0] * minor0 - m_mat[0][2] * minor3 + m_mat[0][3] * minor4) * invDet;
	float a12 = -(m_mat[0][0] * minor1 - m_mat[0][1] * minor3 + m_mat[0][3] * minor5) * invDet;
	float a13 =  (m_mat[0][0] * minor2 - m_mat[0][1] * minor4 + m_mat[0][2] * minor5) * invDet;

	float a20 =  (m_mat[0][1] * minor6 - m_mat[0][2] * minor7 + m_mat[0][3] * minor8) * invDet;
	float a21 = -(m_mat[0][0] * minor6 - m_mat[0][2] * minor9 + m_mat[0][3] * minor10) * invDet;
	float a22 =  (m_mat[0][0] * minor7 - m_mat[0][1] * minor9 + m_mat[0][3] * minor11) * invDet;
	float a23 = -(m_mat[0][0] * minor8 - m_mat[0][1] * minor10 + m_mat[0][2] * minor11) * invDet;

	float a30 = -(m_mat[0][1] * minor12 - m_mat[0][2] * minor13 + m_mat[0][3] * minor14) * invDet;
	float a31 =  (m_mat[0][0] * minor12 - m_mat[0][2] * minor15 + m_mat[0][3] * minor16) * invDet;
	float a32 = -(m_mat[0][0] * minor13 - m_mat[0][1] * minor15 + m_mat[0][3] * minor17) * invDet;
	float a33 =  (m_mat[0][0] * minor14 - m_mat[0][1] * minor16 + m_mat[0][2] * minor17) * invDet;

	// Mise à jour de la matrice
	m_mat[0][0] = a00; m_mat[0][1] = a10; m_mat[0][2] = a20; m_mat[0][3] = a30;
	m_mat[1][0] = a01; m_mat[1][1] = a11; m_mat[1][2] = a21; m_mat[1][3] = a31;
	m_mat[2][0] = a02; m_mat[2][1] = a12; m_mat[2][2] = a22; m_mat[2][3] = a32;
	m_mat[3][0] = a03; m_mat[3][1] = a13; m_mat[3][2] = a23; m_mat[3][3] = a33;
}

Mat4 Mat4::inverted() const {
	Mat4 copy(*this);
	copy.invert();
	return copy;
}

std::ostream& operator<<(std::ostream& flux, const Mat4& mat) {
	mat.afficher(flux);
	return flux;
}

void Mat4::afficher(std::ostream& flux) const {
	flux << "[[" << m_mat[0][0] << ", " << m_mat[0][1] << ", " << m_mat[0][2] << ", " << m_mat[0][3] << "], "
		  << "[" << m_mat[1][0] << ", " << m_mat[1][1] << ", " << m_mat[1][2] << ", " << m_mat[1][3] << "], "
		  << "[" << m_mat[2][0] << ", " << m_mat[2][1] << ", " << m_mat[2][2] << ", " << m_mat[2][3] << "], "
		  << "[" << m_mat[3][0] << ", " << m_mat[3][1] << ", " << m_mat[3][2] << ", " << m_mat[3][3] << "]]";
}

//fonctions non-membres
bool operator!=(const Mat4& mat_a, const Mat4& mat_b) {
	return !(mat_a == mat_b);
}

Mat4 operator*(Mat4 const& a, Mat4 const& b) {
	Mat4 result(a);
	result *= b;
	return result;
}