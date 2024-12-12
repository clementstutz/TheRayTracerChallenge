#pragma once
#include "Mat4.h"
#include "Utils.h"

class Camera
{
private:
    int m_hSize;
    int m_vSize;
    float m_fov;
    Mat4 m_transform;
    float m_pixelSize;
    float m_halfWidth;
    float m_halfHeight;

    void CalculatePixelSize();

public:
    // Constructors
    Camera(int hSize = 160, int vSize = 120, float fieldOfView = Utils::GetPI() / 2.0f);


    // Destructor
    ~Camera() = default;


    // Accessors
    const int GetHSize() const;
    const int GetVSize() const;
    const float GetFov() const;
    const Mat4 GetTransform() const;
    const float GetPixelSize() const;
    const float GetHalfWidth() const;
    const float GetHalfHeight() const;


    // Member functions
    Mat4 ViewTransform(Point from, Point to, Vector up);
};
