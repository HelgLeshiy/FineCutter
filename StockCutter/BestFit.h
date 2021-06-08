#pragma once

#include "BaseCutter.h"

namespace stock_cutter
{
	class BestFitCutter : public BaseCutter
	{
	protected:
		virtual Board* findNextBoard(const Order& order, std::vector<Board>& boards) = 0;

	public:
		BestFitCutter(double size) : BaseCutter(size) { }

		virtual ~BestFitCutter() { }

		virtual std::vector<Board> cut() override
		{
			std::vector<Board> boards;
			for (auto& order : m_orders)
			{
				for (int i = 0; i < order.count; ++i)
				{
					Board* minBoard = findNextBoard(order, boards);

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
	};
}