module;

#include <array>

export module palette.sgl.mlt;

export namespace palette
{
	template <class SMP, size_t N>
	struct MLT
	{
	private:
		std::array<SMP, N> smps;

	public:
		constexpr MLT()noexcept
		{

		}
		constexpr explicit MLT(const SMP &smp)noexcept
		{
			std::fill(smps.begin(), smps.end(), smp);
		}
		constexpr explicit MLT(const std::array<SMP, N> &smps)noexcept :
			smps(smps)
		{

		}
		template <class ConvertedSMP>
		constexpr explicit operator MLT<ConvertedSMP, N>()const noexcept
		{
			MLT<ConvertedSMP, N> ret;
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				ret[i] = static_cast<ConvertedSMP>(smps[i]);
			}
			return ret;
		}
		constexpr SMP &operator[](size_t n)noexcept
		{
			return smps[n];
		}
		constexpr const SMP &operator[](size_t n)const noexcept
		{
			return smps[n];
		}
		constexpr auto begin()noexcept
		{
			return smps.begin();
		}
		constexpr auto begin()const noexcept
		{
			return smps.begin();
		}
		constexpr auto end()noexcept
		{
			return smps.end();
		}
		constexpr auto end()const noexcept
		{
			return smps.end();
		}
		constexpr MLT &operator+=(const MLT &mlt)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] += mlt.smps[i];
			}
			return *this;
		}
		constexpr MLT &operator-=(const MLT &mlt)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] -= mlt.smps[i];
			}
			return *this;
		}
		constexpr MLT &operator*=(const MLT &mlt)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] *= mlt.smps[i];
			}
			return *this;
		}
		constexpr MLT &operator/=(const MLT &mlt)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] /= mlt.smps[i];
			}
			return *this;
		}
		template <class T>
		constexpr MLT &operator+=(const T &t)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] += t;
			}
			return *this;
		}
		template <class T>
		constexpr MLT &operator-=(const T &t)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] -= t;
			}
			return *this;
		}
		template <class T>
		constexpr MLT &operator*=(const T &t)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] *= t;
			}
			return *this;
		}
		template <class T>
		constexpr MLT &operator/=(const T &t)noexcept
		{
#pragma omp for
			for(size_t i = 0; i < N; ++i)
			{
				smps[i] /= t;
			}
			return *this;
		}
		constexpr MLT operator-()const noexcept
		{
			return MLT(*this) *= -1.0;
		}
		constexpr SMP makeMNL()const noexcept
		{
			SMP ret = smps[0];
#pragma omp for
			for(size_t i = 1; i < N; ++i)
			{
				ret += smps[i];
			}
			return ret / N;
		}
		//’Ç‰ÁFs—ñ‚ÅæŽZ
	};

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator+(const MLT<SMP, N> &left, const MLT<SMP, N> &right)noexcept
	{
		return MLT(left) += right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator+(MLT<SMP, N> &&left, const MLT<SMP, N> &right)noexcept
	{
		return left += right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator+(const MLT<SMP, N> &left, MLT<SMP, N> &&right)noexcept
	{
		return right += left;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator+(MLT<SMP, N> &&left, MLT<SMP, N> &&right)noexcept
	{
		return left += right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator-(const MLT<SMP, N> &left, const MLT<SMP, N> &right)noexcept
	{
		return MLT(left) -= right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator-(MLT<SMP, N> &&left, const MLT<SMP, N> &right)noexcept
	{
		return left -= right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator*(const MLT<SMP, N> &left, const MLT<SMP, N> &right)noexcept
	{
		return MLT(left) *= right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator*(MLT<SMP, N> &&left, const MLT<SMP, N> &right)noexcept
	{
		return left *= right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator*(const MLT<SMP, N> &left, MLT<SMP, N> &&right)noexcept
	{
		return right *= left;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator*(MLT<SMP, N> &&left, MLT<SMP, N> &&right)noexcept
	{
		return left *= right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator/(const MLT<SMP, N> &left, const MLT<SMP, N> &right)noexcept
	{
		return MLT(left) /= right;
	}

	template <class SMP, size_t N>
	constexpr MLT<SMP, N> operator/(MLT<SMP, N> &&left, const MLT<SMP, N> &right)noexcept
	{
		return left /= right;
	}
}