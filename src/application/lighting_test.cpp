#include <glm/gtc/matrix_transform.hpp>

#include "application/lighting_test.hpp"
#include "engine/shader.hpp"
#include "input/events.hpp"

namespace app {

    LightingTest::LightingTest()
        : Application::Application("Test", 1280, 720),
        m_camera(engine::Camera(
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        ))
    {
    }

    LightingTest::~LightingTest() {

    }

    void LightingTest::initialize() {
        input::registerKeyHandler(std::bind(&LightingTest::keyHandler, this, 
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

        m_lighting.addDirectionalLight(
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f),
            1.0f
        );
        // How much of ambient/diffuse/specular light does the material reflect. 
        m_lighting.setMaterialCoeffs(0.5f, 1.0f, 1.0f, 32.0f);
        // How much of each color does the material reflect for ambient and diffuse. 
        // No specular light, because specular light is typically white.
        // TODO: Add the ability to change the specular light color. 
        m_lighting.setMaterialIntensities(
            glm::vec3(0.3f, 0.0f, 0.0f), 
            glm::vec3(0.3f, 0.0f, 0.0f)
        );

        m_model = std::make_unique<geometry::Mesh>("res/models/teapot.obj");
    }

    void LightingTest::render() {
        m_model->draw(glm::mat4(1.0f));
    }

    void LightingTest::update(float dt) {
        m_camera.updatePos(dt);
    }

    void LightingTest::updateView() {
        m_lighting.updateShader();
        engine::Shader::getInstance()->setViewMatrix(m_camera.getViewMatrix());
    }

    void LightingTest::keyHandler(int key, int action) {
        // Exit the window
        if (key == GLFW_KEY_ESCAPE)
            destroy();
        if (key == GLFW_KEY_T && action == GLFW_PRESS)
            m_lighting.nextShaderType();
    }
}