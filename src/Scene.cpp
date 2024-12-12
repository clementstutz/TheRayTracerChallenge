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
        Scene::current = nullptr; // R�initialise le pointeur si c'est l'instance active
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
        delete Scene::current; // D�truit l'instance existante
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
    // Utilise std::remove pour d�placer les pointeurs non �gaux � &light vers le d�but
    auto it = std::remove(m_lights.begin(), m_lights.end(), &light);

    // Supprime les �l�ments "supprim�s" de la fin du vecteur
    m_lights.erase(it, m_lights.end());
}

void Scene::RemoveRayObject(RayObject const& rayObject) {
    // Utilise std::remove pour d�placer les pointeurs non �gaux � &rayObject vers le d�but
    auto it = std::remove(m_rayObjects.begin(), m_rayObjects.end(), &rayObject);

    // Supprime les �l�ments "supprim�s" de la fin du vecteur
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
        if (rObj != nullptr) {  // V�rifie que le pointeur n'est pas nul
            std::vector<Intersection> tempList = rObj->Intersect(ray);
            intersections.insert(intersections.end(), tempList.begin(), tempList.end()); //
        }
    }
    return Intersection::SortIntersections(intersections);
}

Intersection Scene::Hit(std::vector<Intersection> const& intersections) {  // WARNING : a d�placer dans Intersection ?
    if (intersections.empty()) {
        return Intersection(); // Retourne un objet par d�faut ou un indicateur d'absence
    }

    for (int i = 0; i < intersections.size(); i++) {
        if (intersections[i].getLength() >= 0.0) {
            return intersections[i];
        }
    }
    return Intersection(); // Aucune intersection valide trouv�e
}

Ray Scene::RayForPixel(Camera const& camera, int x, int y) {
    float xOffset = (x + 0.5f) * camera.GetPixelSize();
    float yOffset = (y + 0.5f) * camera.GetPixelSize();

    float worldX = camera.GetHalfWidth() - xOffset;
    float worldY = camera.GetHalfHeight() - yOffset;

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

    //Color surfaceColor;
    //for (int i = 0; i < m_lights.size(); i++) {
    //    //std::cout << "lights["<<i<<"] = " << *m_lights[i] << std::endl;
    //    // Is this light in shadow?
    //    if (c.GetRayObject().CanReceiveShadows()) {
    //        bool isShadow = IsShadowed(c.GetOverPoint(), *m_lights[i]);
    //        //std::cout << "isShadow = " << isShadow << std::endl;
    //        surfaceColor += c.GetRayObject().Lighting(c.GetPoint(), *m_lights[i], c.GetEye(), c.GetNormal(), isShadow);
    //        //std::cout << "surfaceColor = " << surfaceColor << std::endl;
    //    }
    //}

    //Color reflected = ReflectedColor(c, remaining);
    //Color refracted = RefractedColor(c, remaining);

    //if (c.GetRayObject().GetMaterial().GetReflectivity() > 0 && c.GetRayObject().GetMaterial().GetTransparency() > 0) {
    //    float reflectance = Schlick(c);
    //    return surfaceColor + reflected * reflectance + refracted * (1.0 - reflectance);
    //}

    //return surfaceColor + reflected + refracted;

    Color finalColor;
    for (int i = 0; i < m_lights.size(); i++) {
        finalColor += c.GetRayObject().Lighting(c.GetPoint(), *m_lights[i], c.GetEye(), c.GetNormal());
    }
    return finalColor;
}

bool Scene::IsShadowed(Point const& point, Light const& light) {
    Vector temp = light.GetPosition() - point;
    float distance = temp.Magnitude();
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
    float nRatio = c.GetN1() / c.GetN2();
    float cosI = c.GetEye().Dot(c.GetNormal());
    float sin2T = nRatio * nRatio * (1.0f - (cosI * cosI));
    if (sin2T > 1.0f) {
        return Color::black;
    }

    float cosT = std::sqrt(1.0f - sin2T);

    Vector direction = c.GetNormal() * (nRatio * cosI - cosT) - c.GetEye() * nRatio;

    Ray refractRay(c.GetUnderPoint(), direction);

    Color refractedColor = ColorAt(refractRay, remaining - 1) * c.GetRayObject().GetMaterial().GetTransparency();

    //Replace later with code for refraction calculations
    return refractedColor;
}

float Scene::Schlick(Computations const& c)   // WARNING :Deal with fresnel effect but don't realy know what it does. (cf. Chapter11Test Test 16)
{
    float cosI = c.GetEye().Dot(c.GetNormal());
    if (c.GetN1() > c.GetN2())
    {
        float nRatio = c.GetN1() / c.GetN2();
        float sin2T = nRatio * nRatio * (1.0f - (cosI * cosI));
        if (sin2T > 1.0f)
            return 1.0f;

        float cosT = std::sqrt(1.0f - sin2T);

        cosI = cosT;
    }
    float r0 = std::pow((c.GetN1() - c.GetN2()) / (c.GetN1() + c.GetN2()), 2);
    return r0 + (1.0f - r0) * std::pow((1.0f - cosI), 5);
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
        // affiche le pourcentage de progression de la g�n�ration de l'image
        std::cout << "y progression = " << (static_cast<float>(y + 1) / static_cast<float>(camera.GetVSize()) * 100) << "%" << std::endl;
    }
    std::cout << "Rendering done !" << std::endl;
    return canvas;
}
