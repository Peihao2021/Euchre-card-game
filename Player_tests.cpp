#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;


//Need to fix Max_card in Play_card function


TEST(play_card_round1) {
    Player * AAA = Player_factory("AAA", "Simple"); 
    //same rank, then compare suit
    AAA->add_card(Card(QUEEN, DIAMONDS));
    AAA->add_card(Card(QUEEN, HEARTS));

    Card led(TEN, CLUBS);
    Card test = AAA->play_card(led, SPADES); 

    ASSERT_EQUAL(test, Card(QUEEN, HEARTS));
    delete AAA;


//测原来AAA 10.20 
    Player * aaa = Player_factory("aaa", "Simple");
    aaa->add_card(Card(NINE, SPADES));
    aaa->add_card(Card(NINE, CLUBS));

    Card jack_hearts(JACK, HEARTS);
    Card card_played = aaa->play_card(jack_hearts, DIAMONDS); 

    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete aaa;

    //16/17 version
    Player * BBB = Player_factory("BBB", "Simple");
    BBB->add_card(Card(QUEEN, DIAMONDS));
    BBB->add_card(Card(JACK, DIAMONDS));
    BBB->add_card(Card(ACE, CLUBS));
    BBB->add_card(Card(QUEEN, HEARTS));
    BBB->add_card(Card(TEN, CLUBS));

    Card led_1 = Card(NINE, CLUBS);
    Card test_1 = BBB->play_card(led_1, DIAMONDS);
    ASSERT_EQUAL(test_1, Card(ACE, CLUBS));
    delete BBB;



    Player * CCC = Player_factory("CCC", "Simple"); 
    //no follow suit, choose one of the smallest rank
    
    CCC->add_card(Card(JACK, SPADES));
    CCC->add_card(Card(TEN, CLUBS));
    CCC->add_card(Card(TEN, DIAMONDS));
    CCC->add_card(Card(QUEEN, DIAMONDS));
    CCC->add_card(Card(KING, DIAMONDS));

    Card led_2 = Card(TEN, HEARTS);
    Card test_2 = CCC->play_card(led_2, CLUBS);

    ASSERT_EQUAL(test_2, Card(TEN, DIAMONDS));
    delete CCC;

    Player * DDD = Player_factory("DDD", "Simple");
    DDD->add_card(Card(JACK, CLUBS));
    DDD->add_card(Card(ACE, CLUBS));
    DDD->add_card(Card(TEN, SPADES));
    DDD->add_card(Card(QUEEN, CLUBS));
    DDD->add_card(Card(TEN, DIAMONDS));
    

    Card led_3 = Card(TEN, CLUBS);
    Card test_3 = DDD->play_card(led_3, HEARTS);
    ASSERT_EQUAL(test_3, Card(ACE, CLUBS));
    delete DDD;

    Player * EEE = Player_factory("EEE", "Simple");
    EEE->add_card(Card(NINE, HEARTS));
    EEE->add_card(Card(ACE, DIAMONDS));
    EEE->add_card(Card(JACK, CLUBS));
    EEE->add_card(Card(JACK, SPADES));
    EEE->add_card(Card(QUEEN, HEARTS));

    Card led_4 = Card(NINE, CLUBS);
    Card test_4 = EEE->play_card(led_4, CLUBS);
    ASSERT_EQUAL(test_4, Card(JACK, CLUBS));
    delete EEE;


    //Above needs to fix max_card in Play_card
    //-------------------------------------------------
    //Below needs clarification of Left bower's suit


    Player * FFF = Player_factory("FFF", "Simple"); 
    //lead suit has left bower, then Jack is highest?
    FFF->add_card(Card(TEN, SPADES));
    FFF->add_card(Card(TEN, DIAMONDS));
    FFF->add_card(Card(QUEEN, CLUBS));
    FFF->add_card(Card(JACK, CLUBS));
    FFF->add_card(Card(ACE, CLUBS));

    Card led_5 = Card(TEN, CLUBS);
    Card test_5 = FFF->play_card(led_5, SPADES);
    ASSERT_EQUAL(test_5, Card(ACE, CLUBS));
    delete FFF;

    Player * GGG = Player_factory("GGG", "Simple"); 
    //lead suit has left bower, then Jack is highest
    GGG->add_card(Card(TEN, SPADES));
    GGG->add_card(Card(TEN, DIAMONDS));
    GGG->add_card(Card(TEN, CLUBS));
    GGG->add_card(Card(JACK, CLUBS));
    GGG->add_card(Card(NINE, CLUBS));

    Card led_6 = Card(KING, CLUBS);
    Card test_6 = GGG->play_card(led_6, SPADES);
    ASSERT_EQUAL(test_6, Card(TEN, CLUBS));
    delete GGG;


    Player * HHH = Player_factory("HHH", "Simple"); 
    //have both right and left bower, lead suit is trump suit
    HHH->add_card(Card(TEN, SPADES));
    HHH->add_card(Card(TEN, CLUBS));
    HHH->add_card(Card(JACK, CLUBS));
    HHH->add_card(Card(JACK, SPADES));
    HHH->add_card(Card(NINE, CLUBS));

    Card led_7 = Card(KING, CLUBS);
    Card test_7 = HHH->play_card(led_7, SPADES);
    ASSERT_EQUAL(test_7, Card(TEN, CLUBS));
    delete HHH;

     Player * III = Player_factory("III", "Simple"); 
    //have both right and left bower, lead suit is left's suit
    III->add_card(Card(TEN, SPADES));
    III->add_card(Card(TEN, CLUBS));
    III->add_card(Card(JACK, CLUBS));
    III->add_card(Card(JACK, SPADES));
    III->add_card(Card(NINE, CLUBS));

    Card led_8 = Card(KING, SPADES);
    Card test_8 = III->play_card(led_8, SPADES);
    ASSERT_EQUAL(test_8, Card(JACK, SPADES));
    delete III;

}



