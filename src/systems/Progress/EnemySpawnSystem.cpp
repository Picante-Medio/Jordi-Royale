#include "EnemySpawnSystem.h"
#include "SpawnPointTag.h"
#include "TransformComponent.h"
#include "HugoError.h"
#include "IncreaseEnemyLevelMessage.h"
#include "SpawnBossMessage.h"
#include "ChangeEnemyDensityMessage.h"

void 
EnemySpawnSystem::init() {
    prefabs = std::vector<HUGO::String>();
    bossPrefabs = std::vector<HUGO::String>();

    prefabs.push_back("Enemy");
    //prefabs.push_back("JordiHead");

    bossPrefabs.push_back("Boss");

    rnd.Init();
    spawnTimeWithVariance = spawnTime + static_cast<HUGO::Int>(rnd.randomInRange(-spawnTime * timeVariance, spawnTime * timeVariance));
    actWave = rnd.randomInRange(0, prefabs.size()-1);
    spawners =std::vector<EntityID>();
    for(auto it : scene.query<SpawnPointTag, TransformComponent>()){
        spawners.push_back(it.getConst<SpawnPointTag>().entity);
    }

    scene.subscribe<IncreaseEnemyLevelMessage>([this](std::shared_ptr<HUGO::Message> message){
        enemiesLevel++;
    });

    scene.subscribe<SpawnBossMessage>([this](std::shared_ptr<HUGO::Message> message){
        spawnEnemy(bossPrefabs[actWave]);
    });

    scene.subscribe<ChangeEnemyDensityMessage>([this](std::shared_ptr<HUGO::Message> message){
        std::shared_ptr<ChangeEnemyDensityMessage> m = std::static_pointer_cast<ChangeEnemyDensityMessage>(message);
        spawnTime = m->milisecondsBetweenSpawns;
    });
}

void 
EnemySpawnSystem::onLoad() {

}

void 
EnemySpawnSystem::fixedUpdate(uint32_t) {
}

void 
EnemySpawnSystem::update(uint32_t dt) {

    ms += dt;
    int i = 0;
    for(auto it : scene.query<SpawnPointTag, TransformComponent>()){
        spawners[i] = it.getConst<SpawnPointTag>().entity;
        i++;
    }

    if(spawners.size() > 0 && spawnTimeWithVariance <= ms){
        spawnEnemy(prefabs[actWave]);
        ms = ms - spawnTimeWithVariance;
        spawnTimeWithVariance = spawnTime + static_cast<HUGO::Int>(rnd.randomInRange(-spawnTime * timeVariance, spawnTime * timeVariance));
    }
    
    
}

void
EnemySpawnSystem::spawnEnemy(HUGO::String prefab){
    HUGO::ErrorOrType<EntityID> en = scene.instantiatePrefab(prefab);
    if(en.isError()){
        scene.log(en.getError().description());
    }
    else{
        EntityID enemyID = en.getValue();
        TransformComponent actSpawner = scene.getComponentConst<TransformComponent>(spawners[rnd.randomInRange(0, spawners.size()-1)]);
          
        scene.modifyComponent<TransformComponent>(enemyID, [this, actSpawner](TransformComponent& trans){
            trans.position = HUGO::Vector3(
            rnd.randomDoubleWithVariance(actSpawner.position.x, spawnVariance),
            0.f,
            rnd.randomDoubleWithVariance(actSpawner.position.z, spawnVariance));
        });
    }
      
}
