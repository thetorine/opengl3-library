#include <limits>

#include <catch.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "math/constants.hpp"
#include "math/epsilon.hpp"
#include "math/matrix.hpp"
#include "scene/scene.hpp"
#include "scene/scene_object.hpp"

const float FLOAT_EPSILON { 1.0e-5f };

TEST_CASE("Scene Tree Storage", "[SceneTree]") {
    gl::scene::Scene sceneRoot;

    SECTION("Scene tree with no parents") {
        REQUIRE(sceneRoot.getTreeSize() == 0);
    }

    SECTION("Scene tree with one parent") {
        auto parent { gl::scene::SceneObject::create() };
        sceneRoot.addChild(parent);

        REQUIRE(sceneRoot.getTreeSize() == 1);
    }

    SECTION("Scene tree with one parent and child") {
        auto parent { gl::scene::SceneObject::create() };
        auto child { gl::scene::SceneObject::create() };

        parent->addChild(child);
        sceneRoot.addChild(parent);

        REQUIRE(sceneRoot.getTreeSize() == 2);
        REQUIRE(child->getParent() == parent);
    }

    SECTION("Scene tree with one parent, child and grandchild") {
        auto parent { gl::scene::SceneObject::create() };
        auto child { gl::scene::SceneObject::create() };
        auto grandchild { gl::scene::SceneObject::create() };

        parent->addChild(child);
        child->addChild(grandchild);
        sceneRoot.addChild(parent);

        REQUIRE(sceneRoot.getTreeSize() == 3);
        REQUIRE(child->getParent() == parent);
        REQUIRE(grandchild->getParent() == child);
    }

    SECTION("Scene tree with one parent, two children and one child having a grandchild") {
        auto parent { gl::scene::SceneObject::create() };
        auto child1 { gl::scene::SceneObject::create() };
        auto child2 { gl::scene::SceneObject::create() };
        auto grandchild { gl::scene::SceneObject::create() };

        parent->addChild(child1);
        parent->addChild(child2);
        child1->addChild(grandchild);
        sceneRoot.addChild(parent);

        REQUIRE(sceneRoot.getTreeSize() == 4);
        REQUIRE(child1->getParent() == parent);
        REQUIRE(child2->getParent() == parent);
        REQUIRE(grandchild->getParent() == child1);
    }

    SECTION("Scene tree as a linked list") {
        // The structure of the scene tree at the end of the test should be:
        /*
            Object -> Object -> Object -> ... -> Object
        */
        int childCount { 100 };

        auto parent { gl::scene::SceneObject::create() };
        sceneRoot.addChild(parent);

        for (int i { 0 }; i < childCount; i++) {
            auto child { gl::scene::SceneObject::create() };
            parent->addChild(child);
            parent = child;
        }

        REQUIRE(sceneRoot.getTreeSize() == childCount + 1);
    }

    // TODO: parent->addChild(nullptr) is invalid
    // Currently results in a segfault.
    // Should use precondition?
    SECTION("Add a null child") {
    }

    // TODO: Should not be able to do parent->addChild(parent)
    // Is this is a runtime exception?
    // Or a precondition?
    SECTION("Disconnected tree") {
    }
}

