#pragma once

#include <variant>
#include <string>

// Info containers to pass upgrade info from UpgradesScene to MainScene
struct NewWeapon {
    std::string prefabName;
};

struct WeaponUpgrade {
    enum UpgradeType {
        FiringRate,
        Range,
        Damage,
        WeaponUpgradeType_SIZE
    };

    UpgradeType type;
    float value;
};

// Info containers to pass player weapons info from MainScene to UpgradesScene
struct Weapon {
    std::string prefabName;
    // weapon upgrades already applied to balance offered upgrades
};

class UpgradesManager {
private:
    UpgradesManager();

    std::variant<NewWeapon, WeaponUpgrade> selectedUpgrade;

public:
    ~UpgradesManager();    
    
    static UpgradesManager& Instance();

    // std::variant<NewWeapon, WeaponUpgrade> getSelectedUpgrade() const;
    // void setSelectedUpgrade();

};
