#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include "Pack.hpp"
#include "Player.hpp"
#include "Card.hpp"

using namespace std;

class Game {
 public:

    Game(string fileName, string shuffleInput, 
    int points, string player0Name, string player0Type,
    string player1Name, string player1Type,
    string player2Name, string player2Type, 
    string player3Name, string player3Type) {

        pointsToWin = points;
        dealer = 0;

        players.push_back(Player_factory(player0Name, player0Type));
        players.push_back(Player_factory(player1Name, player1Type));
        players.push_back(Player_factory(player2Name, player2Type));
        players.push_back(Player_factory(player3Name, player3Type));

        ifstream input(fileName);
        pack = Pack(input); // read the pack and cards order
        if (shuffleInput == "shuffle") { shuffle = true; } // set shuffle to true or false
        else { shuffle = false; }
    }
    void play() {
        cout << "Hand 0\n";
        while (player_0_and_2_score < pointsToWin || player_1_and_3_score < pointsToWin ) {
            cout << players[dealer]->get_name() << " deals\n"; 
            deal(players, dealer); // deal the cards

            Card upCard = pack.deal_one();
            cout << upCard << "turned up\n";

            // making trump
            int calledTrump = make_trump(players, upCard); // index of player who calls trump, used in point calculation
            
            // play 5 rounds
            int trump_pair_tricks = 0;
            int non_trump_pair_tricks = 0;
            int leader = 0;

            for (int round = 0; round < 5; round++) { // five rounds in one game
                // call play hand
                leader = play_hand(round, dealer, leader, trump);
                if (leader == calledTrump || leader == calledTrump - 2 || leader == calledTrump + 2) {
                    trump_pair_tricks++;
                }
                else {
                    non_trump_pair_tricks++;
                }
            }

            // score calculation
            score_calculation(trump_pair_tricks, non_trump_pair_tricks, calledTrump);

            // print score
            cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << player_0_and_2_score << " points\n";
            cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << player_1_and_3_score << " points\n";

            dealer = (dealer + 1) % 4;
            pack.shuffle();
            
        }
        if (player_0_and_2_score >= pointsToWin) {
            cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << endl;
        }
        else if (player_1_and_3_score >= pointsToWin) {
            cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << endl;
        }
    }

 private:
    // player 1: player[0]
    // player left of player 1: player[1], etc.
    vector<Player*> players; 
    int player_0_and_2_score;
    int player_1_and_3_score;
    Pack pack;
    bool shuffle;
    int pointsToWin;
    int dealer; //the index of the dealer
    Suit trump;
    Card upCard;

    string get_partner_name(vector<Player*> players, int idx) {
        if (idx <= 1) { // return partner name
            return players[idx + 2]->get_name();
        }
        else {
            return players[idx + 2]->get_name();
        }
    }

    void shuffleDeck(bool shuffleOption) {
        if (shuffle) { 
            pack.shuffle();
        }
        else { // if no shuffle, reset pack to original
            pack.reset();
        }
    }

    void deal(vector<Player*> players, int dealer_idx) {
        //batch 1 deals 3-2-3-2 order
        for (int i = 0; i < 3; i++) {
            players[(dealer_idx + 1) % 4]->add_card(pack.deal_one());
        }

        for (int i = 0; i < 2; i++) {
            players[(dealer_idx + 2) % 4]->add_card(pack.deal_one());
        }

        for (int i = 0; i < 3; i++) {
            players[(dealer_idx + 3) % 4]->add_card(pack.deal_one());
        }

        for (int i = 0; i < 2; i++) {
            players[dealer_idx]->add_card(pack.deal_one());
        }
        // batch 2 deals 2-3-2-3 order
        for (int i = 0; i < 2; i++) {
            players[(dealer_idx + 1) % 4]->add_card(pack.deal_one());
        }

        for (int i = 0; i < 3; i++) {
            players[(dealer_idx + 2) % 4]->add_card(pack.deal_one());
        }

        for (int i = 0; i < 2; i++) {
            players[(dealer_idx + 3) % 4]->add_card(pack.deal_one());
        }

        for (int i = 0; i < 3; i++) {
            players[dealer_idx]->add_card(pack.deal_one());
        }
    }
    
