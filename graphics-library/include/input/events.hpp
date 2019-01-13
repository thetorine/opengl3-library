#pragma once

#include <functional>

namespace gl::input {
    void registerKeyHandler(std::function<void(int key, int action)> callback);
    void registerCursorMovedHandler(std::function<void(float dx, float dy)> callback);
    void onKeyPress(int key, int action);
    void onCursorMove(float dx, float dy);
}