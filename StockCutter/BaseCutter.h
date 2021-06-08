#pragma once

#include <vector>

namespace stock_cutter
{
	struct Order
	{
		double size;
		size_t count;
	};

	struct Board
	{
		std::vector<double> cuts;
		double cutsLen;
		double lenRemaining;
	};

	class BaseCutter
	{
	protected:
		double m_size;
		std::vector<Order> m_orders;

	public:
		BaseCutter(double size)
			: m_size(size) { }

		virtual ~BaseCutter() { }

		void addOrder(double size, size_t count)
		{
			m_orders.push_back({ size, count });
		}

		virtual std::vector<Board> cut() = 0;
	};
}
