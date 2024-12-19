#include <cmath>
#include <iomanip> // Pour std::fixed et std::setprecision

#include "Mat4.h"
#include "Utils.h"
#include "Mat2.h"

// Constructors
Mat4::Mat4(double m00, double m01, double m02, double m03,
		   double m10, double m11, double m12, double m13,
		   double m20, double m21, double m22, double m23,
		   double m30, double m31, double m32, double m33) {
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

Mat4::Mat4(Mat4&& other) noexcept {
	m_mat[0][0] = std::move(other.m_mat[0][0]);
	m_mat[0][1] = std::move(other.m_mat[0][1]);
	m_mat[0][2] = std::move(other.m_mat[0][2]);
	m_mat[0][3] = std::move(other.m_mat[0][3]);

	m_mat[1][0] = std::move(other.m_mat[1][0]);
	m_mat[1][1] = std::move(other.m_mat[1][1]);
	m_mat[1][2] = std::move(other.m_mat[1][2]);
	m_mat[1][3] = std::move(other.m_mat[1][3]);

	m_mat[2][0] = std::move(other.m_mat[2][0]);
	m_mat[2][1] = std::move(other.m_mat[2][1]);
	m_mat[2][2] = std::move(other.m_mat[2][2]);
	m_mat[2][3] = std::move(other.m_mat[2][3]);

	m_mat[3][0] = std::move(other.m_mat[3][0]);
	m_mat[3][1] = std::move(other.m_mat[3][1]);
	m_mat[3][2] = std::move(other.m_mat[3][2]);
	m_mat[3][3] = std::move(other.m_mat[3][3]);

	// Reset source object pour éviter des doublons
	other = Mat4();
}


// Accessors
double(&Mat4::operator[](int row))[4]{
	if (row < 0 || row >= 4) {
		throw std::out_of_range("Index hors limites pour Mat4.");
	}
	return m_mat[row];
}

const double(&Mat4::operator[](int row) const)[4]{
	if (row < 0 || row >= 4) {
		throw std::out_of_range("Index hors limites pour Mat4.");
	}
	return m_mat[row];
}


// Member functions
bool Mat4::operator==(Mat4 const& other) const {
	return Utils::FE(m_mat[0][0], other.m_mat[0][0]) && Utils::FE(m_mat[0][1], other.m_mat[0][1]) && Utils::FE(m_mat[0][2], other.m_mat[0][2]) && Utils::FE(m_mat[0][3], other.m_mat[0][3]) &&
		   Utils::FE(m_mat[1][0], other.m_mat[1][0]) && Utils::FE(m_mat[1][1], other.m_mat[1][1]) && Utils::FE(m_mat[1][2], other.m_mat[1][2]) && Utils::FE(m_mat[1][3], other.m_mat[1][3])&&
		   Utils::FE(m_mat[2][0], other.m_mat[2][0]) && Utils::FE(m_mat[2][1], other.m_mat[2][1]) && Utils::FE(m_mat[2][2], other.m_mat[2][2]) && Utils::FE(m_mat[2][3], other.m_mat[2][3])&&
		   Utils::FE(m_mat[3][0], other.m_mat[3][0]) && Utils::FE(m_mat[3][1], other.m_mat[3][1]) && Utils::FE(m_mat[3][2], other.m_mat[3][2]) && Utils::FE(m_mat[3][3], other.m_mat[3][3]);
}

Mat4& Mat4::operator=(Mat4 const& other) {
	if (this != &other) {
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

Mat4& Mat4::operator=(Mat4&& other) noexcept {
	if (this != &other) {
		m_mat[0][0] = std::move(other.m_mat[0][0]);
		m_mat[0][1] = std::move(other.m_mat[0][1]);
		m_mat[0][2] = std::move(other.m_mat[0][2]);
		m_mat[0][3] = std::move(other.m_mat[0][3]);

		m_mat[1][0] = std::move(other.m_mat[1][0]);
		m_mat[1][1] = std::move(other.m_mat[1][1]);
		m_mat[1][2] = std::move(other.m_mat[1][2]);
		m_mat[1][3] = std::move(other.m_mat[1][3]);

		m_mat[2][0] = std::move(other.m_mat[2][0]);
		m_mat[2][1] = std::move(other.m_mat[2][1]);
		m_mat[2][2] = std::move(other.m_mat[2][2]);
		m_mat[2][3] = std::move(other.m_mat[2][3]);

		m_mat[3][0] = std::move(other.m_mat[3][0]);
		m_mat[3][1] = std::move(other.m_mat[3][1]);
		m_mat[3][2] = std::move(other.m_mat[3][2]);
		m_mat[3][3] = std::move(other.m_mat[3][3]);

		// Reset source object
		other.m_mat[0][0] = 0.0;
		other.m_mat[0][1] = 0.0;
		other.m_mat[0][2] = 0.0;
		other.m_mat[0][3] = 0.0;

		other.m_mat[1][0] = 0.0;
		other.m_mat[1][1] = 0.0;
		other.m_mat[1][2] = 0.0;
		other.m_mat[1][3] = 0.0;

		other.m_mat[2][0] = 0.0;
		other.m_mat[2][1] = 0.0;
		other.m_mat[2][2] = 0.0;
		other.m_mat[2][3] = 0.0;

		other.m_mat[3][0] = 0.0;
		other.m_mat[3][1] = 0.0;
		other.m_mat[3][2] = 0.0;
		other.m_mat[3][3] = 0.0;
	}
	return *this;
}

Mat4& Mat4::operator+=(Mat4 const& other) {
	m_mat[0][0] = m_mat[0][0] + other.m_mat[0][0];
	m_mat[0][1] = m_mat[0][1] + other.m_mat[0][1];
	m_mat[0][2] = m_mat[0][2] + other.m_mat[0][2];
	m_mat[0][3] = m_mat[0][3] + other.m_mat[0][3];

	m_mat[1][0] = m_mat[1][0] + other.m_mat[1][0];
	m_mat[1][1] = m_mat[1][1] + other.m_mat[1][1];
	m_mat[1][2] = m_mat[1][2] + other.m_mat[1][2];
	m_mat[1][3] = m_mat[1][3] + other.m_mat[1][3];

	m_mat[2][0] = m_mat[2][0] + other.m_mat[2][0];
	m_mat[2][1] = m_mat[2][1] + other.m_mat[2][1];
	m_mat[2][2] = m_mat[2][2] + other.m_mat[2][2];
	m_mat[2][3] = m_mat[2][3] + other.m_mat[2][3];

	m_mat[3][0] = m_mat[3][0] + other.m_mat[3][0];
	m_mat[3][1] = m_mat[3][1] + other.m_mat[3][1];
	m_mat[3][2] = m_mat[3][2] + other.m_mat[3][2];
	m_mat[3][3] = m_mat[3][3] + other.m_mat[3][3];

	return *this;
}

Mat4& Mat4::operator-=(Mat4 const& other) {
	m_mat[0][0] = m_mat[0][0] - other.m_mat[0][0];
	m_mat[0][1] = m_mat[0][1] - other.m_mat[0][1];
	m_mat[0][2] = m_mat[0][2] - other.m_mat[0][2];
	m_mat[0][3] = m_mat[0][3] - other.m_mat[0][3];

	m_mat[1][0] = m_mat[1][0] - other.m_mat[1][0];
	m_mat[1][1] = m_mat[1][1] - other.m_mat[1][1];
	m_mat[1][2] = m_mat[1][2] - other.m_mat[1][2];
	m_mat[1][3] = m_mat[1][3] - other.m_mat[1][3];

	m_mat[2][0] = m_mat[2][0] - other.m_mat[2][0];
	m_mat[2][1] = m_mat[2][1] - other.m_mat[2][1];
	m_mat[2][2] = m_mat[2][2] - other.m_mat[2][2];
	m_mat[2][3] = m_mat[2][3] - other.m_mat[2][3];

	m_mat[3][0] = m_mat[3][0] - other.m_mat[3][0];
	m_mat[3][1] = m_mat[3][1] - other.m_mat[3][1];
	m_mat[3][2] = m_mat[3][2] - other.m_mat[3][2];
	m_mat[3][3] = m_mat[3][3] - other.m_mat[3][3];

	return *this;
}

Mat4& Mat4::operator*=(Mat4 const& other) {
    double a00 = m_mat[0][0] * other.m_mat[0][0] + m_mat[0][1] * other.m_mat[1][0] +
                m_mat[0][2] * other.m_mat[2][0] + m_mat[0][3] * other.m_mat[3][0];
    double a01 = m_mat[0][0] * other.m_mat[0][1] + m_mat[0][1] * other.m_mat[1][1] +
                m_mat[0][2] * other.m_mat[2][1] + m_mat[0][3] * other.m_mat[3][1];
    double a02 = m_mat[0][0] * other.m_mat[0][2] + m_mat[0][1] * other.m_mat[1][2] +
                m_mat[0][2] * other.m_mat[2][2] + m_mat[0][3] * other.m_mat[3][2];
    double a03 = m_mat[0][0] * other.m_mat[0][3] + m_mat[0][1] * other.m_mat[1][3] +
                m_mat[0][2] * other.m_mat[2][3] + m_mat[0][3] * other.m_mat[3][3];

    double a10 = m_mat[1][0] * other.m_mat[0][0] + m_mat[1][1] * other.m_mat[1][0] +
                m_mat[1][2] * other.m_mat[2][0] + m_mat[1][3] * other.m_mat[3][0];
    double a11 = m_mat[1][0] * other.m_mat[0][1] + m_mat[1][1] * other.m_mat[1][1] +
                m_mat[1][2] * other.m_mat[2][1] + m_mat[1][3] * other.m_mat[3][1];
    double a12 = m_mat[1][0] * other.m_mat[0][2] + m_mat[1][1] * other.m_mat[1][2] +
                m_mat[1][2] * other.m_mat[2][2] + m_mat[1][3] * other.m_mat[3][2];
    double a13 = m_mat[1][0] * other.m_mat[0][3] + m_mat[1][1] * other.m_mat[1][3] +
                m_mat[1][2] * other.m_mat[2][3] + m_mat[1][3] * other.m_mat[3][3];

    double a20 = m_mat[2][0] * other.m_mat[0][0] + m_mat[2][1] * other.m_mat[1][0] +
                m_mat[2][2] * other.m_mat[2][0] + m_mat[2][3] * other.m_mat[3][0];
    double a21 = m_mat[2][0] * other.m_mat[0][1] + m_mat[2][1] * other.m_mat[1][1] +
                m_mat[2][2] * other.m_mat[2][1] + m_mat[2][3] * other.m_mat[3][1];
    double a22 = m_mat[2][0] * other.m_mat[0][2] + m_mat[2][1] * other.m_mat[1][2] +
                m_mat[2][2] * other.m_mat[2][2] + m_mat[2][3] * other.m_mat[3][2];
    double a23 = m_mat[2][0] * other.m_mat[0][3] + m_mat[2][1] * other.m_mat[1][3] +
                m_mat[2][2] * other.m_mat[2][3] + m_mat[2][3] * other.m_mat[3][3];

    double a30 = m_mat[3][0] * other.m_mat[0][0] + m_mat[3][1] * other.m_mat[1][0] +
                m_mat[3][2] * other.m_mat[2][0] + m_mat[3][3] * other.m_mat[3][0];
    double a31 = m_mat[3][0] * other.m_mat[0][1] + m_mat[3][1] * other.m_mat[1][1] +
                m_mat[3][2] * other.m_mat[2][1] + m_mat[3][3] * other.m_mat[3][1];
    double a32 = m_mat[3][0] * other.m_mat[0][2] + m_mat[3][1] * other.m_mat[1][2] +
                m_mat[3][2] * other.m_mat[2][2] + m_mat[3][3] * other.m_mat[3][2];
    double a33 = m_mat[3][0] * other.m_mat[0][3] + m_mat[3][1] * other.m_mat[1][3] +
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

	//Strassen algorithm
	// Décomposition en sous-matrices 2x2
	//Mat2 a1(m_mat[0][0], m_mat[0][1], m_mat[1][0], m_mat[1][1]);
	//Mat2 a2(m_mat[0][2], m_mat[0][3], m_mat[1][2], m_mat[1][3]);
	//Mat2 a3(m_mat[2][0], m_mat[2][1], m_mat[3][0], m_mat[3][1]);
	//Mat2 a4(m_mat[2][2], m_mat[2][3], m_mat[3][2], m_mat[3][3]);

	//Mat2 b1(other[0][0], other[0][1], other[1][0], other[1][1]);
	//Mat2 b2(other[0][2], other[0][3], other[1][2], other[1][3]);
	//Mat2 b3(other[2][0], other[2][1], other[3][0], other[3][1]);
	//Mat2 b4(other[2][2], other[2][3], other[3][2], other[3][3]);

	//// Calcul des produits de Strassen
	//Mat2 p1 = (a1 + a4) * (b1 + b4);	// P1 = (A1 + A4)(B1 + B4)
	//Mat2 p2 = (a3 + a4) * b1;			// P2 = (A3 + A4)B1
	//Mat2 p3 = a1 * (b2 - b4);			// P3 = A1(B2 - B4)
	//Mat2 p4 = a4 * (b3 - b1);			// P4 = A4(B3 - B1)
	//Mat2 p5 = (a1 + a2) * b4;			// P5 = (A1 + A2)B4
	//Mat2 p6 = (a3 - a1) * (b1 + b2);	// P6 = (A3 - A1)(B1 + B2)
	//Mat2 p7 = (a2 - a4) * (b3 + b4);	// P7 = (A2 - A4)(B3 + B4)

	//// Calcul des sous-blocs de la matrice résultat
	//Mat2 c1 = p1 + p4 - p5 + p7;        // C1 = P1 + P4 - P5 + P7
	//Mat2 c2 = p3 + p5;                  // C2 = P3 + P5
	//Mat2 c3 = p2 + p4;                  // C3 = P2 + P4
	//Mat2 c4 = p1 - p2 + p3 + p6;        // C4 = P1 - P2 + P3 + P6

	//// Reconstruction de la matrice 4x4 à partir des sous-matrices
	//m_mat[0][0] = c1[0][0]; m_mat[0][1] = c1[0][1];
	//m_mat[0][2] = c2[0][0]; m_mat[0][3] = c2[0][1];

	//m_mat[1][0] = c1[1][0]; m_mat[1][1] = c1[1][1];
	//m_mat[1][2] = c2[1][0]; m_mat[1][3] = c2[1][1];

	//m_mat[2][0] = c3[0][0]; m_mat[2][1] = c3[0][1];
	//m_mat[2][2] = c4[0][0]; m_mat[2][3] = c4[0][1];

	//m_mat[3][0] = c3[1][0]; m_mat[3][1] = c3[1][1];
	//m_mat[3][2] = c4[1][0]; m_mat[3][3] = c4[1][1];

	//return *this;
}

std::ostream& operator<<(std::ostream& flux, const Mat4& mat) {
	mat.afficher(flux);
	return flux;
}

void Mat4::afficher(std::ostream& flux) const {
	//flux << std::fixed << std::setprecision(2); // Fixer l'affichage des floats avec 2 chiffres après la virgule
	flux << "[[" << m_mat[0][0] << ", " << m_mat[0][1] << ", " << m_mat[0][2] << ", " << m_mat[0][3] << "], "
		<< "[" << m_mat[1][0] << ", " << m_mat[1][1] << ", " << m_mat[1][2] << ", " << m_mat[1][3] << "], "
		<< "[" << m_mat[2][0] << ", " << m_mat[2][1] << ", " << m_mat[2][2] << ", " << m_mat[2][3] << "], "
		<< "[" << m_mat[3][0] << ", " << m_mat[3][1] << ", " << m_mat[3][2] << ", " << m_mat[3][3] << "]]";
	//flux << std::defaultfloat; // Restaurer le formatage par défaut après l'affichage
}

Mat4& Mat4::transpose() {
	std::swap(m_mat[0][1], m_mat[1][0]);
	std::swap(m_mat[0][2], m_mat[2][0]);
	std::swap(m_mat[0][3], m_mat[3][0]);
	std::swap(m_mat[1][2], m_mat[2][1]);
	std::swap(m_mat[1][3], m_mat[3][1]);
	std::swap(m_mat[2][3], m_mat[3][2]);
	return *this;
}

Mat4 Mat4::transposed() const {
	Mat4 temp(*this);
	temp.transpose();
	return temp;
}

double Mat4::det() {
	double a = m_mat[2][2] * m_mat[3][3] - m_mat[2][3] * m_mat[3][2];
	double b = m_mat[2][1] * m_mat[3][3] - m_mat[2][3] * m_mat[3][1];
	double c = m_mat[2][1] * m_mat[3][2] - m_mat[2][2] * m_mat[3][1];
	double d = m_mat[1][1] * a - m_mat[1][2] * b + m_mat[1][3] * c;

	double e = m_mat[2][0] * m_mat[3][3] - m_mat[2][3] * m_mat[3][0];
	double f = m_mat[2][0] * m_mat[3][2] - m_mat[2][2] * m_mat[3][0];
	double g = m_mat[1][0] * a - m_mat[1][2] * e + m_mat[1][3] * f;

	double h = m_mat[2][0] * m_mat[3][1] - m_mat[2][1] * m_mat[3][0];
	double i = m_mat[1][0] * b - m_mat[1][1] * e + m_mat[1][3] * h;

	double j = m_mat[1][0] * c - m_mat[1][1] * f + m_mat[1][2] * h;

	return m_mat[0][0] * d - m_mat[0][1] * g + m_mat[0][2] * i - m_mat[0][3] * j;
}

Mat4& Mat4::invert() {
	double det = this->det();
	if (Utils::FE(det, 0.0)){
		throw std::runtime_error("La matrice n'est pas inversible.");
	}
	double invDet = 1.0;
	invDet = 1.0 / det;

	// Pré-calcul des termes communs pour les mineurs
	double minor0 = m_mat[2][2] * m_mat[3][3] - m_mat[2][3] * m_mat[3][2];
	double minor1 = m_mat[2][1] * m_mat[3][3] - m_mat[2][3] * m_mat[3][1];
	double minor2 = m_mat[2][1] * m_mat[3][2] - m_mat[2][2] * m_mat[3][1];
	double minor3 = m_mat[2][0] * m_mat[3][3] - m_mat[2][3] * m_mat[3][0];
	double minor4 = m_mat[2][0] * m_mat[3][2] - m_mat[2][2] * m_mat[3][0];
	double minor5 = m_mat[2][0] * m_mat[3][1] - m_mat[2][1] * m_mat[3][0];

	double minor6 = m_mat[1][2] * m_mat[3][3] - m_mat[1][3] * m_mat[3][2];
	double minor7 = m_mat[1][1] * m_mat[3][3] - m_mat[1][3] * m_mat[3][1];
	double minor8 = m_mat[1][1] * m_mat[3][2] - m_mat[1][2] * m_mat[3][1];
	double minor9 = m_mat[1][0] * m_mat[3][3] - m_mat[1][3] * m_mat[3][0];
	double minor10 = m_mat[1][0] * m_mat[3][2] - m_mat[1][2] * m_mat[3][0];
	double minor11 = m_mat[1][0] * m_mat[3][1] - m_mat[1][1] * m_mat[3][0];

	double minor12 = m_mat[1][2] * m_mat[2][3] - m_mat[1][3] * m_mat[2][2];
	double minor13 = m_mat[1][1] * m_mat[2][3] - m_mat[1][3] * m_mat[2][1];
	double minor14 = m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1];
	double minor15 = m_mat[1][0] * m_mat[2][3] - m_mat[1][3] * m_mat[2][0];
	double minor16 = m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0];
	double minor17 = m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0];

	// Calcul des cofacteurs
	double a00 =  (m_mat[1][1] * minor0 - m_mat[1][2] * minor1 + m_mat[1][3] * minor2) * invDet;
	double a01 = -(m_mat[1][0] * minor0 - m_mat[1][2] * minor3 + m_mat[1][3] * minor4) * invDet;
	double a02 =  (m_mat[1][0] * minor1 - m_mat[1][1] * minor3 + m_mat[1][3] * minor5) * invDet;
	double a03 = -(m_mat[1][0] * minor2 - m_mat[1][1] * minor4 + m_mat[1][2] * minor5) * invDet;

	double a10 = -(m_mat[0][1] * minor0 - m_mat[0][2] * minor1 + m_mat[0][3] * minor2) * invDet;
	double a11 =  (m_mat[0][0] * minor0 - m_mat[0][2] * minor3 + m_mat[0][3] * minor4) * invDet;
	double a12 = -(m_mat[0][0] * minor1 - m_mat[0][1] * minor3 + m_mat[0][3] * minor5) * invDet;
	double a13 =  (m_mat[0][0] * minor2 - m_mat[0][1] * minor4 + m_mat[0][2] * minor5) * invDet;

	double a20 =  (m_mat[0][1] * minor6 - m_mat[0][2] * minor7 + m_mat[0][3] * minor8) * invDet;
	double a21 = -(m_mat[0][0] * minor6 - m_mat[0][2] * minor9 + m_mat[0][3] * minor10) * invDet;
	double a22 =  (m_mat[0][0] * minor7 - m_mat[0][1] * minor9 + m_mat[0][3] * minor11) * invDet;
	double a23 = -(m_mat[0][0] * minor8 - m_mat[0][1] * minor10 + m_mat[0][2] * minor11) * invDet;

	double a30 = -(m_mat[0][1] * minor12 - m_mat[0][2] * minor13 + m_mat[0][3] * minor14) * invDet;
	double a31 =  (m_mat[0][0] * minor12 - m_mat[0][2] * minor15 + m_mat[0][3] * minor16) * invDet;
	double a32 = -(m_mat[0][0] * minor13 - m_mat[0][1] * minor15 + m_mat[0][3] * minor17) * invDet;
	double a33 =  (m_mat[0][0] * minor14 - m_mat[0][1] * minor16 + m_mat[0][2] * minor17) * invDet;

	// Mise à jour de la matrice
	m_mat[0][0] = a00; m_mat[0][1] = a10; m_mat[0][2] = a20; m_mat[0][3] = a30;
	m_mat[1][0] = a01; m_mat[1][1] = a11; m_mat[1][2] = a21; m_mat[1][3] = a31;
	m_mat[2][0] = a02; m_mat[2][1] = a12; m_mat[2][2] = a22; m_mat[2][3] = a32;
	m_mat[3][0] = a03; m_mat[3][1] = a13; m_mat[3][2] = a23; m_mat[3][3] = a33;
	return *this;
}

