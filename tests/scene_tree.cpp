#include <limits>

#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "utilities.hpp"
#include "scene/scene_object.hpp"

const float PI = static_cast<float>(std::acos(-1));

// Tests to write:
/*
    Shear tests
    Rotation and translation have no effect on scale.
*/

TEST_CASE("scene objects attached to the root parent can be transformed", "[SceneObject]") {
    scene::SceneObject sceneObj;

    REQUIRE(sceneObj.getTranslation() == glm::vec3(0.0f));
    REQUIRE(sceneObj.getRotation() == glm::quat(glm::vec3(0.0f)));
    REQUIRE(sceneObj.getScale() == glm::vec3(1.0f));
    REQUIRE(sceneObj.getModel() == glm::mat4(1.0f));

    SECTION("the scene object can be translated") {
        glm::vec3 dm(1.0f, 0.0f, 1.0f);
        sceneObj.move(dm);

        SECTION("adding a translation vector changes the local translation") {
            REQUIRE(sceneObj.getTranslation() == dm);
        }

        SECTION("adding a translation vector changes the local model matrix") {
            glm::mat4 modelMatrix = sceneObj.getModel();
            // Get the translation matrix from the affine transformation matrix
            glm::vec3 localTranslation = glm::vec3(modelMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

            REQUIRE(localTranslation == dm);
        }
    }
}

TEST_CASE("scene objects attached with one parent can be translated", "[SceneObject]") {
    scene::SceneObject parent;
    scene::SceneObject child;
    
    glm::vec3 parentTranslation(1.0f, 0.0f, 0.0f);
    parent.move(parentTranslation);

    glm::mat4 parentMatrix = parent.getModel();

    SECTION("the childs global translation is based on the parents local translation") {
        glm::vec3 childTranslation = child.getGlobalTranslation(parentMatrix);
        REQUIRE(childTranslation == parentTranslation);
    }

    SECTION("the childs global translation is offset from the parents local translation") {
        glm::vec3 localTranslation = glm::vec3(0.0f, 1.0f, 0.0f);
        child.move(localTranslation);
        glm::vec3 childTranslation = child.getGlobalTranslation(parentMatrix);
        
        REQUIRE(childTranslation == parentTranslation + localTranslation);
    }

    SECTION("the childs global translation is offset from a translated and rotated parent") {
        glm::vec3 parentRotation(0.0f, 0.0f, PI / 2.0f);
        parent.rotate(parentRotation);
        parentMatrix = parent.getModel();

        glm::vec3 localTranslation = glm::vec3(1.0f, 0.0f, 0.0f);
        child.move(localTranslation);
        glm::vec3 childTranslation = child.getGlobalTranslation(parentMatrix);
        
        // Global parent coordinate frame
        /*
            Identity:     Translated (1, 0):     Rotated (PI / 2 anticlockwise):
            y             y                           x
            ^             ^                           ^
            |             |                           |
            ---->x        ---->x                 y<----
            ^             ^                           ^
            (0, 0)        (1, 0)                      (1, 0) / (0, 0) in local frame
        */

        // Global child coordinate frame
        /*
            Translated (1, 0) in the parents frame
                 x
                 ^
                 |
            y<---- < Child(1, 1) / (1, 0) in parents local frame
                 x
                 ^
                 |
            y<----
                 ^
                 Parent(1, 0) / (0, 0) in local frame

            Therefore the global translation should be (1, 1)
        */

        // TODO: Figure out how you are supposed to use the epsilonEquals
        // function provided in the GLM library.
        // Written my own for now
        REQUIRE(engine::epsilonEquals(
            childTranslation,
            glm::vec3(1.0f, 1.0f, 0.0f),
            std::numeric_limits<float>::epsilon()
        ));
    }
}

TEST_CASE("scene objects attached with one parent can be scaled", "[SceneObject]") {
    scene::SceneObject parent;
    scene::SceneObject child;

    glm::vec3 parentScale = glm::vec3(0.5f);
    parent.scale(parentScale);

    glm::mat4 parentMatrix = parent.getModel();

    SECTION("the childs global scale is based on the parents local scale") {
        glm::vec3 childScale = child.getGlobalScale(parentMatrix);
        REQUIRE(childScale == parentScale);
    }

    SECTION("the childs global scale is offset from the parents local scale") {
        glm::vec3 localScale = glm::vec3(0.5f);
        child.scale(localScale);
        glm::vec3 childScale = child.getGlobalScale(parentMatrix);

        REQUIRE(childScale == parentScale * localScale);
    }
}