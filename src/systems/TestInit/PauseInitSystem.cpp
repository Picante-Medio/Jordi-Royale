#include "PauseInitSystem.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ButtonComponent.h"
#include "PanelComponent.h"
#include "ExitTag.h"
#include "ResumeTag.h"

void 
PauseInitSystem::onLoad(){

}

void 
PauseInitSystem::init(){

    // Camera

    EntityID camera = scene.createEntity();

    scene.addComponent<TransformComponent>(camera, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, 0.8, 4));
        trans.setRotation(HUGO::Vector4(0, 0, 0, 1));
        trans.setScale(HUGO::Vector3(1, 1, 1));
    });

    scene.addComponent<CameraComponent>(camera, [](CameraComponent& cam){
        cam.setProjectionType(HUGO::ProjectionType(0));
        cam.setFOVY(60);
        cam.setNearClip(1);
        cam.setFarClip(10000);
        cam.setOrthographicDimensions(10, 10);
        cam.setMain(true);
        cam.setClearColor(HUGO::Vector4(0, 0, 0, 1));
    });

    // Pause

    EntityID pause = scene.createEntity();

    scene.addComponent<PanelComponent>(pause, [](PanelComponent& panel){
        panel.overlayName = "JordiUI/JordiOverlay";
        panel.containerName = panel.overlayName + "/JordiContainer";
        panel.material = "JordiUI/Pause";
        panel.width = 0.5f;
        panel.height = 0.2f;
        panel.left = 0.25f;
        panel.top = 0.3f;
        panel.zOrder = 501;
        panel.isVisible = true;
    });

     // Resume

    EntityID resume = scene.createEntity();

    scene.addComponent<PanelComponent>(resume, [](PanelComponent& panel){
        panel.overlayName = "JordiUI/JordiOverlay2";
        panel.containerName = panel.overlayName + "/JordiContainer2";
        panel.material = "JordiUI/Resume";
        panel.width = 0.25f;
        panel.height = 0.1f;
        panel.left = 0.25f;
        panel.top = 0.6f;
        panel.zOrder = 502;
        panel.isVisible = true;
    });

    scene.addComponent<ButtonComponent>(resume, [this](ButtonComponent& b){
        b.normalMaterial = "JordiUI/Resume";
        b.hoverMaterial = "JordiUI/ResumeHover";
        b.pressedMaterial = "JordiUI/ResumePressed";
    });

    scene.addComponent<ResumeTag>(resume);

     // Exit

    EntityID exit = scene.createEntity();

    scene.addComponent<PanelComponent>(exit, [](PanelComponent& panel){
        panel.overlayName = "JordiUI/JordiOverlay3";
        panel.containerName = panel.overlayName + "/JordiContainer3";
        panel.material = "JordiUI/Exit";
        panel.width = 0.25f;
        panel.height = 0.1f;
        panel.left = 0.5f;
        panel.top = 0.6f;
        panel.zOrder = 503;
        panel.isVisible = true;
    });

    scene.addComponent<ButtonComponent>(exit, [this](ButtonComponent& b){
        b.normalMaterial = "JordiUI/Exit";
        b.hoverMaterial = "JordiUI/ExitHover";
        b.pressedMaterial = "JordiUI/ExitPressed";
    });

    scene.addComponent<ExitTag>(exit);
}

void 
PauseInitSystem::update(uint32_t){
    
}

void 
PauseInitSystem::fixedUpdate(uint32_t){
    
}