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

public:
    // Constructors
    Camera(int hSize = 160, int vSize = 120, float fieldOfView = Utils::PI / 2.0);

    // Accessors
    int GetHSize() const;
    int GetVSize() const;
    float GetFov() const;
    Mat4 GetTransform() const;
    float GetPixelSize() const;
    float GetHalfWidth() const;
    float GetHalfHeight() const;

    void CalculatePixelSize();
    Mat4 ViewTransform(Point from, Point to, Vector up);

};

