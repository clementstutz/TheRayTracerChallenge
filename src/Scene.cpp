#include "Scene.h"
#include "Computations.h"
#include "Canvas.h"
#include "Camera.h"
#include "Sphere.h"

Scene* Scene::current = nullptr;


// Constructors
Scene::Scene() :
    m_lights(std::vector<Light*>()),
    m_rayObjects(std::vector<RayObject*>()) {
    if (Scene::current == nullptr) {
        Scene::current = this;
    }
    //root = new Group();
}


// Destructor
Scene::~Scene() {
    Scene::Clear();
    if (Scene::current == this) {
        Scene::current = nullptr; // Réinitialise le pointeur si c'est l'instance active
    }
}


//Accessors
Scene* Scene::GetCurrentScene() { return Scene::current; }
std::vector<Light*> Scene::GetLights() { return m_lights; }
std::vector<RayObject*> Scene::GetRayObjects() { return m_rayObjects; }


// Member functions
std::ostream& operator<<(std::ostream& flux, Scene const& scene) {
    scene.afficher(flux);
    return flux;
}

void Scene::afficher(std::ostream& flux) const {
    flux << "Scene -> (a implementer...)";
}

void Scene::DefaultScene() {
    Scene::Clear();

    Light* light = new Light(Point(-10, 10, -10), Color::white);

    Sphere* sphere_1 = new Sphere;
    sphere_1->SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
    Sphere* sphere_2 = new Sphere;
    sphere_2->SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));
}

void Scene::ResetCurrentScene() {
    if (Scene::current) {
        delete Scene::current; // Détruit l'instance existante
        Scene::current = nullptr;
    }
}

void Scene::ClearLights() {
    m_lights.clear();
}

void Scene::ClearRayObjects() {
    m_rayObjects.clear();
}

void Scene::Clear() {
    Scene::ClearLights();
    Scene::ClearRayObjects();
}

void Scene::RemoveLight(Light const& light) {
    // Utilise std::remove pour déplacer les pointeurs non égaux à &light vers le début
    auto it = std::remove(m_lights.begin(), m_lights.end(), &light);

    // Supprime les éléments "supprimés" de la fin du vecteur
    m_lights.erase(it, m_lights.end());
}

void Scene::RemoveRayObject(RayObject const& rayObject) {
    // Utilise std::remove pour déplacer les pointeurs non égaux à &rayObject vers le début
    auto it = std::remove(m_rayObjects.begin(), m_rayObjects.end(), &rayObject);

    // Supprime les éléments "supprimés" de la fin du vecteur
    m_rayObjects.erase(it, m_rayObjects.end());
}

void Scene::AddLight(Light& light) {
    m_lights.push_back(&light);
}

void Scene::AddRayObject(RayObject& rayObject) {
    m_rayObjects.push_back(&rayObject);
}

std::vector<Intersection> Scene::Intersections(Ray const& ray) {
    std::vector<Intersection> intersections;
    for (RayObject* rObj : m_rayObjects) {
        if (rObj != nullptr) {  // Vérifie que le pointeur n'est pas nul
            std::vector<Intersection> tempList = rObj->Intersect(ray);
            intersections.insert(intersections.end(), tempList.begin(), tempList.end()); //
        }
    }
    return Intersection::SortIntersections(intersections);
}

Intersection Scene::Hit(std::vector<Intersection> const& intersections) {  // WARNING : a déplacer dans Intersection ?
    if (intersections.empty()) {
        return Intersection(); // Retourne un objet par défaut ou un indicateur d'absence
    }

    for (int i = 0; i < intersections.size(); i++) {
        if (intersections[i].getLength() >= 0.0) {
            return intersections[i];
        }
    }
    return Intersection(); // Aucune intersection valide trouvée
}

Ray Scene::RayForPixel(Camera const& camera, int x, int y) {
    double xOffset = (x + 0.5) * camera.GetPixelSize();
    double yOffset = (y + 0.5) * camera.GetPixelSize();

    double worldX = camera.GetHalfWidth() - xOffset;
    double worldY = camera.GetHalfHeight() - yOffset;

    Point pixel = camera.GetTransform().inverted() * Point(worldX, worldY, -1.0);
    Point origin = camera.GetTransform().inverted() * Point(0, 0, 0);
    Vector direction = (pixel - origin).Normalize();
    return Ray(origin, direction);
}

Color Scene::ColorAt(Ray const& ray, int remaining) {
    std::vector<Intersection> hits = Intersections(ray);
    if (hits.size() == 0)
        return Color::black;
    Intersection hit = Hit(hits);
    Computations c = Computations::Prepare(hit, ray, &hits);
    Color finalColor = ShadeHit(c, remaining);
    return finalColor;
}

