#include <glm/gtc/matrix_transform.hpp>

#include "application/geometry_test.hpp"
#include "engine/shader.hpp"
#include "illumination/directional_light.hpp"
#include "input/events.hpp"

namespace gl::app {

    GeometryTest::GeometryTest()
        : Application::Application("Test", 1280, 720),
        m_camera(glm::vec3(0.0f, 0.0f, -5.0f),
                 glm::vec3(0.0, 0.0f, 0.0f)) {
    }

    GeometryTest::~GeometryTest() {

    }

    void GeometryTest::initialize() {
        input::registerKeyHandler(std::bind(&GeometryTest::keyHandler, this,
                                            std::placeholders::_1,
                                            std::placeholders::_2));

        // Tells OpenGL to take into account the z coordinate of the 
        // fragment to ensure that it draws fragments in the correct order. 
        glEnable(GL_DEPTH_TEST);

        // Set lighting properties
        engine::Shader::createShader("local");
        engine::Shader::getInstance()->useShader();

        // Clip the fragments that are outside of the 60 degrees FOV
        // and the fragments that are closer than 0.1 units. 
        engine::Shader::getInstance()->setProjMatrix(glm::infinitePerspective(
            glm::radians(60.0f),
            static_cast<float>(m_width) / static_cast<float>(m_height),
            0.1f
        ));

        m_lighting.addDirectionalLight(std::make_shared<illumination::DirectionalLight>(
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(1.0f),
            1.0f)
        );
        // How much of ambient/diffuse/specular light does the material reflect. 
        m_lighting.setMaterialCoeffs(0.5f, 1.0f, 1.0f, 32.0f);
        // How much of each color does the material reflect for ambient and diffuse. 
        // No specular light, because specular light is typically white.
        m_lighting.setMaterialIntensities(
            glm::vec3(0.3f, 0.0f, 0.0f),
            glm::vec3(0.3f, 0.0f, 0.0f)
        );

        m_geomLine = std::make_unique<geometry::Line>(glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
        m_geomPoint = std::make_unique<geometry::Point>(glm::vec3());
        m_geomSphere = std::make_unique<geometry::Sphere>(1.0f);
        m_geomSquare = std::make_unique<geometry::Square>();
    }

    void GeometryTest::render() {
        m_geomLine->draw();
        m_geomPoint->draw();
        m_geomSphere->draw(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f)));
        m_geomSquare->draw(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f)));
    }

    void GeometryTest::update(float dt) {
        m_camera.updatePos(dt);
    }

    void GeometryTest::updateView() {
        m_lighting.updateShader();
        engine::Shader::getInstance()->setViewMatrix(m_camera.getViewMatrix());
    }

    void GeometryTest::keyHandler(int key, int action) {
        // Exit the window
        if (key == GLFW_KEY_ESCAPE)
            destroy();
        if (key == GLFW_KEY_T && action == GLFW_PRESS)
            m_lighting.nextShaderType();
    }
}