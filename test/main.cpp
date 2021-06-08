#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>


int main()
{
	srand(time(nullptr));

	FineCutter cutter(10.0);

	for (int i = 0; i < 100; ++i)
	{
		cutter.addOrder(rand() / (double)RAND_MAX, (rand() % 1000) + 1000);
	}

	auto boards = cutter.cut();

	std::cout << "Result:\n";
	int num = 1;
	double totalWaste = 0.0;
	for (auto& board : boards)
	{
		std::cout << "Board #" << num++ << ": ";
		for (auto& cut : board.cuts)
			std::cout << cut << ", ";

		double waste = 10.0 - board.cutsLen;
		std::cout << "   waste: " << waste << "\n";
		totalWaste += waste;
	}

	std::cout << "Total waste: " << totalWaste;

	return 0;
}
