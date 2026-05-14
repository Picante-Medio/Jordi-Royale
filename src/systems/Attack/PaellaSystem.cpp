#include "PaellaSystem.h"

#include <math.h>
#include <memory>

#include "EcsTypes.h"
#include "HugoError.h"
#include "HugoMath.h"
#include "HugoTypes.h"
#include "Message.h"
#include "PaellaPivotTag.h"
#include "ParentComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ActivatePaellaMessage.h"

void
PaellaSystem::init() {

    scene.subscribe<ActivatePaellaMessage>([this](std::shared_ptr<HUGO::Message> m){
        scene.modifyComponent<RenderComponent>(paellas[0], [](RenderComponent& rc) {
            rc.visible = true;
        });

        active = true;
    });
}

void
PaellaSystem::onLoad() {
    pivot = scene.query<PaellaPivotTag>().begin()->getConst<PaellaPivotTag>().entity;


    const float radius = 1.0f;
    const float angleStep = 2.0f * HUGO::PI / float(MAX_PAELLA);

    for(int i = 0; i < MAX_PAELLA; ++i) {
        // Instantiate paella
        HUGO::ErrorOrType<EntityID> paella = scene.instantiatePrefab("Paella");
        if(paella.isError()) 
            return;

        // Set parent to pivot
        EntityID paellaEntity = paella.getValue();
        scene.addComponent<ParentComponent>(paellaEntity, [this](ParentComponent& pc) {
            pc.parent = pivot;
        });

        // Set relative position according to pivot
        const float angle = i * angleStep;

        const float x = std::cos(angle) * radius;
        const float z = std::sin(angle) * radius;

        scene.addComponent<TransformComponent>(paellaEntity, [x, z](TransformComponent& transform) {
            transform.position = HUGO::Vector3(x, 0.0f, z);
        });

        // Set visible to false
        scene.modifyComponent<RenderComponent>(paellaEntity, [](RenderComponent& rc) {
            rc.visible = false;
        });

        paellas[i] = paellaEntity;
    }
}

void 
PaellaSystem::update(uint32_t dt) {
    if(!active) return;

    for(auto pack : scene.query<PaellaPivotTag, TransformComponent>()) {
        pack.modify<TransformComponent>([](TransformComponent& tr) {
            tr.rotation *= HUGO::Quaternion(HUGO::Degree(5.f), HUGO::Vector3(0.f, 1.f, 0.f));
        });
    }
}

void 
PaellaSystem::fixedUpdate(uint32_t dt) {

}
