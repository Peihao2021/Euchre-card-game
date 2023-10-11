#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(JACK, DIAMONDS));

  Card led(NINE, HEARTS);

  Card play = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(play, Card(KING, HEARTS));

  play = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(play, Card(TEN, HEARTS));

  play = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(play, Card(NINE, SPADES));

  play = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(play, Card(QUEEN, DIAMONDS));

  play = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(play, Card(JACK, DIAMONDS));

  delete bob;
}

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

TEST_MAIN()
