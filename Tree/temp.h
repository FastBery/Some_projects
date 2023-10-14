#pragma once
#include "vec3.h"
#include "ray.h"
#include <cmath>

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