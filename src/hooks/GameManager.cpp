#include "../Internal.hpp"
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

class $modify(IRAGameManager, GameManager) {
    void reportAchievementWithID(const char* id, int percent, bool skipNotification) {
        GameManager::reportAchievementWithID(id, percent, skipNotification);

        UnlockType unlockType;
        int iconID;
        GameManager::getUnlockForAchievement(id, iconID, unlockType);

        if (unlockType != (UnlockType)0) Internal::addToUnlocked(unlockType, iconID);
    }
};
