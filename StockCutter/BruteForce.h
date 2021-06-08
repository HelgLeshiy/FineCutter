#pragma once

#include "BaseCutter.h"

#include <numeric>

namespace stock_cutter
{
	class BruteForceCutter : public BaseCutter
	{
	public:
		BruteForceCutter(size_t size) : BaseCutter(size) { }

		virtual ~BruteForceCutter() { }

		virtual std::vector<Board> cut() override
		{
			return std::vector<Board>();
		}
	};
}