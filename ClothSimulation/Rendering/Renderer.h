#pragma once
#ifndef RENDERER_H
#define RENDERER_H

#define GLFW_INCLUDE_GLCOREARB

// System Includes
#include <glm/vec2.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <set>
#include <algorithm>  // std::copy
#include <math.h>
#include <map>
#include <vector>
#include <string>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

// Model Includes
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "../Util/stb_image.h"


class Renderer
{
public:
	// Constructor/Destructor
	Renderer();
	~Renderer();


	// Shader Management
	std::map<std::string, Shader> shader_manager;

	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// Texture Management
	std::map<std::string, Texture2D> texture_manager;
	static Texture2D load_texture_from_file(std::string file_name);
	Texture2D generate_texture(std::string file_name, std::string texture_key);
private:




	// Render Data Initialization
	void initRenderData();

};

#endif // !RENDERER_H
