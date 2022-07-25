#pragma once

#include "Sphere.h"

// constants //////////////////////////////////////////////////////////////////
const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT = 2;



///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Sphere::Sphere(float radius, int sectors, int stacks, bool smooth)
{
    set(radius, sectors, stacks, smooth);
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Sphere::set(float radius, int sectors, int stacks, bool smooth)
{
    this->radius = radius;
    this->sector_count = sectors;
    if (sectors < MIN_SECTOR_COUNT)
        this->sector_count = MIN_SECTOR_COUNT;
    this->stack_count = stacks;
    if (sectors < MIN_STACK_COUNT)
        this->stack_count = MIN_STACK_COUNT;
    this->smooth = smooth;

    if (smooth)
        build_vertices_smooth();
    else
        build_vertices_flat();

    this->interleaved_stride = 32;

    // Transform Matrix
    glm::mat4 xform = glm::mat4(1.0f);
    xform = glm::translate(xform, glm::vec3(0.0f, 0.0f, 0.0f));
    this->xform = xform;

    this->shader_key = "sphere_shader";
    this->texture_key = "sphere_texture";
    generate_vao();
    
}

void Sphere::generate_vao()
{

	unsigned int vbo_id, ebo_id;
	// Gen VAO, VBO, EBO
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &vbo_id);
	glGenBuffers(1, &ebo_id);

	// Bind the VAO
	glBindVertexArray(this->vao);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, get_interleaved_vertex_size(), get_interleaved_vertices(), GL_STATIC_DRAW);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_index_size(), get_indices(), GL_STATIC_DRAW);

	// Bind Buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);

	// Vertex Layout in memory
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);	// Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	// Normals
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	// Textures
	glEnableVertexAttribArray(2);

}



void Sphere::set_radius(float radius)
{
    if (radius != this->radius)
        set(radius, sector_count, stack_count, smooth);
}

void Sphere::set_sector_count(int sectors)
{
    if (sectors != this->sector_count)
        set(radius, sectors, stack_count, smooth);
}

void Sphere::set_stack_count(int stacks)
{
    if (stacks != this->stack_count)
        set(radius, sector_count, stacks, smooth);
}

void Sphere::set_smooth(bool smooth)
{
    if (this->smooth == smooth)
        return;

    this->smooth = smooth;
    if (smooth)
        build_vertices_smooth();
    else
        build_vertices_flat();
}


///////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void Sphere::print() 
{
    std::cout << "===== Sphere =====\n"
        << "        Radius: " << radius << "\n"
        << "  Sector Count: " << sector_count << "\n"
        << "   Stack Count: " << stack_count << "\n"
        << "Smooth Shading: " << (smooth ? "true" : "false") << "\n"
        << "Triangle Count: " << get_triangle_count() << "\n"
        << "   Index Count: " << get_index_count() << "\n"
        << "  Vertex Count: " << get_vertex_count() << "\n"
        << "  Normal Count: " << get_normal_count() << "\n"
        << "TexCoord Count: " << get_tex_coord_count() << std::endl;
}


