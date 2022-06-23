export module palette.gtw.bypass;

export import palette.ztm;

export namespace palette
{
	class Bypass
	{
	public:
		constexpr Bypass()noexcept
		{

		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM& at(ZTM t, GTW1& gtw1, GTWs&...gtws)
		{
			return gtw1.at<FRM>(t, gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.at<FRM>(t, gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM operator()(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.operator()<FRM>(t, gtws...);
		}
	};
}