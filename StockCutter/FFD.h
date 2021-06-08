#pragma once

#include "BestFit.h"

namespace stock_cutter
{
	class FFDCutter : public BestFitCutter
	{
	private:
		virtual Board* findNextBoard(const Order& order, std::vector<Board>& boards) override
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

	public:
		FFDCutter(double size) : BestFitCutter(size) { }
		virtual ~FFDCutter() { }
	};
}