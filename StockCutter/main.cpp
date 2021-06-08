#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BaseCutter.h"
#include "BFD.h"
#include "FFD.h"

void testCutter(stock_cutter::BaseCutter* cutter, const std::vector<std::pair<double, size_t>>& orders)
{
	std::cout << "Start\n";
	for (auto& order : orders)
	{
		cutter->addOrder(order.first, order.second);
	}

	auto boards = cutter->cut();

	std::cout << "Result:\n";
	int num = 1;
	double totalWaste = 0.0;
	for (auto& board : boards)
	{
		//std::cout << "Board #" << num++ << ": ";
		/*for (auto& cut : board.cuts)
			std::cout << cut << ", ";*/

		double waste = 10.0 - board.cutsLen;
		//std::cout << "   waste: " << waste << "\n";
		totalWaste += waste;
	}

	std::cout << "Total waste: " << totalWaste;
}

int main()
{
	srand(time(nullptr));
	std::vector<std::pair<double, size_t>> orders;
	for (int i = 0; i < 100; ++i)
	{
		orders.push_back(std::make_pair(rand() / (double)RAND_MAX, (rand() % 1000) + 1000));
	}

	stock_cutter::BFDCutter bfd(10.0);
	stock_cutter::FFDCutter ffd(10.0);

	std::cout << "Test BFD\n";
	testCutter(&bfd, orders);
	std::cout << "Test FFD\n";
	testCutter(&ffd, orders);

	return 0;
}