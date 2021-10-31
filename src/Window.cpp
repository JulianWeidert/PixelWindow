
#include <iostream>
#include <glad/gl.h>
#include <PixelWindow/Window.h>

namespace sr {

    void initGlad() {
        if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw - 1;
        }
    }


    namespace internal {

        Glfw::Glfw() {
            if (!glfwInit()) throw - 1;
        }

        Glfw::~Glfw() {
            glfwTerminate();
        }

    }

    const internal::Glfw Window::glfw = internal::Glfw();

    void Window::windowSizeCallback(GLFWwindow* window, int width, int height) {
        Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        for (auto callback : w->windowResizeCallbacks) callback(width, height);
    }

    void Window::windowRefreshCallback(GLFWwindow* window) {
        Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        for (auto callback : w->windowRefreshCallbacks) callback();
    }

    void Window::windowMouseCallback(GLFWwindow* window, int button, int action, int modes) {
        Window* w = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
        for (auto callback : w->windowMouseCallbacks) callback(button, action, modes);
    }

    Window::Window(int width, int height, const char* title) {
        this->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        this->makeCurrent();

        glfwSetWindowUserPointer(this->handle, this);
        glfwSetFramebufferSizeCallback(this->handle, Window::windowSizeCallback);
        glfwSetWindowRefreshCallback(this->handle, Window::windowRefreshCallback);
        glfwSetMouseButtonCallback(this->handle, Window::windowMouseCallback);

        initGlad();
    }

    Window::~Window() {
        glfwDestroyWindow(this->handle);
    }

    Window::Window(Window&& other) noexcept {
        this->windowResizeCallbacks = std::move(other.windowResizeCallbacks);
        this->windowRefreshCallbacks = std::move(other.windowRefreshCallbacks);
        this->handle = other.handle;
        other.handle = nullptr;

        glfwSetWindowUserPointer(this->handle, this);
    }

    Window& Window::operator=(Window&& other) noexcept {
        Window w = Window(std::move(other));
        swap(*this, w);

        glfwSetWindowUserPointer(this->handle, this);
        return *this;
    }

    void swap(Window& w1, Window& w2) {
        using std::swap;

        swap(w1.handle, w2.handle);
        swap(w1.windowMouseCallbacks, w2.windowMouseCallbacks);
        swap(w1.windowRefreshCallbacks, w2.windowRefreshCallbacks);
        swap(w1.windowResizeCallbacks, w2.windowResizeCallbacks);
    }

    bool Window::isActive() const noexcept {
        return !glfwWindowShouldClose(this->handle);
    }

    void Window::pollEvents() const noexcept {
        glfwPollEvents();
    }

    void Window::makeCurrent() const noexcept {
        glfwMakeContextCurrent(this->handle);
    }

    void Window::swapBuffers() const noexcept {
        glfwSwapBuffers(this->handle);
    }

    void Window::addResizeCallback(std::function<void(int, int)> callback) {
        this->windowResizeCallbacks.push_back(callback);
    }

    void Window::addRefreshCallback(std::function<void(void)> callback) {
        this->windowRefreshCallbacks.push_back(callback);
    }

    void Window::addMouseCallback(std::function<void(int, int, int)> callback) {
        this->windowMouseCallbacks.push_back(callback);
    }

}
