#include "Collision.h"

#include <iostream>

#include "Mesh/Mesh.h"

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

Collision::Collision()
{
    
}

bool Collision::AABBCollision(Mesh* mesh1, Mesh* other)
{
    bool overlapX = mesh1->minVert.x <= other->maxVert.x && mesh1->maxVert.x >= other->minVert.x;
    bool overlapY = mesh1->minVert.y <= other->maxVert.y && mesh1->maxVert.y >= other->minVert.y;
    bool overlapZ = mesh1->minVert.z <= other->maxVert.z && mesh1->maxVert.z >= other->minVert.z;
    
    bool collision = overlapX && overlapY && overlapZ;

    std::cout << overlapX << " " << overlapY << " " << overlapZ << std::endl;
    
    if (collision)
    {
        glm::vec3 collisionNormal = glm::normalize(mesh1->globalPosition - other->globalPosition);

        // Reflect velocity
        mesh1->velocity = glm::reflect(mesh1->velocity, collisionNormal);
    }
    
    return collision;
}

bool Collision::SphereCollision(Mesh* mesh1, Mesh* other)
{
    float distance = glm::length(mesh1->globalPosition - other->globalPosition);
    float sumRadius = mesh1->Radius + other->Radius;
    
    bool collision = distance < sumRadius;
    
    if (collision)
    {
        std::cout << "Sphere Collision detected" << std::endl;
        glm::vec3 collisionNormal = glm::normalize(mesh1->globalPosition - other->globalPosition);
        
        
        float penetrationDepth = sumRadius - distance;
    
        // No more clipping hopefully
        mesh1->globalPosition += collisionNormal * (penetrationDepth / 2.0f);
        other->globalPosition -= collisionNormal * (penetrationDepth / 2.0f);
    
        // Refect on poor life choices
        mesh1->velocity = glm::reflect(mesh1->velocity, collisionNormal);
        other->velocity = glm::reflect(other->velocity, -collisionNormal);
    }
    return collision;
}

bool Collision::SphereToAABBCollision(Mesh* mesh1, Mesh* other)
{
    glm::vec3 closestPoint = other->ClosestPointOnAABB(mesh1->globalPosition);
    float distance = glm::length(closestPoint-mesh1->globalPosition);

    bool collision = distance < mesh1->Radius;

    if (collision)
    {
        std::cout << "Sphere AABB Collision detected" << std::endl;
        glm::vec3 collisionNormal = glm::normalize(mesh1->globalPosition - closestPoint);

        mesh1->velocity = glm::reflect(mesh1->velocity, collisionNormal);
    }
    return collision;
}
