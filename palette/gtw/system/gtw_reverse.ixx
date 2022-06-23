export module palette.gtw.reverse;

export import palette.ztm;

export namespace palette
{
	class Reverse
	{
		ZTM offset;

		constexpr ZTM reverse(ZTM t)const noexcept
		{
			return offset - t;
		}

	public:
		constexpr Reverse(ZTM axis)noexcept :
			offset(2 * axis)
		{

		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM& at(ZTM t, GTW1& gtw1, GTWs&...gtws)
		{
			return gtw1.at<FRM>(reverse(t), gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.at<FRM>(reverse(t), gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM operator()(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.operator()<FRM>(reverse(t), gtws...);
		}
		constexpr void setAxis(ZTM axis)noexcept
		{
			offset = 2 * axis;
		}
		constexpr ZTM getAxis()const noexcept
		{
			return offset / 2;
		}
	};
}