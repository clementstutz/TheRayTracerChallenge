#include "Scene.h"
#include "Computations.h"
#include "Canvas.h"
#include "Camera.h"
//#include "Sphere.h"

Scene* Scene::current = nullptr;

// Constructors
Scene::Scene() {
    if (Scene::current == nullptr) {
        Scene::current = this;
    }
    m_lights = std::vector<Light*>();
    m_rayObjects = std::vector<RayObject*>();
    //root = new Group();
    Clear();
}

Scene::Scene(std::vector<Light*> lights, std::vector<RayObject*> rayObjects) : m_lights(lights), m_rayObjects(rayObjects) {}

Scene::Scene(Scene const& other) {}

Scene::Scene(Scene&& other) noexcept {}


// Destructor
Scene::~Scene() {
    if (Scene::current == this) {
        Scene::current = nullptr; // Réinitialise le pointeur si c'est l'instance active
    }
}


//Accessors
std::vector<Light*> Scene::GetLights() {return m_lights;}

std::vector<RayObject*> Scene::GetRayObjects() {return m_rayObjects;}

Scene* Scene::GetCurrentScene() { return Scene::current; }

void Scene::ResetCurrentScene() {
    if (Scene::current) {
        delete Scene::current; // Détruit l'instance existante
        Scene::current = nullptr;
    }
}

// Operators
std::ostream& operator<<(std::ostream& flux, Scene const& scene) {
    scene.afficher(flux);
    return flux;
}


// Member-functions
void Scene::afficher(std::ostream& flux) const {
    flux << "Scene -> (a implementer...)";
}

//void Scene::DefaultScene() {
//    Clear();
//
//    Light light(Point(-10, 10, -10), Color::white);
//
//    Sphere s1;
//    s1.SetMaterial(Material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2));
//    Sphere s2;
//    s2.SetMatrix(Mat4::ScaleMatrix(0.5, 0.5, 0.5));
//}

void Scene::ClearLights() {
    if (!m_lights.empty()) {
        m_lights.clear();
    }
}

void Scene::ClearRayObjects() {
    if (!m_rayObjects.empty()) {
        m_rayObjects.clear();
    }
}

void Scene::Clear() {
    Scene::ClearLights();
    Scene::ClearRayObjects();
}

void Scene::RemoveLight(Light& light) {
    // Utilise std::remove pour déplacer les pointeurs non égaux à &light vers le début
    auto it = std::remove(m_lights.begin(), m_lights.end(), &light);

    // Supprime les éléments "supprimés" de la fin du vecteur
    m_lights.erase(it, m_lights.end());
}

