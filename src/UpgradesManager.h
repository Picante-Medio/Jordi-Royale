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
    
    uint32_t enemiesDefeated = 0;
    uint32_t miliseconds = 0;
    uint32_t seconds = 0;
    uint32_t minutes = 0;
    uint32_t hours = 0;

public:
    ~UpgradesManager();
    
    static UpgradesManager& Instance();

    inline uint32_t getEnemies() {return enemiesDefeated;}
    inline uint32_t getMiliseconds() {return miliseconds;}
    inline uint32_t getSeconds() {return seconds;}
    inline uint32_t getMinutes() {return minutes;}
    inline uint32_t getHours() {return hours;}

    inline void setEnemies(uint32_t enemies) {enemiesDefeated = enemies;}
    inline void setMiliseconds(uint32_t ms) {miliseconds = ms;}
    inline void setSeconds(uint32_t s) {seconds = s;}
    inline void setMinutes(uint32_t min) {minutes = min;}
    inline void setHours(uint32_t h) {hours = h;}

    // std::variant<NewWeapon, WeaponUpgrade> getSelectedUpgrade() const;
    // void setSelectedUpgrade();

};
