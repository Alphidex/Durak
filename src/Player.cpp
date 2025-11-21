// #include "myUtility.h"
// #include "Deck.h"
// #include "Card.h"
// #include <string>
// #include <vector>
// using namespace std;
#include "Player.h"
#include "myUtility.h"
using namespace myUtility;

Player::Player(int id, vector<Card> cards) : id(id), cards(cards){
    name = input("Player " + to_string(id) +  ", please enter a name: ");
}

Card Player::GreatestCard(string koz){
    Card greatest = cards.front();
    for (Card card : cards){
        if (card.BiggerThan(greatest, koz)) {greatest = card;}
    }
    return greatest;
}

void Player::PickupCards(vector<Card> picked_cards){
    for (Card card : picked_cards){
        cards.push_back(card);
    }
}

bool Player::Empty(){
    return cards.size() == 0;
}

string Player::Attack(string koz, vector<Card> cards_in_round){
    bool first_attack = cards_in_round.size() == 0;

    print(repeat("-", 20));

    print("These are the cards that have been played this round:");
    for (Card card : cards_in_round){
        print("\t- " + card.name);
    }
    print("\n");

    // Show all cards
    print(name + " these are the cards in your hand:");
    for(Card card : cards){
        print("\t- " + card.name);
    }

    vector<int> filtered_cards = {};
    if (!first_attack){
        for (int i=0; i<cards.size(); i++){
            Card card_in_hand = cards[i];
            for (Card card_in_round : cards_in_round){
                if (card_in_round.rank == card_in_hand.rank) 
                    {filtered_cards.push_back(i); break; }
            }
        }
    } else {
        for (int i=0; i<cards.size(); i++){
            filtered_cards.push_back(i);
        }
    }

    if (filtered_cards.size() == 0){
        print(name + ", you have no valid cards to attack with. You must pass.");
        return "Pass";
    }

    print("\n" + name + ", these are the cards you can attack with (pick one): ");
    for (int i = 0; i < filtered_cards.size(); i++){
        print(to_string(i+1) + ".) " + cards[filtered_cards[i]].name);
    }

    // Allow passing if not the first attack
    if (!first_attack)
        print(to_string(filtered_cards.size()+1) + ".) Pass");
    
    int card_index = stoi(input("Option: ")) - 1;

    // Validate input
    while (card_index < 0 || (first_attack && card_index >= filtered_cards.size()) || 
                             (!first_attack && card_index > filtered_cards.size())){
        print("Invalid option. Please choose again.");
        card_index = stoi(input("Option: ")) - 1;
    }

    // Check for pass
    if (card_index == filtered_cards.size() && !first_attack)
    {
        print(name + " has chosen to pass.");
        return "Pass";
    }

    int idx = filtered_cards[card_index];
    Card chosen_card = cards[idx];
    cards.erase(cards.begin() + idx);

    print("Player " + to_string(id) + " played a " + chosen_card.name + ".");

    return chosen_card.name;
}

string Player::Defend(string koz, Card attack_card){
    print(repeat("-", 20));
    print(name + " these are the cards in your hand:");
    for(Card card : cards){
        print("\t- " + card.name);
    }

    vector<int> filtered_cards = {};
    for (int i=0; i < cards.size(); i++){
        Card card = cards[i];
        if (card.BiggerThan(attack_card, koz) && (card.suit == koz || card.suit == attack_card.suit))
        {   
            filtered_cards.push_back(i);
        }
    }

    if (filtered_cards.size() == 0) {
        print("Player " + to_string(id) + " has nothing to defend with.");
        print(repeat("-", 20));
        return "Fail";
    }

    print("\n"+ name + ", you can only defend with the following (pick one) : ");
    for (int i = 0; i < filtered_cards.size(); i++){
        print(to_string(i+1) + ".) " + cards[filtered_cards[i]].name);
    }

    int card_index = stoi(input("Card: ")) - 1;

    // Validate input
    while (card_index < 0 || card_index >= filtered_cards.size()){
        print("Invalid option. Please choose again.");
        card_index = stoi(input("Card: ")) - 1;
    }

    int idx = filtered_cards[card_index];
    Card chosen_card = cards[idx];
    cards.erase(cards.begin() + idx);

    print("Player " +  to_string(id) + " defended with " + chosen_card.name + ".");
    return chosen_card.name;
}

Player::~Player(){
    print("This instance was deleted.!");
};