#pragma once
#include "Card.h"
#include <string>
#include <vector>
using namespace std;

class Player
{
public:
    int id;
    string name {};
    vector<Card> cards;

    Player(int id, vector<Card> cards);
    bool Empty();
    Card GreatestCard(string koz);
    void PickupCards(vector<Card> picked_cards);
    string Attack(string koz, vector<Card> cards_in_round);
    string Defend(string koz, Card attack_card);
};