Color Scene::ShadeHit(Computations const& c, int remaining) {
    if (c.GetRayObjectPtr() == nullptr) {
        return Color::black;
    }

    Color surfaceColor;
    for (int i = 0; i < m_lights.size(); i++) {
        // Is this light in shadow?
        if (c.GetRayObject().CanReceiveShadows()) {
            bool isShadow = IsShadowed(c.GetOverPoint(), *m_lights[i]);
            surfaceColor += c.GetRayObject().Lighting(c.GetPoint(), *m_lights[i], c.GetEye(), c.GetNormal(), isShadow);
        }
    }

    //Color reflected = ReflectedColor(c, remaining);
    //Color refracted = RefractedColor(c, remaining);

    //if (c.GetRayObject().GetMaterial().GetReflectivity() > 0 && c.GetRayObject().GetMaterial().GetTransparency() > 0) {
    //    double reflectance = Schlick(c);
    //    return surfaceColor + reflected * reflectance + refracted * (1.0 - reflectance);
    //}

    //return surfaceColor + reflected + refracted;

    //for (int i = 0; i < m_lights.size(); i++) {
    //    surfaceColor += c.GetRayObject().Lighting(c.GetPoint(), *m_lights[i], c.GetEye(), c.GetNormal());
    //}
    return surfaceColor;
}

bool Scene::IsShadowed(Point const& point, Light const& light) {
    Vector temp = light.GetPosition() - point;
    double distance = temp.Magnitude();
    Vector direction = temp.Normalize();

    Ray ray(point, direction);

    std::vector<Intersection> intersections = Intersections(ray);
    Intersection intersection = Hit(intersections);

    // Do we have a hit and is it within the distance to the light?
    if (intersection.getObjPtr() != nullptr && intersection.getObj().CanCastShadows() && intersection.getLength() < distance) {
        return true; // true = shadows on  false = shadows off
    }
    return false;
}

Color Scene::ReflectedColor(Computations const& c, int remaining) {
    if (remaining == 0 || Utils::FE(c.GetRayObject().GetMaterial().GetReflectivity(), 0.0)) {
        return Color::black;
    }

    Ray reflectionRay(c.GetOverPoint(), c.GetReflectVector());
    return ColorAt(reflectionRay, remaining - 1) * c.GetRayObject().GetMaterial().GetReflectivity();
}

Color Scene::RefractedColor(Computations const& c, int remaining) {
    // Check the material of the hit object and if the transparency is 0, return black.
    // Return calculated refracted value if it is transparent.

    if (Utils::FE(c.GetRayObject().GetMaterial().GetTransparency(), 0.0) || remaining == 0) {
        return Color::black;
    }

    //Check for infinit internal reflection.
    double nRatio = c.GetN1() / c.GetN2();
    double cosI = c.GetEye().Dot(c.GetNormal());
    double sin2T = nRatio * nRatio * (1.0 - (cosI * cosI));
    if (sin2T > 1.0) {
        return Color::black;
    }

    double cosT = std::sqrt(1.0 - sin2T);

    Vector direction = c.GetNormal() * (nRatio * cosI - cosT) - c.GetEye() * nRatio;

    Ray refractRay(c.GetUnderPoint(), direction);

    Color refractedColor = ColorAt(refractRay, remaining - 1) * c.GetRayObject().GetMaterial().GetTransparency();

    //Replace later with code for refraction calculations
    return refractedColor;
}

double Scene::Schlick(Computations const& c)   // WARNING :Deal with fresnel effect but don't realy know what it does. (cf. Chapter11Test Test 16)
{
    double cosI = c.GetEye().Dot(c.GetNormal());
    if (c.GetN1() > c.GetN2())
    {
        double nRatio = c.GetN1() / c.GetN2();
        double sin2T = nRatio * nRatio * (1.0 - (cosI * cosI));
        if (sin2T > 1.0)
            return 1.0;

        double cosT = std::sqrt(1.0 - sin2T);

        cosI = cosT;
    }
    double r0 = std::pow((c.GetN1() - c.GetN2()) / (c.GetN1() + c.GetN2()), 2);
    return r0 + (1.0 - r0) * std::pow((1.0 - cosI), 5);
}

Canvas Scene::Render(Camera const& camera, int remaining) {
    Canvas canvas(camera.GetHSize(), camera.GetVSize());
    
    if (m_lights.size() == 0) {
        std::cout << "No lights in scene, this will always produce a black image." << std::endl;
        return canvas;
    }

    //Precalculate the bounds
    //PreCalculateBounds();

    for (int y = 0; y < camera.GetVSize(); y++) { // 1: (int y = 0; y < camera.GetVSize(); y++) -or- 2: (int y = camera.GetVSize()-1; y >=0; y--)
        for (int x = 0; x < camera.GetHSize(); x++) {
            Ray temp = RayForPixel(camera, x, y);
            Color pixelColor = ColorAt(temp, remaining);
            canvas.setPixel(x, y, pixelColor);
        }
        // affiche le pourcentage de progression de la génération de l'image
        std::cout << "y progression = " << ((static_cast<double>(y) + 1.0) / static_cast<double>(camera.GetVSize()) * 100) << "%" << std::endl;
    }
    std::cout << "Rendering done !" << std::endl;
    return canvas;
}
