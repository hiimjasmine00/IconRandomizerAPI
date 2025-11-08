#include "Internal.hpp"
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GameStatsManager.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include <IconRandomizer.hpp>
#include <jasmine/random.hpp>

using namespace geode::prelude;

// A list of the IDs the player has unlocked for each type of icon.
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

$on_mod(Loaded) {
    // Initialize the Icon Randomizer API when the mod is loaded.
    IconRandomizer::init();
}

void IconRandomizer::init() {
    // Get the game manager.
    auto gameManager = GameManager::get();

    // For each icon type, set up the unlocked icons.
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
        // Get the vector of unlocked icons for the unlock type, then clear the vector.
        auto& vec = unlocked[unlockType];
        vec.clear();

        // Get the amount of icons for the type, then iterate through them and add them to the vector if they are unlocked.
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
        // Get the vector of unlocked colors for the unlock type, then clear the vector.
        auto& vec = unlocked[unlockType];
        vec.clear();

        // Iterate through the colors and add them to the vector if they are unlocked.
        for (int i = 0; i < 107; i++) {
            if (gameManager->isColorUnlocked(i, unlockType)) vec.push_back(i);
        }
    }
}

// The function to add an icon or color to the list of unlocked icons or colors.
void Internal::addToUnlocked(UnlockType type, int id) {
    // Get the vector of unlocked icons or colors for the type, then add the ID to the vector if it is not already in it.
    auto& vec = unlocked[type];
    if (!std::ranges::contains(vec, id)) {
        vec.push_back(id);
        std::ranges::sort(vec);
    }
}

int IconRandomizer::random(int min, int max) {
    // Get a random integer between min and max using jasmine::random.
    return jasmine::random::getInt(min, max);
}

RandomizeType IconRandomizer::fromIconType(IconType type) {
    // Convert the icon type to a randomize type.
    switch (type) {
        case IconType::Cube: return ICON_RANDOMIZER_API_CUBE;
        case IconType::Ship: return ICON_RANDOMIZER_API_SHIP;
        case IconType::Ball: return ICON_RANDOMIZER_API_BALL;
        case IconType::Ufo: return ICON_RANDOMIZER_API_UFO;
        case IconType::Wave: return ICON_RANDOMIZER_API_WAVE;
        case IconType::Robot: return ICON_RANDOMIZER_API_ROBOT;
        case IconType::Spider: return ICON_RANDOMIZER_API_SPIDER;
        case IconType::Swing: return ICON_RANDOMIZER_API_SWING;
        case IconType::Jetpack: return ICON_RANDOMIZER_API_JETPACK;
        case IconType::DeathEffect: return ICON_RANDOMIZER_API_DEATH_EFFECT;
        case IconType::Special: return ICON_RANDOMIZER_API_TRAIL;
        case IconType::Item: return ICON_RANDOMIZER_API_ANIMATION;
        case IconType::ShipFire: return ICON_RANDOMIZER_API_SHIP_FIRE;
        default: return ICON_RANDOMIZER_API_CUBE;
    }
}

RandomizeType IconRandomizer::fromUnlockType(UnlockType type) {
    // Convert the unlock type to a randomize type.
    switch (type) {
        case UnlockType::Cube: return ICON_RANDOMIZER_API_CUBE;
        case UnlockType::Col1: return ICON_RANDOMIZER_API_COLOR_1;
        case UnlockType::Col2: return ICON_RANDOMIZER_API_COLOR_2;
        case UnlockType::Ship: return ICON_RANDOMIZER_API_SHIP;
        case UnlockType::Ball: return ICON_RANDOMIZER_API_BALL;
        case UnlockType::Bird: return ICON_RANDOMIZER_API_UFO;
        case UnlockType::Dart: return ICON_RANDOMIZER_API_WAVE;
        case UnlockType::Robot: return ICON_RANDOMIZER_API_ROBOT;
        case UnlockType::Spider: return ICON_RANDOMIZER_API_SPIDER;
        case UnlockType::Streak: return ICON_RANDOMIZER_API_TRAIL;
        case UnlockType::Death: return ICON_RANDOMIZER_API_DEATH_EFFECT;
        case UnlockType::GJItem: return ICON_RANDOMIZER_API_ANIMATION;
        case UnlockType::Swing: return ICON_RANDOMIZER_API_SWING;
        case UnlockType::Jetpack: return ICON_RANDOMIZER_API_JETPACK;
        case UnlockType::ShipFire: return ICON_RANDOMIZER_API_SHIP_FIRE;
        default: return ICON_RANDOMIZER_API_CUBE;
    }
}

