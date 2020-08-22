#ifndef _TIMESTEP_HPP_
#define _TIMESTEP_HPP_

namespace Navia {
class Timestep {
public:
    explicit Timestep(float time = 0.0f);

    float getSeconds() const;
    float getMilliseconds() const;

    operator float() const;

private:
    float time;
};
}

#endif