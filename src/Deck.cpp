#include "Deck.h"
#include "myUtility.h"
#include <random>
#include <algorithm>

using namespace std;
using namespace myUtility;

Deck::Deck() {
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> ranks = {"6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    
    for (auto suit : suits) {
        for (auto rank : ranks) {
            cards.push_back(rank + " of " + suit);
        }
    }
    Shuffle();
}

vector<string> Deck::DealCards(int count) {
    vector<string> dealt;
    for (int i = 0; i < count && !cards.empty(); ++i) {
        dealt.push_back(cards.back());
        cards.pop_back();
    }
    return dealt;
}

void Deck::Shuffle() {
    auto rng = default_random_engine {};
    shuffle(begin(cards), end(cards), rng);
}

string Deck::GetKoz()
{
    if (koz == "None")
    {
        string trump = cards.back();
        koz = split_space(trump).back();

        // The shown trump-card goes to the front
        cards.pop_back();
        cards.insert(cards.begin(), trump);
    } 

    return koz;
}