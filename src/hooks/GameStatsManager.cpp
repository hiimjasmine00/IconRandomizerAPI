#include "../Internal.hpp"
#include <Geode/binding/GJRewardItem.hpp>
#include <Geode/binding/GJRewardObject.hpp>
#include <Geode/binding/GJStoreItem.hpp>
#include <Geode/modify/GameStatsManager.hpp>

using namespace geode::prelude;

class $modify(IRAGameStatsManager, GameStatsManager) {
    // When an icon or color is purchased, add it to the list of unlocked items.
    bool purchaseItem(int id) {
        if (!GameStatsManager::purchaseItem(id)) return false;

        if (auto storeItem = static_cast<GJStoreItem*>(m_storeItems->objectForKey(id))) {
            auto type = (UnlockType)storeItem->m_unlockType.value();
            auto id = storeItem->m_typeID.value();
            if (type != UnlockType::GJItem || (id >= 18 && id <= 20)) Internal::addToUnlocked(type, id);
        }

        return true;
    }

    // When an icon or color is rewarded from a chest or other item, add it to the list of unlocked items.
    void registerRewardsFromItem(GJRewardItem* item) {
        for (auto object : CCArrayExt<GJRewardObject*>(item->m_rewardObjects)) {
            if (object->m_specialRewardItem == SpecialRewardItem::CustomItem && object->m_unlockType != UnlockType::GJItem) {
                Internal::addToUnlocked(object->m_unlockType, object->m_itemID);
            }
        }
    }
};
