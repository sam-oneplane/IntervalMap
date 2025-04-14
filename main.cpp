#include "interval_map.hpp"

int main() 
{
	interval_map<int, char> imap('A');
	imap.assign(3, 15, std::move('A')); // illigal
	imap.assign(13, 5, std::move('B')); // illigal
	imap.assign(3, 18, std::move('B')); // {3:B} {15:A}
	imap.print();
    imap.assign(24, 30, std::move('Z')); //
	imap.print();
	imap.assign(3, 10, std::move('C')); // {3:B} {6:C} {10:A}
	imap.print();
	imap.assign(13, 16, std::move('C')); // {3:B} {6:C} {10:D} {12:A}
	imap.print();
	imap.assign(1, 4, std::move('X')); // {1:X} {4:B} {6:C} {10:D} {12:A}
	imap.print();
	imap.assign(3, 11, std::move('Y')); // {1:X} {3:Y} {11:D} {12:A}
	imap.print();
	imap.assign(3, 11, std::move('Z')); // {1:X} {3:Z} {11:D} {12:A}
	imap.print();
	imap.assign(4, 10, std::move('Z')); // {1:X} {3:Z} {11:D} {12:A}
	imap.print();

	imap.assign(2, 20, std::move('F')); // {1:X} {2:Z} {20:A}
	imap.print();

	return 0;
};