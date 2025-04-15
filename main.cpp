#include "interval_map.hpp"
#include <cassert>

void IntervalMapTest()
{
	interval_map<int, char> imap('A');
    std::map<int, char> tmap_0 { {3,'B'}, {18,'A'}};
    std::map<int, char> tmap_1 { {3,'B'}, {18,'A'}, {24,'Z'}, {30,'A'}};
    std::map<int, char> tmap_2 { {3,'C'}, {10,'B'}, {13,'C'}, {16,'B'}, {18,'A'}, {24,'Z'}, {30,'A'}};
    std::map<int, char> tmap_3 { {1,'X'}, {3,'Y'}, {11,'B'}, {13,'C'}, {16,'B'}, {18,'A'}, {24,'Z'}, {30,'A'}};
	std::map<int, char> tmap_4 { {1,'X'}, {2,'F'}, {20,'A'}, {24,'Z'}, {30,'A'}};

	imap.assign(3, 15, std::move('A')); // illigal
	imap.assign(13, 5, std::move('B')); // illigal
	imap.assign(3, 18, std::move('B')); // {3:B} {15:A}
	imap.print();
    assert(imap.m_map == tmap_0);
    imap.assign(24, 30, std::move('Z')); // 3 : B	18 : A	24 : Z	30 : A	
	imap.print();
    assert(imap.m_map == tmap_1);
	imap.assign(3, 10, std::move('C')); // 3 : C	10 : B	18 : A	24 : Z	30 : A	
	imap.print();
	imap.assign(13, 16, std::move('C')); //3 : C   10 : B	13 : C	16 : B	18 : A	24 : Z	30 : A
    assert(imap.m_map == tmap_2);	
	imap.print();
	imap.assign(1, 4, std::move('X')); // 1 : X	 4 : C	10 : B	13 : C	16 : B	18 : A	24 : Z	30 : A	
	imap.print();
	imap.assign(3, 11, std::move('Y')); // 1 : X	3 : Y	11 : B	13 : C	16 : B	18 : A	24 : Z	30 : A
    assert(imap.m_map == tmap_3);	 
	imap.print();
	imap.assign(3, 11, std::move('Z')); // 1 : X	3 : Z	11 : B	13 : C	16 : B	18 : A	24 : Z	30 : A
	imap.print();
	imap.assign(4, 10, std::move('Z')); // illigal prev & next entries value = 'Z'
	imap.print();
	imap.assign(2, 20, std::move('F')); // 1 : X	2 : F	20 : A	24 : Z	30 : A	
    assert(imap.m_map == tmap_4);
	imap.print();
}

int main() 
{
	
	IntervalMapTest();
	return 0;
};