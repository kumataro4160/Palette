export module palette.sgl.ste;

export import palette.value_type;

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
		constexpr STE& operator*=(value_t value)noexcept
		{
			l *= value;
			r *= value;
			return *this;
		}
		constexpr STE& operator/=(value_t value)noexcept
		{
			return (*this) *= (1.0 / value);
		}
		constexpr STE& calcElementwiseProduct(const STE& ste)noexcept
		{
			l *= ste.l;
			r *= ste.r;
			return *this;
		}
		constexpr STE& calcElementwiseQuotient(const STE& ste)noexcept
		{
			l /= ste.l;
			r /= ste.r;
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
		template <class SGL>
		constexpr STE<SGL> calcMatrixProduct(const SGL& sgl)const
		{
			return STE<SGL>(sgl * l, sgl * r);
		}
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
	constexpr STE<SMP> operator*(const STE<SMP>& left, value_t right)noexcept
	{
		return STE(left) *= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(STE<SMP>&& left, value_t right)noexcept
	{
		return left *= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(value_t left, const STE<SMP>& right)noexcept
	{
		return STE(right) *= left;
	}

	template <class SMP>
	constexpr STE<SMP> operator*(value_t left, STE<SMP>&& right)noexcept
	{
		return right *= left;
	}

	template <class SMP>
	constexpr STE<SMP> operator/(const STE<SMP>& left, value_t right)noexcept
	{
		return STE(left) /= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator/(STE<SMP>&& left, value_t right)noexcept
	{
		return left /= right;
	}

	template <class SMP>
	constexpr STE<SMP> operator/(value_t left, const STE<SMP>& right)noexcept
	{
		return calcElementwiseQuotient(STE<SMP>(left), right);
	}

	template <class SMP>
	constexpr STE<SMP> calcElementwiseProduct(const STE<SMP> &left, const STE<SMP> &right)noexcept
	{
		return STE(left).calcElementwiseProduct(right);
	}

	template <class SMP>
	constexpr STE<SMP> calcElementwiseProduct(STE<SMP> &&left, const STE<SMP> &right)noexcept
	{
		return left.calcElementwiseProduct(right);
	}

	template <class SMP>
	constexpr STE<SMP> calcElementwiseProduct(const STE<SMP> &left, STE<SMP> &&right)noexcept
	{
		return right.calcElementwiseProduct(left);
	}

	template <class SMP>
	constexpr STE<SMP> calcElementwiseProduct(STE<SMP> &&left, STE<SMP> &&right)noexcept
	{
		return left.calcElementwiseProduct(right);
	}

	template <class SMP>
	constexpr STE<SMP> calcElementwiseQuotient(const STE<SMP> &left, const STE<SMP> &right)noexcept
	{
		return STE(left).calcElementwiseQuotient(right);
	}

	template <class SMP>
	constexpr STE<SMP> calcElementwiseQuotient(STE<SMP> &&left, const STE<SMP> &right)noexcept
	{
		return left.calcElementwiseQuotient(right);
	}
}