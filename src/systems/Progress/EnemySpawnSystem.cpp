#include "EnemySpawnSystem.h"

#include <iostream>
#include <math.h>

#include "ChangeEnemyDensityMessage.h"
#include "EcsTypes.h"
#include "HugoError.h"
#include "HugoTypes.h"
#include "IncreaseEnemyLevelMessage.h"
#include "JordiRandom.h"
#include "SpawnBossMessage.h"
#include "TransformComponent.h"
#include "DamageComponent.h"
#include "HPComponent.h"
#include "PlayerComponent.h"

void EnemySpawnSystem::init() {
    JordiRandom& rng = JordiRandom::Instance();

    prefabs = {
        "Enemy",
    };

    bossPrefabs = {
        "Boss",
    };

    scene.subscribe<IncreaseEnemyLevelMessage>([this](std::shared_ptr<HUGO::Message> message) {
        enemyLevel++; 
    });

    scene.subscribe<SpawnBossMessage>([this, &rng](std::shared_ptr<HUGO::Message> message) {
        // If there is more than one
        // spawnEnemy(bossPrefabs[rng.randomIntInRange(0, bossPrefabs.size())]);
        
        spawnEnemy("Boss");
    });

    scene.subscribe<ChangeEnemyDensityMessage>([this](std::shared_ptr<HUGO::Message> message) {
        std::shared_ptr<ChangeEnemyDensityMessage> m = std::static_pointer_cast<ChangeEnemyDensityMessage>(message);
        spawnTime = m->milisecondsBetweenSpawns;
    });
}


void 
EnemySpawnSystem::onLoad() {
    playerID = scene.query<PlayerComponent>().begin()->getConst<PlayerComponent>().entity;
}

void 
EnemySpawnSystem::update(uint32_t dt) {
    enemySpawnTimer += dt;
    if(enemySpawnTimer >= spawnTime) {
        enemySpawnTimer = 0;
        // If there is more than one
        // spawnEnemy(prefabs[JordiRandom::Instance().randomIntInRange(0, prefabs.size())]);

        spawnEnemy("Enemy");
    }
}

void 
EnemySpawnSystem::spawnEnemy(std::string prefab) {
    std::cout << "Spawning enemy\n";
    HUGO::ErrorOrType<EntityID> enemyPrefab = scene.instantiatePrefab(prefab);

    // Check if prefab exists
    if(enemyPrefab.isError()) 
        return;
    const EntityID enemy = enemyPrefab.getValue();

    // Check if enemy is correctly set up
    if(!scene.hasComponent<TransformComponent>(enemy) 
        || !scene.hasComponent<DamageComponent>(enemy)
        || !scene.hasComponent<HPComponent>(enemy))
    {
        scene.removeEntity(enemy);
        return;
    }

    // Change parameters according to level
    scene.modifyComponent<DamageComponent>(enemy, [this](DamageComponent& dc){
        dc.Damage *= enemyLevel;
    });

    if(enemyLevel > 2) {
        scene.modifyComponent<HPComponent>(enemy, [this](HPComponent& hp){
            hp.HPMax *=  0.5 * enemyLevel;
        });
    }

    scene.modifyComponent<TransformComponent>(enemy, [this](TransformComponent& tc) {
        JordiRandom& rng = JordiRandom::Instance();
        const float angle = rng.randomDoubleInRange(0, 2.f * HUGO::PI);
        const TransformComponent& jordiTransform = scene.getComponentConst<TransformComponent>(playerID);

        tc.position.x = jordiTransform.position.x + std::cos(angle) * spawnRadius;
        tc.position.y = jordiTransform.position.y;
        tc.position.z = jordiTransform.position.z + std::sin(angle) * spawnRadius;
    });
}
