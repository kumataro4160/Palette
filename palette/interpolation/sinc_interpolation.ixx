export module palette.interpolation.sinc;

export import palette.xtm;
import palette.ztm;
import palette.value_type;
import deeproot;
import palette.interpolation.linear;

namespace palette
{
	constexpr unsigned interpolationQuality = 10;
	constexpr value_t epsilon = 1.0e-7;

	export template <class SGL>
	constexpr auto estimateBySincInterpolation(const SGL &sgl, XTM t, int quality = interpolationQuality)noexcept
	{
		if(quality <= 1)
		{
			return estimateByLinearInterpolation(sgl, t);
		}
		const ZTM l = static_cast<ZTM>(deeproot::floor(t));
		const ZTM r = l + 1;
		if(t - l <= epsilon)
		{
			return sgl(l);
		}
		else if(r - t <= epsilon)
		{
			return sgl(r);
		}
		auto &&ret = sgl(l) * 0.0;
		const value_t a = deeproot::sin(deeproot::pi * (t - l));
		for(ZTM i = -quality; i < quality; ++i)
		{
			const ZTM n = r + i;
			const value_t piDelta = deeproot::pi * (t - n);
			ret += sgl(n) * (deeproot::hann(piDelta / quality) * deeproot::powerOfNegative1(i) * a / piDelta);
		}
		return ret;
	}

	export template <class SGL>
	constexpr auto estimateBySincInterpolationDownsampling(const SGL &sgl, XTM t, value_t smpRateRatio, int quality = interpolationQuality)noexcept
	{
		if(quality <= 1)
		{
			return estimateByLinearInterpolation(sgl, t);
		}
		if(smpRateRatio > 1.0)
		{
			return estimateBySincInterpolation(sgl, t);
		}
		if(quality < 1.0 / smpRateRatio)
		{
			quality = static_cast<unsigned>(1.0 / smpRateRatio) + 1;
		}
		const ZTM l = static_cast<ZTM>(deeproot::floor(t));
		const ZTM r = l + 1;
		auto &&ret = (t - l <= epsilon) ? sgl(l) : (r - t <= epsilon) ? sgl(r) : 0.0;
		for(ZTM i = -quality; i < quality; ++i)
		{
			const ZTM n = r + i;
			const value_t piDelta = deeproot::pi * (t - n);
			ret += sgl(n) * (deeproot::hann(piDelta / quality) * smpRateRatio * deeproot::sinc(smpRateRatio * piDelta));
		}
		return ret;
	}
}