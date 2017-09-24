#include "quicksort.h"
#include <iostream>

int main (void) {

	Lab309::SList<int> list = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};

	std::cout << list << '\n' << std::endl;

	quicksort(list, 0.5);

	std::cout << '\n' << list << std::endl;

	return 0;
}
