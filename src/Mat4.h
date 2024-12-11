#pragma once
#include <ostream>
//#include "Utils.h"
#include "Point.h"
#include "Vector.h"

class Mat4
{
private:
	float m_mat[4][4];

	void afficher(std::ostream& flux) const;

public:
	// Constructeurs
	Mat4(float m00 = 1.0, float m01 = 0.0, float m02 = 0.0, float m03 = 0.0,
		 float m10 = 0.0, float m11 = 1.0, float m12 = 0.0, float m13 = 0.0,
		 float m20 = 0.0, float m21 = 0.0, float m22 = 1.0, float m23 = 0.0,
		 float m30 = 0.0, float m31 = 0.0, float m32 = 0.0, float m33 = 1.0);
	Mat4(Mat4 const& other);

	// Accesseurs
	float(&operator[](int row))[4];			//setter
	const float(&operator[](int row) const)[4];	//getter

	// Opérateurs
	bool operator==(Mat4 const& other) const;

	Mat4& operator=(Mat4 const& other);

	Mat4& operator+=(Mat4 const& other);

	Mat4& operator-=(Mat4 const& other);

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

	Mat4& invert();

	Mat4 inverted() const;

	static Mat4 TranslateMatrix(float x, float y, float z);
	Mat4& Translate(float x, float y, float z);

	static Mat4 TranslateMatrix(Point p);
	Mat4& Translate(Point p);

	static Mat4 TranslateMatrix(Vector v);
	Mat4& Translate(Vector v);

	static Mat4 ScaleMatrix(float x, float y, float z);
	Mat4& Scale(float x, float y, float z);

	static Mat4  ScaleMatrix(Point p1);
	Mat4& Scale(Point p1);

	static Mat4  ScaleMatrix(Vector v1);
	Mat4& Scale(Vector v1);

	static Mat4  RotateMatrix(float x, float y, float z);
	Mat4& Rotate(float x, float y, float z);

	static Mat4 RotateXMatrix(float x);
	Mat4& RotateX(float x);

	static Mat4 RotateYMatrix(float y);
	Mat4& RotateY(float y);

	static Mat4 RotateZMatrix(float z);
	Mat4& RotateZ(float z);

	static Mat4 ShearMatrix(float xy, float xz, float yx, float yz, float zx, float zy);
	Mat4& Shear(float xy, float xz, float yx, float yz, float zx, float zy);

};

bool operator!=(const Mat4& mat_a, const Mat4& mat_b);

Mat4 operator+(Mat4 const& a, Mat4 const& b);
Mat4 operator-(Mat4 const& a, Mat4 const& b);

template <typename T>
Mat4 operator*(Mat4 const& a, T const& scalar) {
	Mat4 copy(a);
	copy.Mat4::operator*=(scalar);
	return copy;
}

Mat4 operator*(Mat4 const& a, Mat4 const& b);