void Sphere::draw(Shader shader, Texture2D texture, glm::mat4 view, glm::mat4 projection)
{
    shader.Use();


    // Get Model Matrix
    glm::mat4 model;
    model = this->xform;	// Now have MVP matrix that we can pass to shader

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
    glDrawElements(GL_TRIANGLES, get_index_count(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}






/*@@ FIXME: when the radius  = 0
///////////////////////////////////////////////////////////////////////////////
// update vertex positions only
///////////////////////////////////////////////////////////////////////////////
void Sphere::updateRadius()
{
    float scale = sqrtf(radius * radius / (vertices[0] * vertices[0] + vertices[1] * vertices[1] + vertices[2] * vertices[2]));

    std::size_t i, j;
    std::size_t count = vertices.size();
    for(i = 0, j = 0; i < count; i += 3, j += 8)
    {
        vertices[i]   *= scale;
        vertices[i+1] *= scale;
        vertices[i+2] *= scale;

        // for interleaved array
        interleaved_vertices[j]   *= scale;
        interleaved_vertices[j+1] *= scale;
        interleaved_vertices[j+2] *= scale;
    }
}
*/




///////////////////////////////////////////////////////////////////////////////
// build vertices of sphere with smooth shading using parametric equation
// x = r * cos(u) * cos(v)
// y = r * cos(u) * sin(v)
// z = r * sin(u)
// where u: stack(latitude) angle (-90 <= u <= 90)
//       v: sector(longitude) angle (0 <= v <= 360)
///////////////////////////////////////////////////////////////////////////////
void Sphere::build_vertices_smooth()
{
    const float PI = acos(-1);

    // clear memory of prev arrays
    clear_arrays();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / sector_count;
    float stackStep = PI / stack_count;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stack_count; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sector_count+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sector_count; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            add_vertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            add_normal(nx, ny, nz);

            // vertex tex coord between [0, 1]
            s = (float)j / sector_count;
            t = (float)i / stack_count;
            add_tex_coord(s, t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < stack_count; ++i)
    {
        k1 = i * (sector_count + 1);     // beginning of current stack
        k2 = k1 + sector_count + 1;      // beginning of next stack

        for (int j = 0; j < sector_count; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                add_indices(k1, k2, k1 + 1);   // k1---k2---k1+1
            }

            if (i != (stack_count - 1))
            {
                add_indices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
            }

            // vertical lines for all stacks
            lineIndices.push_back(k1);
            lineIndices.push_back(k2);
            if (i != 0)  // horizontal lines except 1st stack
            {
                lineIndices.push_back(k1);
                lineIndices.push_back(k1 + 1);
            }
        }
    }

    // generate interleaved vertex array as well
    build_interleaved_vertices();
}



///////////////////////////////////////////////////////////////////////////////
// generate vertices with flat shading
// each triangle is independent (no shared vertices)
///////////////////////////////////////////////////////////////////////////////
void Sphere::build_vertices_flat()
{
    const float PI = acos(-1);

    // tmp vertex definition (x,y,z,s,t)
    struct Vertex
    {
        float x, y, z, s, t;
    };
    std::vector<Vertex> tmpVertices;

    float sectorStep = 2 * PI / sector_count;
    float stackStep = PI / stack_count;
    float sectorAngle, stackAngle;

    // compute all vertices first, each vertex contains (x,y,z,s,t) except normal
    for (int i = 0; i <= stack_count; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);       // r * cos(u)
        float z = radius * sinf(stackAngle);        // r * sin(u)

        // add (sector_count+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sector_count; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            Vertex vertex;
            vertex.x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
            vertex.y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)
            vertex.z = z;                           // z = r * sin(u)
            vertex.s = (float)j / sector_count;        // s
            vertex.t = (float)i / stack_count;         // t
            tmpVertices.push_back(vertex);
        }
    }

    // clear memory of prev arrays
    clear_arrays();

    Vertex v1, v2, v3, v4;                          // 4 vertex positions and tex coords
    std::vector<float> n;                           // 1 face normal

    int i, j, k, vi1, vi2;
    int index = 0;                                  // index for vertex
    for (i = 0; i < stack_count; ++i)
    {
        vi1 = i * (sector_count + 1);                // index of tmpVertices
        vi2 = (i + 1) * (sector_count + 1);

        for (j = 0; j < sector_count; ++j, ++vi1, ++vi2)
        {
            // get 4 vertices per sector
            //  v1--v3
            //  |    |
            //  v2--v4
            v1 = tmpVertices[vi1];
            v2 = tmpVertices[vi2];
            v3 = tmpVertices[vi1 + 1];
            v4 = tmpVertices[vi2 + 1];

            // if 1st stack and last stack, store only 1 triangle per sector
            // otherwise, store 2 triangles (quad) per sector
            if (i == 0) // a triangle for first stack ==========================
            {
                // put a triangle
                add_vertex(v1.x, v1.y, v1.z);
                add_vertex(v2.x, v2.y, v2.z);
                add_vertex(v4.x, v4.y, v4.z);

                // put tex coords of triangle
                add_tex_coord(v1.s, v1.t);
                add_tex_coord(v2.s, v2.t);
                add_tex_coord(v4.s, v4.t);

                // put normal
                n = compute_face_normal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
                for (k = 0; k < 3; ++k)  // same normals for 3 vertices
                {
                    add_normal(n[0], n[1], n[2]);
                }

                // put indices of 1 triangle
                add_indices(index, index + 1, index + 2);

                // indices for line (first stack requires only vertical line)
                lineIndices.push_back(index);
                lineIndices.push_back(index + 1);

                index += 3;     // for next
            }
            else if (i == (stack_count - 1)) // a triangle for last stack =========
            {
                // put a triangle
                add_vertex(v1.x, v1.y, v1.z);
                add_vertex(v2.x, v2.y, v2.z);
                add_vertex(v3.x, v3.y, v3.z);

                // put tex coords of triangle
                add_tex_coord(v1.s, v1.t);
                add_tex_coord(v2.s, v2.t);
                add_tex_coord(v3.s, v3.t);

                // put normal
                n = compute_face_normal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 3; ++k)  // same normals for 3 vertices
                {
                    add_normal(n[0], n[1], n[2]);
                }

                // put indices of 1 triangle
                add_indices(index, index + 1, index + 2);

                // indices for lines (last stack requires both vert/hori lines)
                lineIndices.push_back(index);
                lineIndices.push_back(index + 1);
                lineIndices.push_back(index);
                lineIndices.push_back(index + 2);

                index += 3;     // for next
            }
            else // 2 triangles for others ====================================
            {
                // put quad vertices: v1-v2-v3-v4
                add_vertex(v1.x, v1.y, v1.z);
                add_vertex(v2.x, v2.y, v2.z);
                add_vertex(v3.x, v3.y, v3.z);
                add_vertex(v4.x, v4.y, v4.z);

                // put tex coords of quad
                add_tex_coord(v1.s, v1.t);
                add_tex_coord(v2.s, v2.t);
                add_tex_coord(v3.s, v3.t);
                add_tex_coord(v4.s, v4.t);

                // put normal
                n = compute_face_normal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z);
                for (k = 0; k < 4; ++k)  // same normals for 4 vertices
                {
                    add_normal(n[0], n[1], n[2]);
                }

                // put indices of quad (2 triangles)
                add_indices(index, index + 1, index + 2);
                add_indices(index + 2, index + 1, index + 3);

                // indices for lines
                lineIndices.push_back(index);
                lineIndices.push_back(index + 1);
                lineIndices.push_back(index);
                lineIndices.push_back(index + 2);

                index += 4;     // for next
            }
        }
    }

    // generate interleaved vertex array as well
    build_interleaved_vertices();
}
