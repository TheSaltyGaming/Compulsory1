#include "Collision.h"

#include <iostream>

#include "Mesh/Mesh.h"

Collision::Collision()
{
    
}

bool Collision::AABBCollision(Mesh* mesh1, Mesh* other)
{
    // bool overlapX = mesh1->minVert.x <= other->maxVert.x && mesh1->maxVert.x >= other->minVert.x;
    // bool overlapY = mesh1->minVert.y <= other->maxVert.y && mesh1->maxVert.y >= other->minVert.y;
    // bool overlapZ = mesh1->minVert.z <= other->maxVert.z && mesh1->maxVert.z >= other->minVert.z;
    //
    // bool collision = overlapX && overlapY && overlapZ;
    //
    // std::cout << overlapX << " " << overlapY << " " << overlapZ << std::endl;
    //
    // if (collision)
    // {
    //     //std::cout << "Collision detected" << std::endl;
    //     //print overlap x y and z
    //     
    //
    //     // Calculate collision normal
    //     glm::vec3 collisionNormal = glm::normalize(globalPosition - other->globalPosition);
    //
    //     // Reflect velocity
    //     velocity = glm::reflect(velocity, collisionNormal);
    // }
    //
    // return collision;

    return true;
}

bool Collision::SphereCollision(Mesh* mesh1, Mesh* mesh2)
{
    return true;
}

bool Collision::SphereToAABBCollision(Mesh* mesh1, Mesh* mesh2)
{
    return true;
}