IconType IconRandomizer::toIconType(RandomizeType type) {
    // Convert the randomize type to an icon type.
    switch (type) {
        case ICON_RANDOMIZER_API_COLOR_1: return IconType::Item;
        case ICON_RANDOMIZER_API_COLOR_2: return IconType::Item;
        case ICON_RANDOMIZER_API_GLOW_COLOR: return IconType::Item;
        case ICON_RANDOMIZER_API_GLOW: return IconType::Item;
        case ICON_RANDOMIZER_API_CUBE: return IconType::Cube;
        case ICON_RANDOMIZER_API_SHIP: return IconType::Ship;
        case ICON_RANDOMIZER_API_BALL: return IconType::Ball;
        case ICON_RANDOMIZER_API_UFO: return IconType::Ufo;
        case ICON_RANDOMIZER_API_WAVE: return IconType::Wave;
        case ICON_RANDOMIZER_API_ROBOT: return IconType::Robot;
        case ICON_RANDOMIZER_API_SPIDER: return IconType::Spider;
        case ICON_RANDOMIZER_API_SWING: return IconType::Swing;
        case ICON_RANDOMIZER_API_JETPACK: return IconType::Jetpack;
        case ICON_RANDOMIZER_API_DEATH_EFFECT: return IconType::DeathEffect;
        case ICON_RANDOMIZER_API_TRAIL: return IconType::Special;
        case ICON_RANDOMIZER_API_ANIMATION: return IconType::Item;
        case ICON_RANDOMIZER_API_SHIP_FIRE: return IconType::ShipFire;
        case ICON_RANDOMIZER_API_EXPLODE: return IconType::DeathEffect;
        default: return IconType::Cube;
    }
}

UnlockType IconRandomizer::toUnlockType(RandomizeType type) {
    // Convert the randomize type to an unlock type.
    switch (type) {
        case ICON_RANDOMIZER_API_COLOR_1: return UnlockType::Col1;
        case ICON_RANDOMIZER_API_COLOR_2: return UnlockType::Col2;
        case ICON_RANDOMIZER_API_GLOW_COLOR: return UnlockType::Col2;
        case ICON_RANDOMIZER_API_GLOW: return UnlockType::Streak;
        case ICON_RANDOMIZER_API_CUBE: return UnlockType::Cube;
        case ICON_RANDOMIZER_API_SHIP: return UnlockType::Ship;
        case ICON_RANDOMIZER_API_BALL: return UnlockType::Ball;
        case ICON_RANDOMIZER_API_UFO: return UnlockType::Bird;
        case ICON_RANDOMIZER_API_WAVE: return UnlockType::Dart;
        case ICON_RANDOMIZER_API_ROBOT: return UnlockType::Robot;
        case ICON_RANDOMIZER_API_SPIDER: return UnlockType::Spider;
        case ICON_RANDOMIZER_API_SWING: return UnlockType::Swing;
        case ICON_RANDOMIZER_API_JETPACK: return UnlockType::Jetpack;
        case ICON_RANDOMIZER_API_DEATH_EFFECT: return UnlockType::Death;
        case ICON_RANDOMIZER_API_TRAIL: return UnlockType::Streak;
        case ICON_RANDOMIZER_API_SHIP_FIRE: return UnlockType::ShipFire;
        case ICON_RANDOMIZER_API_ANIMATION: return UnlockType::GJItem;
        case ICON_RANDOMIZER_API_EXPLODE: return UnlockType::Death;
        default: return UnlockType::Cube;
    }
}

