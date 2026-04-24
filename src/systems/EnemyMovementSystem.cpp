#include "EnemyMovementSystem.h"
#include "EnemyComponent.h"

void 
EnemyMovementSystem::init() {

}

void 
EnemyMovementSystem::onLoad() {

}

void 
EnemyMovementSystem::fixedUpdate(uint32_t dt) {
    for(auto pack : scene.query<EnemyComponent>()) {

    }
}
