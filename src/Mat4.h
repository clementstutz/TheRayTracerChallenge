#pragma once
#include <ostream>
#include "Utils.h"

class Mat4
{
private:
	float m_mat[4][4];

	void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Mat4(float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f,
		 float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f,
		 float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f,
		 float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f);
	Mat4(Mat4 const& other);

	// Accesseurs
	float(&operator[](int row))[4];			//setter
	const float(&operator[](int row) const)[4];	//getter

	// Opérateurs
	bool operator==(Mat4 const& other) const;

	Mat4& operator=(Mat4 const& other);

	template <typename T>
	Mat4& operator*=(T const& scalar) {
		float f_scalar = static_cast<float>(scalar);
		m_mat[0][0] *= f_scalar;
		m_mat[0][1] *= f_scalar;
		m_mat[0][2] *= f_scalar;
		m_mat[0][3] *= f_scalar;

		m_mat[1][0] *= f_scalar;
		m_mat[1][1] *= f_scalar;
		m_mat[1][2] *= f_scalar;
		m_mat[1][3] *= f_scalar;

		m_mat[2][0] *= f_scalar;
		m_mat[2][1] *= f_scalar;
		m_mat[2][2] *= f_scalar;
		m_mat[2][3] *= f_scalar;

		m_mat[3][0] *= f_scalar;
		m_mat[3][1] *= f_scalar;
		m_mat[3][2] *= f_scalar;
		m_mat[3][3] *= f_scalar;
		return *this;
	};

	Mat4& operator*=(Mat4 const& other);

	//Mat4 operator*(const Mat4& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);

	// fonctions-membres
	void transpose();

	Mat4 transposed() const;

	float det();

	void invert();

	Mat4 inverted() const;
};

bool operator!=(const Mat4& mat_a, const Mat4& mat_b);

template <typename T>
Mat4 operator*(Mat4 const& a, T const& scalar) {
	Mat4 copy(a);
	copy.Mat4::operator*=(scalar);
	return copy;
}

Mat4 operator*(Mat4 const& a, Mat4 const& b);