export module palette.sgl.mns;

export import palette.sgl.ste;
export import palette.value_type;

export namespace palette
{
	template <class SMP>
	struct MNS
	{
		SMP m;
		SMP s;

		constexpr MNS()noexcept
		{

		}
		constexpr explicit MNS(SMP m)noexcept :
			m(m)
		{

		}
		constexpr explicit MNS(SMP m, SMP s)noexcept :
			m(m), s(s)
		{

		}
		constexpr explicit MNS(const STE<SMP> &ste)noexcept :
			m((ste.l + ste.r) / 2.0), s((ste.l - ste.r) / 2.0)
		{

		}
		constexpr explicit operator STE<SMP>()const noexcept
		{
			return STE(m + s, m - s);
		}
		template <class ConvertedSMP>
		constexpr explicit operator MNS<ConvertedSMP>()const noexcept
		{
			return MNS<ConvertedSMP>(static_cast<ConvertedSMP>(m), static_cast<ConvertedSMP>(s));
		}
		constexpr MNS &operator+=(const MNS &mns)noexcept
		{
			m += mns.m;
			s += mns.s;
			return *this;
		}
		constexpr MNS &operator-=(const MNS &mns)noexcept
		{
			m -= mns.m;
			s -= mns.s;
			return *this;
		}
		constexpr MNS &operator*=(value_t value)noexcept
		{
			m *= value;
			s *= value;
			return *this;
		}
		constexpr MNS &operator/=(value_t value)noexcept
		{
			return (*this) *= (1.0 / value);
		}
		constexpr MNS& calcElementwiseProduct(const MNS& mns)noexcept
		{
			m *= mns.m;
			s *= mns.s;
			return *this;
		}
		constexpr MNS& calcElementwiseQuotient(const MNS& mns)noexcept
		{
			m /= mns.m;
			s /= mns.s;
			return *this;
		}
		constexpr MNS operator-()const noexcept
		{
			return MNS(-m, -s);
		}
		constexpr MNS swap()noexcept
		{
			const SMP tmp = m;
			m = s;
			s = tmp;
			return *this;
		}
		constexpr MNS makeSwapped()const noexcept
		{
			return MNS(s, m);
		}
		template <class SGL>
		constexpr MNS<SGL> calcMatrixProduct(const SGL& sgl)const
		{
			return MNS<SGL>(sgl * m, sgl * s);
		}
	};

	template <class SMP>
	constexpr MNS<SMP> operator+(const MNS<SMP>& left, const MNS<SMP>& right)noexcept
	{
		return MNS(left) += right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator+(MNS<SMP>&& left, const MNS<SMP>& right)noexcept
	{
		return left += right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator+(const MNS<SMP>& left, MNS<SMP>&& right)noexcept
	{
		return right += left;
	}

	template <class SMP>
	constexpr MNS<SMP> operator+(MNS<SMP>&& left, MNS<SMP>&& right)noexcept
	{
		return left += right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator-(const MNS<SMP>& left, const MNS<SMP>& right)noexcept
	{
		return MNS(left) -= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator-(MNS<SMP>&& left, const MNS<SMP>& right)noexcept
	{
		return left -= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(const MNS<SMP>& left, value_t right)noexcept
	{
		return MNS(left) *= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(MNS<SMP>&& left, value_t right)noexcept
	{
		return left *= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(value_t left, const MNS<SMP>& right)noexcept
	{
		return MNS(right) *= left;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(value_t left, MNS<SMP>&& right)noexcept
	{
		return right *= left;
	}

	template <class SMP>
	constexpr MNS<SMP> operator/(const MNS<SMP>& left, value_t right)noexcept
	{
		return MNS(left) /= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator/(MNS<SMP>&& left, value_t right)noexcept
	{
		return left /= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator/(value_t left, const MNS<SMP>& right)noexcept
	{
		return calcElementwiseQuotient(MNS<SMP>(left), right);
	}

	template <class SMP>
	constexpr MNS<SMP> calcElementwiseProduct(const MNS<SMP>& left, const MNS<SMP>& right)noexcept
	{
		return MNS(left).calcElementwiseProduct(right);
	}

	template <class SMP>
	constexpr MNS<SMP> calcElementwiseProduct(MNS<SMP>&& left, const MNS<SMP>& right)noexcept
	{
		return left.calcElementwiseProduct(right);
	}

	template <class SMP>
	constexpr MNS<SMP> calcElementwiseProduct(const MNS<SMP>& left, MNS<SMP>&& right)noexcept
	{
		return right.calcElementwiseProduct(left);
	}

	template <class SMP>
	constexpr MNS<SMP> calcElementwiseProduct(MNS<SMP>&& left, MNS<SMP>&& right)noexcept
	{
		return left.calcElementwiseProduct(right);
	}

	template <class SMP>
	constexpr MNS<SMP> calcElementwiseQuotient(const MNS<SMP>& left, const MNS<SMP>& right)noexcept
	{
		return MNS(left).calcElementwiseQuotient(right);
	}

	template <class SMP>
	constexpr MNS<SMP> calcElementwiseQuotient(MNS<SMP>&& left, const MNS<SMP>& right)noexcept
	{
		return left.calcElementwiseQuotient(right);
	}
}