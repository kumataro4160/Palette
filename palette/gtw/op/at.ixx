export module palette.gtw.at;

export import palette.ztm;

export namespace palette
{
	template <class FRM, class GTW1, class...GTWs>
	constexpr FRM& at(ZTM t, GTW1& gtw1, GTWs&...gtws)
	{
		return gtw1.at<FRM>(t, gtws...);
	}

	template <class FRM, class GTW1, class...GTWs>
	constexpr const FRM& at(ZTM t, const GTW1& gtw1, const GTWs&...gtws)
	{
		return gtw1.at<FRM>(t, gtws...);
	}
}