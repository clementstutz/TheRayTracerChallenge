#pragma once
#include <ostream>
#include "Point.h"
#include "Vector.h"

class Mat4
{
private:
	double m_mat[4][4];

	void afficher(std::ostream& flux) const;

public:
	// Constructors
	Mat4(double m00 = 1.0, double m01 = 0.0, double m02 = 0.0, double m03 = 0.0,
		 double m10 = 0.0, double m11 = 1.0, double m12 = 0.0, double m13 = 0.0,
		 double m20 = 0.0, double m21 = 0.0, double m22 = 1.0, double m23 = 0.0,
		 double m30 = 0.0, double m31 = 0.0, double m32 = 0.0, double m33 = 1.0);
	Mat4(Mat4 const& other);
	Mat4(Mat4&& other) noexcept;


	// Destructor
	~Mat4() = default;


	// Accessors
	double(&operator[](int row))[4];				//setter
	const double(&operator[](int row) const)[4];	//getter


	// Member functions
	bool operator==(Mat4 const& other) const;

	Mat4& operator=(Mat4 const& other);

	Mat4& operator=(Mat4&& other) noexcept;

	Mat4& operator+=(Mat4 const& other);

	Mat4& operator-=(Mat4 const& other);

	template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
	Mat4& operator*=(T const& scalar) {
		double f_scalar = static_cast<double>(scalar);
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

	friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);

	Mat4& transpose();

	Mat4 transposed() const;

	double det();

	Mat4& invert();

	Mat4 inverted() const;

	static Mat4 TranslateMatrix(double x, double y, double z);
	Mat4& Translate(double x, double y, double z);

	static Mat4 TranslateMatrix(Point p);
	Mat4& Translate(Point p);

	static Mat4 TranslateMatrix(Vector v);
	Mat4& Translate(Vector v);

	static Mat4 ScaleMatrix(double x, double y, double z);
	Mat4& Scale(double x, double y, double z);

	static Mat4  ScaleMatrix(Point p1);
	Mat4& Scale(Point p1);

	static Mat4  ScaleMatrix(Vector v1);
	Mat4& Scale(Vector v1);

	static Mat4  RotateMatrix(double x, double y, double z);
	Mat4& Rotate(double x, double y, double z);

	static Mat4 RotateXMatrix(double x);
	Mat4& RotateX(double x);

	static Mat4 RotateYMatrix(double y);
	Mat4& RotateY(double y);

	static Mat4 RotateZMatrix(double z);
	Mat4& RotateZ(double z);

	static Mat4 ShearMatrix(double xy, double xz, double yx, double yz, double zx, double zy);
	Mat4& Shear(double xy, double xz, double yx, double yz, double zx, double zy);
};

bool operator!=(const Mat4& mat_a, const Mat4& mat_b);
Mat4 operator+(Mat4 const& a, Mat4 const& b);
Mat4 operator-(Mat4 const& a, Mat4 const& b);
Mat4 operator*(Mat4 const& a, Mat4 const& b);
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Mat4 operator*(Mat4 const& a, T const& scalar) {
	Mat4 copy(a);
	copy.Mat4::operator*=(scalar);
	return copy;
}
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
Mat4 operator*(T const& scalar, Mat4 const& a) {
	Mat4 copy(a);
	copy.Mat4::operator*=(scalar);
	return copy;
}
