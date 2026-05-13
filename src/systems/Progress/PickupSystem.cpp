#include "PickupSystem.h"
#include "HPComponent.h"
#include "HealPlayerMessage.h"
#include "PickableComponent.h"
#include "TransformComponent.h"
#include "XPComponent.h"
#include "PlayerComponent.h"
#include "XPGrabMessage.h"
#include "ChestGrabMessage.h"

void
PickupSystem::update(uint32_t dt) {
    for(auto& player : scene.query<PlayerComponent, TransformComponent>()){
        const PlayerComponent& playerComp = player.getConst<PlayerComponent>();
        const TransformComponent& playerTrans = player.getConst<TransformComponent>();

        for(auto& pickable : scene.query<PickableComponent, TransformComponent>()){
            const TransformComponent& pickabeTransform = pickable.getConst<TransformComponent>();
            const PickableComponent& pickableComp = pickable.getConst<PickableComponent>();

            // XP Pickups
            if(pickup(playerTrans, pickabeTransform, playerComp.xpPickupRange + pickableComp.pickupRadius)) {
                if(scene.hasComponent<XPComponent>(pickableComp.entity)) {
                    // Pickup in the form of a message
                    XPGrabMessage message;
                    message.xp = scene.getComponentConst<XPComponent>(pickableComp.entity).experience;

                    scene.sendMessage(message);

                    // TODO Animation of experience moving towards player may be added (optional)
                }

                // Health pickups
                else if(scene.hasComponent<HPComponent>(pickableComp.entity)) {
                    HealPlayerMessage message;
                    message.healPoints = scene.getComponentConst<HPComponent>(pickableComp.entity).HPMax;
                    scene.sendMessage(message);

                }

                // Chest pickups
                else {
                    ChestGrabMessage message;
                    // TODO Add info to message
                    scene.sendMessage(message);
                }

                // Killed the grabbed entity
                scene.removeEntity(pickabeTransform.entity);
            }
        }
    }
}

bool
PickupSystem::pickup(const TransformComponent& playerTransform, const TransformComponent& pickupTransform, float pickupRange) {
    HUGO::Vector3 distance = pickupTransform.position - playerTransform.position;
    float distanceModule = distance.length();

    return distanceModule < pickupRange;
}
