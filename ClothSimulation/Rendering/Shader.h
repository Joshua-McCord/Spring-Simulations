#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.
class Shader
{
public:
	// state
	unsigned int ID;
	// constructor
	Shader() { }
	// sets the current shader as active
	Shader& Use();
	// compiles the shader from given source code
	void    Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); // note: geometry source code is optional
	// utility functions
	void    SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
	void    set_int(std::string name, const int i, bool useShader = false);

private:
	// checks if compilation or linking failed and if so, print the error logs
	void    checkCompileErrors(unsigned int object, std::string type);
};

#endif