export module palette.gtw.cascaded;

export import palette.ztm;

export namespace palette
{
	template <class GTW1, class...GTW2>
	class CascadedGTW
	{
		GTW1 gtw1;
		CascadedGTW<GTW2...> gtw2;

	public:
		constexpr CascadedGTW(GTW1 gtw1, GTW2...gtw2)noexcept :
			gtw1(gtw1), gtw2(gtw2...)
		{

		}
		template <class FRM, class...GTWs>
		constexpr FRM& at(ZTM t, GTWs&...gtws)
		{
			return gtw1.at<FRM>(t, gtw2, gtws...);
		}
		template <class FRM, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTWs&...gtws)const
		{
			return gtw1.at<FRM>(t, gtw2, gtws...);
		}
	};

	template <class GTW1>
	class CascadedGTW<GTW1>
	{
		GTW1 gtw1;

	public:
		constexpr CascadedGTW(GTW1 gtw1)noexcept :
			gtw1(gtw1)
		{

		}
		template <class FRM, class...GTWs>
		constexpr FRM& at(ZTM t, GTWs&...gtws)
		{
			return gtw1.at<FRM>(t, gtws...);
		}
		template <class FRM, class...GTWs>
		constexpr const FRM& at(ZTM t, const GTWs&...gtws)const
		{
			return gtw1.at<FRM>(t, gtws...);
		}
	};
}