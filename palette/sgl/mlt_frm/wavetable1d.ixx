/*
export module subspace.wavetable1d;

export import subspace.ZTM;
import subspace.waveform;
//import subspace.th;
//import deeproot.pi;
//import sense.sinc_interpolation;

namespace subspace
{
	constexpr size_t tableSize = 2048;

	template <class FRM>
	class WaveTable1D;

	template <class FRM>
	WaveTable1D<FRM> operator<<(const WaveTable1D<FRM>&table, TH deltaTheta);

	template <class FRM>
	WaveTable1D<FRM> operator>>(const WaveTable1D<FRM>&table, TH deltaTheta);

	template <class FRM>
	class WaveTable1D
	{
		subspace::Waveform<FRM> waveform;

	public:
		constexpr WaveTable1D() :
			waveform(tableSize)
		{

		}
		template <class SGL>
		constexpr WaveTable1D(const SGL& sgl) :
			waveform(tableSize), looper(tableSize)
		{
			for(ZTM n = 0; n < tableSize; ++n)
			{
				waveform[n] = sgl[n];
			}
		}
		constexpr ZTM getLength()const noexcept
		{
			return tableSize;
		}
		constexpr FRM& operator[](ZTM n)noexcept
		{
			if constexpr(tableSize == 2048)
			{
				return waveform[n & 0x07ff];
			}
			else if constexpr(tableSize == 4096)
			{
				return waveform[n & 0x0fff];
			}
			return waveform[n % tableSize];
		}
		constexpr const FRM& operator[](ZTM n)const noexcept
		{
			if constexpr(tableSize == 2048)
			{
				return waveform[n & 0x07ff];
			}
			else if constexpr(tableSize == 4096)
			{
				return waveform[n & 0x0fff];
			}
			return waveform[n % tableSize];
		}
		constexpr auto begin()noexcept
		{
			return waveform.begin();
		}
		constexpr auto begin()const noexcept
		{
			return waveform.begin();
		}
		constexpr auto end()noexcept
		{
			return waveform.end();
		}
		constexpr auto end()const noexcept
		{
			return waveform.end();
		}
		constexpr WaveTable1D& operator+=(const WaveTable1D& waveTable)noexcept
		{
			for(ZTM n = 0; n < tableSize; ++n)
			{
				waveform[n] += waveTable.waveform[n];
			}
			return *this;
		}
		constexpr WaveTable1D& operator+=(FRM value)noexcept
		{
			for(FRM& frm : waveform)
			{
				frm += value;
			}
			return *this;
		}
		constexpr WaveTable1D& operator-=(const WaveTable1D& waveTable)noexcept
		{
			for(ZTM n = 0; n < tableSize; ++n)
			{
				waveform[n] -= waveTable.waveform[n];
			}
			return *this;
		}
		constexpr WaveTable1D& operator-=(FRM value)noexcept
		{
			return (*this) += (-value);
		}
		constexpr WaveTable1D& operator*=(const WaveTable1D& waveTable)noexcept
		{
			for(ZTM n = 0; n < tableSize; ++n)
			{
				waveform[n] *= waveTable.waveform[n];
			}
			return *this;
		}
		constexpr WaveTable1D& operator*=(FRM value)noexcept
		{
			for(FRM& frm : waveform)
			{
				frm *= value;
			}
			return *this;
		}
		constexpr WaveTable1D& operator/=(FRM value)noexcept
		{
			return (*this) *= (1.0 / value);
		}
		constexpr WaveTable1D& operator<<=(FRM deltaTheta)
		{
			*this = (*this << deltaTheta);
			return *this;
		}
		constexpr WaveTable1D& operator>>=(FRM th)
		{
			return (*this) <<= -th;
		}
		constexpr WaveTable1D& inverse()noexcept
		{
			(*this) *= -1.0;
			return *this;
		}
		constexpr WaveTable1D operator-()const
		{
			return WaveTable1D(*this).inverse();
		}
		constexpr FRM at(int n)const noexcept
		{
			return waveform[n & 0x7ff];//because the table size is 2048 and a wave table has a coronal loop structure.
		}
		constexpr FRM operator()(TH th)const noexcept
		{
			return sense::estimateBySincInterpolation(*this, th * tableSize / (2.0 * deeproot::pi));
		}
	};

	WaveTable1D operator+(const WaveTable1D &table1, const WaveTable1D &table2)
	{
		return WaveTable1D(table1) += table2;
	}

	WaveTable1D operator+(WaveTable1D &&table1, const WaveTable1D &table2)
	{
		return table1 += table2;
	}

	WaveTable1D operator+(const WaveTable1D &table1, WaveTable1D &&table2)
	{
		return table2 += table1;
	}

	WaveTable1D operator+(WaveTable1D &&table1, WaveTable1D &&table2)
	{
		return table1 += table2;
	}

	WaveTable1D operator+(const WaveTable1D &table, float64 value)
	{
		return WaveTable1D(table) += value;
	}

	WaveTable1D operator+(WaveTable1D &&table, float64 value)
	{
		return table += value;
	}

	WaveTable1D operator+(float64 value, const WaveTable1D &table)
	{
		return table + value;
	}

	WaveTable1D operator+(float64 value, WaveTable1D &&table)
	{
		return std::move(table) + value;
	}

	WaveTable1D operator-(const WaveTable1D &table1, const WaveTable1D &table2)
	{
		return WaveTable1D(table1) -= table2;
	}

	WaveTable1D operator-(WaveTable1D &&table1, const WaveTable1D &table2)
	{
		return table1 -= table2;
	}

	WaveTable1D operator-(WaveTable1D &&table1, WaveTable1D &&table2)
	{
		return table1 -= table2;
	}

	WaveTable1D operator-(const WaveTable1D &table, float64 value)
	{
		return WaveTable1D(table) -= value;
	}

	WaveTable1D operator-(WaveTable1D &&table, float64 value)
	{
		return table -= value;
	}

	WaveTable1D operator*(const WaveTable1D &table1, const WaveTable1D &table2)
	{
		return WaveTable1D(table1) *= table2;
	}

	WaveTable1D operator*(WaveTable1D &&table1, const WaveTable1D &table2)
	{
		return table1 *= table2;
	}

	WaveTable1D operator*(const WaveTable1D &table1, WaveTable1D &&table2)
	{
		return table2 *= table1;
	}

	WaveTable1D operator*(WaveTable1D &&table1, WaveTable1D &&table2)
	{
		return table1 *= table2;
	}

	WaveTable1D operator*(const WaveTable1D &table, float64 value)
	{
		return WaveTable1D(table) *= value;
	}

	WaveTable1D operator*(WaveTable1D &&table, float64 value)
	{
		return table *= value;
	}

	WaveTable1D operator*(float64 value, const WaveTable1D &table)
	{
		return table * value;
	}

	WaveTable1D operator*(float64 value, WaveTable1D &&table)
	{
		return std::move(table) * value;
	}

	WaveTable1D operator/(const WaveTable1D &table, float64 k)
	{
		return WaveTable1D(table) /= k;
	}

	WaveTable1D operator/(WaveTable1D &&table, float64 k)
	{
		return table /= k;
	}

	WaveTable1D operator<<(const WaveTable1D &table, float64 deltaTheta)
	{
		WaveTable1D ret;
		for(uint n = 0; n < tableSize; ++n)
		{
			const float64 th = 2.0 * pi * n / tableSize;
			ret[n] = table(th + deltaTheta);
		}
		return ret;
	}

	WaveTable1D operator>>(const WaveTable1D &table, float64 deltaTheta)
	{
		return table << (-deltaTheta);
	}
	
}
*/