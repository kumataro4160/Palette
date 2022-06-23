export module palette.gtw.shift;

export import palette.ztm;

export namespace palette
{
	class Shift
	{
		ZTM offset;

		constexpr ZTM shift(ZTM t)const noexcept
		{
			return t - offset;
		}

	public:
		constexpr Shift(ZTM offset)noexcept :
			offset(offset)
		{

		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM& at(ZTM t, GTW1& gtw1, GTWs&...gtws)
		{
			return gtw1.at<FRM>(shift(t), gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.at<FRM>(shift(t), gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM operator()(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.operator()<FRM>(shift(t), gtws...);
		}
		constexpr Shift& operator>>=(ZTM t)noexcept
		{
			offset += t;
			return *this;
		}
		constexpr Shift& operator<<=(ZTM t)noexcept
		{
			(*this) >>= (-t);
			return *this;
		}
		constexpr void setOffsetTime(ZTM t)noexcept
		{
			offset = t;
		}
		constexpr ZTM getOffsetTime()const noexcept
		{
			return offset;
		}
	};
}