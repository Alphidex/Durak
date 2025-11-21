#include "Deck.h"
#include "myUtility.h"
#include <random>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
using namespace myUtility;

Deck::Deck() {
    vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    vector<string> ranks = {"6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    
    for (auto suit : suits) {
        for (auto rank : ranks) {
            cards.push_back(Card(rank + " of " + suit));
        }
    }
    Shuffle();
}

vector<Card> Deck::DealCards(int count) {
    vector<Card> dealt;
    for (int i = 0; i < count && !cards.empty(); ++i) {
        dealt.push_back(cards.back());
        cards.pop_back();
    }
    if (cards.empty()) {
        print("\n\tDeck is out of cards!\n");
    }
    return dealt;
}

void Deck::Shuffle() {
    // Initialize random number generator
    random_device rd;
    mt19937 g(rd());

    // Shuffle the vector
    shuffle(cards.begin(), cards.end(), g);
}

bool Deck::Empty() {
    return cards.size() == 0;
}

string Deck::GetKoz()
{
    if (koz == "None")
    {
        Card trump = cards.back();
        koz = split_space(trump.name).back();
        
        // The shown trump-card goes to the front
        cards.pop_back();
        cards.insert(cards.begin(), trump);
    } 
    print("\n\t*** Koz is: " + koz + " ***");
    return koz;
}