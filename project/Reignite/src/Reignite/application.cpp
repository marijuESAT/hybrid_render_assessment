#include "application.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "window.h"
#include "component_system.h"
#include "render_context.h"

#include "Components/transform_component.h"
#include "Components/render_component.h"
#include "Components/light_component.h"
#include "Components/camera_component.h"


namespace Reignite {

  struct State {

    std::string title;
    u16 width;
    u16 height;

    GLFWwindow* window;

    struct Entity {
      std::vector<s32> entity;
      std::vector<s32> parent;
    } entities;

    CameraComponent camera;
    std::vector<TransformComponent> transform_components;
    std::vector<RenderComponent> render_components;
    std::vector<LightComponent> light_components;

    State(const std::string& t = "Reignite Render",
      u16 w = 1280, u16 h = 720) : title(t), width(w), height(h) {}
  };

  Application::Application() {

    initialize();
  }

  Application::~Application() {

    shutdown();
  }

  void Application::Run() {

    while (!window->closeWindow() && is_running) {

      window->update();

      component_system->update();

      render_context->setRenderInfo();
      render_context->draw();
    }
  }

  void Application::initialize() {

    state = std::shared_ptr<State>(new State());

    window = std::unique_ptr<Window>(Window::Create(state));
    component_system = std::unique_ptr<ComponentSystem>(new ComponentSystem(state));
    render_context = std::unique_ptr<RenderContext>(new RenderContext(state));

    render_context->submitDisplayList();

    is_running = true;
  }

  void Application::shutdown() {

    is_running = false;
  }

}