TEST_CASE("Transformations", "[SceneTree]") {
    auto parent { gl::scene::SceneObject::create() };
    auto child { gl::scene::SceneObject::create() };
    auto grandchild { gl::scene::SceneObject::create() };

    parent->addChild(child);
    child->addChild(grandchild);

    SECTION("Translations") {
        SECTION("No translation") {
            glm::vec3 parentTranslation { gl::math::getTranslationFromMat4(parent->getGlobalModel()) };
            glm::vec3 childTranslation { gl::math::getTranslationFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildTranslation { gl::math::getTranslationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentTranslation, glm::vec3(0.0f), FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childTranslation, glm::vec3(0.0f), FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildTranslation, glm::vec3(0.0f), FLOAT_EPSILON));
        }

        SECTION("Parent translated") {
            glm::vec3 dt(1.0f, 0.0f, 0.0f);
            parent->translate(dt);

            glm::vec3 parentTranslation { gl::math::getTranslationFromMat4(parent->getGlobalModel()) };
            glm::vec3 childTranslation { gl::math::getTranslationFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildTranslation { gl::math::getTranslationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentTranslation, dt, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childTranslation, dt, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildTranslation, dt, FLOAT_EPSILON));
        }

        SECTION("Parent and child translated") {
            glm::vec3 dt(1.0f, 0.0f, 0.0f);
            parent->translate(dt);
            child->translate(dt);

            glm::vec3 parentTranslation { gl::math::getTranslationFromMat4(parent->getGlobalModel()) };
            glm::vec3 childTranslation { gl::math::getTranslationFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildTranslation { gl::math::getTranslationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentTranslation, dt, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childTranslation, dt * 2.0f, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildTranslation, dt * 2.0f, FLOAT_EPSILON));
        }

        SECTION("Parent, child and grandchild translated") {
            glm::vec3 dt(1.0f, 0.0f, 0.0f);
            parent->translate(dt);
            child->translate(dt);
            grandchild->translate(dt);

            glm::vec3 parentTranslation { gl::math::getTranslationFromMat4(parent->getGlobalModel()) };
            glm::vec3 childTranslation { gl::math::getTranslationFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildTranslation { gl::math::getTranslationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentTranslation, dt, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childTranslation, dt * 2.0f, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildTranslation, dt * 3.0f, FLOAT_EPSILON));
        }
    }

    SECTION("Rotations") {
        SECTION("No rotation") {
            glm::quat parentRotation = { gl::math::getRotationFromMat4(parent->getGlobalModel()) };
            glm::quat childRotation = { gl::math::getRotationFromMat4(child->getGlobalModel()) };
            glm::quat grandchildRotation = { gl::math::getRotationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentRotation, glm::quat(glm::vec3(0.0f)), FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childRotation, glm::quat(glm::vec3(0.0f)), FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildRotation, glm::quat(glm::vec3(0.0f)), FLOAT_EPSILON));
        }

        SECTION("Parent rotated") {
            glm::vec3 dr(gl::math::PI / 3.0f, 0.0f, 0.0f);
            parent->rotate(dr);

            glm::quat qDr = glm::angleAxis(gl::math::PI / 3.0f, glm::vec3(1.0f, 0.0f, 0.0f));

            glm::quat parentRotation = { gl::math::getRotationFromMat4(parent->getGlobalModel()) };
            glm::quat childRotation = { gl::math::getRotationFromMat4(child->getGlobalModel()) };
            glm::quat grandchildRotation = { gl::math::getRotationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentRotation, qDr, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childRotation, qDr, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildRotation, qDr, FLOAT_EPSILON));
        }

        SECTION("Parent and child rotated") {
            glm::vec3 dr(gl::math::PI / 3.0f, 0.0f, 0.0f);
            parent->rotate(dr);
            child->rotate(dr);

            glm::quat qDr = glm::angleAxis(gl::math::PI / 3.0f, glm::vec3(1.0f, 0.0f, 0.0f));

            glm::quat parentRotation = { gl::math::getRotationFromMat4(parent->getGlobalModel()) };
            glm::quat childRotation = { gl::math::getRotationFromMat4(child->getGlobalModel()) };
            glm::quat grandchildRotation = { gl::math::getRotationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentRotation, qDr, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childRotation, qDr * qDr, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildRotation, qDr * qDr, FLOAT_EPSILON));
        }

        SECTION("Parent, child and grandchild rotated") {
            glm::vec3 dr(gl::math::PI / 2.0f, 0.0f, 0.0f);
            parent->rotate(dr);
            child->rotate(dr);
            grandchild->rotate(dr);

            glm::quat qDr = glm::angleAxis(gl::math::PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

            glm::quat parentRotation = { gl::math::getRotationFromMat4(parent->getGlobalModel()) };
            glm::quat childRotation = { gl::math::getRotationFromMat4(child->getGlobalModel()) };
            glm::quat grandchildRotation = { gl::math::getRotationFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentRotation, qDr, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childRotation, qDr * qDr, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildRotation, qDr * qDr * qDr, FLOAT_EPSILON));
        }
    }

    SECTION("Scaling") {
        SECTION("No scaling") {
            glm::vec3 parentScale { gl::math::getScaleFromMat4(parent->getGlobalModel()) };
            glm::vec3 childScale { gl::math::getScaleFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildScale { gl::math::getScaleFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentScale, glm::vec3(1.0f), FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childScale, glm::vec3(1.0f), FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildScale, glm::vec3(1.0f), FLOAT_EPSILON));
        }

        SECTION("Parent scaled") {
            glm::vec3 ds(0.5f);
            parent->scale(ds);

            glm::vec3 parentScale { gl::math::getScaleFromMat4(parent->getGlobalModel()) };
            glm::vec3 childScale { gl::math::getScaleFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildScale { gl::math::getScaleFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentScale, ds, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childScale, ds, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildScale, ds, FLOAT_EPSILON));
        }

        SECTION("Parent and child scaled") {
            glm::vec3 ds(0.5f);
            parent->scale(ds);
            child->scale(ds);

            glm::vec3 parentScale { gl::math::getScaleFromMat4(parent->getGlobalModel()) };
            glm::vec3 childScale { gl::math::getScaleFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildScale { gl::math::getScaleFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentScale, ds, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childScale, ds * ds, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildScale, ds * ds, FLOAT_EPSILON));
        }

        SECTION("Parent, child and grandchild scaled") {
            glm::vec3 ds(0.5f);
            parent->scale(ds);
            child->scale(ds);
            grandchild->scale(ds);

            glm::vec3 parentScale { gl::math::getScaleFromMat4(parent->getGlobalModel()) };
            glm::vec3 childScale { gl::math::getScaleFromMat4(child->getGlobalModel()) };
            glm::vec3 grandchildScale { gl::math::getScaleFromMat4(grandchild->getGlobalModel()) };

            REQUIRE(gl::math::epsilonEquals(parentScale, ds, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(childScale, ds * ds, FLOAT_EPSILON));
            REQUIRE(gl::math::epsilonEquals(grandchildScale, ds * ds * ds, FLOAT_EPSILON));
        }
    }
}

