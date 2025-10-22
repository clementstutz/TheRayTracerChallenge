#include "Group.h"

// Constructors
Group::Group() : Shape() {}


// Member functions
Group& Group::operator=(Group const& other)
{
    if (this != &other) {
        Shape::operator=(other); // Appelle l'operateur d'affectation par copie de la classe mere
        m_children = other.m_children;
    }
    return *this;
}

Group& Group::operator=(Group&& other) noexcept
{
    if (this != &other) { // Verification d'auto-affectation
        Shape::operator=(std::move(other)); // Appelle l'operateur d'affectation par deplacement de la classe mere
        m_children = std::move(other.m_children);
        // Reset source object
        other.m_children = std::vector<Shape*>{ nullptr };
    }
    return *this;
}

bool Group::operator==(Group const& other) const
{
    return Shape::operator==(other) &&
		m_children == other.m_children;
}

std::ostream& operator<<(std::ostream& flux, Group const& group)
{
    group.afficher(flux);
    return flux;
}

void Group::afficher(std::ostream& flux) const
{
    flux << "Group (id: " << m_id << ", Position: " << GetPosition() << ")";
}

void Group::AddChildren(Shape& shape)
{
    if (shape.GetParent() == nullptr)
    {
        m_children.push_back(&shape);
        shape.SetParent(this);
    }
    else if (shape.GetParent() != this)
    {
        std::cerr << "Error: You try to make an object a child's of a Group, but the object is already a child of another Group." << std::endl;
    }
}

const std::vector<Shape*> Group::GetChildrens() const { return m_children; }

std::vector<Intersection> Group::Intersect(Ray const& ray)
{
    //Bounds groupBounds = GetBounds(); //This will be a bound of 0 to 0

    std::vector<Intersection> intersectionPoints;
    intersectionPoints.reserve(GetChildrens().size() * 2);

    //if (groupBounds.Intersect(ray))
    //{
        //Iterate through all child objects and aggregate intersections

        Ray transRay = RayToObjectSpace(ray);

        for(Shape* child : GetChildrens())
        {
            std::vector<Intersection> temp = child->Intersect(transRay);
            intersectionPoints.insert(intersectionPoints.end(), temp.begin(), temp.end());
        }

        //Need to sort resulting intersections...
        return Intersection::SortIntersections(intersectionPoints);
    //}
    //No intersections detected
    //return intersectionPoints;
	//return std::vector<Intersection>();
}

Vector Group::GetNormal(Point const& worldPoint, Intersection const& i) const
{
    return Vector();
}

Vector Group::CalculateLocalNormal(Point const& localPoint, Intersection const& i) const
{
    return Vector();
}


// Non-member functions
bool operator!=(Group const& a, Group const& b) {
    return !(a == b);
}
