#include "myUtility.h"
#include "Card.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>
using namespace std;
using namespace myUtility;

std::vector<std::string> ranks = {"6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
std::vector<std::string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};

Card::Card(string s){
    vector<string> rank_suit = split_space(s);
    rank = rank_suit.front();
    suit = rank_suit.back();
    name = s;
}

bool Card::IsKoz(string& koz){
    return koz == suit;
}

bool Card::BiggerThan(Card& c, string& koz){
    bool is_koz = koz == suit; 
    if (is_koz && !c.IsKoz(koz)) return true;

    // Comparing based on index in ranks
    auto it1 = find(ranks.begin(), ranks.end(), rank);
    auto it2 = find(ranks.begin(), ranks.end(), c.rank);
    int a = distance(ranks.begin(), it1);
    int b = distance(ranks.begin(), it2);

    return a > b;
}
