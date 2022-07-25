#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <fstream>

Renderer::Renderer() {
	this->initRenderData();
}


Renderer::~Renderer() {

}


// Load and Store Shaders + Textures
// ---------------------------------------------------
void Renderer::initRenderData() {
	// Shaders
	this->LoadShader("C:/Users/Josh/source/repos/ClothSimulation/ClothSimulation/Shaders/cube.vert",
		"C:/Users/Josh/source/repos/ClothSimulation/ClothSimulation/Shaders/cube.frag",
		nullptr,
		"cube_shader");

	this->LoadShader("C:/Users/Josh/source/repos/ClothSimulation/ClothSimulation/Shaders/sphere.vert",
		"C:/Users/Josh/source/repos/ClothSimulation/ClothSimulation/Shaders/sphere.frag",
		nullptr,
		"sphere_shader");

	// Textures
	this->generate_texture("C:/Users/Josh/source/repos/ClothSimulation/ClothSimulation/Textures/container.jpg", "cube_texture");
	this->generate_texture("C:/Users/Josh/source/repos/ClothSimulation/ClothSimulation/Textures/nebula.jpg", "sphere_texture");
}


// Various Shader Utilities
// ------------------------
Shader Renderer::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// if geometry shader path is present, also load a geometry shader
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();
	// 2. now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}
Shader Renderer::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
	shader_manager[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shader_manager[name];
}

Texture2D Renderer::generate_texture(std::string file_name, std::string texture_key)
{
	this->texture_manager[texture_key] = load_texture_from_file(file_name);
	return this->texture_manager[texture_key];
}

Texture2D Renderer::load_texture_from_file(std::string file_name)
{
	// load and create a texture 
	// -------------------------
	Texture2D texture;

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		texture.Generate(width, height, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return texture;
}
