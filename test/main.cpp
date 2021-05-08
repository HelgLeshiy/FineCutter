#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

struct Order
{
	double size;
	int count;
};

struct Board
{
	std::vector<double> cuts;
	double cutsLen;
	double lenRemaining;
};

class FineCutter
{
private:
	double m_size;
	std::vector<Order> m_orders;

private:
	Board* bfd(const Order& order, std::vector<Board>& boards)
	{
		double minLenRemaining = 0;
		Board* minBoard = nullptr;
		for (auto& board : boards)
		{
			double lenRemaining = m_size - board.cutsLen - order.size;
			if (lenRemaining > 0.0)
			{
				if (minBoard == nullptr)
				{
					minLenRemaining = lenRemaining;
					minBoard = &board;
				}
				else if (lenRemaining < minLenRemaining)
				{
					minLenRemaining = lenRemaining;
					minBoard = &board;
				}
			}
		}

		return minBoard;
	}

	Board* ffd(const Order& order, std::vector<Board>& boards)
	{
		for (auto& board : boards)
		{
			if (m_size - board.cutsLen - order.size > 0.0)
			{
				return &board;
			}
		}

		return nullptr;
	}

	std::vector<Board> bestFitDecreasing()
	{
		std::vector<Board> boards;
		for (auto& order : m_orders)
		{
			for (int i = 0; i < order.count; ++i)
			{
				Board* minBoard = bfd(order, boards);

				if (minBoard == nullptr)
				{
					Board newBoard = { std::vector<double>(), 0.0, 0.0 };
					boards.push_back(newBoard);
					minBoard = &newBoard;
				}

				minBoard->cuts.push_back(order.size);
				minBoard->cutsLen += order.size;
			}
		}

		return boards;
	}

public:
	FineCutter(double size)
		: m_size(size)
	{
	}

	void addOrder(double size, int count)
	{
		m_orders.push_back({ size, count });
	}

	std::vector<Board> cut()
	{
		// sort by size decreasing
		std::sort(m_orders.begin(), m_orders.end(), [](const Order& a, const Order& b) { return a.size > b.size; });
		int ordersNeededLeft = 0;
		for (auto& order : m_orders)
		{
			ordersNeededLeft += order.count;
		}

		return bestFitDecreasing();
	}
};

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
