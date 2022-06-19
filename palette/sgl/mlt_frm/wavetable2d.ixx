/*
export module subspace.wavetable2d;

namespace subspace
{
	class WaveTable2D
	{
		std::vector<WaveTable1D> table;

		float64 at(float64 y, int x)const noexcept
		{
			const int yLeft = static_cast<int>(y);
			const int yRight = (yLeft + 1) & 0x7ff;
			return table[yLeft][x] * (yRight - y) + table[yRight][x] * (y - yLeft);
		}

	public:
		WaveTable2D() :
			table(tableSize)
		{

		}
		WaveTable2D(const WaveTable1D &waveTable) :
			table(tableSize)
		{
			for(auto &table1D : table)
			{
				table1D = waveTable;
			}
		}
		auto &getTable()noexcept
		{
			return table;
		}
		const auto &getTable()const noexcept
		{
			return table;
		}
		WaveTable2D &operator+=(const WaveTable2D &waveTable)noexcept
		{
			for(uint32_t n = 0; n < tableSize; ++n)
			{
				table[n] += waveTable.getTable()[n];
			}
			return *this;
		}
		WaveTable2D &operator-=(const WaveTable2D &waveTable)noexcept
		{
			for(uint32_t n = 0; n < tableSize; ++n)
			{
				table[n] -= waveTable.getTable()[n];
			}
			return *this;
		}
		WaveTable2D &operator*=(const WaveTable2D &waveTable)noexcept
		{
			for(uint32_t n = 0; n < tableSize; ++n)
			{
				table[n] *= waveTable.getTable()[n];
			}
			return *this;
		}
		WaveTable2D &operator*=(float64 k)noexcept
		{
			for(auto &table1d : table)
			{
				table1d *= k;
			}
			return *this;
		}
		WaveTable2D &operator/=(float64 k)noexcept
		{
			return(*this) *= (1.0 / k);
		}
		WaveTable2D &normalize()
		{
			float64 max = 0.0;
			for(auto &tableX : table)
			{
				float64 maxTableX = *std::max_element(tableX.begin(), tableX.end());
				if(max < maxTableX)
				{
					max = maxTableX;
				}
			}
			*this /= max;
			return *this;
		}
		WaveTable2D &normalizeEach()
		{
			for(auto &tableX : table)
			{
				tableX.normalize();
			}
			return *this;
		}
		WaveTable2D &removeDCOffset()
		{
			float64 mean = 0.0;
			for(auto &&tableX : table)
			{
				float64 meanTableX = std::reduce(tableX.begin(), tableX.end(), 0.0) / tableSize;
				mean += meanTableX;
			}
			mean /= tableSize;
			for(auto &tableX : table)
			{
				for(auto &&smp : tableX)
				{
					smp -= mean;
				}
			}
			return *this;
		}
		WaveTable2D &removeDCOffsetEach()
		{
			for(auto &&tableX : table)
			{
				tableX.removeDCOffset();
			}
			return *this;
		}
		/*float64 out(float64 r, float64 th)const
		{
			const float64 y = std::clamp(r, 0.0, 1.0) * (tableSize - 1.0);
			const int yLeft = static_cast<int>(y);
			const int yRight = (yLeft + 1) & 0x7ff;
			if(y - yLeft <= EPSILON)
			{
				return table[yLeft](th);
			}
			if(yRight - y <= EPSILON)
			{
				return table[yRight](th);
			}
			const float64 xtmp = th * tableSize / (2.0 * pi);
			const int xLeft = static_cast<int>(xtmp) & 0x7ff;
			const float64 x = (xtmp - xtmp) + xLeft;
			const int xRight = (xLeft + 1) & 0x7ff;
			if(x - xLeft <= EPSILON)
			{
				return at(y, xLeft);
			}
			if(xRight - x <= EPSILON)
			{
				return at(y, xRight);
			}
			float64 ret = 0.0;
			for(int n = 0; n < precision; ++n)
			{
				const float64 deltaLeft = (x - (xLeft - n)) * pi;
				const float64 deltaRight = ((xRight + n) - x) * pi;
				const int l = (xLeft - n) % tableSize;
				const int r = (xRight + n) % (tableSize - 1);
				ret += at(y, l) * sin(deltaLeft) / deltaLeft * (0.5 + 0.5 * cos(deltaLeft / precision));
				ret += at(y, r) * sin(deltaRight) / deltaRight * (0.5 + 0.5 * cos(deltaRight / precision));
			}
			return ret;
		}
		float64 out(float64 r, float64 th, float64 og)const
		{
			const float64 bandLimit = og / (2.0 * pi);
			if(bandLimit >= 1.0)
			{
				return out(r, th);
			}
			const float64 y = std::clamp(r, 0.0, 1.0) * (tableSize - 1.0);
			const int yLeft = static_cast<int>(y);
			const int yRight = (yLeft + 1) & 0x7ff;
			if(y - yLeft <= EPSILON)
			{
				return table[yLeft].out(th, og);
			}
			if(yRight - y <= EPSILON)
			{
				return table[yRight].out(th, og);
			}
			const float64 xtmp = th * tableSize / (2.0 * pi);
			int xLeft = static_cast<int>(xtmp) & 0x7ff;
			const float64 x = (xtmp - xtmp) + xLeft;
			int xRight = (xLeft + 1) & 0x7ff;
			float64 ret = 0.0;
			if(x - xLeft <= EPSILON)
			{
				ret = bandLimit * at(y, xLeft);
				--xLeft;
			}
			else if(xRight - x <= EPSILON)
			{
				ret = bandLimit * at(y, xRight);
				++xRight;
			}
			const int N = static_cast<int>(precision / bandLimit);
			for(int n = 0; n < N; ++n)
			{
				const float64 deltaLeft = (x - (xLeft - n)) * pi;
				const float64 deltaRight = ((xRight + n) - x) * pi;
				const int l = (xLeft - n) & 0x7ff;
				const int r = (xRight + n) % 0x7ff;
				ret += at(y, l) * sin(bandLimit * deltaLeft) / deltaLeft * (0.5 + 0.5 * cos(deltaLeft / N));
				ret += at(y, r) * sin(bandLimit * deltaRight) / deltaRight * (0.5 + 0.5 * cos(deltaRight / N));
			}
			return ret;
		}
		WaveTable2D operator-()const
		{
			return WaveTable2D(*this) *= -1.0;
		}
	};
}

*/