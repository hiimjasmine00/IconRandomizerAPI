#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GameStatsManager.hpp>
#include <Geode/loader/GameEvent.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/utils/random.hpp>
#define MORE_ICONS_EVENTS
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include <IconRandomizer.hpp>

using namespace geode::prelude;

std::map<UnlockType, std::vector<int>> unlocked = {
    { UnlockType::Cube, {} },
    { UnlockType::Col1, {} },
    { UnlockType::Col2, {} },
    { UnlockType::Ship, {} },
    { UnlockType::Ball, {} },
    { UnlockType::Bird, {} },
    { UnlockType::Dart, {} },
    { UnlockType::Robot, {} },
    { UnlockType::Spider, {} },
    { UnlockType::Streak, {} },
    { UnlockType::Death, {} },
    { UnlockType::GJItem, {} },
    { UnlockType::Swing, {} },
    { UnlockType::Jetpack, {} },
    { UnlockType::ShipFire, {} }
};

$on_game(ModsLoaded) {
    IconRandomizer::init();
}

void IconRandomizer::init() {
    auto gameManager = GameManager::get();

    constexpr std::array icons = {
        std::make_pair(IconType::Cube, UnlockType::Cube),
        std::make_pair(IconType::Ship, UnlockType::Ship),
        std::make_pair(IconType::Ball, UnlockType::Ball),
        std::make_pair(IconType::Ufo, UnlockType::Bird),
        std::make_pair(IconType::Wave, UnlockType::Dart),
        std::make_pair(IconType::Robot, UnlockType::Robot),
        std::make_pair(IconType::Spider, UnlockType::Spider),
        std::make_pair(IconType::Swing, UnlockType::Swing),
        std::make_pair(IconType::Jetpack, UnlockType::Jetpack),
        std::make_pair(IconType::DeathEffect, UnlockType::Death),
        std::make_pair(IconType::Special, UnlockType::Streak),
        std::make_pair(IconType::Item, UnlockType::GJItem),
        std::make_pair(IconType::ShipFire, UnlockType::ShipFire)
    };

    for (auto [iconType, unlockType] : icons) {
        auto& vec = unlocked[unlockType];
        vec.clear();

        auto amount = iconType == IconType::Item ? 20 : gameManager->countForType(iconType);
        for (int i = iconType == IconType::Item ? 18 : 1; i <= amount; i++) {
            if (gameManager->isIconUnlocked(i, iconType)) vec.push_back(i);
        }
    }

    constexpr std::array colors = {
        UnlockType::Col1,
        UnlockType::Col2
    };

    for (auto unlockType : colors) {
        auto& vec = unlocked[unlockType];
        vec.clear();

        for (int i = 0; i < 107; i++) {
            if (gameManager->isColorUnlocked(i, unlockType)) vec.push_back(i);
        }
    }
}

RandomizeType IconRandomizer::fromIconType(IconType type) {
    switch (type) {
        case IconType::Cube: return RandomizeType::Cube;
        case IconType::Ship: return RandomizeType::Ship;
        case IconType::Ball: return RandomizeType::Ball;
        case IconType::Ufo: return RandomizeType::Ufo;
        case IconType::Wave: return RandomizeType::Wave;
        case IconType::Robot: return RandomizeType::Robot;
        case IconType::Spider: return RandomizeType::Spider;
        case IconType::Swing: return RandomizeType::Swing;
        case IconType::Jetpack: return RandomizeType::Jetpack;
        case IconType::DeathEffect: return RandomizeType::DeathEffect;
        case IconType::Special: return RandomizeType::Trail;
        case IconType::Item: return RandomizeType::Animation;
        case IconType::ShipFire: return RandomizeType::ShipFire;
        default: return RandomizeType::Cube;
    }
}

