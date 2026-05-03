#include "EnemySpawnSystem.h"
#include "SpawnPointTag.h"
#include "TransformComponent.h"
#include "HugoError.h"


void 
EnemySpawnSystem::init() {
    prefabs = std::vector<HUGO::String>();
    prefabs.push_back("EvilJordi");
    prefabs.push_back("JordiHead");
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

    if(spawnTimeWithVariance <= ms){
        HUGO::ErrorOrType<EntityID> en = scene.instantiatePrefab(prefabs[actWave]);
        if(en.isError()){
            //mandar error por la consola "este prfab no existe"
        }
        else{
            EntityID enemyID = en.getValue();
            TransformComponent actSpawner = scene.getComponent<TransformComponent>(rnd.randomInRange(0, spawners.size()-1));
            scene.getComponent<TransformComponent>(enemyID).setWorldPosition(HUGO::Vector3(rnd.randomWithVariance(actSpawner.getWorldPosition().x, spawnVariance), 0, rnd.randomWithVariance(actSpawner.getWorldPosition().z, spawnVariance)));
            
        }

    }
}