#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/GameStatsManager.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/utils/ranges.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include <IconRandomizer.hpp>
#include <random>

using namespace geode::prelude;

#define SDI_ID "weebify.separate_dual_icons"
#define SDI_COLOR_1 "color1"
#define SDI_COLOR_2 "color2"
#define SDI_GLOW_COLOR "colorglow"
#define SDI_GLOW "glow"
#define SDI_CUBE "cube"
#define SDI_SHIP "ship"
#define SDI_BALL "roll"
#define SDI_UFO "bird"
#define SDI_WAVE "dart"
#define SDI_ROBOT "robot"
#define SDI_SPIDER "spider"
#define SDI_SWING "swing"
#define SDI_JETPACK "jetpack"
#define SDI_DEATH "death"
#define SDI_TRAIL "trail"
#define SDI_SHIP_FIRE "shiptrail"

// A list of the IDs the player has unlocked for each type of icon.
std::map<UnlockType, std::vector<int>> UNLOCKED = {
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

// A flag to check if the API has been initialized.
bool INITIALIZED = false;

// The icon part of the initialization function.
// This takes a parameter for the type of icon to initialize.
void setupUnlockedIcons(IconType type) {
    // Get the game manager and the vector of unlocked icons for the icon type, then clear the vector.
    auto gameManager = GameManager::sharedState();
    auto& vec = UNLOCKED[gameManager->iconTypeToUnlockType(type)];
    vec.clear();

    // Get the amount of icons for the type, then iterate through them and add them to the vector if they are unlocked.
    auto amount = type == IconType::Item ? 20 : gameManager->countForType(type);
    for (int i = type == IconType::Item ? 18 : 1; i <= amount; i++) {
        if (gameManager->isIconUnlocked(i, type)) vec.push_back(i);
    }
}

// The color part of the initialization function.
// This takes a parameter for the type of color to initialize.
void setupUnlockedColors(UnlockType type) {
    // Get the game manager and the vector of unlocked colors for the unlock type, then clear the vector.
    auto gameManager = GameManager::sharedState();
    auto& vec = UNLOCKED[type];
    vec.clear();

    // Iterate through the colors and add them to the vector if they are unlocked.
    for (int i = 0; i < 107; i++) {
        if (gameManager->isColorUnlocked(i, type)) vec.push_back(i);
    }
}

// A helper function to get a saved value from a Geode mod.
// This takes the mod, a string for the name of the setting, and a parameter for the default value of the setting.
template <class T>
static T getModValue(geode::Mod* mod, std::string const& key, T const& defaultValue) {
    // Get the mod's saved value if it exists, otherwise return the default value.
    return mod ? mod->getSavedValue(key, defaultValue) : defaultValue;
}

// A helper function to set a saved value from a Geode mod.
// This takes the mod, a string for the name of the setting, and a parameter for the value of the setting.
template <class T>
static void setModValue(geode::Mod* mod, std::string const& key, T const& value) {
    // Set the mod's saved value, if the mod is actually loaded.
    if (mod) mod->setSavedValue(key, value);
}

void IconRandomizer::init() {
    // Set up the unlocked icons and colors.
    setupUnlockedIcons(IconType::Cube);
    setupUnlockedColors(UnlockType::Col1);
    setupUnlockedColors(UnlockType::Col2);
    setupUnlockedIcons(IconType::Ship);
    setupUnlockedIcons(IconType::Ball);
    setupUnlockedIcons(IconType::Ufo);
    setupUnlockedIcons(IconType::Wave);
    setupUnlockedIcons(IconType::Robot);
    setupUnlockedIcons(IconType::Spider);
    setupUnlockedIcons(IconType::Special);
    setupUnlockedIcons(IconType::DeathEffect);
    setupUnlockedIcons(IconType::Item);
    setupUnlockedIcons(IconType::Swing);
    setupUnlockedIcons(IconType::Jetpack);
    setupUnlockedIcons(IconType::ShipFire);

    // Set the initialized flag to true.
    INITIALIZED = true;
}

int IconRandomizer::random(int min, int max) {
    // Cvolton had a much longer way of doing this that he grabbed from Stack Overflow, thank you, Copilot, for minimizing it.
    static std::mt19937 mt(std::random_device{}());
    return std::uniform_int_distribution<int>(min, max)(mt);
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
        default: return UnlockType::Cube;
    }
}