RandomizeType IconRandomizer::fromUnlockType(UnlockType type) {
    switch (type) {
        case UnlockType::Cube: return RandomizeType::Cube;
        case UnlockType::Col1: return RandomizeType::Color1;
        case UnlockType::Col2: return RandomizeType::Color2;
        case UnlockType::Ship: return RandomizeType::Ship;
        case UnlockType::Ball: return RandomizeType::Ball;
        case UnlockType::Bird: return RandomizeType::Ufo;
        case UnlockType::Dart: return RandomizeType::Wave;
        case UnlockType::Robot: return RandomizeType::Robot;
        case UnlockType::Spider: return RandomizeType::Spider;
        case UnlockType::Streak: return RandomizeType::Trail;
        case UnlockType::Death: return RandomizeType::DeathEffect;
        case UnlockType::GJItem: return RandomizeType::Animation;
        case UnlockType::Swing: return RandomizeType::Swing;
        case UnlockType::Jetpack: return RandomizeType::Jetpack;
        case UnlockType::ShipFire: return RandomizeType::ShipFire;
        default: return RandomizeType::Cube;
    }
}

IconType IconRandomizer::toIconType(RandomizeType type) {
    switch (type) {
        case RandomizeType::Color1: return IconType::Item;
        case RandomizeType::Color2: return IconType::Item;
        case RandomizeType::GlowColor: return IconType::Item;
        case RandomizeType::Glow: return IconType::Item;
        case RandomizeType::Cube: return IconType::Cube;
        case RandomizeType::Ship: return IconType::Ship;
        case RandomizeType::Ball: return IconType::Ball;
        case RandomizeType::Ufo: return IconType::Ufo;
        case RandomizeType::Wave: return IconType::Wave;
        case RandomizeType::Robot: return IconType::Robot;
        case RandomizeType::Spider: return IconType::Spider;
        case RandomizeType::Swing: return IconType::Swing;
        case RandomizeType::Jetpack: return IconType::Jetpack;
        case RandomizeType::DeathEffect: return IconType::DeathEffect;
        case RandomizeType::Trail: return IconType::Special;
        case RandomizeType::Animation: return IconType::Item;
        case RandomizeType::ShipFire: return IconType::ShipFire;
        case RandomizeType::Explode: return IconType::DeathEffect;
        default: return IconType::Cube;
    }
}

UnlockType IconRandomizer::toUnlockType(RandomizeType type) {
    switch (type) {
        case RandomizeType::Color1: return UnlockType::Col1;
        case RandomizeType::Color2: return UnlockType::Col2;
        case RandomizeType::GlowColor: return UnlockType::Col2;
        case RandomizeType::Glow: return UnlockType::Streak;
        case RandomizeType::Cube: return UnlockType::Cube;
        case RandomizeType::Ship: return UnlockType::Ship;
        case RandomizeType::Ball: return UnlockType::Ball;
        case RandomizeType::Ufo: return UnlockType::Bird;
        case RandomizeType::Wave: return UnlockType::Dart;
        case RandomizeType::Robot: return UnlockType::Robot;
        case RandomizeType::Spider: return UnlockType::Spider;
        case RandomizeType::Swing: return UnlockType::Swing;
        case RandomizeType::Jetpack: return UnlockType::Jetpack;
        case RandomizeType::DeathEffect: return UnlockType::Death;
        case RandomizeType::Trail: return UnlockType::Streak;
        case RandomizeType::ShipFire: return UnlockType::ShipFire;
        case RandomizeType::Animation: return UnlockType::GJItem;
        case RandomizeType::Explode: return UnlockType::Death;
        default: return UnlockType::Cube;
    }
}

