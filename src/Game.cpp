#include "Game.h"

Game::Game(){
    print("Welcome to Durak");
    print("Game rules found at: 'https://en.wikipedia.org/wiki/Durak' \n");

    while (player_count < 2 || player_count > 5){
        print("Choose the number of players. (Must be between 2 and 5)");
        player_count = stoi(input("Enter player count: "));
    }
    
    for(int i = 0; i < player_count; ++i){
        players.emplace_back(i+1, deck.DealCards(cards_per_player));
    }

    koz = deck.GetKoz();
    turn = GetStartingTurn();
}

// The player with the smallest trump card starts first, or the one with none of them
int Game::GetStartingTurn(){
    int turn = 0;
    Card smallest_card = players[turn].GreatestCard(koz);
    for (int i = 1; i < player_count; i++){
        Card card = players[i].GreatestCard(koz);
        if (smallest_card.BiggerThan(card, koz)){
            turn = i;
            smallest_card = card;
        }
    }
    print("\n" + players[turn].name + " is the starting player.");
    return turn;
}

void Game::Play(){
    while (player_count > 1){
        NewRound();
    }
    print(players.front().name + " is the remaining fool.");
}

void Game::NewRound(){
    int attacks = 0; // Max 6 attacks
    int passes = 0; // Check if everyone decides to pass
    bool failed_to_defend = false; 
    vector<Card> cards_in_round = {};

    // Makes it easier for checking
    attacker_turn = turn;
    defender_turn = (turn+1) % player_count;
    Player* attacker = &players[attacker_turn];
    Player* defender = &players[defender_turn];

    print(repeat("-", 30));
    print("New Round Begins!");
    print("\nAttacker: " + attacker->name + " | Defender: " + defender->name);

    while(!defender->Empty() && passes != player_count-1 && !failed_to_defend){
        if (attacks == 0){
            attacks++;
            string attack_state = attacker->Attack(koz, {}); // Attack state can be either a Card or a Pass
            string defense_state = defender->Defend(koz, attack_state); // Either a Card or a Fail
            if (defense_state == "Fail") failed_to_defend = true;
            else {cards_in_round.push_back(defense_state);}
            cards_in_round.push_back(attack_state); 
        } else {
            attacker = &players[attacker_turn];

            string attack_state = attacker->Attack(koz, cards_in_round);
            if (attack_state == "Pass") {passes++; NextAttacker(); continue;}
            cards_in_round.push_back(attack_state);
            passes = 0;
            attacks++;

            string defense_state = defender->Defend(koz, attack_state); 
            if (defense_state == "Fail") {failed_to_defend = true; break;}
            cards_in_round.push_back(defense_state);
        }

        CheckIfPlayersOut();
    }

    // Defender picks up all cards if they failed to defend.
    if (failed_to_defend) {
        print(defender->name + " failed to defend and picks up all cards in the round.");
        defender->PickupCards(cards_in_round);
        turn = (turn + 2) % player_count;
    } else {
        turn = (turn + 1) % player_count;
    }
    RestockCards(); // Deal cards to players if they have less than six
}

void Game::NextAttacker()
{
    if ((attacker_turn + 1) % player_count == defender_turn) 
    {attacker_turn = (attacker_turn+2) % player_count; return;} 
    attacker_turn = (attacker_turn + 1) % player_count;
}

void Game::RestockCards()
{
    // Attackers pick-up cards first in clockwise direction, then defender last.
    for (int i = 0; i < player_count-1; i++){
        Player* player = &players[attacker_turn];
        player->PickupCards(deck.DealCards(cards_per_player - player->cards.size()));
        NextAttacker();
    }
    Player* player = &players[defender_turn];
    player->PickupCards(deck.DealCards(cards_per_player - player->cards.size()));
}

void Game::CheckIfPlayersOut()
{
    vector<int> to_remove = {};
    for (int i = 0; i < players.size(); i++){
        if (deck.Empty() && players[i].Empty()){
            // Remove player
            to_remove.push_back(i);
        }
    }
    for (int i : to_remove){
        players.erase(players.begin() + i);
        player_count--;

        if (defender_turn == i){
            turn--;
            // Prob something else
        } else if (attacker_turn == i) {
            attacker_turn--;
        } else {
            throw "Error";
        }
    }
}