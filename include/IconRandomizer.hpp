#include <Geode/Enums.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifdef ICON_RANDOMIZER_API_EXPORTING
        #define ICON_RANDOMIZER_API_DLL __declspec(dllexport)
    #else
        #define ICON_RANDOMIZER_API_DLL __declspec(dllimport)
    #endif
#else
    #ifdef ICON_RANDOMIZER_API_EXPORTING
        #define ICON_RANDOMIZER_API_DLL __attribute__((visibility("default")))
    #else
        #define ICON_RANDOMIZER_API_DLL
    #endif
#endif

/// The types of icons and colors that can be randomized.
enum RandomizeType {
    ICON_RANDOMIZER_API_COLOR_1 = 0,
    ICON_RANDOMIZER_API_COLOR_2 = 1,
    ICON_RANDOMIZER_API_GLOW_COLOR = 2,
    ICON_RANDOMIZER_API_GLOW = 3,
    ICON_RANDOMIZER_API_CUBE = 4,
    ICON_RANDOMIZER_API_SHIP = 5,
    ICON_RANDOMIZER_API_BALL = 6,
    ICON_RANDOMIZER_API_UFO = 7,
    ICON_RANDOMIZER_API_WAVE = 8,
    ICON_RANDOMIZER_API_ROBOT = 9,
    ICON_RANDOMIZER_API_SPIDER = 10,
    ICON_RANDOMIZER_API_SWING = 11,
    ICON_RANDOMIZER_API_JETPACK = 12,
    ICON_RANDOMIZER_API_DEATH_EFFECT = 13,
    ICON_RANDOMIZER_API_TRAIL = 14,
    ICON_RANDOMIZER_API_SHIP_FIRE = 15,
    ICON_RANDOMIZER_API_ANIMATION = 16,
    ICON_RANDOMIZER_API_EXPLODE = 17
};

/// The types of groups of icons and colors that can be randomized.
enum RandomizeAllType {
    ICON_RANDOMIZER_API_ALL_ICONS = 0,
    ICON_RANDOMIZER_API_ALL_SPECIAL = 1,
    ICON_RANDOMIZER_API_ALL_COLORS = 2
};

/// The class for the Icon Randomizer API.
class ICON_RANDOMIZER_API_DLL IconRandomizer {
public:
    /// The function to initalize the Icon Randomizer API.
    /// It is recommended that this function is called before any other functions in the API, but it is done automatically if forgotten.
    /// This function can be rerun to refresh the unlocked icons and colors.
    static void init();

    /// A function to get a random number using the mersenne twister algorithm.
    /// @param min The minimum number to generate.
    /// @param max The maximum number to generate.
    /// @returns A random number between min and max.
    static int random(int min, int max);

    /// A function to convert an icon type to a randomize type.
    /// @param type The icon type to convert.
    /// @returns The randomize type for the icon type.
    static RandomizeType fromIconType(IconType type);

    /// A function to convert an unlock type to a randomize type.
    /// @param type The unlock type to convert.
    /// @returns The randomize type for the unlock type.
    static RandomizeType fromUnlockType(UnlockType type);

    /// A function to convert a randomize type to an icon type.
    /// @param type The randomize type to convert.
    /// @returns The icon type for the randomize type.
    static IconType toIconType(RandomizeType type);

    /// A function to convert a randomize type to an unlock type.
    /// @param type The randomize type to convert.
    /// @returns The unlock type for the randomize type.
    static UnlockType toUnlockType(RandomizeType type);

    /// The function to randomize an icon or color.
    /// @param type The type of icon or color to randomize.
    /// @param dual Whether or not to randomize the separate dual icon or color. (Requires the mod "Separate Dual Icons" by Weebify)
    /// @returns The ID of the randomized icon.
    static int randomize(RandomizeType type, bool dual = false);

    /// The function to randomize multiple types of icons or colors at once.
    /// @param type The types of icons to randomize.
    /// @param dual Whether or not to randomize the separate dual icon or color. (Requires the mod "Separate Dual Icons" by Weebify)
    static void randomizeAll(RandomizeAllType type, bool dual = false);

    /// Gets the current icon or color ID for a specific type.
    /// @param type The type of icon or color to get the ID for.
    /// @param dual Whether or not to get the ID for the separate dual icon or color. (Requires the mod "Separate Dual Icons" by Weebify)
    /// @returns The ID of the current icon.
    static int active(RandomizeType type, bool dual = false);
};
