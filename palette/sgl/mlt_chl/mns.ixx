export module palette.sgl.mns;

export import palette.sgl.ste;

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
		constexpr MNS &operator*=(const MNS &mns)noexcept
		{
			m *= mns.m;
			s *= mns.s;
			return *this;
		}
		constexpr MNS &operator/=(const MNS &mns)noexcept
		{
			m /= mns.m;
			s /= mns.s;
			return *this;
		}
		constexpr MNS &operator+=(const SMP &t)noexcept
		{
			m += t;
			return *this;
		}
		constexpr MNS &operator-=(const SMP &t)noexcept
		{
			m -= t;
			return *this;
		}
		constexpr MNS &operator*=(const SMP &t)noexcept
		{
			m *= t;
			s *= t;
			return *this;
		}
		constexpr MNS &operator/=(const SMP &t)noexcept
		{
			m /= t;
			s /= t;
			return *this;
		}
		constexpr MNS operator-()const noexcept
		{
			return MNS(-m, -s);
		}
	};

	template <class SMP>
	constexpr MNS<SMP> operator+(const MNS<SMP> &left, const MNS<SMP> &right)noexcept
	{
		return MNS(left) += right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator+(MNS<SMP> &&left, const MNS<SMP> &right)noexcept
	{
		return left += right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator+(const MNS<SMP> &left, MNS<SMP> &&right)noexcept
	{
		return right += left;
	}

	template <class SMP>
	constexpr MNS<SMP> operator+(MNS<SMP> &&left, MNS<SMP> &&right)noexcept
	{
		return left += right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator-(const MNS<SMP> &left, const MNS<SMP> &right)noexcept
	{
		return MNS(left) -= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator-(MNS<SMP> &&left, const MNS<SMP> &right)noexcept
	{
		return left -= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(const MNS<SMP> &left, const MNS<SMP> &right)noexcept
	{
		return MNS(left) *= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(MNS<SMP> &&left, const MNS<SMP> &right)noexcept
	{
		return left *= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(const MNS<SMP> &left, MNS<SMP> &&right)noexcept
	{
		return right *= left;
	}

	template <class SMP>
	constexpr MNS<SMP> operator*(MNS<SMP> &&left, MNS<SMP> &&right)noexcept
	{
		return left *= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator/(const MNS<SMP> &left, const MNS<SMP> &right)noexcept
	{
		return MNS(left) /= right;
	}

	template <class SMP>
	constexpr MNS<SMP> operator/(MNS<SMP> &&left, const MNS<SMP> &right)noexcept
	{
		return left /= right;
	}
}