int IconRandomizer::randomize(RandomizeType type, bool dual) {
    // If the type is invalid, return -1.
    if (type < 0 || type > 16) return -1;

    // Get the UnlockType from the randomize type, and get the vector of unlocked icons.
    auto& vec = unlocked[toUnlockType(type)];

    // If it is an animation, randomly enable or disable the animations, and return 0.
    if (type == ICON_RANDOMIZER_API_ANIMATION) {
        auto gameStatsManager = GameStatsManager::get();
        for (int i = 0; i < vec.size(); i++) {
            gameStatsManager->toggleEnableItem(UnlockType::GJItem, vec[i], random(0, 1));
        }
        return 0;
    }

    // Get the game manager and the Separate Dual Icons mod.
    // If the mod is enabled and the dual parameter is true, use separate dual icons.
    // Then get a random number from the vector of unlocked icons.
    auto gameManager = GameManager::get();
    auto separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto useDual = separateDualIcons && dual;
    auto iconType = toIconType(type);
    auto loadedIcons = MoreIcons::getIcons(iconType);
    auto vecSize = vec.size();
    auto idx = random(0, vecSize + loadedIcons.size() - 1);
    auto num = idx < vecSize ? vec[idx] : idx - vecSize;
    auto glow = type == ICON_RANDOMIZER_API_GLOW && std::ranges::contains(unlocked[UnlockType::Streak], 2) ? (bool)random(0, 1) : false;
    auto explode = type == ICON_RANDOMIZER_API_EXPLODE ? (bool)random(0, 1) : false;

    // Then, set the icon to the random number.
    // If Separate Dual Icons is enabled and the dual parameter is true, set the value in the mod.
    // Otherwise, set the value in the game manager.
    switch (type) {
        case ICON_RANDOMIZER_API_COLOR_1:
            if (useDual) separateDualIcons->setSavedValue("color1", num);
            else gameManager->setPlayerColor(num);
            return num;
        case ICON_RANDOMIZER_API_COLOR_2:
            if (useDual) separateDualIcons->setSavedValue("color2", num);
            else gameManager->setPlayerColor2(num);
            return num;
        case ICON_RANDOMIZER_API_GLOW_COLOR:
            if (useDual) separateDualIcons->setSavedValue("colorglow", num);
            else gameManager->setPlayerColor3(num);
            return num;
        case ICON_RANDOMIZER_API_GLOW:
            if (useDual) separateDualIcons->setSavedValue("glow", glow);
            else gameManager->setPlayerGlow(glow);
            return glow;
        case ICON_RANDOMIZER_API_CUBE:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("cube", num);
                else gameManager->setPlayerFrame(num);
                MoreIcons::setIcon("", IconType::Cube, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Cube, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SHIP:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("ship", num);
                else gameManager->setPlayerShip(num);
                MoreIcons::setIcon("", IconType::Ship, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Ship, useDual);
            return 0;
        case ICON_RANDOMIZER_API_BALL:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("roll", num);
                else gameManager->setPlayerBall(num);
                MoreIcons::setIcon("", IconType::Ball, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Ball, useDual);
            return 0;
        case ICON_RANDOMIZER_API_UFO:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("bird", num);
                else gameManager->setPlayerBird(num);
                MoreIcons::setIcon("", IconType::Ufo, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Ufo, useDual);
            return 0;
        case ICON_RANDOMIZER_API_WAVE:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("dart", num);
                else gameManager->setPlayerDart(num);
                MoreIcons::setIcon("", IconType::Wave, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Wave, useDual);
            return 0;
        case ICON_RANDOMIZER_API_ROBOT:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("robot", num);
                else gameManager->setPlayerRobot(num);
                MoreIcons::setIcon("", IconType::Robot, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Robot, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SPIDER:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("spider", num);
                else gameManager->setPlayerSpider(num);
                MoreIcons::setIcon("", IconType::Spider, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Spider, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SWING:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("swing", num);
                else gameManager->setPlayerSwing(num);
                MoreIcons::setIcon("", IconType::Swing, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Swing, useDual);
            return 0;
        case ICON_RANDOMIZER_API_JETPACK:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("jetpack", num);
                else gameManager->setPlayerJetpack(num);
                MoreIcons::setIcon("", IconType::Jetpack, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Jetpack, useDual);
            return 0;
        case ICON_RANDOMIZER_API_DEATH_EFFECT:
            if (useDual) separateDualIcons->setSavedValue("death", num);
            else gameManager->setPlayerDeathEffect(num);
            return num;
        case ICON_RANDOMIZER_API_TRAIL:
            if (idx < vecSize) {
                if (useDual) separateDualIcons->setSavedValue("trail", num);
                else gameManager->setPlayerStreak(num);
                MoreIcons::setIcon("", IconType::Special, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num]->name, IconType::Special, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SHIP_FIRE:
            if (useDual) separateDualIcons->setSavedValue("shiptrail", num);
            else gameManager->setPlayerShipStreak(num);
            return num;
        case ICON_RANDOMIZER_API_EXPLODE:
            if (useDual) separateDualIcons->setSavedValue("deathexplode", explode);
            else gameManager->setGameVariable(GameVar::PlayerExplode, explode);
            return explode;
        default:
            return -1;
    }
}

void IconRandomizer::randomizeAll(RandomizeAllType type, bool dual) {
    // Switch on the randomize all type and randomize all the icons of that type.
    switch (type) {
        case ICON_RANDOMIZER_API_ALL_ICONS:
            randomize(ICON_RANDOMIZER_API_CUBE, dual);
            randomize(ICON_RANDOMIZER_API_SHIP, dual);
            randomize(ICON_RANDOMIZER_API_BALL, dual);
            randomize(ICON_RANDOMIZER_API_UFO, dual);
            randomize(ICON_RANDOMIZER_API_WAVE, dual);
            randomize(ICON_RANDOMIZER_API_ROBOT, dual);
            randomize(ICON_RANDOMIZER_API_SPIDER, dual);
            randomize(ICON_RANDOMIZER_API_SWING, dual);
            randomize(ICON_RANDOMIZER_API_JETPACK, dual);
            break;
        case ICON_RANDOMIZER_API_ALL_SPECIAL:
            randomize(ICON_RANDOMIZER_API_DEATH_EFFECT, dual);
            randomize(ICON_RANDOMIZER_API_TRAIL, dual);
            randomize(ICON_RANDOMIZER_API_SHIP_FIRE, dual);
            randomize(ICON_RANDOMIZER_API_ANIMATION, dual);
            randomize(ICON_RANDOMIZER_API_EXPLODE, dual);
            break;
        case ICON_RANDOMIZER_API_ALL_COLORS:
            randomize(ICON_RANDOMIZER_API_COLOR_1, dual);
            randomize(ICON_RANDOMIZER_API_COLOR_2, dual);
            randomize(ICON_RANDOMIZER_API_GLOW_COLOR, dual);
            randomize(ICON_RANDOMIZER_API_GLOW, dual);
            break;
    }
}

int IconRandomizer::active(RandomizeType type, bool dual) {
    // Get the game manager, then get the Separate Dual Icons mod.
    // If the mod is enabled and the dual parameter is true, use separate dual icons.
    auto gameManager = GameManager::get();
    auto separateDualIcons = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
    auto useDual = separateDualIcons && dual;

    // Get the value from the Separate Dual Icons mod if it is enabled and the dual parameter is true,
    // otherwise get the value from the game manager.
    switch (type) {
        case ICON_RANDOMIZER_API_COLOR_1:
            return useDual ? separateDualIcons->getSavedValue("color1", 0) : gameManager->getPlayerColor();
        case ICON_RANDOMIZER_API_COLOR_2:
            return useDual ? separateDualIcons->getSavedValue("color2", 0) : gameManager->getPlayerColor2();
        case ICON_RANDOMIZER_API_GLOW_COLOR:
            return useDual ? separateDualIcons->getSavedValue("colorglow", 0) : gameManager->getPlayerGlowColor();
        case ICON_RANDOMIZER_API_GLOW:
            return useDual ? separateDualIcons->getSavedValue("glow", false) : gameManager->getPlayerGlow();
        case ICON_RANDOMIZER_API_CUBE:
            return useDual ? separateDualIcons->getSavedValue("cube", 1) : gameManager->getPlayerFrame();
        case ICON_RANDOMIZER_API_SHIP:
            return useDual ? separateDualIcons->getSavedValue("ship", 1) : gameManager->getPlayerShip();
        case ICON_RANDOMIZER_API_BALL:
            return useDual ? separateDualIcons->getSavedValue("roll", 1) : gameManager->getPlayerBall();
        case ICON_RANDOMIZER_API_UFO:
            return useDual ? separateDualIcons->getSavedValue("bird", 1) : gameManager->getPlayerBird();
        case ICON_RANDOMIZER_API_WAVE:
            return useDual ? separateDualIcons->getSavedValue("dart", 1) : gameManager->getPlayerDart();
        case ICON_RANDOMIZER_API_ROBOT:
            return useDual ? separateDualIcons->getSavedValue("robot", 1) : gameManager->getPlayerRobot();
        case ICON_RANDOMIZER_API_SPIDER:
            return useDual ? separateDualIcons->getSavedValue("spider", 1) : gameManager->getPlayerSpider();
        case ICON_RANDOMIZER_API_SWING:
            return useDual ? separateDualIcons->getSavedValue("swing", 1) : gameManager->getPlayerSwing();
        case ICON_RANDOMIZER_API_JETPACK:
            return useDual ? separateDualIcons->getSavedValue("jetpack", 1) : gameManager->getPlayerJetpack();
        case ICON_RANDOMIZER_API_DEATH_EFFECT:
            return useDual ? separateDualIcons->getSavedValue("death", 1) : gameManager->getPlayerDeathEffect();
        case ICON_RANDOMIZER_API_TRAIL:
            return useDual ? separateDualIcons->getSavedValue("trail", 1) : gameManager->getPlayerStreak();
        case ICON_RANDOMIZER_API_SHIP_FIRE:
            return useDual ? separateDualIcons->getSavedValue("shiptrail", 1) : gameManager->getPlayerShipFire();
        case ICON_RANDOMIZER_API_EXPLODE:
            return useDual ? separateDualIcons->getSavedValue("deathexplode", 0) : gameManager->getGameVariable(GameVar::PlayerExplode);
        default:
            return -1;
    }
}
