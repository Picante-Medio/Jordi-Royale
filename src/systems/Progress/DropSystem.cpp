#include "DropSystem.h"

#include <memory>

#include "EcsTypes.h"
#include "EnemyDeadMessage.h"
#include "HPComponent.h"
#include "BossTag.h"
#include "HugoMath.h"
#include "TransformComponent.h"
#include "XPComponent.h"

void
DropSystem::init() {
    scene.subscribe<EnemyDeadMessage>([this](std::shared_ptr<HUGO::Message> message){
        std::shared_ptr<EnemyDeadMessage> m = std::static_pointer_cast<EnemyDeadMessage>(message);
        killEnemy(m->enemy);
    });
}

void
DropSystem::update(uint32_t dt) {
    //Rotate spawned xp on update
    for(auto pack : scene.query<XPComponent, TransformComponent>()) {
        pack.modify<TransformComponent>([](TransformComponent& tc){
            tc.rotation *= HUGO::Quaternion(HUGO::Degree(ROTATION_OFFSET), HUGO::Vector3(0, 1, 0));
        });
    }
}

void 
DropSystem::killEnemy(EntityID enemy) {

    const TransformComponent& tr = scene.getComponentConst<TransformComponent>(enemy);

    // If enemy is a boss, spawn a chest
    if(scene.hasComponent<BossTag>(enemy)) {
        spawnChest(tr.position);
    }

    //Otherwise, spawn xp depending on max health
    else {
        const HPComponent& hp = scene.getComponentConst<HPComponent>(enemy);
        spawnXP(tr.position, (hp.HPMax / HP_FOR_SPAWN) + 1);
    }

    // Play audio of dead enemy
    // HELP

    // Kill entity
    scene.removeEntity(enemy);
}

void 
DropSystem::spawnChest(HUGO::Vector3 position) {
    HUGO::ErrorOrType<EntityID> chestPrefab = scene.instantiatePrefab("Chest");

    // If the prefab does not exist, log it to console
    if(chestPrefab.isError()) {
        scene.log(std::make_shared<HUGO::StringError>(chestPrefab.getError()));
        return;
    }

    EntityID chest = chestPrefab.getValue();

    scene.modifyComponent<TransformComponent>(chest, [position](TransformComponent& tr) {
        tr.position = position;
    });
}

void 
DropSystem::spawnXP(HUGO::Vector3 position, int amount) {
    for(int i = 0; i < amount; ++i) {
        HUGO::ErrorOrType<EntityID> xpPrefab = scene.instantiatePrefab("Experience");

        // If the prefab does not exist, log it to console
        if(xpPrefab.isError()) {
            scene.log(std::make_shared<HUGO::StringError>(xpPrefab.getError()));
            return;
        }

        EntityID XP = xpPrefab.getValue();

        scene.modifyComponent<TransformComponent>(XP, [position](TransformComponent& tr) {
            tr.position = position;
        });
    }
}
