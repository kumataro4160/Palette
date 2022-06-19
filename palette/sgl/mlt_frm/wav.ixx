module;

#include <vector>

export module palette.sgl.wav;

export import palette.ztm;

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
		constexpr explicit WAV(const std::vector<FRM> &wav) :
			frms(wav)
		{

		}
		constexpr explicit WAV(std::vector<FRM> &&wav)noexcept :
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
		constexpr WAV& operator+=(const FRM& f)noexcept
		{
			for(FRM& frm : frms)
			{
				frm += f;
			}
			return *this;
		}
		constexpr WAV& operator-=(const FRM& f)noexcept
		{
			for(FRM& frm : frms)
			{
				frm -= f;
			}
			return *this;
		}
		constexpr WAV& operator*=(const FRM& f)noexcept
		{
			for(FRM& frm : frms)
			{
				frm *= f;
			}
			return *this;
		}
		constexpr WAV& operator/=(const FRM& f)noexcept
		{
			return (*this) *= (FRM(1.0) /= f);
		}
		constexpr WAV operator-()const
		{
			return WAV<FRM>(*this) *= -1.0;
		}
		constexpr ZTM getLength()const noexcept
		{
			return static_cast<ZTM>(frms.size());
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
	constexpr WAV<FRM> operator*(const WAV<FRM>& left, const FRM& right)
	{
		return WAV<FRM>(left) *= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(WAV<FRM>&& left, const FRM& right)
	{
		return left *= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(const FRM& left, const WAV<FRM>& right)
	{
		return WAV<FRM>(right) *= left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator*(const FRM& left, WAV<FRM>&& right)
	{
		return right *= left;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(const WAV<FRM>& left, const FRM& right)
	{
		return WAV<FRM>(left) /= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(WAV<FRM>&& left, const FRM& right)
	{
		return left /= right;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(const FRM& left, const WAV<FRM>& right)
	{
		const ZTM wavLength = right.getLength();
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = left / right[t];
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> operator/(const FRM& left, WAV<FRM>&& right)
	{
		for(FRM& rightFrm : right)
		{
			rightFrm = left / rightFrm;
		}
		return right;
	}
}