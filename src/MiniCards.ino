#include <Gamebuino-Meta.h>
#include "Styx.h"

void setup()
{
    gb.begin();
    Styx::LoadImages();
    Styx::Init();
}

void loop()
{
    if (gb.update())
    {
        Styx::Update();
        gb.display.clear(WHITE);
        Styx::Draw();
    }
}

void Styx::SetColor(uint8_t color_index)
{
    Gamebuino_Meta::Graphics::tint = *(uint16_t *) ColorTable[color_index];
}

void Styx::DrawImage(uint8_t bank, uint8_t id, int16_t x, int16_t y, ImageFlip flip)
{
    Image * img = (Image*)(Styx::ImageData[bank].ptr);
    int16_t width =  Styx::ImageData[bank].spr_width;
    int16_t height =  Styx::ImageData[bank].spr_height;
    img->setFrame(id);
    switch (flip)
    {
        case ImageFlip::NONE :
            gb.display.drawImage(x,y, *img);
            break;
        case ImageFlip::H_FLIP :
            gb.display.drawImage(x,y, *img, -width, height);
            break;
        case ImageFlip::V_FLIP :
            gb.display.drawImage(x,y+height, *img, width, -height);
            break;
        case ImageFlip ::HV_FLIP :
            gb.display.drawImage(x+width,y+height, *img, -width, -height);
            break;
    }
}

bool Styx::IsDown(Styx::Buttons button)
{
    switch (button)
    {

        case BTN_A:
            return gb.buttons.repeat(BUTTON_A,0);
            break;
        case BTN_B:
            return gb.buttons.repeat(BUTTON_B,0);
            break;
        case BTN_MENU:
            return gb.buttons.repeat(BUTTON_MENU,0);
            break;
        case BTN_UP:
            return gb.buttons.repeat(BUTTON_UP,0);
            break;
        case BTN_DOWN:
            return gb.buttons.repeat(BUTTON_DOWN,0);
            break;
        case BTN_LEFT:
            return gb.buttons.repeat(BUTTON_LEFT,0);
            break;
        case BTN_RIGHT:
            return gb.buttons.repeat(BUTTON_RIGHT,0);
            break;
    }
    return false;
}

bool Styx::IsPressed(Styx::Buttons button)
{
    switch (button)
    {

        case BTN_A:
            return gb.buttons.pressed(BUTTON_A);
            break;
        case BTN_B:
            return gb.buttons.pressed(BUTTON_B);
            break;
        case BTN_MENU:
            return gb.buttons.pressed(BUTTON_MENU);
            break;
        case BTN_UP:
            return gb.buttons.pressed(BUTTON_UP);
            break;
        case BTN_DOWN:
            return gb.buttons.pressed(BUTTON_DOWN);
            break;
        case BTN_LEFT:
            return gb.buttons.pressed(BUTTON_LEFT);
            break;
        case BTN_RIGHT:
            return gb.buttons.pressed(BUTTON_RIGHT);
            break;
    }
    return false;
}