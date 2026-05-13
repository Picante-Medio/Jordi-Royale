#include "UpgradesManager.h"

UpgradesManager::UpgradesManager() {
}

UpgradesManager::~UpgradesManager() {
    
}

UpgradesManager& UpgradesManager::Instance() {
    static UpgradesManager instance;
    return instance;
}