int IconRandomizer::randomize(RandomizeType type, bool dual) {
    if (type < RandomizeType::Color1 || type > RandomizeType::Explode) return -1;

    auto& vec = unlocked[toUnlockType(type)];

    if (type == RandomizeType::Animation) {
        auto gameStatsManager = GameStatsManager::get();
        for (int i = 0; i < vec.size(); i++) {
            gameStatsManager->toggleEnableItem(UnlockType::GJItem, vec[i], random::generate<bool>());
        }
        return 0;
    }

    auto gameManager = GameManager::get();
    auto separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto useDual = separateDualIcons && dual;
    auto iconType = toIconType(type);
    auto loadedIcons = more_icons::getIcons(iconType);
    auto vecSize = vec.size();
    auto idx = random::generate(0uz, vecSize + (loadedIcons ? loadedIcons->size() : 0) - 1);
    auto num = idx < vecSize ? vec[idx] : idx - vecSize;
    auto glow = type == RandomizeType::Glow && std::ranges::contains(unlocked[UnlockType::Streak], 2) ? random::generate<bool>() : false;
    auto explode = type == RandomizeType::Explode ? random::generate<bool>() : false;

    switch (type) {
        case RandomizeType::Color1:
            if (useDual) separateDualIcons->setSavedValue("color1", num);
            else gameManager->setPlayerColor(num);
            return num;
        case RandomizeType::Color2:
            if (useDual) separateDualIcons->setSavedValue("color2", num);
            else gameManager->setPlayerColor2(num);
            return num;
        case RandomizeType::GlowColor:
            if (useDual) separateDualIcons->setSavedValue("colorglow", num);
            else gameManager->setPlayerColor3(num);
            return num;
        case RandomizeType::Glow:
            if (useDual) separateDualIcons->setSavedValue("glow", glow);
            else gameManager->setPlayerGlow(glow);
            return glow;
        case RandomizeType::Cube:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("cube", num);
                else gameManager->setPlayerFrame(num);
                more_icons::setIcon(nullptr, IconType::Cube, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Cube, useDual);
            return 0;
        case RandomizeType::Ship:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("ship", num);
                else gameManager->setPlayerShip(num);
                more_icons::setIcon(nullptr, IconType::Ship, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Ship, useDual);
            return 0;
        case RandomizeType::Ball:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("roll", num);
                else gameManager->setPlayerBall(num);
                more_icons::setIcon(nullptr, IconType::Ball, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Ball, useDual);
            return 0;
        case RandomizeType::Ufo:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("bird", num);
                else gameManager->setPlayerBird(num);
                more_icons::setIcon(nullptr, IconType::Ufo, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Ufo, useDual);
            return 0;
        case RandomizeType::Wave:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("dart", num);
                else gameManager->setPlayerDart(num);
                more_icons::setIcon(nullptr, IconType::Wave, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Wave, useDual);
            return 0;
        case RandomizeType::Robot:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("robot", num);
                else gameManager->setPlayerRobot(num);
                more_icons::setIcon(nullptr, IconType::Robot, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Robot, useDual);
            return 0;
        case RandomizeType::Spider:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("spider", num);
                else gameManager->setPlayerSpider(num);
                more_icons::setIcon(nullptr, IconType::Spider, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Spider, useDual);
            return 0;
        case RandomizeType::Swing:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("swing", num);
                else gameManager->setPlayerSwing(num);
                more_icons::setIcon(nullptr, IconType::Swing, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Swing, useDual);
            return 0;
        case RandomizeType::Jetpack:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("jetpack", num);
                else gameManager->setPlayerJetpack(num);
                more_icons::setIcon(nullptr, IconType::Jetpack, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Jetpack, useDual);
            return 0;
        case RandomizeType::DeathEffect:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("death", num);
                else gameManager->setPlayerDeathEffect(num);
                more_icons::setIcon(nullptr, IconType::DeathEffect, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::DeathEffect, useDual);
            return num;
        case RandomizeType::Trail:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("trail", num);
                else gameManager->setPlayerStreak(num);
                more_icons::setIcon(nullptr, IconType::Special, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::Special, useDual);
            return 0;
        case RandomizeType::ShipFire:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("shiptrail", num);
                else gameManager->setPlayerShipStreak(num);
                more_icons::setIcon(nullptr, IconType::ShipFire, useDual);
                return num;
            }
            if (loadedIcons) more_icons::setIcon(loadedIcons->data() + num, IconType::ShipFire, useDual);
            return num;
        case RandomizeType::Explode:
            if (useDual) separateDualIcons->setSavedValue("deathexplode", explode);
            else gameManager->setGameVariable(GameVar::PlayerExplode, explode);
            return explode;
        default:
            return -1;
    }
}

