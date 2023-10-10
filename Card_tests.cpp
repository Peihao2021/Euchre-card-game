#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_greater_than) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card e(JACK, SPADES);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_FALSE(a > b);
    ASSERT_FALSE(b > a);
    ASSERT_FALSE(c > a);
    ASSERT_TRUE(a > c);
    ASSERT_TRUE(e > b);
    ASSERT_FALSE(f > c);
    ASSERT_TRUE(e > f);
    ASSERT_FALSE(g <= e);
    ASSERT_TRUE(b <= g);
}

TEST(test_less_than_or_equal_to) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card e(JACK, SPADES);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_TRUE(a <= b);
    ASSERT_TRUE(b <= a);
    ASSERT_TRUE(c <= a);
    ASSERT_FALSE(e <= b);
    ASSERT_TRUE(f <= c);
    ASSERT_FALSE(g <= e);
    ASSERT_TRUE(b <= g);
}

TEST(test_less_than) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card e(JACK, SPADES);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_FALSE(a < b);
    ASSERT_FALSE(b < a);
    ASSERT_TRUE(c < a);
    ASSERT_FALSE(e < b);
    ASSERT_TRUE(f < c);
    ASSERT_FALSE(g < e);
    ASSERT_TRUE(b < g);
}

// trump: HEARTS
TEST(test_get_suit_right_bower) {
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
    ASSERT_EQUAL(HEARTS, c.get_suit(HEARTS));
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_left_bower(HEARTS));
    ASSERT_TRUE(c.is_right_bower(HEARTS));
    ASSERT_TRUE(c.is_trump(HEARTS));
}

// trump: CLUBS
TEST(test_get_suit_left_bower) {
    Card c(JACK, SPADES);
    ASSERT_EQUAL(JACK, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
    ASSERT_EQUAL(CLUBS, c.get_suit(CLUBS));
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_TRUE(c.is_left_bower(CLUBS));
    ASSERT_FALSE(c.is_right_bower(CLUBS));
    ASSERT_TRUE(c.is_trump(CLUBS));
}

// trump: CLUBS
TEST(test_is_face_or_ace_false) {
    Card c(TEN, DIAMONDS);
    ASSERT_EQUAL(TEN, c.get_rank());
    ASSERT_EQUAL(DIAMONDS, c.get_suit());
    ASSERT_EQUAL(DIAMONDS, c.get_suit(CLUBS));
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_left_bower(CLUBS));
    ASSERT_FALSE(c.is_right_bower(CLUBS));
    ASSERT_FALSE(c.is_trump(CLUBS));
}

// trump: SPADES
TEST(test_card_default_ctor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
    ASSERT_EQUAL(SPADES, c.get_suit(SPADES));
    ASSERT_FALSE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_left_bower(SPADES));
    ASSERT_FALSE(c.is_right_bower(SPADES));
    ASSERT_TRUE(c.is_trump(SPADES));
}

// trump: DIAMONDS
TEST(test_card_overloaded_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
    ASSERT_EQUAL(HEARTS, c.get_suit(DIAMONDS));
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_FALSE(c.is_left_bower(HEARTS));
    ASSERT_FALSE(c.is_right_bower(HEARTS));
    ASSERT_FALSE(c.is_trump(DIAMONDS));
}

// Add more test cases here

TEST_MAIN()
