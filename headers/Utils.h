// Header file for Crazy Tanks utility objects and functions

#ifndef UTILS_H
#define UTILS_H

#include <windows.h>
#include <array>
#include <random>
#include <ctime>

enum eKey {
            KEYBOARD_ESC,
            KEYBOARD_LEFT,
            KEYBOARD_LEFT_AND_SPACE,
            KEYBOARD_RIGHT,
            KEYBOARD_RIGHT_AND_SPACE,
            KEYBOARD_UP,
            KEYBOARD_UP_AND_SPACE,
            KEYBOARD_DOWN,
            KEYBOARD_DOWN_AND_SPACE,
            KEYBOARD_SPACE,
            KEYBOARD_R
        };
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT};
enum eTag {PLAYER, NPC, BULLET, BRICK, WALL, LIFE_ICON, HEALTH_ICON, ARMOUR_ICON, EXPLOSION, EMPTY};

class Utils final   // final keyword means 'sealed' class (can't inherit from this class)
{
    private:
        static std::mt19937 m_randomGenerator;      // random number generator
        static bool seeded;

    public:
        static const uint16_t MAX_NUMBER = 65535;

        static const int TANK_PATTERN_WIDTH = 20;
        static const int TANK_PATTERN_HEIGHT = 20;
        static const int BULLET_PATTERN_WIDTH = 4;
        static const int BULLET_PATTERN_HEIGHT = 4;
        static const int ICON_PATTERN_WIDTH = 20;
        static const int ICON_PATTERN_HEIGHT = 20;
        static const int BRICK_PATTERN_WIDTH = 10;
        static const int BRICK_PATTERN_HEIGHT = 10;
        static const int EXPLOSION_EFFECT_PAT_WIDTH = 20;
        static const int EXPLOSION_EFFECT_PAT_HEIGHT = 20;
        static const int HEALTH_PATTERN_HEIGHT = 20;
        static const int HEALTH_PATTERN_WIDTH = 20;
        static const int ARMOUR_PATTERN_HEIGHT = 20;
        static const int ARMOUR_PATTERN_WIDTH = 20;
        static const COLORREF COLOR_BLACK = RGB(0, 0, 0);
        static const COLORREF COLOR_WHITE = RGB(255, 255, 255);
        static const COLORREF COLOR_GAINSBORO = RGB(220, 220, 220);
        static const COLORREF COLOR_DARKGREY = RGB(169, 169, 169);
        static const COLORREF COLOR_DIMGREY = RGB(105, 105, 105);
        static const COLORREF COLOR_DARKSLATEGREY = RGB(47, 79, 79);
        static const COLORREF COLOR_RED = RGB(255, 0, 0);
        static const COLORREF COLOR_GREEN = RGB(0, 128, 0);
        static const COLORREF COLOR_BLUE = RGB(0, 0, 255);
        static const COLORREF COLOR_YELLOW = RGB(255, 255, 0);
        static const COLORREF COLOR_ORANGE = RGB(255, 165, 0);

        static COLORREF GetColor(int colorIndex);
        static int GetColorIndex(COLORREF color);

        // random generation functions
        static bool GetRandomFlag();
        static int GetRandomNumber(int min, int max);
        static int GetRandomRoundedNumber(int min, int max);
        static eDirection GetRandomDirection();

        static std::array<int, TANK_PATTERN_WIDTH * TANK_PATTERN_HEIGHT> GetTankPattern(COLORREF color);
        static std::array<int, TANK_PATTERN_WIDTH * TANK_PATTERN_HEIGHT> GetTankArmouredPattern(COLORREF color);
        static std::array<int, BULLET_PATTERN_WIDTH * BULLET_PATTERN_HEIGHT> GetBulletPattern(COLORREF color);
        static std::array<int, ICON_PATTERN_WIDTH * ICON_PATTERN_HEIGHT> GetIconPattern(COLORREF color);
        static std::array<int, BRICK_PATTERN_WIDTH * BRICK_PATTERN_HEIGHT> GetBrickPattern(COLORREF color);
        static std::array<int, HEALTH_PATTERN_WIDTH * HEALTH_PATTERN_HEIGHT> GetHealthPattern();
        static std::array<int, ARMOUR_PATTERN_WIDTH * ARMOUR_PATTERN_HEIGHT> GetArmourPattern();

    private:

        static std::array<int, TANK_PATTERN_WIDTH * TANK_PATTERN_HEIGHT> m_tankPatternArray;
        static std::array<int, TANK_PATTERN_WIDTH * TANK_PATTERN_HEIGHT> m_tankArmouredPatternArray;
        static std::array<int, BULLET_PATTERN_WIDTH * BULLET_PATTERN_HEIGHT> m_bulletPatternArray;
        static std::array<int, ICON_PATTERN_WIDTH * ICON_PATTERN_HEIGHT> m_iconPatternArray;
        static std::array<int, BRICK_PATTERN_WIDTH * BRICK_PATTERN_HEIGHT> m_brickPatternArray;
        static std::array<int, HEALTH_PATTERN_WIDTH * HEALTH_PATTERN_HEIGHT> m_healthPatternArray;
        static std::array<int, ARMOUR_PATTERN_WIDTH * ARMOUR_PATTERN_HEIGHT> m_armourPatternArray;

        Utils() {}  // it is private to disallow creating instance of this class    
};

#endif 