#pragma once
#include <string>
using namespace std;

class Card
{
public:
    string rank;
    string suit;
    string name;
    Card(string s);
    bool BiggerThan(Card& c, string& koz);
    bool IsKoz(string& koz);
};
