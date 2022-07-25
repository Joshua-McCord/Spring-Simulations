#pragma once
#ifndef ANCHOR_H
#define ANCHOR_H

#define GLM_ENABLE_EXPERIMENTAL
// System Includes
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>


// Model Includes
#include "../Shapes/Cube.h"

class Anchor
{
public:

	// ctor/dtor
	Anchor(glm::vec3 anchor_position);
	~Anchor();


	// getters/setters
	void set(glm::vec3 anchor_position);
	void set_position(glm::vec3 new_position);

	glm::vec3 get_position() const { return position; }
	Cube* get_geometry() const { return geometry; }

	// Utility
	void print();

private:

	Cube* geometry;
	glm::vec3 position;
};

#endif // !ANCHOR_H