Mat4 Mat4::inverted() const {
	Mat4 copy(*this);
	copy.invert();
	return copy;
}

Mat4 Mat4::TranslateMatrix(double x, double y, double z) {
	Mat4 temp;
	temp[0][3] = x;
	temp[1][3] = y;
	temp[2][3] = z;
	return temp;
}

Mat4& Mat4::Translate(double x, double y, double z) {
	Mat4 temp = TranslateMatrix(x, y, z);
	*this *= temp;
	return *this;
}

Mat4 Mat4::TranslateMatrix(Point p) {
	Mat4 temp;
	temp[0][3] = p.getX();
	temp[1][3] = p.getY();
	temp[2][3] = p.getZ();
	return temp;
}

Mat4& Mat4::Translate(Point p) {
	Mat4 temp = TranslateMatrix(p);
	*this *= temp;
	return *this;
}

Mat4 Mat4::TranslateMatrix(Vector v) {
	Mat4 temp;
	temp[0][3] = v.getX();
	temp[1][3] = v.getY();
	temp[2][3] = v.getZ();
	return temp;
}

Mat4& Mat4::Translate(Vector v) {
	Mat4 temp = TranslateMatrix(v);
	*this *= temp;
	return *this;
}

Mat4 Mat4::ScaleMatrix(double x, double y, double z) {
	Mat4 temp;
	temp[0][0] = x;
	temp[1][1] = y;
	temp[2][2] = z;
	return temp;
}

