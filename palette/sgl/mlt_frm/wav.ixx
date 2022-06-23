module;

#include <vector>

export module palette.sgl.wav;

export import palette.ztm;
export import palette.ntm;
export import palette.value_type;

export namespace palette
{
	template <class FRM>
	class WAV
	{
		std::vector<FRM> frms;

	public:
		constexpr WAV()noexcept
		{

		}
		constexpr explicit WAV(size_t length) :
			frms(length)
		{

		}
		constexpr explicit WAV(const std::vector<FRM>& wav) :
			frms(wav)
		{

		}
		constexpr explicit WAV(std::vector<FRM>&& wav)noexcept :
			frms(std::move(wav))
		{

		}
		constexpr FRM& operator[](ZTM n)noexcept
		{
			return frms[n];
		}
		constexpr const FRM& operator[](ZTM n)const noexcept
		{
			return frms[n];
		}
		constexpr FRM& at(ZTM n)
		{
			return frms.at(n);
		}
		constexpr const FRM& at(ZTM n)const
		{
			return frms.at(n);
		}
		constexpr FRM operator()(ZTM n)const noexcept
		{
			if(0 <= n && n < getLength())
			{
				return frms[n];
			}
			return FRM(0.0);
		}
		constexpr WAV& operator+=(const FRM& frm)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f += frm;
			}
			return *this;
		}
		constexpr WAV& operator-=(const FRM& frm)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f -= frm;
			}
			return *this;
		}
		constexpr WAV& operator*=(value_t value)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f *= value;
			}
			return *this;
		}
		constexpr WAV& operator/=(value_t value)noexcept
		{
			return (*this) *= (1.0 / value);
		}
		constexpr WAV& calcElementwiseProduct(const FRM& frm)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f.calcElementwiseProduct(frm);
			}
			return *this;
		}
		constexpr WAV& calcElementwiseQuotient(const FRM& frm)noexcept
		{
			return this->calcElementwiseQuotient(FRM(1.0).calcElementwiseQuotient(frm));
		}
		constexpr WAV operator-()const
		{
			return WAV<FRM>(*this) *= -1.0;
		}
		constexpr NTM getLength()const noexcept
		{
			return static_cast<NTM>(frms.size());
		}
		constexpr auto begin()noexcept
		{
			return frms.begin();
		}
		constexpr auto begin()const noexcept
		{
			return frms.begin();
		}
		constexpr auto end()noexcept
		{
			return frms.end();
		}
		constexpr auto end()const noexcept
		{
			return frms.end();
		}
		constexpr void resize(size_t n)
		{
			frms.resize(n);
		}
	};

	template <class FRM>
	constexpr WAV<FRM> operator+(const WAV<FRM>& left, const FRM& right)
	{
		return WAV<FRM>(left) += right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator+(WAV<FRM>&& left, const FRM& right)
	{
		return left += right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator+(const FRM& left, const WAV<FRM>& right)
	{
		return WAV<FRM>(right) += left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator+(const FRM& left, WAV<FRM>&& right)
	{
		return right += left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator-(const WAV<FRM>& left, const FRM& right)
	{
		return WAV<FRM>(left) -= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator-(WAV<FRM>&& left, const FRM& right)
	{
		return left -= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator-(const FRM& left, const WAV<FRM>& right)
	{
		return -right += left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator-(const FRM& left, WAV<FRM>&& right)
	{
		return (right *= -1.0) += left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(const WAV<FRM>& left, value_t right)
	{
		return WAV<FRM>(left) *= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(WAV<FRM>&& left, value_t right)
	{
		return left *= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(value_t left, const WAV<FRM>& right)
	{
		return WAV<FRM>(right) *= left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(value_t left, WAV<FRM>&& right)
	{
		return right *= left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(const WAV<FRM>& left, value_t right)
	{
		return WAV<FRM>(left) /= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(WAV<FRM>&& left, value_t right)
	{
		return left /= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(value_t left, const WAV<FRM>& right)
	{
		const ZTM wavLength = right.getLength();
		WAV<FRM> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = calcElementwiseQuotient(FRM(left), right[t]);
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseProduct(const WAV<FRM>& left, const FRM& right)
	{
		return WAV<FRM>(left).calcElementwiseProduct(right);
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseProduct(WAV<FRM>&& left, const FRM& right)
	{
		return left.calcElementwiseProduct(right);
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseProduct(const FRM& left, const WAV<FRM>& right)
	{
		return WAV<FRM>(right).calcElementwiseProduct(left);
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseProduct(const FRM& left, WAV<FRM>&& right)
	{
		return right.calcElementwiseProduct(left);
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseQuotient(const WAV<FRM>& left, const FRM& right)
	{
		return WAV<FRM>(left).calcElementwiseQuotient(right);
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseQuotient(WAV<FRM>&& left, const FRM& right)
	{
		return left.calcElementwiseQuotient(right);
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseQuotient(const FRM& left, const WAV<FRM>& right)
	{
		const ZTM wavLength = right.getLength();
		WAV<FRM> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = calcElementwiseQuotient(left, right[t]);
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> calcElementwiseQuotient(const FRM& left, WAV<FRM>&& right)
	{
#pragma omp for
		for(FRM& rightFrm : right)
		{
			rightFrm = calcElementwiseQuotient(left, rightFrm);
		}
		return right;
	}
}