void IconRandomizer::randomizeAll(RandomizeAllType type, bool dual) {
    switch (type) {
        case RandomizeAllType::Icons:
            randomize(RandomizeType::Cube, dual);
            randomize(RandomizeType::Ship, dual);
            randomize(RandomizeType::Ball, dual);
            randomize(RandomizeType::Ufo, dual);
            randomize(RandomizeType::Wave, dual);
            randomize(RandomizeType::Robot, dual);
            randomize(RandomizeType::Spider, dual);
            randomize(RandomizeType::Swing, dual);
            randomize(RandomizeType::Jetpack, dual);
            break;
        case RandomizeAllType::Special:
            randomize(RandomizeType::DeathEffect, dual);
            randomize(RandomizeType::Trail, dual);
            randomize(RandomizeType::ShipFire, dual);
            randomize(RandomizeType::Animation, dual);
            randomize(RandomizeType::Explode, dual);
            break;
        case RandomizeAllType::Colors:
            randomize(RandomizeType::Color1, dual);
            randomize(RandomizeType::Color2, dual);
            randomize(RandomizeType::GlowColor, dual);
            randomize(RandomizeType::Glow, dual);
            break;
    }
}

int IconRandomizer::active(RandomizeType type, bool dual) {
    auto separateDualIcons = dual ? Loader::get()->getLoadedMod("weebify.separate_dual_icons") : nullptr;
    auto gameManager = separateDualIcons ? nullptr : GameManager::get();

    switch (type) {
        case RandomizeType::Color1:
            return separateDualIcons ? separateDualIcons->getSavedValue("color1", 0) : gameManager->getPlayerColor();
        case RandomizeType::Color2:
            return separateDualIcons ? separateDualIcons->getSavedValue("color2", 0) : gameManager->getPlayerColor2();
        case RandomizeType::GlowColor:
            return separateDualIcons ? separateDualIcons->getSavedValue("colorglow", 0) : gameManager->getPlayerGlowColor();
        case RandomizeType::Glow:
            return separateDualIcons ? separateDualIcons->getSavedValue("glow", false) : gameManager->getPlayerGlow();
        case RandomizeType::Cube:
            return separateDualIcons ? separateDualIcons->getSavedValue("cube", 1) : gameManager->getPlayerFrame();
        case RandomizeType::Ship:
            return separateDualIcons ? separateDualIcons->getSavedValue("ship", 1) : gameManager->getPlayerShip();
        case RandomizeType::Ball:
            return separateDualIcons ? separateDualIcons->getSavedValue("roll", 1) : gameManager->getPlayerBall();
        case RandomizeType::Ufo:
            return separateDualIcons ? separateDualIcons->getSavedValue("bird", 1) : gameManager->getPlayerBird();
        case RandomizeType::Wave:
            return separateDualIcons ? separateDualIcons->getSavedValue("dart", 1) : gameManager->getPlayerDart();
        case RandomizeType::Robot:
            return separateDualIcons ? separateDualIcons->getSavedValue("robot", 1) : gameManager->getPlayerRobot();
        case RandomizeType::Spider:
            return separateDualIcons ? separateDualIcons->getSavedValue("spider", 1) : gameManager->getPlayerSpider();
        case RandomizeType::Swing:
            return separateDualIcons ? separateDualIcons->getSavedValue("swing", 1) : gameManager->getPlayerSwing();
        case RandomizeType::Jetpack:
            return separateDualIcons ? separateDualIcons->getSavedValue("jetpack", 1) : gameManager->getPlayerJetpack();
        case RandomizeType::DeathEffect:
            return separateDualIcons ? separateDualIcons->getSavedValue("death", 1) : gameManager->getPlayerDeathEffect();
        case RandomizeType::Trail:
            return separateDualIcons ? separateDualIcons->getSavedValue("trail", 1) : gameManager->getPlayerStreak();
        case RandomizeType::ShipFire:
            return separateDualIcons ? separateDualIcons->getSavedValue("shiptrail", 1) : gameManager->getPlayerShipFire();
        case RandomizeType::Explode:
            return separateDualIcons ? separateDualIcons->getSavedValue("deathexplode", 0) : gameManager->getGameVariable(GameVar::PlayerExplode);
        default:
            return -1;
    }
}
