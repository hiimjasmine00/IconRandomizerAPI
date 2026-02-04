# Icon Randomizer API
A mod that provides an API for randomizing icons and colors.

## Usage
To use this API, you must first add the following dependency to your `mod.json` file:
```json
{
    "dependencies": {
        "hiimjustin000.icon_randomizer_api": ">=v3.0.0"
    }
}
```

Then, you can use the API. For example:
```cpp
// Include the API
#include <hiimjustin000.icon_randomizer_api/include/IconRandomizer.hpp>

using namespace geode::prelude;

// Initialize the randomizer
IconRandomizer::init();

// Randomize an icon or color
IconRandomizer::randomize(RandomizeType::Cube);
IconRandomizer::randomize(RandomizeType::Color1);

// Randomize all of a certain type
IconRandomizer::randomizeAll(RandomizeAllType::Icons);
IconRandomizer::randomizeAll(RandomizeAllType::Special);
IconRandomizer::randomizeAll(RandomizeAllType::Colors);

// Refresh unlocked icons and colors
IconRandomizer::init();

// Randomize a separate dual icon or color (Requires the Separate Dual Icons mod by Weebify)
IconRandomizer::randomize(RandomizeType::Cube, true);
IconRandomizer::randomize(RandomizeType::Color1, true);

// Randomize all of a certain type for a separate dual icon or color
IconRandomizer::randomizeAll(RandomizeAllType::Icons, true);
IconRandomizer::randomizeAll(RandomizeAllType::Special, true);
IconRandomizer::randomizeAll(RandomizeAllType::Colors, true);
```
Full documentation can be found [here](https://github.com/hiimjasmine00/IconRandomizerAPI/blob/master/include/IconRandomizer.hpp).

## Constants
The following enums are available for use:
```cpp
enum class RandomizeType {
    Color1 = 0,
    Color2 = 1,
    GlowColor = 2,
    Glow = 3,
    Cube = 4,
    Ship = 5,
    Ball = 6,
    Ufo = 7,
    Wave = 8,
    Robot = 9,
    Spider = 10,
    Swing = 11,
    Jetpack = 12,
    DeathEffect = 13,
    Trail = 14,
    ShipFire = 15,
    Animation = 16,
    Explode = 17
};

enum class RandomizeAllType {
    Icons = 0,
    Special = 1,
    Colors = 2
};
```

## License
This mod is licensed under the [MIT License](https://github.com/hiimjasmine00/IconRandomizerAPI/blob/master/LICENSE).
