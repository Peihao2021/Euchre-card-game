#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <cstdlib>
#include <sstream>
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

        // initialize pointsToWin, team points and staring dealer index
        pointsToWin = points;
        player_0_and_2_score = 0;
        player_1_and_3_score = 0;
        dealer = 0;

        // push players into vector
        players.push_back(Player_factory(player0Name, player0Type));
        players.push_back(Player_factory(player1Name, player1Type));
        players.push_back(Player_factory(player2Name, player2Type));
        players.push_back(Player_factory(player3Name, player3Type));

        // initialize deck using given file
        ifstream input(fileName);
        pack = Pack(input); // read the pack and cards order

        // initialize shuffle status to true or false using shuffleInput
        if (shuffleInput == "shuffle") { shuffle = true; } // set shuffle to true or false
        else { shuffle = false; }
    }

    void play() {

        int round = 0;
        while (player_0_and_2_score < pointsToWin && player_1_and_3_score < pointsToWin ) {

            // print hand number
            cout << "Hand " << round << endl;

            // deal pack into player hands
            cout << players[dealer]->get_name() << " deals\n"; 
            deal(players, dealer); // deal the cards

            // flip upcard starting the round
            Card upCard = pack.deal_one();
            cout << upCard << " turned up\n";

            // returns which player makes trup 
            int calledTrump = make_trump(players, upCard); // index of player who calls trump, used in point calculation
            
            // initalize trick counter and round leader
            int trump_pair_tricks = 0; // team that called trump
            int non_trump_pair_tricks = 0;  // team that did not call trump
            int leader = 1;

            // play 5 rounds
            for (int round = 0; round < 5; round++) { 
                // leader starts the round
                leader = play_hand(leader, trump);
                if (leader == calledTrump || leader == calledTrump - 2 || leader == calledTrump + 2) {
                    trump_pair_tricks++;
                    // cout << "round: " << round << " Trump pair" << endl;
                }
                else {
                    non_trump_pair_tricks++;
                    // cout << "round: " << round << " Non Trump pair" << endl;
                }
            }

            // cout << "Called Trump: " << calledTrump << endl;
            // cout << "Called Trump Tricks: " << trump_pair_tricks << endl;
            // cout << "Other Tricks: " << non_trump_pair_tricks << endl;

            // score calculation
            score_calculation(trump_pair_tricks, non_trump_pair_tricks, calledTrump);

            // print score
            cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << player_0_and_2_score << " points\n";
            cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << player_1_and_3_score << " points\n\n";

            dealer = (dealer + 1) % 4;
            pack.shuffle();
            round++;
            
        }
        if (player_0_and_2_score >= pointsToWin) {
            print_winner(0); // gives the index of the winner
        }
        else if (player_1_and_3_score >= pointsToWin) {
            print_winner(1); // gives the index of the winner
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

    void print_winner(int team) {
        // print the winner of the game
        cout << players[team]->get_name() << " and " << players[team + 2]->get_name() << " win!\n";
    }

    void print_winner_hand(vector<Player*> players, int winner) {
        // print the winner of the round
        cout << players[winner]->get_name() << " and " << players[winner + 2]->get_name() << " win the hand\n";
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
        // iterate over two rounds
        for (int i = dealer + 1; i < dealer + 9; i++) { 
            int player = i % 4; // determine player index
            int round = (i - 1) / 4 + 1; // determine round number
            bool isDealer = player == 0; // determine if player if dealer

            // if player calls trump
            if (players[player]->make_trump(upCard, isDealer, round, trump)) {
                // if round one, dealer add and discard
                if (round == 1) { 
                    players[dealer]->add_and_discard(upCard);
                }
                cout <<  players[player]->get_name() << " orders up " << trump << endl;
                return player;
            }
            else { // player does not call trump
               cout <<  players[player]->get_name() << " passes\n";
            }
        }
        return -1; // need to compile
    }

    int play_hand(int leader, Suit trump) {
        // leader leads with card
        Card led_card = players[leader]->lead_card(trump);
        cout << led_card << " led by " << players[leader]->get_name() << endl;

        // three other players play cards
        int winner = 0;
        for (int i = 1; i < 4; i++) { 
            int player = (leader + i) % 4;
            // cout << "Player: " << player << endl;
            Card playCard = players[player]->play_card(led_card, trump); // player plays card
            cout << playCard << " played by " << players[player]->get_name() << endl;
            if (Card_less(led_card, playCard, led_card, trump)) { // check if card is greater than lead card
                winner = player; // set idx to index of the player with highest card
            }
        }

        cout << players[winner]->get_name() << " takes the trick\n";
        return winner; // return index of player who won the trick
    }
    
    void score_calculation(int trump_tricks, int non_trump_tricks, int called_trump) {
        stringstream term;
        int team1 = 0;
        int team2 = 0;
        if (called_trump == 0 || called_trump == 2) {
            if (trump_tricks == 5) {
                player_0_and_2_score += 2;
                team1 += 2;
                term << "marched!\n";
            }
            else if (trump_tricks == 3 || trump_tricks == 4) {
                player_0_and_2_score += 1;
                team1 += 1;
            }
            if (non_trump_tricks >= 3 && trump_tricks <= 5) {
                player_1_and_3_score += 2;
                team2 += 2;
                term << "euchred!\n";
            }
        }
        else {
            if (trump_tricks == 5) {
                player_1_and_3_score += 2;
                team2 += 2;
                term << "marched!\n";
            }
            else if (trump_tricks == 3 || trump_tricks == 4) {
                player_1_and_3_score += 1;
                team2 += 2;
            }
            if (non_trump_tricks >= 3 && trump_tricks <= 5) {
                player_0_and_2_score += 2;
                team1 += 2;
                term << "euchred!\n";
            }
        }
        if (team1 > team2) {
                print_winner_hand(players, 0);
            }
        else if (team2 < team1) {
                print_winner_hand(players, 1);
        }
        string output = term.str();
        cout << output;
    }

    
};

int main(int argc, char *argv[]) {

    // Check if arguments is 12
    // Check if pointsToWin is between 1 and 100 inclusive
    // Check if shuffle argument is "shuffle" or "noshuffle"

    bool shuffleCheck = false;
    if (strcmp(argv[2], "shuffle") == 0 || strcmp(argv[2], "noshuffle") == 0) {
        shuffleCheck = true;
    }

    if (argc != 12 || atoi(argv[3]) < 1 || atoi(argv[3]) > 100 || !shuffleCheck) {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }

    // Check if Players are all Human players or Simple players
    for(int i = 5; i < 12; i+=2){
        if(!(strcmp(argv[i], "Human") == 0 || strcmp(argv[i], "Simple") == 0)) {
            cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
        }
    }            

    // Print out the command line arguments
    for(int i = 0; i < argc; i++){
        cout << argv[i] <<" ";
    }
    cout<<endl;

    // Extract the filename and open file
    string pack_filename = argv[1];
    ifstream input;
    input.open(pack_filename);
    
    // Check if file open
    if(!input.is_open()){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
            << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
            << "NAME4 TYPE4" << endl;
        return 1;
    }
    
    Game oneGame = Game(argv[1], argv[2], atoi(argv[3]),
                        argv[4], argv[5], argv[6],
                        argv[7], argv[8], argv[9], 
                        argv[10], argv[11]);

    oneGame.play();
}
