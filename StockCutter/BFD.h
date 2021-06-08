#pragma once

#include "BestFit.h"

namespace stock_cutter
{
	class BFDCutter : public BestFitCutter
	{
	private: 
		virtual Board* findNextBoard(const Order& order, std::vector<Board>& boards) override
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

	public:
		BFDCutter(double size) : BestFitCutter(size) { }
		virtual ~BFDCutter() { }
	};
}