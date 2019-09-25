#include "Camera.h"
#include "../math/Vec3.h"
#include "../math/Mat3.h"

#include <math.h>

Camera::Camera() {
	location = {0,0,0};

	forward  = {0,0,1};
	up 		 = {0,1,0};
	right 	 = {1,0,0};

	yaw = 0.0f;
	pitch = 0.0f;

	fov = 3.1415/2;
}

const Vec3& Camera::get_forward() const {
	return forward;
}

const Vec3& Camera::get_right() const {
	return right;
}

const Vec3& Camera::get_up() const {
	return up;
}

const Vec3& Camera::get_location() const {
	return location;
}

float Camera::get_pitch() const {
	return pitch;
}

float Camera::get_yaw() const {
	return yaw;
}

float Camera::get_fov() const {
	return fov;
}

float Camera::get_aspect_ratio() const {
	return aspect_ratio;
}

Vec2 Camera::project_point(const Camera& cam, const Vec3& in) {
	//the point using our camera's coordinate system
	Vec3 relative_point = {
		Vec3::dot(cam.right, in),
		Vec3::dot(cam.up, in),
		Vec3::dot(cam.forward, in)
	};

	Vec2 projected = {
		relative_point.x / relative_point.z,
		relative_point.y / relative_point.z
	};
	
	return projected;
}

void Camera::set_rotation(float pitch, float yaw) {
	this->pitch = pitch;
	this->yaw	= yaw;

	//rotate default frame by this pitch, then this yaw
	forward = {0,0,1};
	up 		= {0,1,0};
	right	= {1,0,0};

    Mat3 pitch_rotation = Mat3::rotation_around_x(pitch);
    Mat3 yaw_rotation   = Mat3::rotation_around_y(yaw);

    //pitch
    forward = pitch_rotation * forward;
    up = pitch_rotation * up;
    right = pitch_rotation * right;

    //then yaw
    forward = yaw_rotation * forward;
    up = yaw_rotation * up;
    right = yaw_rotation * right;
}

void Camera::rotate(float d_pitch, float d_yaw) {
	pitch += d_pitch;
    yaw += d_yaw;

    set_rotation(pitch, yaw);
}
