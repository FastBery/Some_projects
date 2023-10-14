#include "../structs.h"
#include "functions.h"
#include "../otrisovochka.h"
#include "../readf.h"
#include "camera.h"
#include <optional>


// using namespace std;

int main(){
    using u32 = unsigned int;

    u32 const width  = 1920u;
    u32 const height = 1080u;

    float const fwidth  =  width;
    float const fheight = height;

    Camera const camera =
    {
        .position = {0.f, 0.8f, -2.f},
        .at = {0.f, 0.f, 0.f},
        .up = {0.f, 1.f, 0.f},
        .aspectRatio = fwidth / fheight,
        .verticalFOV = 0.55f,
    };

    std::vector<triangle> TrMass = maketrigon("cube.obj");
    TriangleRange range = {&TrMass[0], &TrMass[(TrMass.size())]};

    Tree tr = createTree(range);

    auto const trace = [&TrMass](Ray const &ray)
    {
        vec3 const   skyColor = {0.53f, 0.81f, 0.92f};
        vec3 const lightColor = {1.00f, 0.98f, 0.88f};
        vec3 const lightDir   = normalize({3.f, 3.f, -1.f});

        std::optional<intersection> hit = coordinate_of_intersection(tr, ray);
        if(!hit)
            return dot(ray.direction, lightDir) < 0.999f
                ? skyColor
                : lightColor * 2.f;

        Ray const shadowRay =
        {
            .origin = hit->position,
            .direction = lightDir
        };
        std::optional<intersection> const shadowHit = coordinate_of_intersection(shadowRay, sphere);
        float const NL = std::max(0.f, dot(hit->normal, lightDir));

        vec3 const color = !shadowHit
            ? lightColor * NL
            : vec3{0.f, 0.f, 0.f};

        return (skyColor * 0.3f + color) * hit->albedo;
    };

}