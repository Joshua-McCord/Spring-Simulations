#include "Anchor.h"

Anchor::Anchor(glm::vec3 anchor_position)
{
	set(anchor_position);
}

Anchor::~Anchor()
{
	free(geometry);
}

void Anchor::set(glm::vec3 anchor_position)
{
	this->geometry = new Cube();
	glm::mat4 xform = glm::mat4(1.0f);
	xform = glm::scale(xform, glm::vec3(0.25f, 0.25f, 0.25f));
	xform = glm::translate(xform, position);
	geometry->set_xform_matrix(xform);

	this->position = anchor_position;
}

void Anchor::set_position(glm::vec3 new_position)
{
	this->position = new_position;
	glm::mat4 xform = glm::mat4(1.0f);
	xform = glm::translate(xform, position);
	geometry->set_xform_matrix(xform);
}

void Anchor::print()
{
	std::cout << "===== Anchor =====" << std::endl;
	std::cout << " Position: " << glm::to_string(this->position) << std::endl;
}
