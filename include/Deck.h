#pragma once
#include "Card.h"
#include <vector>
#include <string>

class Deck {
public:
    Deck();
    std::vector<Card> DealCards(int count);
    bool Empty(); 
    void Shuffle();
    std::string GetKoz();
    std::vector<Card> cards;

private:
    std::string koz = "None";
};