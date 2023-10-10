#include "Pack.hpp"
#include <string>
#include <cstring>
#include <cassert>
#include <array>
#include <iostream>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack(){

    int index = 0;

    for(int s = SPADES; s >=SPADES; s--){
        for(int r = NINE; r < ACE + 1; r++){
            cards[index] = Card((Rank)r, (Suit)s);
            index++;
        }
    }

    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input){
    string rank;
    string junk;
    string suit;

    int index = 0;

    while(pack_input >> rank >> junk >> suit){
        cards[index] = Card(string_to_rank(rank), string_to_suit(suit));
        index++;
    }

    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one(){
    Card *next_card = &cards[next];
    ++next;
    return *next_card;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset(){
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle(){

    const int HALF = PACK_SIZE / 2; // HALF = 12
    const int ROUND_NUM = 7;        //ROUND_NUM = 7

    Card *half_1 = new Card[HALF];
    Card *half_2 = new Card[HALF];

    for(int round = 0; round < ROUND_NUM; round++) { // we will shuffle for 7 rounds

        for(int i = 0; i < PACK_SIZE; i++){  // we split the 24 cards into two pack
            if(i < HALF){
                half_1[i] = cards[i];
            }
            else{
                half_2[i - HALF] = cards[i];
            }
        }

        for(int i = 0; i < HALF; i++) {
            cards[2 * i] = half_2[i];
            cards[2 * i + 1] = half_1[i];
        }

    }

    delete[] half_1;
    delete[] half_2;
    next = 0;// EFFECTS: returns true if there are no more cards left in the pack
    

}

bool Pack::empty() const{
    return next == 24;
}