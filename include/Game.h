#pragma once

#include "myUtility.h"
#include "Deck.h"
#include "Player.h"
#include <string>
#include <vector>

using namespace myUtility;
using namespace std;

class Game 
{
public:
    Game();
    void Play();
    void NewRound();
    void NextAttacker();
    void RestockCards();
    void CheckIfPlayersOut();

private:
    Deck deck;
    int player_count = 0;
    int cards_per_player = 6;
    string koz = "None";
    vector<Player> players = {};
    bool gameOver = false;
    int turn = -1;
    int attacker_turn = -1; // During the round there's multiple attackers
    int defender_turn = -1;
    int GetStartingTurn();
};