#include <IconRandomizer.hpp>
#include <Geode/modify/GJAccountManager.hpp>

using namespace geode::prelude;

class $modify(IRAAccountManager, GJAccountManager) {
    // When the account sync is completed, reinitialize the Icon Randomizer API to refresh unlocked icons and colors.
    void onSyncAccountCompleted(gd::string response, gd::string tag) {
        GJAccountManager::onSyncAccountCompleted(response, tag);

        if (
            response != "-1" && response != "-2" &&
            (response.size() > 9 || atoi(response.c_str()) > -1) &&
            string::count(response, ';') > 4
        ) {
            IconRandomizer::init();
        }
    }
};
