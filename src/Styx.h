//
// Created by Element on 24/02/2018.
//

#ifndef MINICARD_STYX_H
#define MINICARD_STYX_H

//
// Target defines =====================
//
#if defined(__SAMD21G18A__)
#define PLATFORM_ARDUINO
#elif  defined(EMSCRIPTEN)
#define PLATFORM_WEB
#else
#define PLATFORM_DESKTOP
#endif

#if defined(PLATFORM_DESKTOP) || defined(PLATFORM_WEB)
#define PLATFORM_RAYLIB
#endif

#include <cstdint>

// Main loop function

namespace Styx
{
    enum class ImageFlip : uint8_t
    {
        NONE,
        H_FLIP,
        V_FLIP,
        HV_FLIP
    };

    struct ImageInfo {
        uint8_t spr_width;
        uint8_t spr_height;
        uint8_t spr_per_row;
        void * ptr;
    };

    enum Buttons
    {
        BTN_A,
        BTN_B,
        BTN_MENU,
        BTN_UP,
        BTN_DOWN,
        BTN_LEFT,
        BTN_RIGHT
    };



    typedef void* StyxColor;

    // Should be init by platform specific code
    extern ImageInfo ImageData[];
    extern StyxColor ColorTable[];

    // Called at the begining of the program
    extern void Init();

    // Should be created by the user, called each frame
    extern void Update();

    // Should be created by the user, called each frame
    extern void Draw();

    // Should init all the images for the game depending of the chosen target
    extern void LoadImages();

    // PLATFORM Specific API
    extern void SetColor(uint8_t color_index);
    void DrawImage(uint8_t bank, uint8_t id, int16_t x, int16_t y, Styx::ImageFlip flip = Styx::ImageFlip::NONE);
    void Clear();
    bool IsDown(Buttons button);
    bool IsPressed(Buttons button);

    // Common API
    void DrawText(const char * text, uint8_t font_bank, int16_t x, int16_t y);


}


#endif //MINICARD_STYX_H
