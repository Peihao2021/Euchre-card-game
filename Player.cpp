#include "Player.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>

class SimplePlayer : public Player{
    public:

    // constructor
    SimplePlayer(std::string playerName) : name(playerName) {}

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, 
                    int round, Suit &order_up_suit) const override {
        if (round == 1) {
            int counter = 0;
            for (int card = 0; card < hand.size(); card++) {
                if (hand[card].is_face_or_ace() && 
                    hand[card].is_trump(upcard.get_suit())) {
                    counter++;
                }
            }
            if (counter >= 2) {
                order_up_suit = upcard.get_suit(); 
                return true;
            }
            return false;
        }
        else { // round 2
            if (is_dealer) {
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            else {
                int counter = 0;
                for (int card = 0; card < hand.size(); card++) {
                    if (hand[card].is_face_or_ace() && 
                        hand[card].get_suit() == Suit_next(upcard.get_suit())) {
                        counter++;
                    }
                }
                if (counter >= 1) {
                    order_up_suit = Suit_next(upcard.get_suit());
                    return true;
                }
                return false;
            }
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        int minIdx = -1;
        Card min = upcard;

        for (int idx = 0; idx < hand.size(); idx++) {
            if (Card_less(hand[idx], min, upcard.get_suit())) {
                minIdx = idx;
                min = hand[idx];
            }
        }
        if (minIdx != -1) {
            hand[minIdx] = upcard;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override {
        int max_non_trump_idx = -1;
        Card max_non_trump = Card(TWO, Suit_next(trump));

        int max_trump_idx = -1;
        Card max_trump = Card(TWO, Suit_next(trump));

        // finds trump and nontrump max value
        for (int idx = 0; idx < hand.size(); idx++) {
            if (!hand[idx].is_trump(trump) && 
                Card_less(max_non_trump, hand[idx], trump)) {
                max_non_trump = hand[idx];
                max_non_trump_idx = idx;
            }
            else if (hand[idx].is_trump(trump) && 
                Card_less(max_trump, hand[idx], trump)) {
                max_trump = hand[idx];
                max_trump_idx = idx;
            }
        }

        // return max card if trump or nontrump
        if (max_non_trump_idx != -1) {
            hand.erase(hand.begin() + max_non_trump_idx);
            return max_non_trump;
        }
        else {
            hand.erase(hand.begin() + max_trump_idx);
            return max_trump;
        }
    }

    Card play_card(const Card &led_card, Suit trump) override {

        std::vector<Card> note_suit; // note down the preferable card suit
        std::vector<Card> note_rank; // note down the preferable card suit
        Card lowest_rank_card = Card(JACK, trump);;
        Card highest_rank_card = Card(TWO, Suit_next(trump));;
        int cnt_1 = 0; //lowest_rank index if no same suit as lead 
        int cnt_2 = 0; //if there is only 1 same suit as lead 
        int cnt_3 = 0; //highest_rank index if many same suit as lead

        //先找最低的牌
        for(int idx = 0; idx < hand.size(); idx++){
            if(Card_less(hand[idx], lowest_rank_card, trump)){
                lowest_rank_card = hand[idx];
                cnt_1 = idx; //note lowest_rank_card index
            }
        }

        //再看有没有和lead同花色的牌
        for(int idx = 0; idx < hand.size(); idx++){
            if(hand[idx].get_suit(trump) == led_card.get_suit(trump)){
                note_suit.push_back(hand[idx]);
                cnt_2 = idx;
            }
            else{continue;}
        }

        if(note_suit.size() == 0){
            hand.erase(hand.begin() + cnt_1);
            return lowest_rank_card;
        }
        else if(note_suit.size() == 1){
            hand.erase(hand.begin() + cnt_2);
            return note_suit[0];
        }
        else{
            //if there are same suit cards, pick highest card
            for(int idx = 0; idx < hand.size(); idx++){
                if(hand[idx].get_suit(trump) == led_card.get_suit(trump)
                   && Card_less(highest_rank_card, hand[idx], trump)){
                    highest_rank_card = hand[idx];
                    cnt_3 = idx;
                }
            }
            hand.erase(hand.begin() + cnt_3);
            return highest_rank_card;
        }

    }
    private:
    std::vector<Card> hand;
    std::string name;
};

class HumanPlayer : public Player{
    public:

    HumanPlayer(std::string playerName) : name(playerName) {}

    //EFFECTS returns player's name
    const std::string & get_name() const override {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) override {
        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit. If Player wishes to pass, 
    //  then do not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer, 
                    int round, Suit &order_up_suit) const override {
        print_hand();
        std::cout << "Human player " << name 
                    << ", please enter a suit, or \"pass\":\n";
        
        std::string decision;
        std::cin >> decision;

        if (decision != "pass") {
            order_up_suit = string_to_suit(decision);
            return true;
        }
        return false;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) override {
        print_hand();
        std::cout << "Discard upcard: [-1]\n";
        std::cout << "Human player " << name 
                  << ", please select a card to discard:\n";;

        std::string decision;
        std::cin >> decision;

        if (stoi(decision) != 1) {
            hand[stoi(decision)] = upcard;
            std::sort(hand.begin(), hand.end());
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(Suit trump) override {
        print_hand();
        std::cout << "Human player " << name << ", please select a card:\n";
        
        std::string decision;
        std::cin >> decision;

        Card temp = hand[stoi(decision)];
        hand.erase(hand.begin() + stoi(decision));
        return temp;
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump) override {
        return lead_card(trump);
    }

    private:

    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i) {
            std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
        }
    }

    std::vector<Card> hand;
    std::string name;

};


//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  // We need to check the value of strategy and return 
  // the corresponding player type.
  if (strategy == "Simple") {
    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);
  }
  else if (strategy == "Human") {
    return new HumanPlayer(name);
  }
  // Invalid strategy if we get here
  return nullptr;
}