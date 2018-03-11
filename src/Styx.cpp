//
// Created by Element on 25/02/2018.
//
#include "Styx.h"

void Styx::DrawText(const char * text, uint8_t font_bank, int16_t x, int16_t y)
{
    const ImageInfo & bank = Styx::ImageData[font_bank];

    uint8_t cursor = 0;
    const uint8_t ASCII_OFFSET = '!';

    while( text[cursor] != '\0')
    {
        char currentChar = text[cursor];
        bool isCurrentCharSpace = currentChar == ' ';
        if (!isCurrentCharSpace)
        {
            uint8_t imageIndex = (uint8_t)currentChar - ASCII_OFFSET;
            Styx::DrawImage(font_bank, imageIndex, x, y);
        }

        cursor ++;
        x += bank.spr_width + 1;
    }

}
