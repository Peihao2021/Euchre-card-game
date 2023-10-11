#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

TEST(test_shuffle_overloaded_ctor) {
    ifstream input("pack.in");
    Pack pack(input);
    pack.shuffle();

    Card a = pack.deal_one();
    ASSERT_TRUE(a.get_rank() == KING && a.get_suit() == CLUBS);
    Card b = pack.deal_one();
    ASSERT_TRUE(b.get_rank() == JACK && b.get_suit() == HEARTS);
    Card c = pack.deal_one();
    ASSERT_TRUE(c.get_rank() == NINE && c.get_suit() == SPADES);
    Card d = pack.deal_one();
    ASSERT_TRUE(d.get_rank() == ACE && d.get_suit() == CLUBS);
    Card e = pack.deal_one();
    ASSERT_TRUE(e.get_rank() == QUEEN && e.get_suit() == HEARTS);
    Card f = pack.deal_one();
    ASSERT_TRUE(f.get_rank() == TEN && f.get_suit() == SPADES);
    Card g = pack.deal_one();
    ASSERT_TRUE(g.get_rank() == NINE && g.get_suit() == DIAMONDS);
    Card h = pack.deal_one();
    ASSERT_TRUE(h.get_rank() == KING && h.get_suit() == HEARTS);
    Card i = pack.deal_one();
    ASSERT_TRUE(i.get_rank() == JACK && i.get_suit() == SPADES);
    Card j = pack.deal_one();
    ASSERT_TRUE(j.get_rank() == TEN && j.get_suit() == DIAMONDS);
    Card k = pack.deal_one();
    ASSERT_TRUE(k.get_rank() == ACE && k.get_suit() == HEARTS);
    Card l = pack.deal_one();
    ASSERT_TRUE(l.get_rank() == QUEEN && l.get_suit() == SPADES);
    Card m = pack.deal_one();
    ASSERT_TRUE(m.get_rank() == JACK && m.get_suit() == DIAMONDS);
    Card n = pack.deal_one();
    ASSERT_TRUE(n.get_rank() == NINE && n.get_suit() == CLUBS);
    Card o = pack.deal_one();
    ASSERT_TRUE(o.get_rank() == KING && o.get_suit() == SPADES);
    Card p = pack.deal_one();
    ASSERT_TRUE(p.get_rank() == QUEEN && p.get_suit() == DIAMONDS);
    Card q = pack.deal_one();
    ASSERT_TRUE(q.get_rank() == TEN && q.get_suit() == CLUBS);
    Card r = pack.deal_one();
    ASSERT_TRUE(r.get_rank() == ACE && r.get_suit() == SPADES);
    Card s = pack.deal_one();
    ASSERT_TRUE(s.get_rank() == KING && s.get_suit() == DIAMONDS);
    Card t = pack.deal_one();
    ASSERT_TRUE(t.get_rank() == JACK && t.get_suit() == CLUBS);
    Card u = pack.deal_one();
    ASSERT_TRUE(u.get_rank() == NINE && u.get_suit() == HEARTS);
    Card v = pack.deal_one();
    ASSERT_TRUE(v.get_rank() == ACE && v.get_suit() == DIAMONDS);
    Card w = pack.deal_one();
    ASSERT_TRUE(w.get_rank() == QUEEN && w.get_suit() == CLUBS);
    Card x = pack.deal_one();
    ASSERT_TRUE(x.get_rank() == TEN && x.get_suit() == HEARTS);
   
   ASSERT_TRUE(pack.empty());
}

