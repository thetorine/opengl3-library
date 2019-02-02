#pragma once

// control how many particles per second
// control the area from which the particles spawn from
// control how the color of the particle changes
// control the direction of the particles

namespace gl::particle {
    class Emitter {
    public:
        Emitter(int spawnRate);
        void updateParticles();
    };
}