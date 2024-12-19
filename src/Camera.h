#pragma once
#include "Mat4.h"
#include "Utils.h"

class Camera
{
private:
    int m_hSize;
    int m_vSize;
    double m_fov;
    Mat4 m_transform;
    double m_pixelSize;
    double m_halfWidth;
    double m_halfHeight;

    void CalculatePixelSize();

public:
    // Constructors
    Camera(int hSize = 160, int vSize = 120, double fieldOfView = Utils::GetPI() / 2.0);


    // Destructor
    ~Camera() = default;


    // Accessors
    const int GetHSize() const;
    const int GetVSize() const;
    const double GetFov() const;
    const Mat4 GetTransform() const;
    const double GetPixelSize() const;
    const double GetHalfWidth() const;
    const double GetHalfHeight() const;


    // Member functions
    Mat4 ViewTransform(Point from, Point to, Vector up);
};
