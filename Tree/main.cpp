#include "camera.h"

#include "readf2.h"
#include <iostream>
#include "functions.h"
#include <vector>
#include <fstream>

int main()
{
    using u32 = unsigned int;

    u32 const width  = 800u;
    u32 const height = 640u;

    float const fwidth  =  width;
    float const fheight = height;

    

    std::ifstream file("cube.obj");
    std::vector<triangle> trmass = parseOBJ(file);

    TriangleRange range = {&trmass[0], &trmass[trmass.size()]};

    Tree tr = createTree(range);
    Camera const camera =
    {
        .position = {110.f, 90.f, 15.f},
        .at = tr->box.center(),
        .up = {0.f, 1.f, 0.f},
        .aspectRatio = fwidth / fheight,
        .verticalFOV = 0.55f,
    };

    // std::cout << tr->box.min_corner[0] << " ";
    // std::cout << tr->box.min_corner[1] << " ";
    // std::cout << tr->box.min_corner[2] << " ";
    // std::cout << std::endl;
    // std::cout << tr->box.max_corner[0] << " ";
    // std::cout << tr->box.max_corner[1] << " ";
    // std::cout << tr->box.max_corner[2] << " ";

    vec3 const   skyColor = {0.53f, 0.81f, 0.92f};

    // auto const trace = [&trmass](Ray const &ray)
    // {
    //     vec3 const   skyColor = {0.53f, 0.81f, 0.92f};
    //     vec3 const lightColor = {1.00f, 0.98f, 0.88f};
    //     vec3 const lightDir   = normalize({3.f, 3.f, -1.f});

    //     std::optional<Intersection> const hit = coordinate_of_intersection(tr, ray);
    //     if(!hit)
    //         return dot(ray.direction, lightDir) < 0.999f
    //             ? skyColor
    //             : lightColor * 2.f;

    //     Ray const shadowRay =
    //     {
    //         .origin = hit->position,
    //         .direction = lightDir
    //     };
    //     std::optional<Intersection> const shadowHit = coordinate_of_intersection(tr, ray);
    //     float const NL = std::max(0.f, dot(hit->normal, lightDir));

    //     vec3 const color = !shadowHit
    //         ? lightColor * NL
    //         : vec3{0.f, 0.f, 0.f};

    //     return (skyColor * 0.3f + color) * hit->albedo;
    // };
    // auto const tonemap = [](vec3 const c)
    // {
    //     float const exposure = 0.3f;
    //     float const almost256 = 255.999f;
    //     return vec3
    //     {
    //         almost256 * (1.f - std::exp(-exposure * c.x)),
    //         almost256 * (1.f - std::exp(-exposure * c.y)),
    //         almost256 * (1.f - std::exp(-exposure * c.z)),
    //     };
    // };
    struct DirectionSample
    {
        vec3 direction;
        float pdf;
    }

    DirectionSample sampleHemisphere(vec3 const norm) noexcept
    {
        static thread_local RNG rng(std::random_device{}());

        float const r = float01(rng);
        float const sinTheta = std::sqrt(r);
        float const cosTheta = std::sqrt(q.f - r);

        float const phi = floatPhi(rng);

        vec3 const x0 = std::abs(norm.x) < 0.9f
            ? vec3(1.f, 0.f, 0.f)
            : vec3(0.f, 1.f, 0.f);
        vec3 const y = normalize(cross(norm, x0));
        vec3 const x = cross(y, norm);

        return
        {
            x * sinTheta * std::cos(phi) +
            y * sinTheta * std::sin(phi) +
            norm * cosTheta,
            std::numbers::inv_pi_v<float>,
        };
    }

    auto const trace = [&](Ray ray)
    {
        vec3 mask = {1.f, 1.f, 1.f};
        vec3 color = {0.f, 0.f, 0.f};

        for(u32 b = 0u; b < 6u; ++b)
        {
            auto const I = intersect(ray);
            if(!I)
                break;

            auto const [i, rti] = *I;
            auto const &material = triangleMaterial[topology.order[i]];

            auto const &[pos3, tex3, norm3] = triangle0[i];
            vec3 const pos = rti.interpolate(pos3);
            vec3 const n0 = normalize(cross(pos3[1] - pos3[0], pos3[2] - pos3[0]));
            vec3 const norm = dot(ray.direction, n0) >= 0.f ? -n0 : n0;

            auto const [dir, pdf] = sampleHemisphere(norm);

            color = color + mask * material.emission;
            mask = mask * material.albedo / (std::numbers::pi_v<float> * pdf);
            ray = {offsetPoint(pos, norm), dir};
        }
        return color;
    }

    std::ofstream out("out.ppm");
    out << "P3\n" << width << " " << height << "\n255\n";
    for(u32 y = 0u; y < height; ++y)
        for(u32 x = 0u; x <  width; ++x)
        {
            float const u = -1.f + 2.f * float(x) / fwidth;
            float const v = -1.f + 2.f * float(y) / fheight;
            float const du = 1.f / fwidth;
            float const dv = 1.f / fheight;

            // 4 rays for antialiasing
            // vec3 const color = tonemap
            // (
            //     trace(camera.castRay(u - du, -v - dv))
            //   + trace(camera.castRay(u - du, -v + dv))
            //   + trace(camera.castRay(u + du, -v - dv))
            //   + trace(camera.castRay(u + du, -v + dv))
            // );
            if(coordinate_of_intersection(tr, camera.castRay(u, v)) == std::nullopt){
                out << u32(32) << " ";
                out << u32(32) << " ";
                out << u32(32) << " ";
            }
            else{
                out << u32(100) << " ";
                out << u32(100) << " ";
                out << u32(100) << " ";
            }
            // std::cout << u32(color.x) << " ";
            // std::cout << u32(color.y) << " ";
            // std::cout << u32(color.z) << " ";
        }
}
