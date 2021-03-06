#pragma once

#include <ostream>

#include "../math/Vec3.h"
#include "../math/Vec2.h"
#include "Tri2.h"
#include "Tri3.h"

namespace bh {

class Camera {
public:
    Camera();
    Camera(const Vec3& location_in);

    const Vec3& get_forward() const;
    const Vec3& get_right() const;
    const Vec3& get_up() const;

    const Vec3& get_location() const;

    float get_pitch() const;
    float get_yaw() const;

    float get_fov() const;
    float get_aspect_ratio() const;

    //yaw and pitch in radians
    void set_rotation(float pitch, float yaw);
    void rotate(float d_pitch, float d_yaw);

    void set_location(const Vec3& new_location);
    void move_location(const Vec3& delta);

    enum NumTrianglesGenerated {
        Zero,
        One,
        Two,
        Three
    };

    static bool project_point(const Camera& cam, const Vec3& in, Vec2* filled);
    static NumTrianglesGenerated project_triangle(const Camera& cam, const Tri3& in, Tri2* filled);

    static bool triangle_is_behind(const Camera& cam, const Tri3& triangle);

    friend std::ostream& operator<<(std::ostream& os, const Camera& cam){
        os << "Camera:" 
           << "\tlocation:" << cam.get_location() << std::endl
           << "\tforward: " << cam.get_forward() << std::endl
           << "\tright:   " << cam.get_right() << std::endl
           << "\tup:      " << cam.get_up() << std::endl;
        return os;
    }

private:
    Vec3 forward, right, up;
    Vec3 location;//location or position?
    float yaw, pitch;

    float fov;
    float aspect_ratio;
};

}