TEST(test_shuffle_default_ctor) {
    Pack pack;
    pack.shuffle();

    Card a = pack.deal_one();
    ASSERT_TRUE(a.get_rank() == KING && a.get_suit() == CLUBS);
    Card b = pack.deal_one();
    ASSERT_TRUE(b.get_rank() == JACK && b.get_suit() == HEARTS);
    Card c = pack.deal_one();
    ASSERT_TRUE(c.get_rank() == NINE && c.get_suit() == SPADES);
    Card d = pack.deal_one();
    ASSERT_TRUE(d.get_rank() == ACE && d.get_suit() == CLUBS);
    Card e = pack.deal_one();
    ASSERT_TRUE(e.get_rank() == QUEEN && e.get_suit() == HEARTS);
    Card f = pack.deal_one();
    ASSERT_TRUE(f.get_rank() == TEN && f.get_suit() == SPADES);
    Card g = pack.deal_one();
    ASSERT_TRUE(g.get_rank() == NINE && g.get_suit() == DIAMONDS);
    Card h = pack.deal_one();
    ASSERT_TRUE(h.get_rank() == KING && h.get_suit() == HEARTS);
    Card i = pack.deal_one();
    ASSERT_TRUE(i.get_rank() == JACK && i.get_suit() == SPADES);
    Card j = pack.deal_one();
    ASSERT_TRUE(j.get_rank() == TEN && j.get_suit() == DIAMONDS);
    Card k = pack.deal_one();
    ASSERT_TRUE(k.get_rank() == ACE && k.get_suit() == HEARTS);
    Card l = pack.deal_one();
    ASSERT_TRUE(l.get_rank() == QUEEN && l.get_suit() == SPADES);
    Card m = pack.deal_one();
    ASSERT_TRUE(m.get_rank() == JACK && m.get_suit() == DIAMONDS);
    Card n = pack.deal_one();
    ASSERT_TRUE(n.get_rank() == NINE && n.get_suit() == CLUBS);
    Card o = pack.deal_one();
    ASSERT_TRUE(o.get_rank() == KING && o.get_suit() == SPADES);
    Card p = pack.deal_one();
    ASSERT_TRUE(p.get_rank() == QUEEN && p.get_suit() == DIAMONDS);
    Card q = pack.deal_one();
    ASSERT_TRUE(q.get_rank() == TEN && q.get_suit() == CLUBS);
    Card r = pack.deal_one();
    ASSERT_TRUE(r.get_rank() == ACE && r.get_suit() == SPADES);
    Card s = pack.deal_one();
    ASSERT_TRUE(s.get_rank() == KING && s.get_suit() == DIAMONDS);
    Card t = pack.deal_one();
    ASSERT_TRUE(t.get_rank() == JACK && t.get_suit() == CLUBS);
    Card u = pack.deal_one();
    ASSERT_TRUE(u.get_rank() == NINE && u.get_suit() == HEARTS);
    Card v = pack.deal_one();
    ASSERT_TRUE(v.get_rank() == ACE && v.get_suit() == DIAMONDS);
    Card w = pack.deal_one();
    ASSERT_TRUE(w.get_rank() == QUEEN && w.get_suit() == CLUBS);
    Card x = pack.deal_one();
    ASSERT_TRUE(x.get_rank() == TEN && x.get_suit() == HEARTS);
   
   ASSERT_TRUE(pack.empty());
}

TEST(test_pack_overloaded_ctor) {
    ifstream input("pack.in");
    Pack pack1(input);
    Pack pack2;

    for (int i = 0; i < 24; i++) {
        Card current1 = pack1.deal_one();
        Card current2 = pack2.deal_one();
        // cout << current1.get_rank() << " of " << current1.get_suit() << endl;
        // cout << current2.get_rank() << " of " << current2.get_suit() << endl;
        ASSERT_EQUAL(current1.get_rank(), current2.get_rank());
        ASSERT_EQUAL(current1.get_suit(), current2.get_suit());
    }
}

TEST(reset) {
    Pack pack;

    for (int i = 0; i < 12; i++) {
        pack.deal_one();
    }

    pack.reset();

    Card top = pack.deal_one();
    ASSERT_TRUE(top.get_rank() == NINE && top.get_suit() == SPADES);
}

TEST(test_pack_default_ctor) {
    Pack pack;

    for(int s = SPADES; s < DIAMONDS + 1; s++){
        for(int r = NINE; r < ACE + 1; r++){
            Card current = pack.deal_one();
            // cout << current.get_rank() << " of " << current.get_suit() << endl;
            ASSERT_EQUAL(r, current.get_rank());
            ASSERT_EQUAL(s, current.get_suit());
        }
    }

    ASSERT_TRUE(pack.empty());
    pack.reset();

    for(int s = SPADES; s < DIAMONDS + 1; s++){
        for(int r = NINE; r < ACE + 1; r++){
            Card current = pack.deal_one();
            // cout << current.get_rank() << " of " << current.get_suit() << endl;
            ASSERT_EQUAL(r, current.get_rank());
            ASSERT_EQUAL(s, current.get_suit());
        }
    }

    ASSERT_TRUE(pack.empty());
}

TEST_MAIN()