TEST_CASE("Complete transformation", "[SceneTree]") {
    auto parent { gl::scene::SceneObject::create() };

    glm::vec3 dt(1.0f, 0.0f, 0.0f);
    glm::vec3 dr(gl::math::PI / 2.0f, 0.0f, 0.0f);
    glm::vec3 ds(0.5f);

    parent->translate(dt);
    parent->rotate(dr);
    parent->scale(ds);

    SECTION("Decomposition of global transformation matrix") {
        glm::vec3 globalTranslation;
        glm::quat globalRotation;
        glm::vec3 globalScale;

        gl::math::decomposeMat4(parent->getGlobalModel(),
                                globalTranslation,
                                globalRotation,
                                globalScale);

        glm::quat quatDr { glm::angleAxis(gl::math::PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f)) };

        REQUIRE(gl::math::epsilonEquals(dt, globalTranslation, FLOAT_EPSILON));
        REQUIRE(gl::math::epsilonEquals(quatDr, globalRotation, FLOAT_EPSILON));
        REQUIRE(gl::math::epsilonEquals(ds, globalScale, FLOAT_EPSILON));
    }

    SECTION("Decomposition of child global transformation matrix") {
        auto child { gl::scene::SceneObject::create() };
        parent->addChild(child);

        glm::vec3 cDt(1.0f, 0.0f, 0.0f);
        glm::vec3 cDr(gl::math::PI / 2.0f, 0.0f, 0.0f);
        glm::vec3 cDs(0.5f);

        child->translate(cDt);
        child->rotate(cDr);
        child->scale(cDs);

        // Calculating the childs global transformation matrix:
        /*
            Parents global transformation matrix:
                = Local Translation Matrix * Local Rotation Matrix * Local Scale Matrix

                = |1.00  0.00  0.00  1.00|   |1.00  0.00  0.00  0.00|   |0.50  0.00  0.00  0.00|
                  |0.00  1.00  0.00  0.00| * |0.00  0.00 -1.00  0.00| * |0.00  0.50  0.00  0.00|
                  |0.00  0.00  1.00  0.00|   |0.00  1.00  0.00  0.00|   |0.00  0.00  0.50  0.00|
                  |0.00  0.00  0.00  1.00|   |0.00  0.00  0.00  1.00|   |0.00  0.00  0.00  1.00|

                = |0.50  0.00  0.00  1.00|
                  |0.00  0.00 -0.50  0.00|
                  |0.00  0.50  0.00  0.00|
                  |0.00  0.00  0.00  1.00|

            Childs local transformation matrix:
                = Local Translation Matrix * Local Rotation Matrix * Local Scale Matrix

                = |1.00  0.00  0.00  1.00|   |1.00  0.00  0.00  0.00|   |0.50  0.00  0.00  0.00|
                  |0.00  1.00  0.00  0.00| * |0.00  0.00 -1.00  0.00| * |0.00  0.50  0.00  0.00|
                  |0.00  0.00  1.00  0.00|   |0.00  1.00  0.00  0.00|   |0.00  0.00  0.50  0.00|
                  |0.00  0.00  0.00  1.00|   |0.00  0.00  0.00  1.00|   |0.00  0.00  0.00  1.00|

                = |0.50  0.00  0.00  1.00|
                  |0.00  0.00 -0.50  0.00|
                  |0.00  0.50  0.00  0.00|
                  |0.00  0.00  0.00  1.00|

            Childs global transformation matrix:
                = Childs local transformation matrix * Parents global transformation matrix:

                = |0.50  0.00  0.00  1.00|   |0.50  0.00  0.00  1.00|
                  |0.00  0.00 -0.50  0.00| * |0.00  0.00 -0.50  0.00|
                  |0.00  0.50  0.00  0.00|   |0.00  0.50  0.00  0.00|
                  |0.00  0.00  0.00  1.00|   |0.00  0.00  0.00  1.00|

                = |0.25  0.00  0.00  1.50|
                  |0.00 -0.25  0.00  0.00|
                  |0.00  0.00 -0.25  0.00|
                  |0.00  0.00  0.00  1.00|
        */

        glm::mat4 result(
            glm::vec4(0.25f, 0.0f, 0.0f, 0.0f),
            glm::vec4(0.0f, -0.25f, 0.0f, 0.0f),
            glm::vec4(0.0f, 0.0f, -0.25f, 0.0f),
            glm::vec4(1.5f, 0.0f, 0.0f, 1.0f));

        REQUIRE(gl::math::epsilonEquals(result, child->getGlobalModel(), FLOAT_EPSILON));
    }
}

