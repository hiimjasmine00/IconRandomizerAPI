#pragma once
#include "Enums.hpp"
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

namespace IconRandomizer {
    /// The function to initalize the Icon Randomizer API.
    /// It is recommended that this function is called before any other functions in the API, but it is done automatically if forgotten.
    /// This function can be rerun to refresh the unlocked icons and colors.
    ICON_RANDOMIZER_API_DLL void init();

    /// A function to convert an icon type to a randomize type.
    /// @param type The icon type to convert.
    /// @returns The randomize type for the icon type.
    ICON_RANDOMIZER_API_DLL RandomizeType fromIconType(IconType type);

    /// A function to convert an unlock type to a randomize type.
    /// @param type The unlock type to convert.
    /// @returns The randomize type for the unlock type.
    ICON_RANDOMIZER_API_DLL RandomizeType fromUnlockType(UnlockType type);

    /// A function to convert a randomize type to an icon type.
    /// @param type The randomize type to convert.
    /// @returns The icon type for the randomize type.
    ICON_RANDOMIZER_API_DLL IconType toIconType(RandomizeType type);

    /// A function to convert a randomize type to an unlock type.
    /// @param type The randomize type to convert.
    /// @returns The unlock type for the randomize type.
    ICON_RANDOMIZER_API_DLL UnlockType toUnlockType(RandomizeType type);

    /// The function to randomize an icon or color.
    /// @param type The type of icon or color to randomize.
    /// @param dual Whether or not to randomize the separate dual icon or color. (Requires the mod "Separate Dual Icons" by Weebify)
    /// @returns The ID of the randomized icon.
    ICON_RANDOMIZER_API_DLL int randomize(RandomizeType type, bool dual = false);

    /// The function to randomize multiple types of icons or colors at once.
    /// @param type The types of icons to randomize.
    /// @param dual Whether or not to randomize the separate dual icon or color. (Requires the mod "Separate Dual Icons" by Weebify)
    ICON_RANDOMIZER_API_DLL void randomizeAll(RandomizeAllType type, bool dual = false);

    /// Gets the current icon or color ID for a specific type.
    /// @param type The type of icon or color to get the ID for.
    /// @param dual Whether or not to get the ID for the separate dual icon or color. (Requires the mod "Separate Dual Icons" by Weebify)
    /// @returns The ID of the current icon.
    ICON_RANDOMIZER_API_DLL int active(RandomizeType type, bool dual = false);
}
