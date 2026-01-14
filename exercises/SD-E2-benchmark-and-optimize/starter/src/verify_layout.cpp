#include "ParticleLayouts.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>

int main() {
    constexpr size_t N = 10000;

    sd_e2::ParticlesAoS aos;
    sd_e2::ParticlesSoA soa;
    aos.resize(N);
    soa.resize(N);

    for (size_t i = 0; i < N; ++i) {
        const double px = 0.1 * i;
        const double py = 0.2 * i;
        const double pz = 0.3 * i;
        const double m  = 0.511;

        aos.particles[i].px = px;
        aos.particles[i].py = py;
        aos.particles[i].pz = pz;
        aos.particles[i].mass = m;

        soa.px[i] = px;
        soa.py[i] = py;
        soa.pz[i] = pz;
        soa.mass[i] = m;
    }

    const double a = aos.sumEnergy();
    const double b = soa.sumEnergy();

    const double rel = std::abs(a - b) / (std::abs(a) + 1e-12);
    std::cout << "AoS sum: " << a << "\n";
    std::cout << "SoA sum: " << b << "\n";
    std::cout << "Relative diff: " << rel << "\n";

    if (rel > 1e-12) {
        std::cerr << "Mismatch: optimisation changed the result too much\n";
        return 1;
    }

    return 0;
}