TEST_CASE("Reparenting", "[SceneTree]") {
    auto parent { gl::scene::SceneObject::create() };

    SECTION("Remove child") {
        // Perhaps this should raise a runtime exception
        SECTION("Remove a null object") {
            auto child { gl::scene::SceneObject::create() };
            parent->addChild(child);
            parent->removeChild(nullptr);

            REQUIRE(parent->getSize() == 2);
        }

        SECTION("Remove a object that is not connected to the parent") {
            auto child { gl::scene::SceneObject::create() };
            parent->removeChild(child);

            REQUIRE(parent->getSize() == 1);
        }

        SECTION("Only one child") {
            auto child { gl::scene::SceneObject::create() };
            parent->addChild(child);
            parent->removeChild(child);

            REQUIRE(parent->getSize() == 1);
        }

        SECTION("Multiple children") {
            auto mainChild { gl::scene::SceneObject::create() };
            auto otherChild1 { gl::scene::SceneObject::create() };
            auto otherChild2 { gl::scene::SceneObject::create() };
            auto otherChild3 { gl::scene::SceneObject::create() };

            parent->addChild(mainChild);
            parent->addChild(otherChild1);
            parent->addChild(otherChild2);
            parent->addChild(otherChild3);

            parent->removeChild(mainChild);

            REQUIRE(parent->getSize() == 4);
        }
    }

    SECTION("Reparent") {
        auto parent { gl::scene::SceneObject::create() };

        SECTION("Reparent a child to another child") {
            auto child1 { gl::scene::SceneObject::create() };
            auto child2 { gl::scene::SceneObject::create() };

            parent->addChild(child1);
            parent->addChild(child2);

            child2->reparent(child1);

            REQUIRE(parent->getSize() == 3);
            REQUIRE(child1->getParent() == parent);
            REQUIRE(child2->getParent() == child1);
        }

        SECTION("Reparent a child with grandchildren") {
            auto child1 { gl::scene::SceneObject::create() };
            auto child2 { gl::scene::SceneObject::create() };
            auto grandchild { gl::scene::SceneObject::create() };

            parent->addChild(child1);
            parent->addChild(child2);
            child1->addChild(grandchild);

            child1->reparent(child2);

            REQUIRE(parent->getSize() == 4);
            REQUIRE(child1->getParent() == child2);
            REQUIRE(child2->getParent() == parent);
            REQUIRE(grandchild->getParent() == child1);
        }

        SECTION("The global transformation matrix does not change") {
            auto child1 { gl::scene::SceneObject::create() };
            auto child2 { gl::scene::SceneObject::create() };

            parent->translate(glm::vec3(1.0f, 0.0f, 0.0f));
            parent->rotate(glm::vec3(gl::math::PI / 2.0f, 0.0f, 0.0f));
            parent->scale(glm::vec3(0.5f, 0.0f, 0.0f));

            child1->rotate(glm::vec3(gl::math::PI / 3.0f, 0.0f, 0.0f));
            child2->translate(glm::vec3(-1.0f, 0.0f, 0.0f));

            parent->addChild(child1);
            parent->addChild(child2);

            glm::mat4 originalGlobal { child1->getGlobalModel() };

            child1->reparent(child2);

            glm::mat4 newGlobal { child1->getGlobalModel() };

            REQUIRE(gl::math::epsilonEquals(originalGlobal, newGlobal, FLOAT_EPSILON));
        }
    }
}