export module palette.gtw.loop;

export import palette.ztm;

export namespace palette
{
	class Loop
	{
		ZTM cycle;

		constexpr ZTM loop(ZTM t)const noexcept
		{
			if(t >= 0)
			{
				return t % cycle;
			}
			return (t + 1) % cycle + cycle - 1;
		}

	public:
		constexpr Loop(ZTM cycle)noexcept :
			cycle(cycle == 0 ? 1 : cycle)
		{

		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr FRM& at(ZTM t, GTW1& gtw1, GTWs&...gtws)
		{
			return gtw1.at<FRM>(loop(t), gtws...);
		}
		template <class FRM, class GTW1, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTW1& gtw1, const GTWs&...gtws)const
		{
			return gtw1.at<FRM>(loop(t), gtws...);
		}
		constexpr void setCycleTime(ZTM cycle)noexcept
		{
			this->cycle = cycle == 0 ? 1 : cycle;
		}
		constexpr ZTM getCycleTime()const noexcept
		{
			return cycle;
		}
	};
}