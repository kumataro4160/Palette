module;

#include <vector>

export module palette.sgl.spc;

export import palette.ztm;
export import palette.ntm;
export import palette.value_type;

export namespace palette
{
	template <class FRM>
	class SPC
	{
		std::vector<FRM> frms;

	public:
		constexpr SPC()noexcept
		{

		}
		constexpr explicit SPC(size_t length) :
			frms(length)
		{

		}
		constexpr explicit SPC(const std::vector<FRM> &spc) :
			frms(spc)
		{

		}
		constexpr explicit SPC(std::vector<FRM> &&spc)noexcept :
			frms(std::move(spc))
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
		constexpr SPC& operator+=(const FRM& frm)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f += frm;
			}
			return *this;
		}
		constexpr SPC& operator-=(const FRM& frm)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f -= frm;
			}
			return *this;
		}
		constexpr SPC& operator*=(value_t value)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f *= value;
			}
			return *this;
		}
		constexpr SPC& operator/=(value_t value)noexcept
		{
			return (*this) *= (1.0 / value);
		}
		constexpr SPC& calcElementwiseProduct(const FRM& frm)noexcept
		{
#pragma omp for
			for(FRM& f : frms)
			{
				f.calcElementwiseProduct(frm);
			}
			return *this;
		}
		constexpr SPC& calcElementwiseQuotient(const FRM& frm)noexcept
		{
			return this->calcElementwiseQuotient(FRM(1.0).calcElementwiseQuotient(frm));
		}
		constexpr SPC operator-()const
		{
			return SPC<FRM>(*this) *= -1.0;
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
	constexpr SPC<FRM> operator+(const SPC<FRM>& left, const FRM& right)
	{
		return SPC<FRM>(left) += right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator+(SPC<FRM>&& left, const FRM& right)
	{
		return left += right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator+(const FRM& left, const SPC<FRM>& right)
	{
		return SPC<FRM>(right) += left;
	}

	template <class FRM>
	constexpr SPC<FRM> operator+(const FRM& left, SPC<FRM>&& right)
	{
		return right += left;
	}

	template <class FRM>
	constexpr SPC<FRM> operator-(const SPC<FRM>& left, const FRM& right)
	{
		return SPC<FRM>(left) -= right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator-(SPC<FRM>&& left, const FRM& right)
	{
		return left -= right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator-(const FRM& left, const SPC<FRM>& right)
	{
		return -right += left;
	}

	template <class FRM>
	constexpr SPC<FRM> operator-(const FRM& left, SPC<FRM>&& right)
	{
		return (right *= -1.0) += left;
	}

	template <class FRM>
	constexpr SPC<FRM> operator*(const SPC<FRM>& left, value_t right)
	{
		return SPC<FRM>(left) *= right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator*(SPC<FRM>&& left, value_t right)
	{
		return left *= right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator*(value_t left, const SPC<FRM>& right)
	{
		return SPC<FRM>(right) *= left;
	}

	template <class FRM>
	constexpr SPC<FRM> operator*(value_t left, SPC<FRM>&& right)
	{
		return right *= left;
	}

	template <class FRM>
	constexpr SPC<FRM> operator/(const SPC<FRM>& left, value_t right)
	{
		return SPC<FRM>(left) /= right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator/(SPC<FRM>&& left, value_t right)
	{
		return left /= right;
	}

	template <class FRM>
	constexpr SPC<FRM> operator/(value_t left, const SPC<FRM>& right)
	{
		const ZTM wavLength = right.getLength();
		SPC<FRM> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = calcElementwiseQuotient(FRM(left), right[t]);
		}
		return ret;
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseProduct(const SPC<FRM>& left, const FRM& right)
	{
		return SPC<FRM>(left).calcElementwiseProduct(right);
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseProduct(SPC<FRM>&& left, const FRM& right)
	{
		return left.calcElementwiseProduct(right);
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseProduct(const FRM& left, const SPC<FRM>& right)
	{
		return SPC<FRM>(right).calcElementwiseProduct(left);
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseProduct(const FRM& left, SPC<FRM>&& right)
	{
		return right.calcElementwiseProduct(left);
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseQuotient(const SPC<FRM>& left, const FRM& right)
	{
		return SPC<FRM>(left).calcElementwiseQuotient(right);
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseQuotient(SPC<FRM>&& left, const FRM& right)
	{
		return left.calcElementwiseQuotient(right);
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseQuotient(const FRM& left, const SPC<FRM>& right)
	{
		const ZTM wavLength = right.getLength();
		SPC<FRM> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = calcElementwiseQuotient(left, right[t]);
		}
		return ret;
	}

	template <class FRM>
	constexpr SPC<FRM> calcElementwiseQuotient(const FRM& left, SPC<FRM>&& right)
	{
#pragma omp for
		for(FRM& rightFrm : right)
		{
			rightFrm = calcElementwiseQuotient(left, rightFrm);
		}
		return right;
	}
}