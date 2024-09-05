﻿#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh()
{
}

Mesh::Mesh(MeshType type, float radius, glm::vec3 color)
{
    mType = type;
    switch (type)
    {
    case Cube:
        CreateCube(radius, color);
        break;
    case Triangle:
        CreateTriangle(radius, color);
        break;
    case Square:
        CreateSquare(radius, color);
        break;
    case Pyramid:
        CreatePyramid(radius, color);
        break;
    case Plane:
        CreatePlane(radius, color);
        break;
    case Sphere:
        std::cout << "Error, please specify number of segments" << std::endl;
        break;
        
    }
}

Mesh::Mesh(MeshType type, float radius, int segments, glm::vec3 color)
{
    mType = type;
    switch (type)
    {
    case Sphere:
        CreateSphere(radius, segments, color);
        break;
    default:
        std::cout << "Only sphere accepts int segments" << std::endl;
        break;
    }
}


void Mesh::CreateCube(float radius, glm::vec3 color)
{
    // Define cube vertices
    vertices = {
        // Positions           // Normals           // Color
        { glm::vec3(-radius, -radius, -radius), glm::vec3(-1.0f, -1.0f, -1.0f), color },
        { glm::vec3(radius, -radius, -radius), glm::vec3(1.0f, -1.0f, -1.0f), color },
        { glm::vec3(radius, radius, -radius), glm::vec3(1.0f, 1.0f, -1.0f), color },
        { glm::vec3(-radius, radius, -radius), glm::vec3(-1.0f, 1.0f, -1.0f), color },
        { glm::vec3(-radius, -radius, radius), glm::vec3(-1.0f, -1.0f, 1.0f), color },
        { glm::vec3(radius, -radius, radius), glm::vec3(1.0f, -1.0f, 1.0f), color },
        { glm::vec3(radius, radius, radius), glm::vec3(1.0f, 1.0f, 1.0f), color },
        { glm::vec3(-radius, radius, radius), glm::vec3(-1.0f, 1.0f, 1.0f), color }
    };

    // Define triangles
    indices = {
        0, 1, 2, 2, 3, 0,   // front
        1, 5, 6, 6, 2, 1,   // right
        7, 6, 5, 5, 4, 7,   // back
        4, 0, 3, 3, 7, 4,   // left
        4, 5, 1, 1, 0, 4,   // bottom
        3, 2, 6, 6, 7, 3    // top
    };

    Setup();
}