//testing DDD&EEE, still AAA,CCC

// TEST(play_card_round1) {


//  }
















TEST(test_lead_card_left_bower)
{
    Player* Jefford = Player_factory("Jefford", "Simple");

    Jefford->add_card(Card(JACK, SPADES));
    Jefford->add_card(Card(KING, CLUBS));
    Jefford->add_card(Card(NINE, CLUBS));
    Jefford->add_card(Card(TEN, CLUBS));
    Jefford->add_card(Card(ACE, CLUBS));
    

    ASSERT_EQUAL(Jefford->lead_card(CLUBS), Card(JACK, SPADES));

    delete Jefford;
}

//
TEST(test_lead_card_only_off_suit)
{
    Player* bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(ACE, CLUBS));

    ASSERT_EQUAL(bob->lead_card(DIAMONDS), Card(ACE, CLUBS));

    delete bob;
}

//
TEST(test_only_trump_suit)
{
    Player* bob = Player_factory("Bob", "Simple");

    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(NINE, CLUBS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(TEN, CLUBS));
    

    ASSERT_EQUAL(bob->lead_card(CLUBS), Card(ACE, CLUBS));

    delete bob;
}

//
TEST(test_lead_card_right_bower)
{
    Player* Balen = Player_factory("Balen", "Simple");

    Balen->add_card(Card(QUEEN, CLUBS));
    Balen->add_card(Card(ACE, CLUBS));
    Balen->add_card(Card(KING, CLUBS));
    Balen->add_card(Card(TEN, CLUBS));
    Balen->add_card(Card(JACK, CLUBS));
    

    ASSERT_EQUAL(Balen->lead_card(CLUBS), Card(JACK, CLUBS));

    delete Balen;
}


//
TEST(test_make_trump_as_dealer){
    Player* const Jefford = Player_factory("Jefford", "Simple");

    Suit s = HEARTS;
    Jefford->add_card(Card(NINE, CLUBS));
    Jefford->add_card(Card(JACK, CLUBS));
    Jefford->add_card(Card(JACK, DIAMONDS));
    Jefford->add_card(Card(QUEEN, SPADES));
    Jefford->add_card(Card(TEN, HEARTS));
    

    ASSERT_TRUE(Jefford->make_trump(Card(NINE, DIAMONDS), 1, 2, s));

    delete Jefford;
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



TEST(test_play_card_follow_suit) {
    Player * Alex = Player_factory("Alex", "Simple");

    Alex->add_card(Card(JACK, DIAMONDS));
    Alex->add_card(Card(TEN, DIAMONDS));
    Alex->add_card(Card(QUEEN, HEARTS));
    Alex->add_card(Card(KING, CLUBS));
    Alex->add_card(Card(NINE, SPADES));

    Card led(TEN, CLUBS);

    Card test = Alex->play_card(led, DIAMONDS);

    ASSERT_EQUAL(test, Card(KING, CLUBS));

    delete Alex;
}


TEST(test_play_card_left_bower) {
    Player * bob = Player_factory("Bob", "Simple");
    
    bob->add_card(Card(ACE, CLUBS));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(KING, DIAMONDS));

    Card led(NINE, CLUBS);

    Card test = bob->play_card(led, CLUBS);

    ASSERT_EQUAL(test, Card(JACK, SPADES));

    delete bob;
}


TEST(test_play_card_no_follow_suit) {
    Player * Alex = Player_factory("Alex", "Simple");
    
    Alex->add_card(Card(NINE, CLUBS));
    Alex->add_card(Card(TEN, SPADES));
    Alex->add_card(Card(JACK, SPADES));
    Alex->add_card(Card(KING, HEARTS));
    Alex->add_card(Card(KING, CLUBS));

    Card led(KING, DIAMONDS);

    Card test = Alex->play_card(led, CLUBS);

    ASSERT_EQUAL(test, Card(TEN, SPADES));

    delete Alex;
}


TEST(test_play_card_right_bower) {
    Player * bob = Player_factory("Bob", "Simple");
    
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(JACK, HEARTS));

    Card led(QUEEN, HEARTS);

    Card test = bob->play_card(led, HEARTS);

    ASSERT_EQUAL(test, Card(JACK, HEARTS));

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


TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(KING, DIAMONDS));

  Card led(NINE, HEARTS);

  Card test = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(test, Card(KING, HEARTS));

  test = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(test, Card(TEN, HEARTS));

  test = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(test, Card(NINE, SPADES));

  test = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(test, Card(QUEEN, DIAMONDS));

  test = bob->play_card(led, DIAMONDS); 
  ASSERT_EQUAL(test, Card(KING, DIAMONDS));

  delete bob;
}



TEST_MAIN()