#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 center,
    float length,
    float width,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-length / 2, -width / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, - width / 2, 0), color),
        VertexFormat(center + glm::vec3(length / 2, width / 2, 0), color),
        VertexFormat(center + glm::vec3(-length / 2, width / 2, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 center,
    float ccm_radius,
    glm::vec3 color,
    bool fill)

{

    float xA = center.x, yA = center.y + ccm_radius;
    float xB = center.x - 0.4f * ccm_radius;
    float yB = center.y - float(sqrt(21)) / 5 * ccm_radius;
    float xC = center.x + 0.4f * ccm_radius;
    float yC = yB;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(xA, yA, 0), color),
        VertexFormat(glm::vec3(xB, yB, 0), color),
        VertexFormat(glm::vec3(xC, yC, 0), color),
        //VertexFormat(glm::vec3(center.x, center.y, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    //std::vector<unsigned int> indices = { 0, 1, 3, 0, 2, 3, 1, 2};
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    int sides,
    glm::vec3 color,
    bool fill)

{
    float angle = 3 / (float)4.0;
    float apothem = float(radius * cos(M_PI / (float)sides));
    float yTopOffset = (sides % 2 == 0) ? 0.0f : (radius - apothem) / 2.0f;
    
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    Mesh* circle = new Mesh(name);
    
    vertices.push_back(VertexFormat(glm::vec3(center.x, center.y, 0), color));

    for (int i = 1; i <= sides; ++i) {
        float t = float(2 * M_PI * ((float)(i - 1) / (float)sides + angle));
        float x = center.x + cos(t) * radius;
        float y = center.y + sin(t) * radius + yTopOffset;
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }
    if (fill) {
        for (int i = 1; i < sides; ++i) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back(i + 1);
        }
        indices.push_back(0);
        indices.push_back(sides);
        indices.push_back(1);

    }
    else {
        for (int i = 1; i <= sides; ++i) {
            indices.push_back(i);
        }
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    circle->InitFromData(vertices, indices);
    return circle;
}


