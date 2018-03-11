//
// Created by Element on 04/03/2018.
//

#ifndef MINICARD_CARDGAME_H
#define MINICARD_CARDGAME_H
#include "Styx.h"

class CardGame {

public:
    void Init();
    void Update();
    void Draw();

    enum Phase
    {
        PHASE_SELECT_CARD,
        PHASE_SELECT_SPOT,
        PHASE_ANIMATION
    };

    Phase CurrentPhase;

    struct CardData
    {
        uint8_t monster_id;
        uint8_t up : 4;
        uint8_t down : 4;
        uint8_t left : 4;
        uint8_t right : 4;
    };

    enum CardStatus
    {
        STATUS_NULL = 255,
        RED = 0,
        BLUE = 1
    };

    struct CardInstance
    {
        const CardData * data;
        uint8_t status;
    };

    // Used by the UpdateBoard function to handle recursion on the board ...
    struct BoardInfo
    {
        CardInstance * Instance;
        bool visited;
    };

    struct Player
    {
        CardInstance Hand[5];
        uint8_t score;
        int8_t current_selected_card_id;
        int8_t current_selected_spot;
        int8_t cards_in_hand;
    };

private:

    CardInstance board[9];
    CardInstance hands[2][5];

    Player players[2];

    static void DrawCard(int16_t x, int16_t y, const CardInstance &card, bool isHighlight);
    void DrawHand(int player, bool hidden);

    int8_t current_player_id;

    uint32_t gameTick;
    void UpdateSelectCard();
    void UpdateSelectSpot();
    void DrawSelectCard();
    void DrawSelectSpot();

    // Returns true if the card was played, false otherwise
    bool PlayCard(int8_t player, int8_t card_in_hand_id, int8_t board_position);
    void CompactPlayerHand(int8_t player);
    void UpdateBoard(int8_t new_card_pos);
    void UpdateBoard(int8_t newCard, BoardInfo *info);
};


#endif //MINICARD_CARDGAME_H
