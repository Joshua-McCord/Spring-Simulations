#pragma once
#include "Geometry.h"
#include <iostream>

class Cube : public Geometry
{
public:
   
    // ctor/dtor
    Cube(float edge_length = 1);
    ~Cube() { }

    // setters
    void set(float edge_length);
    void set_edge_length(float edge_length);

    // getters
    const float get_edge_length() const { return edge_length; }

    // Virtual Interface Implementations
    void draw(Shader shader, Texture2D texture, glm::mat4 view, glm::mat4 projection);
    void print();
    void generate_vao();

private:
    float edge_length;

    void build_vertices();

};