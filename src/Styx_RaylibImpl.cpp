//
// Created by Element on 24/02/2018.
//

#include "Styx_RaylibImpl.h"

#ifdef PLATFORM_RAYLIB

/*******************************************************************************************
*
*   raylib [core] example - Basic window (adapted for HTML5 platform)
*
*   This example is prepared to compile for PLATFORM_WEB, PLATFORM_DESKTOP and PLATFORM_RPI
*   As you will notice, code structure is slightly diferent to the other examples...
*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/


#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 80*6;
int screenHeight = 64*6;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame
RenderTexture2D Screen;

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Styx::LoadImages();

    Screen = LoadRenderTexture(80,64);
    SetTextureFilter(Screen.texture, FILTER_POINT);

    Styx::Init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 30, 1);
    SetTargetFPS(60);
#else
    // Set our game to run at 60 frames-per-second
    SetTargetFPS(30);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    Styx::Update();

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    //ClearBackground(BLACK);
    BeginTextureMode(Screen);

    Styx::Draw();

    EndTextureMode();

    DrawTexturePro(Screen.texture, (Rectangle){0,0,Screen.texture.width, -Screen.texture.height}, (Rectangle){ 0, 0, Screen.texture.width*6, Screen.texture.height*6}, (Vector2){ 0, 0 },0.0f, WHITE);
    EndDrawing();
    //----------------------------------------------------------------------------------
}

Color CurrentDrawColor = WHITE;

void Styx::SetColor(uint8_t color_index)
{
    CurrentDrawColor = *(Color*) ColorTable[color_index];
}

void Styx::DrawImage(uint8_t bank, uint8_t id, int16_t x, int16_t y, ImageFlip flip)
{
    int16_t width = Styx::ImageData[bank].spr_width;
    int16_t height = Styx::ImageData[bank].spr_height;

    int16_t origin_x = (id) % Styx::ImageData[bank].spr_per_row;
    origin_x *= width;
    int16_t origin_y = (id / Styx::ImageData[bank].spr_per_row);
    origin_y *= height;


    Rectangle RectOrigin = {origin_x, origin_y, width, height};

    // Todo : Take ImageFlip into account
    const Rectangle RectDest = {x,y,width, height};

    switch (flip)
    {
        case ImageFlip::NONE :
            break;
        case ImageFlip::H_FLIP :
            RectOrigin.width = -width;
            break;
        case ImageFlip::V_FLIP :
            RectOrigin.height = -height;
            break;
        case ImageFlip ::HV_FLIP :
            RectOrigin.width = -width;
            RectOrigin.height = -height;
            break;
    }

    DrawTexturePro(*(Texture2D*) Styx::ImageData[bank].ptr, RectOrigin, RectDest, {0,0}, 0, CurrentDrawColor);

}

void Styx::Clear()
{
    ClearBackground(CurrentDrawColor);
}

bool Styx::IsDown(Styx::Buttons button)
{
    const float DEADZONE = 0.25;
    switch (button)
    {

        case BTN_A:
            return IsKeyDown(KEY_X) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_A);
            break;
        case BTN_B:
            return IsKeyDown(KEY_C) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_B);
            break;
        case BTN_MENU:
            return IsKeyDown(KEY_ENTER) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_START);
            break;
        case BTN_UP:
            return IsKeyDown(KEY_UP) || GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LEFT_Y) > DEADZONE;
            break;
        case BTN_DOWN:
            return IsKeyDown(KEY_DOWN) || GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LEFT_Y) < -DEADZONE;
            break;
        case BTN_LEFT:
            return IsKeyDown(KEY_LEFT) || GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LEFT_X) < -DEADZONE;
            break;
        case BTN_RIGHT:
            return IsKeyDown(KEY_RIGHT) || GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_XBOX_AXIS_LEFT_X) > DEADZONE;
            break;
    }
    return false;
}

bool Styx::IsPressed(Styx::Buttons button)
{
    const float DEADZONE = 0.25;
    switch (button)
    {

    case BTN_A:
        return IsKeyPressed(KEY_X) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_A);
        break;
    case BTN_B:
        return IsKeyPressed(KEY_C) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_B);
        break;
    case BTN_MENU:
        return IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_START);
        break;
    case BTN_UP:
        return IsKeyPressed(KEY_UP) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_UP);
        break;
    case BTN_DOWN:
        return IsKeyPressed(KEY_DOWN) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_DOWN);
        break;
    case BTN_LEFT:
        return IsKeyPressed(KEY_LEFT) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_LEFT);
        break;
    case BTN_RIGHT:
        return IsKeyPressed(KEY_RIGHT) || IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_XBOX_BUTTON_RIGHT);
        break;
    }
    return false;
}

#endif