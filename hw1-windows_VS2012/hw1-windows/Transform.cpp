// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

#include <iostream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	float radian = glm::radians(degrees);

	mat3 aaT(
		axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
		axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
		axis.x * axis.z, axis.y * axis.z, axis.z * axis.z
	);

	mat3 Astar(0, -axis.z, axis.y,
				axis.z, 0, -axis.x,
				-axis.y, axis.x, 0);

	return cos(radian)*mat3() + (1 - cos(radian))*aaT + sin(radian)*Astar;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	vec3 normAxis = glm::normalize(up);
	eye = eye * rotate(degrees, normAxis);

	//printf("UP: %.2f, %.2f, %.2f\n", up.x, up.y, up.z);
	//printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 newAxis = glm::normalize(glm::cross(eye, up));
	eye = eye*rotate(degrees, newAxis);
	up = up*rotate(degrees, newAxis);

	//printf("UP: %.2f, %.2f, %.2f\n", up.x, up.y, up.z);
	//printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 a = eye;
	vec3 b = up;

	//First, create a coordinate frame for the camera
	vec3 w = glm::normalize(a);
	vec3 u = glm::normalize(glm::cross(b, w));
	vec3 v = glm::cross(w, u);

	//Define rotation matrix
	mat3 Ruvw = mat3(
		u.x, v.x, w.x,
		u.y, v.y, w.y,
		u.z, v.z, w.z
		);

	//Apply appropriate translation for camera (eye) location
	mat4 translationToEye = mat4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1);
	mat4 _Ruvw = mat4(Ruvw);

	return _Ruvw * translationToEye;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
