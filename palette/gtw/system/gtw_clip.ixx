module;

#include <utility>

export module palette.gtw.clip;

export import palette.ztm;

export namespace palette
{
	class Clip
	{
		ZTM startTime;
		ZTM endTime;

	public:
		constexpr Clip()noexcept
		{

		}
		constexpr Clip(ZTM startTime, ZTM endTime)noexcept :
			startTime(startTime), endTime(endTime)
		{

		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM& at(ZTM t, GTW1& gtw1, GTWs&...gtws)
		{
			if(startTime <= t && t < endTime)
			{
				return gtw1.at<FRM>(t, gtws...);
			}
			static FRM dummy(0.0);
			dummy = FRM(0.0);
			return dummy;
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			if(startTime <= t && t < endTime)
			{
				return gtw1.at<FRM>(t, gtws...);
			}
			return FRM(0.0);
		}
		constexpr void setStartTime(ZTM startTime)noexcept
		{
			this->startTime = startTime;
		}
		constexpr ZTM getStartTime()const noexcept
		{
			return startTime;
		}
		constexpr void setEndTime(ZTM endTime)noexcept
		{
			this->endTime = endTime;
		}
		constexpr ZTM getEndTime()const noexcept
		{
			return endTime;
		}
	};
}