int IconRandomizer::randomize(RandomizeType type, bool dual) {
    // Initialize the API if it hasn't been already.
    if (!INITIALIZED) {
        init();
        INITIALIZED = true;
    }

    // If the type is invalid, return -1.
    if (type < 0 || type > 16) return -1;

    // Get the UnlockType from the randomize type, and get the vector of unlocked icons.
    auto& vec = UNLOCKED[toUnlockType(type)];

    // If it is an animation, randomly enable or disable the animations, and return 0.
    if (type == ICON_RANDOMIZER_API_ANIMATION) {
        auto gameStatsManager = GameStatsManager::sharedState();
        for (int i = 0; i < vec.size(); i++) {
            gameStatsManager->toggleEnableItem(UnlockType::GJItem, vec[i], random(0, 1));
        }
        return 0;
    }

    // Get the game manager and the Separate Dual Icons mod. If the mod is enabled and the dual parameter is true, use separate dual icons.
    // Then get a random number from the vector of unlocked icons.
    auto gameManager = GameManager::sharedState();
    auto separateDualIcons = Loader::get()->getLoadedMod(SDI_ID);
    auto useDual = separateDualIcons && dual;
    auto loadedIcons = MoreIcons::vectorForType(toIconType(type));
    auto idx = random(0, vec.size() + loadedIcons.size() - 1);
    auto num = idx < vec.size() ? vec[idx] : idx - vec.size();
    auto glow = type == ICON_RANDOMIZER_API_GLOW && ranges::contains(UNLOCKED[UnlockType::Streak], 2) ? (bool)random(0, 1) : false;

    // Then, set the icon to the random number.
    // If Separate Dual Icons is enabled and the dual parameter is true, set the value in the mod.
    // Otherwise, set the value in the game manager.
    switch (type) {
        case ICON_RANDOMIZER_API_COLOR_1:
            if (useDual) setModValue(separateDualIcons, SDI_COLOR_1, num);
            else gameManager->setPlayerColor(num);
            return num;
        case ICON_RANDOMIZER_API_COLOR_2:
            if (useDual) setModValue(separateDualIcons, SDI_COLOR_2, num);
            else gameManager->setPlayerColor2(num);
            return num;
        case ICON_RANDOMIZER_API_GLOW_COLOR:
            if (useDual) setModValue(separateDualIcons, SDI_GLOW_COLOR, num);
            else gameManager->setPlayerColor3(num);
            return num;
        case ICON_RANDOMIZER_API_GLOW:
            if (useDual) setModValue(separateDualIcons, SDI_GLOW, glow);
            else gameManager->setPlayerGlow(glow);
            return glow;
        case ICON_RANDOMIZER_API_CUBE:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_CUBE, num);
                else gameManager->setPlayerFrame(num);
                MoreIcons::setIcon("", IconType::Cube, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Cube, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SHIP:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_SHIP, num);
                else gameManager->setPlayerShip(num);
                MoreIcons::setIcon("", IconType::Ship, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Ship, useDual);
            return 0;
        case ICON_RANDOMIZER_API_BALL:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_BALL, num);
                else gameManager->setPlayerBall(num);
                MoreIcons::setIcon("", IconType::Ball, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Ball, useDual);
            return 0;
        case ICON_RANDOMIZER_API_UFO:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_UFO, num);
                else gameManager->setPlayerBird(num);
                MoreIcons::setIcon("", IconType::Ufo, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Ufo, useDual);
            return 0;
        case ICON_RANDOMIZER_API_WAVE:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_WAVE, num);
                else gameManager->setPlayerDart(num);
                MoreIcons::setIcon("", IconType::Wave, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Wave, useDual);
            return 0;
        case ICON_RANDOMIZER_API_ROBOT:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_ROBOT, num);
                else gameManager->setPlayerRobot(num);
                MoreIcons::setIcon("", IconType::Robot, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Robot, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SPIDER:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_SPIDER, num);
                else gameManager->setPlayerSpider(num);
                MoreIcons::setIcon("", IconType::Spider, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Spider, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SWING:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_SWING, num);
                else gameManager->setPlayerSwing(num);
                MoreIcons::setIcon("", IconType::Swing, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Swing, useDual);
            return 0;
        case ICON_RANDOMIZER_API_JETPACK:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_JETPACK, num);
                else gameManager->setPlayerJetpack(num);
                MoreIcons::setIcon("", IconType::Jetpack, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Jetpack, useDual);
            return 0;
        case ICON_RANDOMIZER_API_DEATH_EFFECT:
            if (useDual) setModValue(separateDualIcons, SDI_DEATH, num);
            else gameManager->setPlayerDeathEffect(num);
            return num;
        case ICON_RANDOMIZER_API_TRAIL:
            if (idx < vec.size()) {
                if (useDual) setModValue(separateDualIcons, SDI_TRAIL, num);
                else gameManager->setPlayerStreak(num);
                MoreIcons::setIcon("", IconType::Special, useDual);
                return num;
            }
            MoreIcons::setIcon(loadedIcons[num], IconType::Special, useDual);
            return 0;
        case ICON_RANDOMIZER_API_SHIP_FIRE:
            if (useDual) setModValue(separateDualIcons, SDI_SHIP_FIRE, num);
            else gameManager->setPlayerShipStreak(num);
            return num;
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
    auto gameManager = GameManager::sharedState();
    auto separateDualIcons = Loader::get()->getLoadedMod(SDI_ID);
    auto useDual = separateDualIcons && dual;

    // Get the value from the Separate Dual Icons mod if it is enabled and the dual parameter is true, otherwise get the value from the game manager.
    switch (type) {
        case ICON_RANDOMIZER_API_COLOR_1:
            return useDual ? getModValue(separateDualIcons, SDI_COLOR_1, 0) : gameManager->getPlayerColor();
        case ICON_RANDOMIZER_API_COLOR_2:
            return useDual ? getModValue(separateDualIcons, SDI_COLOR_2, 0) : gameManager->getPlayerColor2();
        case ICON_RANDOMIZER_API_GLOW_COLOR:
            return useDual ? getModValue(separateDualIcons, SDI_GLOW_COLOR, 0) : gameManager->getPlayerGlowColor();
        case ICON_RANDOMIZER_API_GLOW:
            return useDual ? getModValue(separateDualIcons, SDI_GLOW, false) : gameManager->getPlayerGlow();
        case ICON_RANDOMIZER_API_CUBE:
            return useDual ? getModValue(separateDualIcons, SDI_CUBE, 1) : gameManager->getPlayerFrame();
        case ICON_RANDOMIZER_API_SHIP:
            return useDual ? getModValue(separateDualIcons, SDI_SHIP, 1) : gameManager->getPlayerShip();
        case ICON_RANDOMIZER_API_BALL:
            return useDual ? getModValue(separateDualIcons, SDI_BALL, 1) : gameManager->getPlayerBall();
        case ICON_RANDOMIZER_API_UFO:
            return useDual ? getModValue(separateDualIcons, SDI_UFO, 1) : gameManager->getPlayerBird();
        case ICON_RANDOMIZER_API_WAVE:
            return useDual ? getModValue(separateDualIcons, SDI_WAVE, 1) : gameManager->getPlayerDart();
        case ICON_RANDOMIZER_API_ROBOT:
            return useDual ? getModValue(separateDualIcons, SDI_ROBOT, 1) : gameManager->getPlayerRobot();
        case ICON_RANDOMIZER_API_SPIDER:
            return useDual ? getModValue(separateDualIcons, SDI_SPIDER, 1) : gameManager->getPlayerSpider();
        case ICON_RANDOMIZER_API_SWING:
            return useDual ? getModValue(separateDualIcons, SDI_SWING, 1) : gameManager->getPlayerSwing();
        case ICON_RANDOMIZER_API_JETPACK:
            return useDual ? getModValue(separateDualIcons, SDI_JETPACK, 1) : gameManager->getPlayerJetpack();
        case ICON_RANDOMIZER_API_DEATH_EFFECT:
            return useDual ? getModValue(separateDualIcons, SDI_DEATH, 1) : gameManager->getPlayerDeathEffect();
        case ICON_RANDOMIZER_API_TRAIL:
            return useDual ? getModValue(separateDualIcons, SDI_TRAIL, 1) : gameManager->getPlayerStreak();
        case ICON_RANDOMIZER_API_SHIP_FIRE:
            return useDual ? getModValue(separateDualIcons, SDI_SHIP_FIRE, 1) : gameManager->getPlayerShipFire();
        default:
            return -1;
    }
}
