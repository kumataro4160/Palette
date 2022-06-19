export module palette.interpolation.linear;

export import palette.xtm;
import palette.ztm;
import deeproot;

export namespace palette
{
	template <class SGL>
	constexpr auto estimateByLinearInterpolation(const SGL& sgl, XTM t)noexcept
	{
		const ZTM l = static_cast<ZTM>(deeproot::floor(t));
		const ZTM r = l + 1;
		return sgl(l) * (r - t) + sgl(r) * (t - l);
	}
}