void Scene::RemoveRayObject(RayObject& rayObject) {
    // Utilise std::remove pour déplacer les pointeurs non égaux à &light vers le début
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

std::vector<Intersection> Scene::Intersections(Ray ray) {
    std::vector<Intersection> intersections;
    for (RayObject* rObj : m_rayObjects) {
        if (rObj != nullptr) {  // Vérifie que le pointeur n'est pas nul
            //std::cout << rObj->GetMatrix() << std::endl;
            std::vector<Intersection> tempList = rObj->Intersect(ray);
            /*for (int i = 0; i < tempList.size(); i++) {
                std::cout << "tempList[" << i << "] =" << tempList[i] << std::endl;
            }*/
            intersections.insert(intersections.end(), tempList.begin(), tempList.end()); //
        }
    }
    return Intersection::SortIntersections(intersections);  // WARNING : Surement à supprimer car doublon avec Hit().
}

Intersection Scene::Hit(std::vector<Intersection> intersections) {  // WARNING : a déplacer dans Intersection ?
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

bool Scene::IsShadowed(Point point, Light light) {
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

Color Scene::ShadeHit(Computations c, int remaining) {
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

Color Scene::ColorAt(Ray ray, int remaining) {
    //std::cout << "ray = " << ray << std::endl;
    std::vector<Intersection> hits = Intersections(ray);
    /*for (int i = 0; i < hits.size(); i++) {
        std::cout << "hits[" << i << "] = " << hits[i] << std::endl;
    }*/
    if (hits.size() == 0)
        return Color::black;
    Intersection hit = Hit(hits);
    //std::cout << "hit : " << hit << std::endl;
    Computations c = Computations::Prepare(hit, ray, &hits);
    //std::cout << "c : " << std::endl;
    //std::cout << c.GetLength() << std::endl;
    ////std::cout << c.GetRayObject() << std::endl;
    //std::cout << c.GetPoint() << std::endl;
    //std::cout << c.GetEye() << std::endl;
    //std::cout << c.GetNormal() << std::endl;
    //std::cout << c.GetInside() << std::endl;
    //std::cout << c.GetOverPoint() << std::endl;
    //std::cout << c.GetUnderPoint() << std::endl;
    //std::cout << c.GetReflectVector() << std::endl;
    //std::cout << c.GetN1() << std::endl;
    //std::cout << c.GetN2() << std::endl;
    Color finalColor = ShadeHit(c, remaining);
    return finalColor;
}

Ray Scene::RayForPixel(Camera camera, int x, int y) {
    float xOffset = (x + 0.5f) * camera.GetPixelSize();
    float yOffset = (y + 0.5f) * camera.GetPixelSize();

    float worldX = camera.GetHalfWidth() - xOffset;
    float worldY = camera.GetHalfHeight() - yOffset;

    Point pixel = camera.GetTransform().inverted() * Point(worldX, worldY, -1.0);
    Point origin = camera.GetTransform().inverted() * Point(0, 0, 0);
    Vector direction = (pixel - origin).Normalize();
    return Ray(origin, direction);
}

Canvas Scene::Render(Camera camera, int remaining) {
    Canvas canvas(camera.GetHSize(), camera.GetVSize());
    
    if (m_lights.size() == 0) {
        std::cout << "No lights in scene, this will always produce a black image." << std::endl;
        return canvas;
    }

    //canvas.fillCanvas(Color::black); // WARNING : pas sur qu'il y ait besoit de faire ça...

    //Precalculate the bounds
    //PreCalculateBounds();

    for (int y = 0; y < camera.GetVSize(); y++) {
        for (int x = 0; x < camera.GetHSize(); x++) {
            Ray temp = RayForPixel(camera, x, y);
            //std::cout << "ray = " << temp << std::endl;
            /*for (auto& rObj : m_rayObjects) {
                std::cout << *rObj << std::endl;
            }*/
            Color pixelColor = ColorAt(temp, remaining);
            //std::cout << "pixelColor = " << pixelColor << std::endl;
            canvas.setPixel(x, y, pixelColor);
            // affiche le pourcentage de progression de la génération de l'image
            //Console.WriteLine(((float)(x + y * camera.hSize) / (float)(camera.vSize * camera.hSize) * 100).ToString() + "%");
        }
        // affiche le pourcentage de progression de la génération de l'image
        std::cout << "y progression = " << (static_cast<float>(y + 1) / static_cast<float>(camera.GetVSize()) * 100) << "%" << std::endl;
    }
    std::cout << "Rendering done !" << std::endl;
    return canvas;
}

Color Scene::ReflectedColor(Computations c, int remaining) {
    if (remaining == 0 || Utils::FE(c.GetRayObject().GetMaterial().GetReflectivity(), 0.0)) {
        return Color::black;
    }

    Ray reflectionRay(c.GetOverPoint(), c.GetReflectVector());
    return ColorAt(reflectionRay, remaining - 1) * c.GetRayObject().GetMaterial().GetReflectivity();
}

Color Scene::RefractedColor(Computations c, int remaining) {
    // Check the material of the hit object and if the transparency is 0, return black.
    // Return calculated refracted value if it is transparent.

    if (Utils::FE(c.GetRayObject().GetMaterial().GetTransparency(), 0.0) || remaining == 0) {
        return Color::black;
    }

    //Check for infinit internal reflection.
    float nRatio = c.GetN1() / c.GetN2();
    float cosI = c.GetEye().Dot(c.GetNormal());
    float sin2T = nRatio * nRatio * (1.0 - (cosI * cosI));
    if (sin2T > 1.0) {
        return Color::black;
    }

    float cosT = std::sqrt(1.0 - sin2T);

    Vector direction = c.GetNormal() * (nRatio * cosI - cosT) - c.GetEye() * nRatio;

    Ray refractRay(c.GetUnderPoint(), direction);

    Color refractedColor = ColorAt(refractRay, remaining - 1) * c.GetRayObject().GetMaterial().GetTransparency();

    //Replace later with code for refraction calculations
    return refractedColor;
}

float Scene::Schlick(Computations c)   // WARNING :Deal with fresnel effect but don't realy know what it does. (cf. Chapter11Test Test 16)
{
    float cosI = c.GetEye().Dot(c.GetNormal());
    if (c.GetN1() > c.GetN2())
    {
        float nRatio = c.GetN1() / c.GetN2();
        float sin2T = nRatio * nRatio * (1.0 - (cosI * cosI));
        if (sin2T > 1.0)
            return 1.0;

        float cosT = std::sqrt(1.0 - sin2T);

        cosI = cosT;
    }
    float r0 = std::pow((c.GetN1() - c.GetN2()) / (c.GetN1() + c.GetN2()), 2);
    return r0 + (1.0 - r0) * std::pow((1.0 - cosI), 5);
}