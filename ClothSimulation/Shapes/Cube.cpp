#pragma once

#include "Cube.h"
//#include <iostream>

// ctor
Cube::Cube(float edge_length)
{
    set(edge_length);
}

// setters
void Cube::set(float edge_length)
{
    this->edge_length = edge_length;
    this->shader_key = "cube_shader";
    this->texture_key = "cube_texture";

    glm::mat4 xform = glm::mat4(1.0f);
    xform = glm::scale(xform, glm::vec3(edge_length, edge_length, edge_length));
    this->set_xform_matrix(xform);

    generate_vao();
}

void Cube::generate_vao()
{
    
    build_vertices();

    unsigned int vbo_id, ebo_id;
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &vbo_id);
    glGenBuffers(1, &ebo_id);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, get_interleaved_vertex_size(), get_interleaved_vertices(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_index_size(), get_indices(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

void Cube::set_edge_length(float edge_length)
{
    this->edge_length = edge_length;
}

void Cube::build_vertices()
{
    // Front
    add_vertex(0.5f, 0.5f, 0.5f); // top right
    add_vertex(0.5f, -0.5f, 0.5f); // bottom right
    add_vertex(-0.5f, -0.5f, 0.5f); // bottom left
    add_vertex(-0.5f, 0.5f, 0.5f); // top left

    // Back
    add_vertex(0.5f, 0.5f, -0.5f); // top right
    add_vertex(0.5f, -0.5f, -0.5f); // bottom right
    add_vertex(-0.5f, -0.5f, -0.5f); // bottom left
    add_vertex(-0.5f, 0.5f, -0.5f); // top left


    add_tex_coord(1.0, 1.0);
    add_tex_coord(1.0, 0.0);
    add_tex_coord(0.0, 0.0);
    add_tex_coord(0.0, 1.0);

    add_tex_coord(0.0, 1.0);
    add_tex_coord(0.0, 0.0);
    add_tex_coord(1.0, 0.0);
    add_tex_coord(1.0, 1.0);


    // Texture Coords
    for (int i = 0; i < 8; i++)
    {
        add_tex_coord(1.0, 1.0);
        add_tex_coord(1.0, 0.0);
        add_tex_coord(0.0, 0.0);
        add_tex_coord(0.0, 1.0);

        add_tex_coord(0.0, 1.0);
        add_tex_coord(0.0, 0.0);
        add_tex_coord(1.0, 0.0);
        add_tex_coord(1.0, 1.0);
    }


    for(int i = 0; i != 8; i++)
        add_normal(0, 0, 0);



    // Front
    add_indices(0, 1, 3);
    add_indices(1, 2, 3);

    // Back
    add_indices(4, 5, 7);
    add_indices(5, 6, 7);

    // Left Side
    add_indices(3, 2, 7);
    add_indices(2, 6, 7);

    // Right Side
    add_indices(4, 5, 0);
    add_indices(5, 1, 0);

    // Top
    add_indices(4, 0, 7);
    add_indices(0, 3, 7);

    // Bottom
    add_indices(1, 5, 2);
    add_indices(5, 6, 2);

    build_interleaved_vertices();
}

void Cube::print()
{
    std::cout << "Cube" << std::endl;
}

void Cube::draw(Shader shader, Texture2D texture, glm::mat4 view, glm::mat4 projection)
{
    shader.Use();


    // Get Model Matrix
    glm::mat4 model = this->xform;	// Now have MVP matrix that we can pass to shader



    // Activate and Bind Texture
    shader.set_int("_texture", 0);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    // Set Uniforms
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("model", model);

    // Get Primitive VAO
    unsigned int vao = this->vao;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, get_index_count(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
