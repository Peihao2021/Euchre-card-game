#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

// TEST(test_simple_player_play_card) {
//   // Bob's hand
//   Player * bob = Player_factory("Bob", "Simple");
//   bob->add_card(Card(NINE, SPADES));
//   bob->add_card(Card(TEN, HEARTS));
//   bob->add_card(Card(QUEEN, DIAMONDS));
//   bob->add_card(Card(KING, HEARTS));
//   bob->add_card(Card(JACK, DIAMONDS));

//   Card led(NINE, HEARTS);

//   Card play = bob->play_card(led, DIAMONDS); 
//   ASSERT_EQUAL(play, Card(KING, HEARTS));

//   play = bob->play_card(led, DIAMONDS); 
//   ASSERT_EQUAL(play, Card(TEN, HEARTS));

//   play = bob->play_card(led, DIAMONDS); 
//   ASSERT_EQUAL(play, Card(NINE, SPADES));

//   play = bob->play_card(led, DIAMONDS); 
//   ASSERT_EQUAL(play, Card(QUEEN, DIAMONDS));

//   play = bob->play_card(led, DIAMONDS); 
//   ASSERT_EQUAL(play, Card(JACK, DIAMONDS));

//   delete bob;
// }

TEST(test_simple_player__add_and_discard_AND_lead_card) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(ACE, HEARTS));

    bob->add_and_discard(Card(NINE, CLUBS));
    bob->add_and_discard(Card(JACK, SPADES));
    /*  Resulting Hand
        JACK of SPADES
        JACK CLUBS
        QUEEN DIAMONDS
        KING CLUBS
        ACE HEARTS
    */

   Card led = bob->lead_card(CLUBS);
   ASSERT_EQUAL(led, Card(ACE, HEARTS));

   led = bob->lead_card(CLUBS);
   ASSERT_EQUAL(led, Card(QUEEN, DIAMONDS));

   led = bob->lead_card(CLUBS);
   ASSERT_EQUAL(led, Card(JACK, CLUBS));
   
   led = bob->lead_card(CLUBS);
   ASSERT_EQUAL(led, Card(JACK, SPADES));

   led = bob->lead_card(CLUBS);
   ASSERT_EQUAL(led, Card(KING, CLUBS));

   delete bob;
}

TEST(test_simple_player_make_trump) {
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(ACE, DIAMONDS));

    Suit trump;

    Card king_clubs(FIVE, CLUBS);
    bool orderup = bob->make_trump(king_clubs, false, 1, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);

    Card queen_hearts(QUEEN, HEARTS);
    orderup = bob->make_trump(queen_hearts, true, 1, trump);
    ASSERT_FALSE(orderup);

    Card nine_clubs(NINE, CLUBS);
    orderup = bob->make_trump(nine_clubs, true, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    Card nine_hearts(NINE, HEARTS);
    orderup = bob->make_trump(nine_hearts, false, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, DIAMONDS);

    Card nine_spades(NINE, SPADES);
    orderup = bob->make_trump(nine_spades, true, 2, trump);
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);

    orderup = bob->make_trump(nine_clubs, false, 2, trump);
    ASSERT_FALSE(orderup);
    
    delete bob;
}

TEST(test_player_get_name) {
    Player *alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    ostringstream oss1;
    oss1 << *alice;
    ASSERT_EQUAL(oss1.str(), "Alice");

    Player *bob = Player_factory("Bob", "Human");
    ASSERT_EQUAL("Bob", bob->get_name());

    ostringstream oss2;
    oss2 << *bob;
    ASSERT_EQUAL(oss2.str(), "Bob");

    delete alice;
    delete bob;
}

//
TEST(test_make_trump_left_bower) {
    Player * bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(TEN, SPADES));
    


    Card upcard(TEN, DIAMONDS);
    bool is_dealer = 0;
    int round = 2;
    Suit order_up;

    bool real = bob->make_trump(upcard, is_dealer, round, order_up);

    ASSERT_EQUAL(real, 1);

    ASSERT_EQUAL(order_up, HEARTS);

    delete bob;
}

TEST(test_play_card_right_bower) {
    Player * bob = Player_factory("Bob", "Simple");
    
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, DIAMONDS));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(JACK, HEARTS));

    Card led(QUEEN, HEARTS);

    Card test = bob->play_card(led, HEARTS);

    ASSERT_EQUAL(test, Card(JACK, HEARTS));

    delete bob;
}

//
TEST(test_lead_card_only_trump_suit)
{
    Player* bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(KING, HEARTS));

    ASSERT_EQUAL(bob->lead_card(HEARTS), Card(ACE, HEARTS));

    delete bob;
}

//
TEST(test_lead_card_only_off_suit)
{
    Player* bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(NINE, CLUBS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, CLUBS));

    ASSERT_EQUAL(bob->lead_card(HEARTS), Card(ACE, CLUBS));

    delete bob;
}

//
TEST(test_lead_card_right_bower)
{
    Player* Balen = Player_factory("Balen", "Simple");

    Balen->add_card(Card(NINE, HEARTS));
    Balen->add_card(Card(TEN, HEARTS));
    Balen->add_card(Card(JACK, HEARTS));
    Balen->add_card(Card(QUEEN, HEARTS));
    Balen->add_card(Card(KING, HEARTS));

    ASSERT_EQUAL(Balen->lead_card(HEARTS), Card(JACK, HEARTS));

    delete Balen;
}

