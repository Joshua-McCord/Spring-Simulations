#pragma once
#ifndef SPHERE_H
#define SPHERE_H

// System Includes
#include <iostream>
#include <cmath>
#include <vector>

// Model Includes
#include "Geometry.h"


// Based off the Sector/Stack Spherical Model by Song Ho @ http://www.songho.ca/opengl/gl_sphere.html
class Sphere : public Geometry
{
public:

	// ctor/dtor
	Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, bool smooth = true);
	~Sphere() { }

	// setters
	void set(float radius, int sectorCount, int stackCount, bool smooth = true);
	void set_radius(float radius);
	void set_sector_count(int sectorCount);
	void set_stack_count(int stackCount);
	void set_smooth(bool smooth);

	// getters
	float get_radius() const { return radius; }
	int get_sector_count() const { return sector_count; }
	int get_stack_count() const { return stack_count; }


	// Virtual Interface Implementations
	void draw(Shader shader, Texture2D texture, glm::mat4 view, glm::mat4 projection);
	void print();
	void generate_vao();


private:
	void build_vertices_smooth();
	void build_vertices_flat();

	// memeber vars
	float radius;
	int sector_count;                        // longitude, # of slices
	int stack_count;                         // latitude, # of stacks
	bool smooth;

};

#endif // !SPHERE_H
