#pragma once

#include "FPSCamera.h"

class FloatingCamera : public FPSCamera {
public:
	FloatingCamera(float fov, float width, float height) : FPSCamera(fov, width, height) {}

	void moveUp(float amount) {
		translate(up * amount);
	}
};