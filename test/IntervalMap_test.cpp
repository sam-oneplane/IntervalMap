#include "interval_map.hpp"
#include <gtest/gtest.h>

class IntervalMapTest : public ::testing::Test {

protected:
    interval_map<int, char> imap;

    IntervalMapTest() : imap('A'){}
    void SetUp() override {}
    void TearDown() override {}

};

TEST_F(IntervalMapTest, test1) {
    std::map<int, char> tmap { {3,'B'}, {18,'A'}};

    imap.assign(3, 15, std::move('A')); // illigal
	imap.assign(13, 5, std::move('B')); // illigal
	imap.assign(3, 18, std::move('B')); // {3:B} {15:A}

    ASSERT_EQ(imap.get_imap(), tmap);
}

TEST_F(IntervalMapTest, test2) {
    std::map<int, char> tmap { {3,'B'}, {18,'A'}, {24,'Z'}, {30,'A'}};

    imap.assign(3, 18, std::move('B'));
    imap.assign(24, 30, std::move('Z'));

    ASSERT_EQ(imap.get_imap(), tmap);
}

TEST_F(IntervalMapTest, test3) {
    std::map<int, char> tmap { {3,'C'}, {10,'B'}, {13,'C'}, {16,'B'}, {18,'A'}, {24,'Z'}, {30,'A'}};

    imap.assign(3, 18, std::move('B'));
    imap.assign(24, 30, std::move('Z'));
    imap.assign(3, 10, std::move('C'));
    imap.assign(13, 16, std::move('C'));
    
    ASSERT_EQ(imap.get_imap(), tmap);
}

TEST_F(IntervalMapTest, test4) {
    std::map<int, char> tmap { {1,'X'}, {3,'Y'}, {11,'B'}, {13,'C'}, {16,'B'}, {18,'A'}, {24,'Z'}, {30,'A'}};

    imap.assign(3, 18, std::move('B'));
    imap.assign(24, 30, std::move('Z'));
    imap.assign(3, 10, std::move('C'));
    imap.assign(13, 16, std::move('C'));
    imap.assign(1, 4, std::move('X'));
    imap.assign(3, 11, std::move('Y'));
    
    ASSERT_EQ(imap.get_imap(), tmap);
}

TEST_F(IntervalMapTest, test5) {
    std::map<int, char> tmap { {1,'X'}, {2,'F'}, {20,'A'}, {24,'Z'}, {30,'A'}};

    imap.assign(3, 18, std::move('B'));
    imap.assign(24, 30, std::move('Z'));
    imap.assign(3, 10, std::move('C'));
    imap.assign(13, 16, std::move('C'));
    imap.assign(1, 4, std::move('X'));
    imap.assign(3, 11, std::move('Y'));
    imap.assign(3, 11, std::move('Z')); // 1 : X	3 : Z	11 : B	13 : C	16 : B	18 : A	24 : Z	30 : A
	imap.assign(4, 10, std::move('Z')); // illigal prev & next entries value = 'Z'
	imap.assign(2, 20, std::move('F')); 
    
    ASSERT_EQ(imap.get_imap(), tmap);
}