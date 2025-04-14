#include "interval_map.hpp"

int main() 
{
	interval_map<int, char> imap('A');
	imap.assign(3, 15, std::move('A')); // illigal
	imap.assign(13, 5, std::move('B')); // illigal
	imap.assign(3, 18, std::move('B')); //  3 : B, 15 : A
	imap.print();
    imap.assign(24, 30, std::move('Z')); // 3 : B ,  18 : A,  24 : Z,  30 : A
	imap.print();
	imap.assign(3, 10, std::move('C')); // 3 : C, 10 : B, 18 : A, 24 : Z, 30 : A
	imap.print();
	imap.assign(13, 16, std::move('C')); // 3 : C,  10 : B, 13 : C, 16 : B, 18 : A, 24 : Z, 30 : A
	imap.print();
	imap.assign(1, 4, std::move('X')); // 1 : X, 4 : C, 10 : B, 13 : C, 16 : B, 18 : A, 24 : Z, 30 : A
	imap.print();
	imap.assign(3, 11, std::move('Y')); // 1 : X, 3 : Y, 11 : B, 13 : C, 16 : B, 18 : A, 24 : Z, 30 : A
	imap.print();
	imap.assign(3, 11, std::move('Z')); // 1 : X, 3 : Z, 11 : B, 13 : C, 16 : B, 18 : A, 24 : Z, 30 : A
	imap.print();
	imap.assign(4, 10, std::move('Z')); // non valid move stay the same
	imap.print();

	imap.assign(2, 20, std::move('F')); // 1 : X, 2 : F, 20 : A, 24 : Z, 30 : A
	imap.print();

	return 0;
};