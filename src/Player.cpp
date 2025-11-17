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
    print(string('-', 20));
    print(name + " these are the cards in your hand:");
    for(Card card : cards){
        print("\t- " + card.name);
    }

    vector<Card> filtered_cards = {};
    if (cards_in_round.size() > 0){
        for (Card card_in_round : cards_in_round){
            for (Card card_in_hand : cards){
                if (card_in_round.rank == card_in_hand.rank) 
                    filtered_cards.push_back(card_in_hand);
            }
        }
        if (filtered_cards.size() == 0){
            print(name + ", you have no valid cards to attack with. You must pass.");
            print(string('-', 20));
            return "Pass";
        }
    } else {
        filtered_cards = cards;
    }

    print(name + ", these are the cards you can attack with (pick one): ");
    for (int i = 0; i < filtered_cards.size(); i++){
        print(to_string(i+1) + ".) " + cards[i].name);
    }

    // Allow passing if not the first attack
    if (cards_in_round.size() > 0){
        print(to_string(filtered_cards.size()+1) + ".) Pass");
    }

    int card_index = stoi(input("Option: ")) - 1;
    
    // Check for pass
    if (card_index == filtered_cards.size() && cards_in_round.size() > 0){
        print(name + " has chosen to pass.");
        print(string('-', 20));
        return "Pass";
    }

    // Validate input
    while (card_index < 0 || card_index >= filtered_cards.size()){
        print("Invalid option. Please choose again.");
        card_index = stoi(input("Option: ")) - 1;
    }

    Card chosen_card = cards[card_index];
    cards.erase(cards.begin() + card_index);

    print("Player " + to_string(id) + " played a " + chosen_card.name + ".");
    print(string('-', 20));

    return chosen_card.name;
}

string Player::Defend(string koz, Card attack_card){
    print(string('-', 20));
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
        print(string('-', 20));
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

    Card chosen_card = cards[filtered_cards[card_index]];
    cards.erase(cards.begin() + filtered_cards[card_index]);

    print("Player " +  to_string(id) + " defended with " + chosen_card.name + ".");
    print(string('-', 20));

    return chosen_card.name;
}

Player::~Player(){
    print("This instance was deleted. !!!!!!!!!");
};