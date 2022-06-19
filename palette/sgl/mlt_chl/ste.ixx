module;

#include <utility>

export module palette.sgl.ste;

export namespace palette
{
	template <class SMP>
	struct STE
	{
		SMP l;
		SMP r;

		constexpr STE()noexcept
		{

		}
		constexpr explicit STE(SMP mid)noexcept :
			l(mid), r(mid)
		{

		}
		constexpr explicit STE(SMP l, SMP r)noexcept :
			l(l), r(r)
		{

		}
		template <class ConvertedSMP>
		constexpr explicit operator STE<ConvertedSMP>()const noexcept
		{
			return STE<ConvertedSMP>(static_cast<ConvertedSMP>(l), static_cast<ConvertedSMP>(r));
		}
		constexpr STE &operator+=(const STE &ste)noexcept
		{
			l += ste.l;
			r += ste.r;
			return *this;
		}
		constexpr STE &operator-=(const STE &ste)noexcept
		{
			l -= ste.l;
			r -= ste.r;
			return *this;
		}
		constexpr STE &operator*=(const STE &ste)noexcept
		{
			l *= ste.l;
			r *= ste.r;
			return *this;
		}
		constexpr STE &operator/=(const STE &ste)noexcept
		{
			l /= ste.l;
			r /= ste.r;
			return *this;
		}
		constexpr STE &operator+=(const SMP &t)noexcept
		{
			l += t;
			r += t;
			return *this;
		}
		constexpr STE &operator-=(const SMP &t)noexcept
		{
			l -= t;
			r -= t;
			return *this;
		}
		constexpr STE &operator*=(const SMP &t)noexcept
		{
			l *= t;
			r *= t;
			return *this;
		}
		constexpr STE &operator/=(const SMP &t)noexcept
		{
			l /= t;
			r /= t;
			return *this;
		}
		constexpr STE operator-()const noexcept
		{
			return STE(-l, -r);
		}
		constexpr SMP makeMNL()const noexcept
		{
			return (l + r) / 2.0;
		}
		constexpr STE swap()noexcept
		{
			const SMP tmp = l;
			l = r;
			r = tmp;
			return *this;
		}
		constexpr STE makeSwapped()const noexcept
		{
			return STE(r, l);
		}
		//í«â¡ÅFçsóÒÇ≈èÊéZ
	};
	
	template <class SMP>
	constexpr STE<SMP> operator+(const STE<SMP> &left, const STE<SMP> &right)noexcept
	{
		return STE(left) += right;
	}
	
	template <class SMP>
	constexpr STE<SMP> operator+(STE<SMP> &&left, const STE<SMP> &right)noexcept
	{
		return left += right;
	}
	
	template <class SMP>
	constexpr STE<SMP> operator+(const STE<SMP> &left, STE<SMP> &&right)noexcept
	{
		return right += left;
	}
	
	template <class SMP>
	constexpr STE<SMP> operator+(STE<SMP> &&left, STE<SMP> &&right)noexcept
	{
		return left += right;
	}
	
	template <class SMP>
	constexpr STE<SMP> operator-(const STE<SMP> &left, const STE<SMP> &right)noexcept
	{
		return STE(left) -= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator-(STE<SMP> &&left, const STE<SMP> &right)noexcept
	{
		return left -= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(const STE<SMP> &left, const STE<SMP> &right)noexcept
	{
		return STE(left) *= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(STE<SMP> &&left, const STE<SMP> &right)noexcept
	{
		return left *= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(const STE<SMP> &left, STE<SMP> &&right)noexcept
	{
		return right *= left;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(STE<SMP> &&left, STE<SMP> &&right)noexcept
	{
		return left *= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator/(const STE<SMP> &left, const STE<SMP> &right)noexcept
	{
		return STE(left) /= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator/(STE<SMP> &&left, const STE<SMP> &right)noexcept
	{
		return left /= right;
	}
}