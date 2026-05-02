#include "PickupSystem.h"
#include "TransformComponent.h"
#include "XPComponent.h"
#include "PlayerComponent.h"
#include "XPGrabMessage.h"

void
PickupSystem::update(uint32_t dt) {
    for(auto& player : scene.query<PlayerComponent, TransformComponent>()){
        const PlayerComponent& playerComp = player.getConst<PlayerComponent>();
        const TransformComponent& playerTrans = player.getConst<TransformComponent>();

        // XP Pickups
        for(auto& xp : scene.query<XPComponent, TransformComponent>()){
            const TransformComponent& xpTrans = xp.getConst<TransformComponent>();
            const XPComponent& xpComponent = xp.getConst<XPComponent>();

            if(pickup(playerTrans, xpTrans, playerComp.pickupRange)) {
                // Pickup in the form of a message
                XPGrabMessage message;
                message.xp = xpComponent.experience;
                scene.sendMessage(message);

                // Animation of experience moving towards player may be added (optional)
                scene.removeEntity(xpTrans.entity);
            }

            // Chest pickups


            // Health pickups

        }


    }
}

bool
PickupSystem::pickup(const TransformComponent& playerTransform, const TransformComponent& pickupTransform, float pickupRange) {
    HUGO::Vector3 distance = pickupTransform.getPosition() - playerTransform.getPosition();
    float distanceModule = distance.length();

    return distanceModule < pickupRange;
}
