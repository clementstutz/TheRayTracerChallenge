#include "Camera.h"

Camera::Camera(int hSize, int vSize, float fieldOfView) : 
    m_hSize(hSize),
    m_vSize(vSize),
    m_fov(fieldOfView),
    m_transform(Mat4()) {
    CalculatePixelSize();
}

int Camera::GetHSize() const {return m_hSize;}

int Camera::GetVSize() const{return m_vSize;}

float Camera::GetFov() const{return m_fov;}

Mat4 Camera::GetTransform() const {return m_transform;}

float Camera::GetPixelSize() const{return m_pixelSize;}

float Camera::GetHalfWidth() const{return m_halfWidth;}

float Camera::GetHalfHeight() const { return m_halfHeight; }

void Camera::CalculatePixelSize() {
    float halfView = std::tan(m_fov / 2.0);
    float aspect = static_cast<float>(m_hSize) / static_cast<float>(m_vSize);

    if (aspect >= 1) {
        m_halfWidth = halfView;
        m_halfHeight = halfView / aspect;
    }
    else {
        m_halfWidth = halfView * aspect;
        m_halfHeight = halfView;
    }
    m_pixelSize = (m_halfWidth * 2.0) / m_hSize;
}

Mat4 Camera::ViewTransform(Point from, Point to, Vector up) {
    up = up.Normalize();
    Vector forward = (to - from).Normalize();
    // NaN check.
    if (std::isnan(forward.getX()))
        std::cout << "Bad Forward Vector in Camera's View Transform." << std::endl;

    Vector left = forward.Cross(up).Normalize();
    if (std::isnan(left.getX()))
        std::cout << "Bad Left Vector in Camera's View Transform." << std::endl;

    Vector true_up = left.Cross(forward).Normalize();
    if (std::isnan(true_up.getX()))
        std::cout << "Bad Up Vector in Camera's View Transform." << std::endl;

    Mat4 orientation(left.getX(), left.getY(), left.getZ(), 0,
        true_up.getX(), true_up.getY(), true_up.getZ(), 0,
        -forward.getX(), -forward.getY(), -forward.getZ(), 0,
        0, 0, 0, 1);
    // Move to the from position.
    m_transform = orientation * Mat4::TranslateMatrix(-from.getX(), -from.getY(), -from.getZ()); // Erreur ? Ne colle pas avec Wikipedia..!
    return m_transform;
}