Mat4& Mat4::Scale(double x, double y, double z) {
	Mat4 temp = ScaleMatrix(x, y, z);
	*this *= temp;
	return *this;
}

Mat4 Mat4::ScaleMatrix(Point p) {
	Mat4 temp;
	temp[0][0] = p.getX();
	temp[1][1] = p.getY();
	temp[2][2] = p.getZ();
	return temp;
}

Mat4& Mat4::Scale(Point p) {
	Mat4 temp = ScaleMatrix(p);
	*this *= temp;
	return *this;
}

Mat4 Mat4::ScaleMatrix(Vector v) {
	Mat4 temp;
	temp[0][0] = v.getX();
	temp[1][1] = v.getY();
	temp[2][2] = v.getZ();
	return temp;
}

Mat4& Mat4::Scale(Vector v) {
	Mat4 temp = ScaleMatrix(v);
	*this *= temp;
	return *this;
}

Mat4 Mat4::RotateMatrix(double x, double y, double z) {
	// Ces rotations sont par rapport au repere globale qui rest inchangé par les rotations!!
	// on tourne dabord au tour de X, puis de Y puis de Z !!
	Mat4 tempX = Mat4::RotateXMatrix(x);
	Mat4 tempY = Mat4::RotateYMatrix(y);
	Mat4 tempZ = Mat4::RotateZMatrix(z);
	return tempZ * tempY * tempX;
}

