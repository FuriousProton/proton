//
// Created by teeebor on 2017-11-18.
//

#include "DemoComponent.h"
#include "../../../include/component/Transform.h"
#include "../../../lib/imgui/imgui.h"

void proton::DemoComponent::start() {
    Component::start();
}

void proton::DemoComponent::update() {
    ImGui::Begin(
            "Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::End();
    
    mpEntity->transform().rotate(glm::vec3(0,.0005f,0));
    Component::update();
}

void proton::DemoComponent::end() {
    Component::end();
}
