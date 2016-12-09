#ifndef MESH_H
#define MESH_H

#include <string>
#include <qopengl.h>
#include <vector>
#include "meshio.h"

class Mesh
{
public:
    Mesh();

    void draw();
    void loadPointers(std::string file_name);

public:
    bool readPointers(std::string file_name);

    unsigned int v_cnt;
    unsigned int h_cnt;
    GLushort * item_indices;
    GLushort * wire_indices;
    // store vertices and sequence
    GLfloat * vertices;
    GLint * sequence;
    // vertices array for drawElements
    GLfloat * linesArray;
    GLfloat * verticesArray;
};

#endif // MESH_H
