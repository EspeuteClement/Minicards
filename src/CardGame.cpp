//
// Created by Element on 04/03/2018.
//

#include "CardGame.h"
#include "MiniCards.h"

CardGame::CardData tmpDatabase[] =
{
    {1,2,3,4,4},
    {2,3,4,5,9},
    {3,6,1,4,2},
    {4,4,5,7,1},
    {5,3,7,6,3},
};

void CardGame::Init() {
    Player * ply = &players[0];
    ply->Hand[0] = {&tmpDatabase[0], CardStatus::RED};
    ply->Hand[1] = {&tmpDatabase[1], CardStatus::RED};
    ply->Hand[2] = {&tmpDatabase[2], CardStatus::RED};
    ply->Hand[3] = {&tmpDatabase[3], CardStatus::RED};
    ply->Hand[4] = {&tmpDatabase[4], CardStatus::RED};
    ply->current_selected_card_id = 0;
    ply->current_selected_spot = 0;
    ply->score = 5;
    ply->cards_in_hand = 5;

    ply = &players[1];
    ply->Hand[0] = {&tmpDatabase[0], CardStatus::BLUE};
    ply->Hand[1] = {&tmpDatabase[1], CardStatus::BLUE};
    ply->Hand[2] = {&tmpDatabase[2], CardStatus::BLUE};
    ply->Hand[3] = {&tmpDatabase[3], CardStatus::BLUE};
    ply->Hand[4] = {&tmpDatabase[4], CardStatus::BLUE};
    ply->current_selected_card_id = 0;
    ply->current_selected_spot = 0;
    ply->score = 5;
    ply->cards_in_hand = 5;

    for (int i = 0; i < 9; i++)
    {
        board[i].status = CardStatus::STATUS_NULL;
        board[i].data = nullptr;
    }

    //board[4] = {&tmpDatabase[0], CardStatus::BLUE};

    gameTick = 0;
    current_player_id = 0;

    CurrentPhase = PHASE_SELECT_CARD;
}

void CardGame::Update() {

    gameTick ++;
    // Select card

    switch(CurrentPhase)
    {
    case PHASE_SELECT_CARD:
        UpdateSelectCard();
        break;
    case PHASE_SELECT_SPOT:
        UpdateSelectSpot();
        break;
    case PHASE_ANIMATION:break;
    }



}
void CardGame::UpdateSelectCard()
{
    Player * ply = &players[current_player_id];
    if (IsPressed(Styx::BTN_UP))
    {
        if (ply->current_selected_card_id > 0)
        {
            ply->current_selected_card_id --;
        }
    }

    if (IsPressed(Styx::BTN_DOWN))
    {
        if (ply->current_selected_card_id < ply->cards_in_hand-1)
        {
            ply->current_selected_card_id ++;
        }
    }

    if (IsPressed(Styx::BTN_A))
    {
        CardInstance * card = &ply->Hand[ply->current_selected_card_id];
        if (card && card->status != CardStatus::STATUS_NULL)
        {
            CurrentPhase = PHASE_SELECT_SPOT;
        }
    }
}

void CardGame::UpdateSelectSpot()
{
    Player * ply = &players[current_player_id];

    if (IsPressed(Styx::BTN_B))
    {
        CurrentPhase = PHASE_SELECT_CARD;
    }

    if (IsPressed(Styx::BTN_A))
    {
        if (PlayCard(current_player_id, ply->current_selected_card_id, ply->current_selected_spot))
        {
            current_player_id = !current_player_id;
            CurrentPhase = PHASE_SELECT_CARD;
            return;
        }
    }

    if (IsPressed(Styx::BTN_LEFT))
    {
        if (ply->current_selected_spot % 3 > 0)
        {
            ply->current_selected_spot--;
        }
    }

    if (IsPressed(Styx::BTN_RIGHT))
    {
        if (ply->current_selected_spot % 3 < 2)
        {
            ply->current_selected_spot++;
        }
    }

    if (IsPressed(Styx::BTN_UP))
    {
        if (ply->current_selected_spot / 3 > 0)
        {
            ply->current_selected_spot-=3;
        }
    }

    if (IsPressed(Styx::BTN_DOWN))
    {
        if (ply->current_selected_spot / 3 < 2)
        {
            ply->current_selected_spot+=3;
        }
    }

}

void CardGame::Draw() {

    Styx::SetColor(Colors::COLOR_WHITE);

    Styx::DrawImage(4,0,0,0);

    DrawHand(0, false);
    DrawHand(1, false);

    // DrawBoard

    for( int i = 0; i < 9; i++)
    {
        int pos_x = (i % 3)*16 + 16;
        int pos_y = (i / 3)*16 + 6;

        DrawCard(pos_x, pos_y, board[i], false);
    }

    // Draw score
    Styx::DrawImage(2, players[0].score-1, 20, 56);
    Styx::DrawImage(2, players[1].score-1, 57, 56);

    // Draw phase specifics
    switch(CurrentPhase)
    {
    case PHASE_SELECT_CARD:
        DrawSelectCard();
        break;
    case PHASE_SELECT_SPOT:
        DrawSelectSpot();
        break;
    case PHASE_ANIMATION:break;
    }
}

