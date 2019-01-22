#include <glm/gtc/matrix_transform.hpp>

#include "sample.hpp"
#include "engine/shader.hpp"
#include "geometry/sphere.hpp"
#include "illumination/point_light.hpp"
#include "input/events.hpp"
#include "math/constants.hpp"
#include "math/bezier.hpp"
#include "math/revolution.hpp"

Sample::Sample()
    : Application::Application("Test", 1280, 720),
    m_camera(glm::vec3(0.0f, 0.0f, -5.0f),
             glm::vec3(0.0, 0.0f, 0.0f)) {
}

Sample::~Sample() {

}

void Sample::initialize() {
    gl::input::registerKeyHandler(std::bind(&Sample::keyHandler, this,
                                            std::placeholders::_1,
                                            std::placeholders::_2));

    // Tells OpenGL to take into account the z coordinate of the 
    // fragment to ensure that it draws fragments in the correct order. 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set lighting properties
    gl::engine::Shader::createShader("local");
    gl::engine::Shader::getInstance()->useShader();

    // Clip the fragments that are outside of the 60 degrees FOV
    // and the fragments that are closer than 0.1 units. 
    gl::engine::Shader::getInstance()->setProjMatrix(glm::infinitePerspective(
        glm::radians(60.0f),
        static_cast<float>(m_width) / static_cast<float>(m_height),
        0.1f
    ));

    glm::vec3 lightPos(1.0f, 1.0f, 0.0f);
    m_lightPoint = std::make_unique<gl::geometry::Point>(std::vector<float>({ lightPos.x, lightPos.y, lightPos.z }));
    m_lighting.addPointLight(std::make_shared<gl::illumination::PointLight>(
        lightPos,
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

    auto mesh { std::make_shared<gl::geometry::Sphere>(0.5f) };
    m_parentObj = gl::scene::SceneShape::create(mesh);
    m_child1Obj = gl::scene::SceneShape::create(mesh);
    m_child2Obj = gl::scene::SceneShape::create(mesh);
    m_grandchild1Obj = gl::scene::SceneShape::create(mesh);

    m_reparentObj = gl::scene::SceneShape::create(mesh);

    m_child1Obj->setTranslation(glm::vec3(1.5f, 0.0f, 0.0f));
    m_child1Obj->setScale(glm::vec3(0.5f));

    m_child2Obj->setTranslation(glm::vec3(0.0f, 1.5f, 0.0f));

    m_grandchild1Obj->setTranslation(glm::vec3(1.5f, 1.5f, 0.0f));
    m_reparentObj->setTranslation(glm::vec3(-1.5f, -1.5f, 0.0f));
    m_reparentObj->setScale(glm::vec3(0.5f));

    m_parentObj->addChild(m_child1Obj);
    m_parentObj->addChild(m_child2Obj);
    m_parentObj->addChild(m_reparentObj);
    m_child1Obj->addChild(m_grandchild1Obj);

    m_scene.addChild(m_parentObj);

    m_sceneObjects.insert(std::end(m_sceneObjects), { m_parentObj, m_child1Obj, m_child2Obj, m_grandchild1Obj });

    gl::math::Bezier curve(3, std::vector<glm::vec3>({
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.5f, 0.0f),
        glm::vec3(2.5f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.5f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f) }));
    std::vector<float> verticesCurve { gl::math::generateVertices(
        curve.getX(), curve.getY(), std::make_pair<float, float>(0.0f, curve.getT()), false
    ) };
    std::vector<float> verticesMesh { gl::math::generateVertices(
        curve.getX(), curve.getY(), std::make_pair<float, float>(0.0f, curve.getT())
    ) };
    std::vector<float> normals { gl::math::generateNormals(
        curve.getX(), curve.getY(), std::make_pair<float, float>(0.0f, curve.getT())
    ) };
    std::vector<int> indices { gl::math::generateIndices(verticesMesh, std::make_pair<float, float>(0.0f, curve.getT())) };
    m_bezierCurve = std::make_unique<gl::geometry::Curve>(verticesCurve);
    m_bezierMesh = std::make_unique<gl::geometry::Mesh>(verticesMesh, normals, indices);
}

void Sample::render() {
    m_scene.drawScene();
    m_lightPoint->draw();
    m_bezierCurve->draw(glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 5.0f)));
    m_bezierMesh->draw(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 5.0f)));
}

void Sample::update(float dt) {
    m_camera.updatePos(dt);
    m_scene.updateScene(dt);

    static float pi { gl::math::PI };
    static float radius { 1.5f };
    static float rotationSpeed { pi / 2.0f }; // Quarter circle every second

    m_child1Rotation += rotationSpeed * dt;
    m_grandchild1Rotation += 2.0f * rotationSpeed * dt; // Twice as fast as parent

    m_child1Obj->setTranslation(glm::vec3(
        radius * std::cos(m_child1Rotation),
        radius * std::sin(m_child1Rotation),
        m_child1Obj->getTranslation().z
    ));

    m_grandchild1Obj->setTranslation(glm::vec3(
        radius * std::cos(m_grandchild2Rotation),
        radius * std::sin(m_grandchild2Rotation),
        m_grandchild1Obj->getTranslation().z
    ));

    m_parentObj->rotate(glm::vec3(
        pi / 2.0f * dt,
        pi * dt,
        0.0f
    ));
}

void Sample::updateView() {
    m_lighting.updateShader();
    gl::engine::Shader::getInstance()->setViewMatrix(m_camera.getViewMatrix());
}

void Sample::keyHandler(int key, int action) {
    // Exit the window
    if (key == GLFW_KEY_ESCAPE)
        destroy();
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        m_lighting.nextShaderType();
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        size_t sceneSize { m_sceneObjects.size() };
        m_currentParent--;
        if (m_currentParent == -1)
            m_currentParent = static_cast<int>(sceneSize) - 1;
        m_reparentObj->reparent(m_sceneObjects[m_currentParent]);
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        size_t sceneSize { m_sceneObjects.size() };
        m_currentParent = (m_currentParent + 1) % static_cast<int>(sceneSize);
        m_reparentObj->reparent(m_sceneObjects[m_currentParent]);
    }
}