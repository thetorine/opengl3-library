#include <cstdio>
#include <thread>

#include "utilities.hpp"
#include "application/application.hpp"
#include "input/keyboard.hpp"

namespace app {

    Application::Application(std::string title, int width, int height) 
        : m_width(width), m_height(height), m_title(title)
    {
    }

    Application::~Application() {

    }

    void Application::start() {
        glewExperimental = true;
        if (!glfwInit()) {
            std::printf("Unable to initialize GLFW");
            exit(-1);
        }

        setWindowHints();

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
        if (m_window == NULL) {
            std::printf("Failed to open GLFW window\n");
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1); // vsync

        if (glewInit() != GLEW_OK) {
            std::printf("Failed to initialize GLEW\n");
            exit(-1);
        }

        engine::genVAO();

        setInputMode();

        initialize();
        startLoops();
    }

    void Application::destroy() {
        m_hasExited = true;
    }

    void Application::setWindowHints() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_SAMPLES, 16);
    }

    void Application::setInputMode() {
        glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetKeyCallback(m_window, &input::glfwKeyCallback);
    }

    void Application::startLoops() {

        double time = glfwGetTime();
        std::thread updateThread([lastTime = time, frameTime = time, frameCount = 0, this]() mutable {
            while (!m_hasExited) {
                double currentTime = glfwGetTime();
                float dt = static_cast<float>(currentTime - lastTime);
                lastTime = currentTime;

                update(dt);
            }
        });

        // TODO: needs synchronization for the keyboard/mouse input, so that the update thread
        // never misses a key press.
        // TODO: fps counter 
        // note: rendering must be done from the main thread
        // this breaks in a separate thread.
        while (!m_hasExited && glfwWindowShouldClose(m_window) == 0) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

            render();

            glfwSetCursorPos(m_window, m_width / 2.0, m_height / 2.0);

            glfwSwapBuffers(m_window); 
            glfwPollEvents(); // only works in main thread - hence need synchcronization
        }

        // this waits until the thread has exited - when destroy is called
        // should not deadlock because it will 
        // only be called once destroy is called which breaks the above loop
        updateThread.join();
    }
}