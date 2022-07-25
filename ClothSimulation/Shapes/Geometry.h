#pragma once
#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/matrix_decompose.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "../Rendering/Shader.h"
#include "../Rendering/Texture.h"


class Geometry 
{
public:

	// ctor/dtor
	// ---------
	Geometry();
	~Geometry();

	// Virtual Interface
	// ---------------
	virtual void draw(Shader shader, Texture2D texture, glm::mat4 view, glm::mat4 projection) = 0;
	virtual void print() = 0;
	virtual void generate_vao() = 0;



	// getters	
	// -------
	unsigned int get_vertex_count() const { return (unsigned int)vertices.size() / 3; }
	unsigned int get_normal_count() const { return (unsigned int)normals.size() / 3; }
	unsigned int get_tex_coord_count() const { return (unsigned int)tex_coords.size() / 2; }
	unsigned int get_index_count() const { return (unsigned int)indices.size(); }
	unsigned int get_line_index_count() const { return (unsigned int)lineIndices.size(); }
	unsigned int get_triangle_count() const { return get_index_count() / 3; }
	unsigned int get_vertex_size() const { return (unsigned int)vertices.size() * sizeof(float); }
	unsigned int get_normal_size() const { return (unsigned int)normals.size() * sizeof(float); }
	unsigned int get_tex_coord_size() const { return (unsigned int)tex_coords.size() * sizeof(float); }
	unsigned int get_index_size() const { return (unsigned int)indices.size() * sizeof(unsigned int); }
	unsigned int get_line_index_size() const { return (unsigned int)lineIndices.size() * sizeof(unsigned int); }
	const float* get_vertices() const { return vertices.data(); }
	const float* get_normals() const { return normals.data(); }
	const float* get_tex_coords() const { return tex_coords.data(); }
	const unsigned int* get_indices() const { return indices.data(); }
	const unsigned int* get_line_indices() const { return lineIndices.data(); }
	const glm::mat4 get_xform_matrix() const { return this->xform; }
	const std::string get_shader_key() const { return this->shader_key; }
	const std::string get_texture_key() const { return this->texture_key; }

	// for interleaved vertices: V/N/T
	unsigned int get_interleaved_vertex_count() const { return get_vertex_count(); }    // # of vertices
	unsigned int get_interleaved_vertex_size() const { return (unsigned int)interleaved_vertices.size() * sizeof(float); }    // # of bytes
	int get_interleaved_stride() const { return interleaved_stride; }   // should be 32 bytes
	const float* get_interleaved_vertices() const { return interleaved_vertices.data(); }

	// setters
	void set_xform_matrix(glm::mat4 model_matrix);
	void build_interleaved_vertices();

	
protected:

	void clear_arrays();
	void add_vertex(float x, float y, float z);
	void add_normal(float x, float y, float z);
	void add_tex_coord(float s, float t);
	void add_indices(unsigned int i1, unsigned int i2, unsigned int i3);
	std::vector<float> compute_face_normal(float x1, float y1, float z1,
		float x2, float y2, float z2,
		float x3, float y3, float z3);

	unsigned int vao;
	glm::mat4 xform;

	std::string shader_key;
	std::string texture_key;

	std::vector<float>			vertices;
	std::vector<float>			normals;
	std::vector<float>			tex_coords;
	std::vector<unsigned int>   indices;
	std::vector<unsigned int>   lineIndices;

	std::vector<float>			interleaved_vertices;
	int interleaved_stride;
};
#endif // !PRIMITIVE_H
