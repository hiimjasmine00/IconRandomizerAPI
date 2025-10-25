#include "../Internal.hpp"
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

class $modify(IRAGameManager, GameManager) {
    // For achievements that unlock icons or colors, add them to the list of unlocked items when the achievement is completed.
    void completedAchievement(gd::string id) {
        GameManager::completedAchievement(id);

        UnlockType unlockType;
        int iconID;
        GameManager::getUnlockForAchievement(id, iconID, unlockType);

        if (iconID != 0 && unlockType != (UnlockType)0) Internal::addToUnlocked(unlockType, iconID);
    }
};
