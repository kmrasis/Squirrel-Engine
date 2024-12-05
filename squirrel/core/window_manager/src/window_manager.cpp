#include "window_manager.h"
#include "window_property.h"
#include "log-impl.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

/**
 *  Squirrel Engine at this stage supports only single window
 */

namespace Squirrel
{
    WindowManager::WindowManager() = default;
    WindowManager::~WindowManager() = default;

    void WindowManager::Init()
    {
        if (!glfwInit())
        {
            CONSOLE_ERROR("Failed to initialise Window Manager!");
        }
        else
        {
            CONSOLE_INFO("Window Manager initialised successfully");
            is_initialised_ = true;
        }
    }

    void WindowManager::DeInit()
    {
        if (window_)
        {
            CloseWindow();
        }
        glfwTerminate();
        CONSOLE_INFO("Window Manager deinitialised successfully");
    }

    bool WindowManager::CreateWindow(WindowProperty &props)
    {
        if (!is_initialised_)
        {
            CONSOLE_ERROR("Failed to Create Window : Window Manager not initialised!");
            return false;
        }

        window_ = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        CONSOLE_INFO("Window created successfully with Title : {}", props.Title);

        glfwMakeContextCurrent(window_);
        glfwSetWindowUserPointer(window_, &props);
        SetVSync(true);
        return true;
    }

    void WindowManager::SetVSync(const bool &enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
    }

    void WindowManager::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(window_);
    }

    void WindowManager::CloseWindow()
    {
        glfwDestroyWindow(window_);
        window_ = nullptr;
        CONSOLE_INFO("Window closed successfully");
    }

} // namespace Squirrel
