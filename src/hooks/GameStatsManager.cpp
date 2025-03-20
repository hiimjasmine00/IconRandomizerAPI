#include "../Internal.hpp"
#include <Geode/binding/GJRewardItem.hpp>
#include <Geode/binding/GJRewardObject.hpp>
#include <Geode/binding/GJStoreItem.hpp>
#include <Geode/modify/GameStatsManager.hpp>

using namespace geode::prelude;

class $modify(IRAGameStatsManager, GameStatsManager) {
    bool purchaseItem(int id) {
        if (!GameStatsManager::purchaseItem(id)) return false;

        if (auto storeItem = static_cast<GJStoreItem*>(m_storeItems->objectForKey(id))) {
            auto type = (UnlockType)storeItem->m_unlockType.value();
            auto id = storeItem->m_typeID.value();
            if (type != UnlockType::GJItem || (id >= 18 && id <= 20)) Internal::addToUnlocked(type, id);
        }

        return true;
    }

    GJRewardItem* unlockSecretChest(int id) {
        if (auto item = GameStatsManager::unlockSecretChest(id)) {
            for (auto object : CCArrayExt<GJRewardObject*>(item->m_rewardObjects)) {
                if (object->m_specialRewardItem == SpecialRewardItem::CustomItem && object->m_unlockType != UnlockType::GJItem)
                    Internal::addToUnlocked(object->m_unlockType, object->m_itemID);
            }
            return item;
        }
        return nullptr;
    }

    GJRewardItem* unlockSpecialChest(gd::string id) {
        if (auto item = GameStatsManager::unlockSpecialChest(id)) {
            for (auto object : CCArrayExt<GJRewardObject*>(item->m_rewardObjects)) {
                if (object->m_specialRewardItem == SpecialRewardItem::CustomItem && object->m_unlockType != UnlockType::GJItem)
                    Internal::addToUnlocked(object->m_unlockType, object->m_itemID);
            }
            return item;
        }
        return nullptr;
    }
};
