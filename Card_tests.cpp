#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

// trump: CLUBS
// led: DIAMONDS
TEST(test_card_less_with_led) {
    Card led(NINE, DIAMONDS);
    Card a(JACK, CLUBS);
    Card b(JACK, CLUBS);
    Card c(JACK, DIAMONDS);
    Card d(ACE, HEARTS);
    Card e(JACK, SPADES);
    Card f(JACK, HEARTS);
    Card g(TEN, CLUBS);
    Card h(TEN, SPADES);
    Card i;
    ASSERT_FALSE(Card_less(a,b,led,CLUBS) && Card_less(b,a,led,CLUBS));
    ASSERT_TRUE(Card_less(e,a,led,CLUBS));
    ASSERT_FALSE(Card_less(b,e,led,CLUBS));
    ASSERT_FALSE(Card_less(c,f,led,CLUBS));
    ASSERT_TRUE(Card_less(f,c,led,CLUBS));
    ASSERT_FALSE(Card_less(c,f,led,CLUBS));
    ASSERT_FALSE(Card_less(a,d,led,CLUBS));
    ASSERT_TRUE(Card_less(d,c,led,CLUBS));
    ASSERT_FALSE(Card_less(g,h,led,CLUBS));
    ASSERT_TRUE(Card_less(h,g,led,CLUBS));
    ASSERT_FALSE(Card_less(g,i,led,CLUBS));
    ASSERT_TRUE(Card_less(i,h,led,CLUBS));
    ASSERT_FALSE(Card_less(led,h,led,CLUBS));
    ASSERT_FALSE(Card_less(g,led,led,CLUBS));
    ASSERT_TRUE(Card_less(led,g,led,CLUBS));
    ASSERT_TRUE(Card_less(i,led,led,CLUBS));
    ASSERT_FALSE(Card_less(led,i,led,CLUBS));
}

// trump: SPADES
TEST(test_card_less_no_led) {
    Card a(JACK, SPADES);
    Card b(JACK, SPADES);
    Card c(JACK, CLUBS);
    Card d(ACE, DIAMONDS);
    Card e(JACK, DIAMONDS);
    Card f(JACK, HEARTS);
    Card g(TEN, CLUBS);
    Card h(TEN, HEARTS);
    Card i;
    ASSERT_FALSE(Card_less(a,b,SPADES) && Card_less(b,a,SPADES));
    ASSERT_TRUE(Card_less(e,c,SPADES));
    ASSERT_FALSE(Card_less(c,e,SPADES));
    ASSERT_FALSE(Card_less(c,f,SPADES));
    ASSERT_TRUE(Card_less(f,c,SPADES));
    ASSERT_FALSE(Card_less(c,f,SPADES));
    ASSERT_TRUE(Card_less(d,c,SPADES));
    ASSERT_TRUE(Card_less(d,a,SPADES));
    ASSERT_FALSE(Card_less(a,d,SPADES));
    ASSERT_FALSE(Card_less(g,h,SPADES));
    ASSERT_TRUE(Card_less(h,g,SPADES));
    ASSERT_TRUE(Card_less(g,i,SPADES));
    ASSERT_FALSE(Card_less(i,h,SPADES));
}

TEST(test_suit_next) {
    ASSERT_TRUE(DIAMONDS == Suit_next(HEARTS));
    ASSERT_TRUE(CLUBS == Suit_next(SPADES));
    ASSERT_TRUE(HEARTS == Suit_next(DIAMONDS));
    ASSERT_TRUE(SPADES == Suit_next(CLUBS));
}

TEST(test_not_equal_to) {
    Card a(JACK, DIAMONDS);
    Card b(JACK, DIAMONDS);
    Card c(QUEEN, SPADES);
    ASSERT_FALSE(a != b);
    ASSERT_FALSE(b != a);
    ASSERT_TRUE(c != a);
    ASSERT_TRUE(a != c);
}

TEST(test_equal_to) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(FIVE, CLUBS);
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(b == a);
    ASSERT_FALSE(c == a);
    ASSERT_FALSE(a == c);
}

TEST(test_greater_than_or_equal_to) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card d(JACK, SPADES);
    Card e(JACK, DIAMONDS);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_TRUE(a >= b && b >= a);
    ASSERT_TRUE(c >= a);
    ASSERT_FALSE(a >= c);
    ASSERT_FALSE(d >= b);
    ASSERT_TRUE(b >= d);
    ASSERT_TRUE(e >= a && e >= b && e >= c && e >= d);
    ASSERT_FALSE(f >= c);
    ASSERT_TRUE(c >= f);
    ASSERT_TRUE(g >= d);
    ASSERT_FALSE(b >= g);
}

TEST(test_greater_than) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card d(JACK, SPADES);
    Card e(JACK, DIAMONDS);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_FALSE(a > b);
    ASSERT_FALSE(b > a);
    ASSERT_TRUE(c > a);
    ASSERT_FALSE(a > c);
    ASSERT_FALSE(d > b);
    ASSERT_TRUE(b > d);
    ASSERT_TRUE(e > a && e > b && e > c && e > d);
    ASSERT_FALSE(f > c);
    ASSERT_TRUE(c > f);
    ASSERT_TRUE(g > d);
    ASSERT_FALSE(b > g);
}

TEST(test_less_than_or_equal_to) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card d(JACK, SPADES);
    Card e(JACK, DIAMONDS);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_TRUE(a <= b && b <= a);
    ASSERT_FALSE(c <= a);
    ASSERT_TRUE(a <= c);
    ASSERT_TRUE(d <= b);
    ASSERT_TRUE(a <= e && b <= e && c <= e && d <= e);
    ASSERT_TRUE(f <= c);
    ASSERT_FALSE(g <= d);
    ASSERT_TRUE(b <= g);
}

TEST(test_less_than) {
    Card a(JACK, HEARTS);
    Card b(JACK, HEARTS);
    Card c(JACK, CLUBS);
    Card d(JACK, SPADES);
    Card e(JACK, DIAMONDS);
    Card f;
    Card g(ACE, DIAMONDS);
    ASSERT_FALSE(a < b);
    ASSERT_FALSE(b < a);
    ASSERT_FALSE(c < a);
    ASSERT_TRUE(a < c);
    ASSERT_TRUE(d < b);
    ASSERT_TRUE(a < e && b < e && c < e && d < e);
    ASSERT_TRUE(f < c);
    ASSERT_FALSE(g < d);
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

TEST_MAIN()
