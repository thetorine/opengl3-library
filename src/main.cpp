#include <stdio.h>
#include <string.h>

#include <memory>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <lodepng.h>

#include "camera.hpp"
#include "engine/shader.hpp"
#include "illumination/lighting.hpp"
#include "geometry/mesh.hpp"
#include "geometry/sphere.hpp"
#include "utilities.hpp"

#define WIDTH 1280
#define HEIGHT 720

void processCamera(GLFWwindow *window, engine::Camera &cam, float mdx, float mdy, float dt);

bool shader = false;

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
        printf("Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    engine::genVAO();

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);

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
    printf("%d %d\n", width, height);

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

    //mesh model("res/models/teapot.obj");
    geometry::Sphere model(1.0f);

    double lastTime = glfwGetTime();
    double frameTime = lastTime;
    int frameCount = 0;

    glm::mat4 i = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

    engine::Shader::createShader("local");
    engine::Shader::getInstance()->useShader();

    illumination::Lighting lightingObj;
    //lightingObj.addPointLight(glm::vec3(5, 3, -5), glm::vec3(1.0f), 1.0f);
    //lightingObj.addPointLight(glm::vec3(-5, -3, 5), glm::vec3(1.0f), 1.0f);
    lightingObj.addDirectionalLight(glm::vec3(1, 0, 0), glm::vec3(1.0f), 1.0f);
    lightingObj.addDirectionalLight(glm::vec3(-1, 1, 0), glm::vec3(1.0f), 1.0f);

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        frameCount++;
        if (currentTime - frameTime >= 1.0) {
            printf("FPS = %d\n", frameCount);
            frameCount = 0;
            frameTime = currentTime;
        }

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);

        processCamera(window, cam, static_cast<float>(mx - WIDTH / 2), static_cast<float>(my - HEIGHT / 2), dt);
        glfwSetCursorPos(window, WIDTH / 2.0, HEIGHT / 2.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        engine::Shader::getInstance()->setViewMatrix(cam.getViewMatrix());
        engine::Shader::getInstance()->setProjMatrix(projMatrix);

        lightingObj.setMaterialCoeffs(0.5f, 1.0f, 1.0f, 32.0f);
        lightingObj.setMaterialIntensities(glm::vec3(0.3f, 0.0f, 0.0f), glm::vec3(0.3f, 0.0f, 0.0f));
        lightingObj.setShaderType(shader);
        lightingObj.updateShader();

        model.draw(i);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void processCamera(GLFWwindow *window, engine::Camera &cam, float mdx, float mdy, float dt) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.move(engine::FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.move(engine::BACK, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.move(engine::LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.move(engine::RIGHT, dt);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cam.move(engine::UP, dt);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cam.move(engine::DOWN, dt);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        shader = !shader;
    cam.rotateMouse(mdx * 0.1f, mdy * 0.1f);
}