//
TEST(test_make_trump_as_dealer){
    Player* const Jefford = Player_factory("Jefford", "Simple");

    Suit s = HEARTS;
    Jefford->add_card(Card(KING, SPADES));
    Jefford->add_card(Card(QUEEN, SPADES));
    Jefford->add_card(Card(KING, CLUBS));
    Jefford->add_card(Card(QUEEN, CLUBS));
    Jefford->add_card(Card(KING, HEARTS));

    ASSERT_TRUE(Jefford->make_trump(Card(NINE, DIAMONDS), 1, 2, s));

    delete Jefford;
}


//
TEST(test_play_card_no_follow_suit) {
    Player * Alex = Player_factory("Alex", "Simple");
    
    Alex->add_card(Card(NINE, HEARTS));
    Alex->add_card(Card(TEN, DIAMONDS));
    Alex->add_card(Card(JACK, SPADES));
    Alex->add_card(Card(QUEEN, SPADES));
    Alex->add_card(Card(ACE, HEARTS));

    Card led(QUEEN, CLUBS);

    Card test = Alex->play_card(led, HEARTS);

    ASSERT_EQUAL(test, Card(TEN, DIAMONDS));

    delete Alex;
}

//
TEST(test_play_card_left_bower) {
    Player * bob = Player_factory("Bob", "Simple");
    
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(ACE, HEARTS));

    Card led(QUEEN, HEARTS);

    Card test = bob->play_card(led, HEARTS);

    ASSERT_EQUAL(test, Card(JACK, DIAMONDS));

    delete bob;
}

//
TEST(test_lead_card_left_bower)
{
    Player* Jefford = Player_factory("Jefford", "Simple");

    Jefford->add_card(Card(NINE, HEARTS));
    Jefford->add_card(Card(TEN, HEARTS));
    Jefford->add_card(Card(JACK, DIAMONDS));
    Jefford->add_card(Card(QUEEN, HEARTS));
    Jefford->add_card(Card(KING, HEARTS));

    ASSERT_EQUAL(Jefford->lead_card(HEARTS), Card(JACK, DIAMONDS));

    delete Jefford;
}

//
TEST(test_play_card_follow_suit) {
    Player * Alex = Player_factory("Alex", "Simple");

    Alex->add_card(Card(NINE, HEARTS));
    Alex->add_card(Card(TEN, DIAMONDS));
    Alex->add_card(Card(JACK, SPADES));
    Alex->add_card(Card(QUEEN, CLUBS));
    Alex->add_card(Card(ACE, HEARTS));

    Card led(QUEEN, SPADES);

    Card test = Alex->play_card(led, HEARTS);

    ASSERT_EQUAL(test, Card(JACK, SPADES));

    delete Alex;
}

//
TEST(play_card_round1) {
    Player * AAA = Player_factory("AAA", "Simple");
    AAA->add_card(Card(NINE, SPADES));
    AAA->add_card(Card(NINE, CLUBS));

    Card jack_hearts(JACK, HEARTS);
    Card card_played = AAA->play_card(jack_hearts, DIAMONDS); 

    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete AAA;

    Player * BBB = Player_factory("BBB", "Simple");
    BBB->add_card(Card(TEN, HEARTS));
    BBB->add_card(Card(JACK, CLUBS));
    BBB->add_card(Card(JACK, SPADES));
    BBB->add_card(Card(QUEEN, DIAMONDS));
    BBB->add_card(Card(KING, SPADES));

    Card led_1 = Card(QUEEN, SPADES);
    Card right_1 = BBB->play_card(led_1, HEARTS);
    ASSERT_EQUAL(right_1, Card(KING, SPADES));
    delete BBB;

    Player * CCC = Player_factory("CCC", "Simple");
    CCC->add_card(Card(TEN, HEARTS));
    CCC->add_card(Card(JACK, HEARTS));
    CCC->add_card(Card(JACK, SPADES));
    CCC->add_card(Card(QUEEN, DIAMONDS));
    CCC->add_card(Card(KING, SPADES));

    Card led_2 = Card(QUEEN, CLUBS);
    Card right_2 = CCC->play_card(led_2, HEARTS);
    ASSERT_EQUAL(right_2, Card(JACK, SPADES));
    delete CCC;

    Player * DDD = Player_factory("DDD", "Simple");
    DDD->add_card(Card(TEN, DIAMONDS));
    DDD->add_card(Card(JACK, HEARTS));
    DDD->add_card(Card(JACK, SPADES));
    DDD->add_card(Card(QUEEN, DIAMONDS));
    DDD->add_card(Card(KING, SPADES));

    Card led_3 = Card(NINE, DIAMONDS);
    Card right_3 = DDD->play_card(led_3, HEARTS);
    ASSERT_EQUAL(right_3, Card(QUEEN, DIAMONDS));
    delete DDD;

    Player * EEE = Player_factory("EEE", "Simple");
    EEE->add_card(Card(TEN, SPADES));
    EEE->add_card(Card(JACK, HEARTS));
    EEE->add_card(Card(JACK, DIAMONDS));
    EEE->add_card(Card(QUEEN, CLUBS));
    EEE->add_card(Card(KING, SPADES));

    Card led_4 = Card(QUEEN, DIAMONDS);
    Card right_4 = EEE->play_card(led_4, DIAMONDS);
    ASSERT_EQUAL(right_4, Card(JACK, DIAMONDS));
    delete EEE;
}



TEST_MAIN()