#include <array>
//#include <algorithm>  // Pour std::swap

#include "Bounds.h"
#include "Tuple.h"
#include "Point.h"
#include "Utils.h"

// Constructors
Bounds::Bounds() {}

Bounds Bounds::GetAABB(const Mat4& transformMatrix)
{
	std::vector<std::shared_ptr<Point>> corners = GetTransformedCorners(transformMatrix);
	return GetAABB(corners);
}

Bounds Bounds::GetAABB(std::vector<std::shared_ptr<Point>> points)
{
    Bounds bounds;

    if (points.size() > 0)
    {
        bounds.m_min = *points[0];
        bounds.m_max = *points[0];

        for (int i = 1; i < points.size(); i++)
        {
            if (points[i]->getX() < bounds.m_min.getX()) {
                bounds.m_min.set(points[i]->getX(), bounds.m_min.getY(), bounds.m_min.getZ());
            }
            if (points[i]->getY() < bounds.m_min.getY()) {
                bounds.m_min.set(bounds.m_min.getX(), points[i]->getY(), bounds.m_min.getZ());
            }
            if (points[i]->getZ() < bounds.m_min.getZ()) {
                bounds.m_min.set(bounds.m_min.getX(), bounds.m_min.getY(), points[i]->getZ());
            }
            if (points[i]->getX() > bounds.m_max.getX()) {
                bounds.m_max.set(points[i]->getX(), bounds.m_max.getY(), bounds.m_max.getZ());
            }
            if (points[i]->getY() > bounds.m_max.getY()) {
                bounds.m_max.set(bounds.m_max.getX(), points[i]->getY(), bounds.m_max.getZ());
            }
            if (points[i]->getZ() > bounds.m_max.getZ()) {
                bounds.m_max.set(bounds.m_max.getX(), bounds.m_max.getY(), points[i]->getZ());
            }
        }
    }
    return bounds;
}

std::vector<std::shared_ptr<Point>> Bounds::GetTransformedCorners(const Mat4& mat)
{
    std::vector<std::shared_ptr<Point>> corners = GetCorners();

    for (int i = 0; i < corners.size(); i++)
    {
        corners[i] = std::make_shared<Point>(mat * *corners[i]);
    }
    return corners;
}

std::vector<std::shared_ptr<Point>> Bounds::GetCorners()
{
    std::vector<std::shared_ptr<Point>> corners;

    /*
    *Looking down, winding order CW
    *  p2---p3
    *  |    |
    *  p1---p0
    *
    */

    //Bottom of cube
    corners.emplace_back(std::make_shared<Point>(m_max.getX(), m_min.getY(), m_min.getZ()));
    corners.emplace_back(std::make_shared<Point>(m_min.getX(), m_min.getY(), m_min.getZ()));
    corners.emplace_back(std::make_shared<Point>(m_min.getX(), m_min.getY(), m_max.getZ()));
    corners.emplace_back(std::make_shared<Point>(m_max.getX(), m_min.getY(), m_max.getZ()));

    /*
    *Looking down, winding order CW
    *  p6---p7
    *  |    |
    *  p5---p4
    *
    */

    //Top of cube
    corners.emplace_back(std::make_shared<Point>(m_max.getX(), m_max.getY(), m_min.getZ()));
    corners.emplace_back(std::make_shared<Point>(m_min.getX(), m_max.getY(), m_min.getZ()));
    corners.emplace_back(std::make_shared<Point>(m_min.getX(), m_max.getY(), m_max.getZ()));
    corners.emplace_back(std::make_shared<Point>(m_max.getX(), m_max.getY(), m_max.getZ()));

    return corners;
}

bool Bounds::Intersect(const Ray& ray)
{
    std::array<double, 2> xt = CheckAxis(Axis::X, ray.getOrigin().getX(), ray.getDirection().getX());
    std::array<double, 2> yt = CheckAxis(Axis::Y, ray.getOrigin().getY(), ray.getDirection().getY());
    std::array<double, 2> zt = CheckAxis(Axis::Z, ray.getOrigin().getZ(), ray.getDirection().getZ());

    double tMin = std::max(std::max(xt[0], yt[0]), zt[0]);
    double tMax = std::min(std::min(xt[1], yt[1]), zt[1]);

    //Box not hit
    if (tMin > tMax)
    {
        return false;
    }

    //Box hit
    return true;
}

std::array<double, 2> Bounds::CheckAxis(uint8_t axis, double origin, double direction)
{
    std::array<double, 2> t;

    double tMinNumerator{ 0 };
    double tMaxNumerator{ 0 };

    switch (axis)
    {
    case Axis::X:
        tMinNumerator = (m_min.getX() - origin);
        tMaxNumerator = (m_max.getX() - origin);
        break;
    case Axis::Y:
        tMinNumerator = (m_min.getY() - origin);
        tMaxNumerator = (m_max.getY() - origin);
        break;
    case Axis::Z:
        tMinNumerator = (m_min.getZ() - origin);
        tMaxNumerator = (m_max.getZ() - origin);
        break;
    }

    //Infinities might pop here due to division by zero
    if (std::abs(direction) >= Utils::GetEpsilon())
    {
        t[0] = tMinNumerator / direction;
        t[1] = tMaxNumerator / direction;
    }
    else
    {
        t[0] = std::numeric_limits<double>::infinity();
        t[1] = std::numeric_limits<double>::infinity();
    }

    if (t[0] > t[1]) { std::swap(t[0], t[1]); }

    return t;
}
