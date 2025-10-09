#include "Group.h"

// Constructors
Group::Group() : RayObject() {}


// Member functions
std::vector<Intersection> Group::Intersect(Ray const& ray)
{
    //For right now we'll only have groups do the axis-aligned bounding box test,
            //however with the way it has been programmed it should easily extend to every object
            //which may be usedful when we get to triangular meshed in the next chapter?

    //Bounds groupBounds = GetBounds(); //This will be a bound of 0 to 0

    std::vector<Intersection> hits;

    if (groupBounds.Intersect(ray))
    {
        //Iterate through all child objects and aggregate intersections

        Ray transRay = GetMatrix().Inverse() * ray;

        foreach(RayObject obj in GetChildren())
        {
            hits.AddRange(obj.Intersect(transRay));
        }

        //Need to sort resulting intersections...
        return Intersection.SortIntersections(hits);
    }
    //No intersections detected
    return hits;
	return std::vector<Intersection>();
}