    int make_trump(vector<Player*> players, Card upCard) {
        for (int i = dealer + 1; i < dealer + 9; i++) { 
            int player = i % 4;
            int round = (i / 4) + 1;
            bool isDealer = dealer == i % 4;

            if (players[player]->make_trump(upCard, isDealer, round, trump)) {
                if (round == 1) {
                    players[dealer]->add_and_discard(upCard);
                }
                cout <<  players[player]->get_name() << " orders up " << trump << endl;
                return player;
            }
            else {
               cout <<  players[player]->get_name() << " passes\n";
            }
        }
        return -1;
    }

    void score_calculation(int trump_tricks, int non_trump_tricks, int called_trump) {
        if (called_trump == 0 || called_trump == 2) {
            if (trump_tricks == 5) {
                player_0_and_2_score += 2;
                cout << "marched!\n";
            }
            else if (trump_tricks == 3 || trump_tricks == 4) {
                player_0_and_2_score += 1;
            }
            else if (non_trump_tricks >= 3 && trump_tricks <= 5) {
                player_0_and_2_score += 2;
                cout << "euchred!\n";
            }
        }
        else {
            if (trump_tricks == 5) {
                player_1_and_3_score += 2;
                cout << "marched!\n";
            }
            else if (trump_tricks == 3 || trump_tricks == 4) {
                player_1_and_3_score += 1;
            }
            else if (non_trump_tricks >= 3 && trump_tricks <= 5) {
                player_1_and_3_score += 2;
                cout << "euchred!\n";
            }
        }
    }

    int play_hand(int round, int dealer, int leader, Suit trump) {
        if (round == 0) {
            leader = (dealer + 1) % 4; 
        }
        Card led_card = players[leader]->lead_card(trump);
        cout << led_card << " led by " << players[leader]->get_name() << endl;

        int idx = 0;
        for (int i = 0; i < 3; i++) { // three other players play cards
            int player = (leader + 2 + 1) % 4;
            Card playCard = players[player]->play_card(led_card, trump); // player plays card
            cout << playCard << " played by " << players[player]->get_name() << endl;
            if (Card_less(led_card, playCard, trump)) { // check if card is greater than lead card
                idx = player; // set idx to index of the player with highest card
            }
        }

        cout << players[idx]->get_name() << " takes the trick\n";
        cout << players[idx]->get_name() << " and " << get_partner_name(players, idx) << " win the hand\n";
        return idx; // return idx of player who won the trick
    }
    // ...
    
    
};

bool is_player_type(string player_type){
    if (player_type == "Human" || player_type == "Simple"){
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {

//Judge if the arguments are not 12 || points to win is out of range of 1-100
//Or the shuffle argument is not right
    if (argc != 12 || 1 >= stoi(argv[3]) || stoi(argv[3]) >= 100 
        || strcmp(argv[2], "shuffle") != 0 || strcmp(argv[2], "noshuffle") != 0) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }

//Judge if the Player type is not Human or Simple
    for(int i = 5; i < 12; i+=2){
        if(is_player_type(argv[i])){
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
        }
    }            

    //1. print out the command line
    for(int i = 0; i < argc; i++){
        cout << argv[i] <<" ";
    }
    cout<<endl;

    //2. input the filenam
    string pack_filename = argv[1];

    ifstream input;
    input.open(pack_filename);
    
    if(!input.is_open()){
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }
    
    Game oneGame = Game(argv[1], argv[2], stoi(argv[3]),
                        argv[4], argv[5], argv[6],
                        argv[7], argv[8], argv[9], 
                        argv[10], argv[11]);

    oneGame.play();
}
