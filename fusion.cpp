#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

struct Engine {
    GLFWwindow* window;
    int WIDTH = 800;
    int HEIGHT = 600;

    Engine() {
        // --- Init GLFW ---
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11); // GLEW needs a GLX context; native Wayland breaks glewInit()
        if (!glfwInit()) { cerr << "GLFW init failed\n"; exit(EXIT_FAILURE); }

        // --- Init Window ---
        // Fixed size + floating: tiling WMs (bspwm/i3/sway/Hyprland) auto-float
        // non-resizable windows instead of tiling them, and FLOATING keeps it on top.
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Fusion Reactor Simulation", nullptr, nullptr);
        if (!window) { cerr << "Failed to create GLFW window\n"; glfwTerminate(); exit(EXIT_FAILURE); }

        // --- Center on primary monitor ---
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(window, (mode->width - WIDTH) / 2, (mode->height - HEIGHT) / 2);

        glfwMakeContextCurrent(window);
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // --- Init GLEW ---
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) { cerr << "Failed to initialize GLEW\n"; glfwTerminate(); exit(EXIT_FAILURE); }
    }
};
Engine engine;

int main() {
    cout << "Starting Fusion..." << endl;
    while (!glfwWindowShouldClose(engine.window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }

    glfwDestroyWindow(engine.window);
    glfwTerminate();
    return 0;
}
