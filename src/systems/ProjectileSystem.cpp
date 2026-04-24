#include "ProjectileSystem.h"
#include "ProjectileComponent.h"

void ProjectileSystem::init() {

}

void ProjectileSystem::onLoad() {

}

void ProjectileSystem::fixedUpdate(uint32_t dt) {
    for(auto pack : scene.query<ProjectileComponent>()) {
        pack.modify<ProjectileComponent>([dt] (ProjectileComponent& comp) {
            comp.t += dt;
        });
    }
}

void ProjectileSystem::update(uint32_t) {

}