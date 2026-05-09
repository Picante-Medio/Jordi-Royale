#include "EnemySpawnSystem.h"
#include "SpawnPointTag.h"
#include "TransformComponent.h"


void 
EnemySpawnSystem::init() {
    prefabs = std::vector<HUGO::String>();
    bossPrefabs = std::vector<HUGO::String>();

    prefabs.push_back("Enemy");
    //prefabs.push_back("JordiHead");

    prefabs.push_back("Boss");

    rnd.Init();
    spawnTimeWithVariance = spawnTime + static_cast<HUGO::Int>(rnd.randomInRange(-spawnTime * timeVariance, spawnTime * timeVariance));
    actWave = rnd.randomInRange(0, prefabs.size()-1);
    spawners =std::vector<EntityID>();
    for(auto it : scene.query<SpawnPointTag, TransformComponent>()){
        spawners.push_back(it.getConst<SpawnPointTag>().entity);
    }
    
}

void 
EnemySpawnSystem::onLoad() {

}

void 
EnemySpawnSystem::fixedUpdate(uint32_t dt) {

}

void 
EnemySpawnSystem::update(uint32_t dt) {
    ms += dt;
    int i = 0;
    for(auto it : scene.query<SpawnPointTag, TransformComponent>()){
        spawners[i] = it.getConst<SpawnPointTag>().entity;
        i++;
    }

    /*
    if(spawnTimeWithVariance <= ms){
        HUGO::ErrorOrType<EntityID> en = scene.instantiatePrefab(prefabs[actWave]);
        if(en.isError()){
            scene.log(en.getError().description());
        }
        else{
            EntityID enemyID = en.getValue();
            TransformComponent actSpawner = scene.getComponent<TransformComponent>(rnd.randomInRange(0, spawners.size()-1));
            scene.getComponent<TransformComponent>(enemyID).setWorldPosition(HUGO::Vector3(
                rnd.randomWithVariance(actSpawner.getWorldPosition().x, spawnVariance),
                0,
                rnd.randomWithVariance(actSpawner.getWorldPosition().z, spawnVariance)));
        }

    }
        */
}