Mat4& Mat4::Rotate(double x, double y, double z) {
	Mat4 temp = RotateMatrix(x, y, z);
	*this *= temp;
	return *this;
}

Mat4 Mat4::RotateXMatrix(double x) {
	Mat4 temp;
	temp[1][1] = cos(x);
	temp[1][2] = -sin(x);
	temp[2][1] = sin(x);
	temp[2][2] = cos(x);
	return temp;
}

Mat4& Mat4::RotateX(double x) {
	Mat4 temp = RotateXMatrix(x);
	*this *= temp;
	return *this;
}

Mat4 Mat4::RotateYMatrix(double y) {
	Mat4 temp;
	temp[0][0] = cos(y);
	temp[0][2] = sin(y);
	temp[2][0] = -sin(y);
	temp[2][2] = cos(y);
	return temp;
}

Mat4& Mat4::RotateY(double y) {
	Mat4 temp = RotateYMatrix(y);
	*this *= temp;
	return *this;
}

Mat4 Mat4::RotateZMatrix(double z) {
	Mat4 temp;
	temp[0][0] = cos(z);
	temp[0][1] = -sin(z);
	temp[1][0] = sin(z);
	temp[1][1] = cos(z);
	return temp;
}

Mat4& Mat4::RotateZ(double z) {
	Mat4 temp = RotateZMatrix(z);
	*this *= temp;
	return *this;
}

Mat4 Mat4::ShearMatrix(double xy, double xz, double yx, double yz, double zx, double zy) {
	Mat4 temp;
	temp[0][1] = xy;
	temp[0][2] = xz;
	temp[1][0] = yx;
	temp[1][2] = yz;
	temp[2][0] = zx;
	temp[2][1] = zy;
	return temp;
}

Mat4& Mat4::Shear(double xy, double xz, double yx, double yz, double zx, double zy) {
	Mat4 temp = ShearMatrix(xy, xz, yx, yz, zx, zy);
	*this *= temp;
	return *this;
}


// Non-member functions
bool operator!=(const Mat4& mat_a, const Mat4& mat_b) {
	return !(mat_a == mat_b);
}

Mat4 operator+(Mat4 const& a, Mat4 const& b) {
	Mat4 copy(a);
	copy += b;
	return copy;
}

Mat4 operator-(Mat4 const& a, Mat4 const& b) {
	Mat4 copy(a);
	copy -= b;
	return copy;
}

Mat4 operator*(Mat4 const& a, Mat4 const& b) {
	Mat4 copy(a);
	copy *= b;
	return copy;
}