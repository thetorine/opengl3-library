#include <cstdio>
#include <memory>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <lodepng.h>

#include "camera.hpp"
#include "utilities.hpp"
#include "engine/shader.hpp"
#include "illumination/lighting.hpp"
#include "illumination/spotlight.hpp"
#include "input/keyboard.hpp"
#include "geometry/mesh.hpp"
#include "geometry/sphere.hpp"
#include "geometry/square.hpp"

#define WIDTH 1280
#define HEIGHT 720

void processCamera(GLFWwindow *window, engine::Camera &cam, float mdx, float mdy, float dt);

int main() {
    glewExperimental = true;
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 16);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "My Title", NULL, NULL);
    if (window == NULL) {
        std::printf("Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::printf("Failed to initialize GLEW\n");
        return -1;
    }

    engine::genVAO();

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
    glfwSetKeyCallback(window, &input::glfwKeyCallback);

    engine::Camera cam(
        glm::vec3(0.0f, 0.0f, -5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 viewMatrix = cam.getViewMatrix();
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 projMatrix = glm::infinitePerspective(
        glm::radians(60.0f),
        static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
        0.1f
    );

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);

    std::vector<unsigned char> image;
    unsigned int width, height;
    unsigned error = lodepng::decode(image, width, height, "res/textures/square.png");
    std::printf("%d %d\n", width, height);

    glActiveTexture(GL_TEXTURE0);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    glGenerateMipmap(GL_TEXTURE_2D);

    geometry::Mesh model("res/models/teapot.obj");

    double lastTime = glfwGetTime();
    double frameTime = lastTime;
    int frameCount = 0;

    glm::mat4 i = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

    engine::Shader::createShader("local");
    engine::Shader::getInstance()->useShader();

    engine::Shader::getInstance()->setProjMatrix(projMatrix);

    std::shared_ptr<illumination::Spotlight> torchLight = 
        std::make_shared<illumination::Spotlight>(
            cam.getPos(), 
            cam.getFacingDir(),
            glm::vec3(1.0),
            1.0f,
            30.0f);
    illumination::Lighting lightingObj;
    lightingObj.addSpotlight(torchLight);
    lightingObj.addDirectionalLight(
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f),
        0.8f
    );

    lightingObj.setMaterialCoeffs(0.5f, 1.0f, 1.0f, 32.0f);
    lightingObj.setMaterialIntensities(glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.3f, 0.0f, 0.0f));

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        frameCount++;
        if (currentTime - frameTime >= 1.0) {
            std::printf("FPS = %d\n", frameCount);
            frameCount = 0;
            frameTime = currentTime;
        }

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);

        processCamera(window, cam, static_cast<float>(mx - WIDTH / 2), static_cast<float>(my - HEIGHT / 2), dt);
        glfwSetCursorPos(window, WIDTH / 2.0, HEIGHT / 2.0);
        if (input::wasPressed(GLFW_KEY_T)) {
            lightingObj.nextShaderType();
        }

        torchLight->setFacingFrom(cam.getPos(), cam.getFacingDir());
        lightingObj.updateShader();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        engine::Shader::getInstance()->setViewMatrix(cam.getViewMatrix());

        model.draw(i);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void processCamera(GLFWwindow *window, engine::Camera &cam, float mdx, float mdy, float dt) {
    if (input::isPressed(GLFW_KEY_W))
        cam.move(engine::FORWARD, dt);
    if (input::isPressed(GLFW_KEY_S))
        cam.move(engine::BACK, dt);
    if (input::isPressed(GLFW_KEY_A))
        cam.move(engine::LEFT, dt);
    if (input::isPressed(GLFW_KEY_D))
        cam.move(engine::RIGHT, dt);
    if (input::isPressed(GLFW_KEY_LEFT_SHIFT))
        cam.move(engine::UP, dt);
    if (input::isPressed(GLFW_KEY_LEFT_CONTROL))
        cam.move(engine::DOWN, dt);
    cam.rotateMouse(mdx * 0.1f, mdy * 0.1f);
}