void Mesh::CreateTriangle(float radius, glm::vec3 color)
{
    // Define triangle vertices
    vertices = {
        // Positions           // Normals           // Color
        { glm::vec3(-radius, -radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color },
        {  glm::vec3(radius, -radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color },
        {  glm::vec3(0.0f,   radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color }
    };

    // Define triangles
    indices = {
        0, 1, 2    // front
    };

    Setup();
}

void Mesh::CreateSquare(float radius, glm::vec3 color)
{
    // Define square vertices
    vertices = {
        // Positions           // Normals           // Color
        { glm::vec3(-radius, -radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color },
        { glm::vec3(radius, -radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color },
        { glm::vec3(radius, radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color },
        { glm::vec3(-radius, radius, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), color }
    };

    // Define triangles
    indices = {
        0, 1, 2,    // first triangle
        2, 3, 0     // second triangle
    };

    Setup();
}

void Mesh::CreatePyramid(float radius, glm::vec3 color)
{
    // Vertices
    vertices = {
        // Positions           // Normals           // Color
        { glm::vec3(-radius, -radius, -radius), glm::vec3(-1.0f, -1.0f, -1.0f), color }, // 0
        { glm::vec3(radius, -radius, -radius), glm::vec3(1.0f, -1.0f, -1.0f), color }, // 1
        { glm::vec3(radius, -radius,  radius), glm::vec3(1.0f, -1.0f,  1.0f), color }, // 2
        { glm::vec3(-radius, -radius,  radius), glm::vec3(-1.0f, -1.0f,  1.0f), color }, // 3
        { glm::vec3(0.0f,   radius,  0.0f),   glm::vec3(0.0f,  1.0f,  0.0f), color }  // 4
    };

    // Define triangles
    indices = {
        0, 1, 4,    // front
        1, 2, 4,    // right
        2, 3, 4,    // back
        3, 0, 4,    // left
        3, 2, 1, 1, 0, 3     // base
    };

    Setup();
    CalculateBoundingBox();
} 

void Mesh::CreateSphere(float radius, int segments, glm::vec3 color)
{

    for (int i = 0; i <= segments; ++i) {
        for (int j = 0; j <= segments; ++j) {
            float y = radius * cos(glm::radians(180.0f - i * 180.0f / segments));
            float x = radius * cos(glm::radians(j * 360.0f / segments)) * sin(glm::radians(180.0f - i * 180.0f / segments));
            float z = radius * sin(glm::radians(j * 360.0f / segments)) * sin(glm::radians(180.0f - i * 180.0f / segments));

            vertices.emplace_back(glm::vec3(x,y,z), glm::normalize(glm::vec3(x, y, z)), color);
        }
    }

    for (int i = 0; i < segments; ++i) {
        for (int j = 0; j < segments; ++j) {
            indices.push_back(i * (segments + 1) + j);
            indices.push_back((i + 1) * (segments + 1) + j);
            indices.push_back((i + 1) * (segments + 1) + j + 1);

            indices.push_back(i * (segments + 1) + j);
            indices.push_back((i + 1) * (segments + 1) + j + 1);
            indices.push_back(i * (segments + 1) + j + 1);
        }
    }

    Setup();
    CalculateBoundingBox();
}

void Mesh::CreatePlane(float radius, glm::vec3 color)
{
    // Define plane vertices
    vertices = {
        // Positions           // Normals           // Color
        { glm::vec3(-radius, 0.0f, -radius), glm::vec3(0.0f, 1.0f, 0.0f), color },
        {  glm::vec3(radius, 0.0f, -radius), glm::vec3(0.0f, 1.0f, 0.0f), color },
        {  glm::vec3(radius, 0.0f,  radius), glm::vec3(0.0f, 1.0f, 0.0f), color },
        { glm::vec3(-radius, 0.0f,  radius), glm::vec3(0.0f, 1.0f, 0.0f), color }
    };

    // Define triangles
    indices = {
        2, 1, 0,    // first triangle
        0, 3, 2     // second triangle
    };

    Setup();
}

void Mesh::Setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // Color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color)); // Add this line
    glEnableVertexAttribArray(2);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::CalculateBoundingBox()
{
    minVert = maxVert = vertices[0].Position;
    for (const auto& vertex : vertices)
    {
        minVert = glm::min(minVert, vertex.Position);
        maxVert = glm::max(maxVert, vertex.Position);
    }
}

void Mesh::Draw(unsigned shaderProgram)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, globalPosition);
    
    model = glm::rotate(model, glm::radians(globalRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(globalRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(globalRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    glBindVertexArray(VAO);

    switch (mType)
    {
    case Cube:
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        break;
    case Square:
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        break;
    case Triangle:
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        break;
    case Pyramid:
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        break;
    case Sphere:
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        break;
    }

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

bool Mesh::CheckCollision(Mesh* other)
{
    // Calculate the bounding box in world space
    glm::vec3 worldMinVert = minVert + globalPosition;
    glm::vec3 worldMaxVert = maxVert + globalPosition;

    // Calculate other mesh bounding box in world space
    glm::vec3 otherWorldMinVert = other->minVert + other->globalPosition;
    glm::vec3 otherWorldMaxVert = other->maxVert + other->globalPosition;

    // Check overlap
    bool overlapX = worldMinVert.x <= otherWorldMaxVert.x && worldMaxVert.x >= otherWorldMinVert.x;
    bool overlapY = worldMinVert.y <= otherWorldMaxVert.y && worldMaxVert.y >= otherWorldMinVert.y;
    bool overlapZ = worldMinVert.z <= otherWorldMaxVert.z && worldMaxVert.z >= otherWorldMinVert.z;

    // Collision only if overlap on all axes
    std::cout << "Collision: " << overlapX << " " << overlapY << " " << overlapZ << std::endl;


    // std::cout << "worldMinVert: " << worldMinVert.x << " " << worldMinVert.y << " " << worldMinVert.z << std::endl;
    // std::cout << "worldMaxVert: " << worldMaxVert.x << " " << worldMaxVert.y << " " << worldMaxVert.z << std::endl;
    return overlapX && overlapY && overlapZ;
}