void CardGame::DrawCard(int16_t x, int16_t y, const CardInstance &card, bool isHighlight)
{
    if (card.status == CardStatus::STATUS_NULL || card.data == nullptr) return;

    Styx::DrawImage(3, card.status == CardStatus::BLUE, x, y);

    if (isHighlight)
    {
        Styx::DrawImage(3, 2, x, y);
    }

    Styx::DrawImage(2, card.data->up-1, x+4, y+0);
    Styx::DrawImage(2, card.data->down-1, x+4, y+6);
    Styx::DrawImage(2, card.data->left-1, x+0, y+2);
    Styx::DrawImage(2, card.data->right-1, x+8, y+2);

    Styx::DrawImage(0, card.data->monster_id, x+7, y+7);
}

void CardGame::DrawHand(int player, bool hidden)
{
    const int Y_OFFSET = 12;

    int8_t selected_index = players[player].current_selected_card_id;

    int pos_x = 0;
    if (player != 0)
    {
        pos_x = 64;
    }

    // Draw the other cards
    int pos_y = 0;
    for (int i = 0; i < 5; i++)
    {
        if (i == selected_index)
        {
            pos_y += 16;
            continue;
        }
        DrawCard(pos_x, pos_y, players[player].Hand[i], false);
        pos_y += Y_OFFSET;
    }

    // Draw the selected card first
    pos_y = selected_index * Y_OFFSET;

    if (selected_index >= 0)
    {
        bool shouldFlashSelect = (CurrentPhase == PHASE_SELECT_CARD) && (player == current_player_id ) && ((gameTick / 4) % 2);
        DrawCard(pos_x, pos_y, players[player].Hand[selected_index], shouldFlashSelect);
    }
}
void CardGame::DrawSelectCard()
{

}
void CardGame::DrawSelectSpot()
{
    bool shouldFlashSelect = ((gameTick / 4) % 2);

    if (shouldFlashSelect)
    {
        Player * ply = &players[current_player_id];

        int pos_x = (ply->current_selected_spot % 3)*16 + 16;
        int pos_y = (ply->current_selected_spot / 3)*16 + 6;

        Styx::DrawImage(3, 2, pos_x, pos_y);
    }

}
bool CardGame::PlayCard(int8_t player, int8_t card_in_hand_id, int8_t board_position)
{
    if (board[board_position].status == CardStatus::STATUS_NULL)
    {
        Player * ply = &players[player];
        const CardData * card_data = ply->Hand[card_in_hand_id].data;
        ply->Hand[card_in_hand_id].status = CardStatus::STATUS_NULL;

        board[board_position].status = player;
        board[board_position].data = card_data;

        ply->cards_in_hand --;
        
        CompactPlayerHand(player);

        UpdateBoard(board_position);

        return true;
    }

    return false;
}

void CardGame::CompactPlayerHand(int8_t player)
{
    Player * ply = &players[player];
    ply->current_selected_card_id = 0;
    for (int i = 0; i < 5; i++)
    {
        CardInstance * current_slot = &ply->Hand[i];
        if (current_slot->status == CardStatus::STATUS_NULL)
        {
            for (int j = i+1; j < 5; j++)
            {
                CardInstance * other_slot = &ply->Hand[j];

                if (other_slot->status != CardStatus::STATUS_NULL)
                {
                    // Perform "swap"
                    *current_slot = *other_slot;
                    other_slot->status = CardStatus ::STATUS_NULL;
                    break;
                }
            }
        }
    }
}
void CardGame::UpdateBoard(int8_t new_card_pos)
{
    // Simple Flip test
    CardInstance * card = &board[new_card_pos];

    for (int i = 0; i < 4; i++)
    {
        CardInstance * other_card = nullptr;
        int8_t our_value, their_value;

        switch (i)
        {
        case 0: // Card is above
            if (new_card_pos / 3 > 0)
            {
                other_card = &board[new_card_pos-3];
                our_value = card->data->up;
                if (other_card->status != CardStatus::STATUS_NULL)
                    their_value = other_card->data->down;
            }
            break;
        case 1: // Card is left
            if (new_card_pos % 3 > 0)
            {
                other_card = &board[new_card_pos-1];
                our_value = card->data->left;
                if (other_card->status != CardStatus::STATUS_NULL)
                    their_value = other_card->data->right;
            }
            break;
        case 2: // Card is down
            if (new_card_pos / 3 < 2)
            {
                other_card = &board[new_card_pos+3];
                our_value = card->data->down;
                if (other_card->status != CardStatus::STATUS_NULL)
                    their_value = other_card->data->up;
            }
            break;
        case 3: // Card is right
            if (new_card_pos % 3 < 2)
            {
                other_card = &board[new_card_pos+1];
                our_value = card->data->right;
                if (other_card->status != CardStatus::STATUS_NULL)
                    their_value = other_card->data->left;
            }
            break;
        default:
            break;
        }

        if (other_card &&
            other_card->status != CardStatus::STATUS_NULL &&
            other_card->status != card->status &&
            our_value > their_value)
        {
            other_card->status = card->status;
            players[current_player_id].score ++;
            players[(current_player_id + 1) % 2].score --;
            
        }

    }

}

void CardGame::UpdateBoard(int8_t newCard, CardGame::BoardInfo info[])
{

}