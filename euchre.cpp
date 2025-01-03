#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <cassert>
#include <vector>
#include <cstdlib>
#include "Pack.hpp"
#include "Player.hpp"
#include "Card.hpp"

using namespace std;

class Game {
 public:

    Game(string fileName, string shuffleInput, 
    int points) {

        // initialize pointsToWin, team points and staring dealer index
        pointsToWin = points;
        player_0_and_2_score = 0;
        player_1_and_3_score = 0;
        dealer = 0;

        // initialize deck using given file
        ifstream input(fileName);
        pack = Pack(input); // read the pack and cards order

        // initialize shuffle status 
        //to true or false using shuffleInput
        if (shuffleInput == "shuffle") { 
            shuffle = true;
        } // set shuffle to true or false
        else { 
            shuffle = false; 
        }
        shuffleDeck(shuffle);
    }

    void addPlayers(string name, string strategy) {
        players.push_back(Player_factory(name, strategy));
    }

    void play() {

        int round = 0;
        while (player_0_and_2_score < pointsToWin 
               && player_1_and_3_score < pointsToWin){

            // print hand number
            cout << "Hand " << round << endl;

            // deal pack into player hands
            cout << players[dealer]->get_name() << " deals\n"; 
            deal(players, dealer); // deal the cards

            // flip upcard starting the round
            Card upCard = pack.deal_one();
            cout << upCard << " turned up\n";

            // returns which player makes trup 
            int calledTrump = make_trump(players, upCard); 
            // index of player who calls trump, used in point calculation
            
            // initalize trick counter and round leader
            int trump_pair_tricks = 0; // team that called trump
            int non_trump_pair_tricks = 0;  // team that did not call trump
            int leader = (dealer + 1) % 4;

            // play 5 rounds
            for (int round = 0; round < 5; round++) { 
                // leader starts the round
                leader = play_hand(leader, trump);
                if (leader == calledTrump 
                || leader == calledTrump - 2 
                || leader == calledTrump + 2) {

                    trump_pair_tricks++;
            // cout << "round: " 
            //<< round << " Trump pair" << endl;
                }
                else {
                    non_trump_pair_tricks++;
            // cout << "round: " << round 
            //<< " Non Trump pair" << endl;
                }
            }
            
            // score calculation
            score_calculation(trump_pair_tricks, 
            non_trump_pair_tricks, calledTrump);

            // print score
            cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " have " 
            << player_0_and_2_score << " points\n";

            cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " have " 
            << player_1_and_3_score << " points\n\n";

            dealer = (dealer + 1) % 4;
            shuffleDeck(shuffle);
            round++;
            
        }
        if (player_0_and_2_score >= pointsToWin) {
            print_winner(0); // gives the index of the winner
        }
        else if (player_1_and_3_score >= pointsToWin) {
            print_winner(1); // gives the index of the winner
        }
        // delete dynamic memory players
        for (size_t i = 0; i < players.size(); ++i) {
            delete players[i];
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
        cout << players[team]->get_name() << " and " 
             << players[team + 2]->get_name() << " win!\n";
    }

    void print_winner_hand(vector<Player*> players, int winner) {
        // print the winner of the round
        cout << players[winner]->get_name() << " and " 
             << players[winner + 2]->get_name() << " win the hand\n";
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

        // vector<int> order {3, 2, 3, 2, 2, 3, 2, 3};
        // cout << order.size() << endl;

        // for (int i = 0; i < order.size(); i++) {
        //  for (int j = 0; j < order[j]; j++) {
        //   players[(dealer_idx + i + 1) % 4]
        //   ->add_card(pack.deal_one());
        //   }
        // }

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
        
        int passes = 0;
        int currentPlayer = dealer;
        while (passes < 8) {
            int player = (currentPlayer + 1) % 4; // determine player index
            currentPlayer = player;
            int round = passes / 4 + 1; // determine round number
        //cout << players[player]->get_name() << "Round: " << round <<endl; 
            bool isDealer = player == dealer; 
            // determine if player if dealer

            // if player calls trump
            if (players[player]->make_trump(upCard, isDealer, round, trump))
            {
                cout <<  players[player]->get_name() << " orders up " 
                     << trump << endl;
                // if round one, dealer add and discard
                if (round == 1) { 
                    players[dealer]->add_and_discard(upCard);
                }
                return player;
            }
            else { // player does not call trump
               cout <<  players[player]->get_name() << " passes\n";
            }
            passes++;
        }
        return -1;
    }

    int play_hand(int leader, Suit trump) {
        // leader leads with card
        Card led_card = players[leader]->lead_card(trump);
        cout << led_card << " led by " 
             << players[leader]->get_name() << endl;

        // three other players play cards
        Card maxCard = led_card;
        int winner = leader;
        for (int i = 1; i < 4; i++) { 
            int player = (leader + i) % 4;
            // cout << "Player: " << player << endl;
            Card playCard = players[player]->play_card(led_card, trump); 
            cout << playCard << " played by " 
                 << players[player]->get_name() << endl;
            if (Card_less(maxCard, playCard, led_card, trump)) { 
                maxCard = playCard;
                winner = player; // index of highest card
            }
        }

        cout << players[winner]->get_name() << " takes the trick\n";
        return winner; // return index of player who won the trick
    }
    
    void score_calculation(int trump_tricks, int non_trump_tricks, 
                           int called_trump) {

        if (called_trump == 0 || called_trump == 2) {
            if (trump_tricks == 5) {
                print_winner_hand(players, 0);
                player_0_and_2_score += 2;
                cout << "marched!\n";
            }
            else if (trump_tricks == 3 || trump_tricks == 4) {
                print_winner_hand(players, 0);
                player_0_and_2_score += 1;
            }
            if (non_trump_tricks >= 3 && trump_tricks <= 5) {
                print_winner_hand(players, 1);
                player_1_and_3_score += 2;
                cout << "euchred!\n";
            }
        }
        else {
            if (trump_tricks == 5) {
                print_winner_hand(players, 1);
                player_1_and_3_score += 2;
                cout << "march!\n";
            }
            else if (trump_tricks == 3 || trump_tricks == 4) {
                print_winner_hand(players, 1);
                player_1_and_3_score += 1;
            }
            if (non_trump_tricks >= 3 && trump_tricks <= 5) {
                print_winner_hand(players, 0);
                player_0_and_2_score += 2;
                cout << "euchred!\n";
            }
        }
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
    for(int i = 5; i < 12; i += 2){
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
    
    Game oneGame = Game(argv[1], argv[2], atoi(argv[3]));
    for(int i = 4; i < 12; i += 2){
        oneGame.addPlayers(argv[i], argv[i + 1]);
    }  
    oneGame.play();
}