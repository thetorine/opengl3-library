#include <vector>

#include "input/events.hpp"

namespace input {
    
    std::vector<std::function<void(int key, int action)>> keyCallbackList;
    std::vector<std::function<void(float dx, float dy)>> mouseCallbackList;

    void registerKeyHandler(std::function<void(int key, int action)> callback) {
        keyCallbackList.push_back(callback);
    }

    void registerCursorMovedHandler(std::function<void(float dx, float dy)> callback) {
        mouseCallbackList.push_back(callback);
    }

    void onKeyPress(int key, int action) {
        auto iter = keyCallbackList.begin();
        while (iter != keyCallbackList.end()) {
            (*iter++)(key, action);
        }
    }

    void onCursorMove(float dx, float dy) {
        auto iter = mouseCallbackList.begin();
        while (iter != mouseCallbackList.end()) {
            (*iter++)(dx, dy);
        }
    }
}