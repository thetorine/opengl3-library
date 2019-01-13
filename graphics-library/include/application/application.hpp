#pragma once

#include <memory>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace gl::app {
    class Application {
    public:
        Application(std::string title, int width, int height);
        ~Application();
        void start();
        void destroy();
        virtual void setWindowHints();
        virtual void setInputMode();
        virtual void initialize() = 0;
        virtual void render() = 0;
        virtual void update(float dt) = 0;
        virtual void updateView() = 0;
    protected:
        GLFWwindow * m_window;
        int m_width;
        int m_height;
        std::string m_title;
        bool m_hasExited;
    private:
        void startLoops();
    };
}