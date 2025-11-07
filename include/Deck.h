#pragma once
#include <vector>
#include <string>

class Deck {
public:
    Deck();
    std::vector<std::string> DealCards(int count); 
    void Shuffle();
    std::string GetKoz();

private:
    std::vector<std::string> cards;
    std::string koz = "None";
};