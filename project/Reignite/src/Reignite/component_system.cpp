#include "component_system.h"

#include <string>
#include <vector>
#include <algorithm>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

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

  struct ComponentSystem::Data {

    ComponentSystemParams params;
  };

  Reignite::ComponentSystem::ComponentSystem(const std::shared_ptr<State> s) {

    data = new Data();

    initialize(s);
  }

  Reignite::ComponentSystem::~ComponentSystem() {
  
    shutdown();

    delete data;
  }

  void Reignite::ComponentSystem::update() {

    u32 size = 1;
    for (u32 i = 0; i < size; ++i)
      UpdateTransformComponent(state->transform_components[i]);

    UpdateCameraComponent(state->camera);

    for (u32 i = 0; i < size; ++i)
      UpdateRenderComponent(state->render_components[i]);

    for (u32 i = 0; i < size; ++i)
      UpdateLightComponent(state->light_components[i]);

  }

  void Reignite::ComponentSystem::initialize(const std::shared_ptr<State> s) {
    
    this->state = s;

    state->entities.entity.push_back(state->entities.entity.size());
    state->entities.parent.push_back(state->entities.parent.size());

    TransformComponent tc;
    tc.position = vec3f(0.0f, 0.0f, 0.0f);
    state->transform_components.push_back(tc);

    RenderComponent rc;
    state->render_components.push_back(rc);

    LightComponent lc;
    lc.is_active = false;
    state->light_components.push_back(lc);
  }

  void Reignite::ComponentSystem::shutdown() {}

}
