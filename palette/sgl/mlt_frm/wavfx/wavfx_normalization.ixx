module;

#include <algorithm>

export module palette.sgl.wavfx.normalization;

export import palette.sgl.wav;
import palette.sgl.ste;
import deeproot;

namespace palette
{
	template <class SMP>
	constexpr SMP extractMaxAPFRM(const WAV<SMP>& wav)
	{
		SMP maxrap = SMP(0.0);
		for(const SMP& smp : wav)
		{
			const SMP rap = deeproot::abs(smp);
			if(maxrap < rap)
			{
				maxrap = rap;
			}
		}
		return maxrap;
	}

	template <class SMP>
	constexpr STE<SMP> extractMaxAPFRM(const WAV<STE<SMP>>& wav)
	{
		STE<SMP> rMaxAp = STE<SMP>(0.0);
		for(const STE<SMP>& ste : wav)
		{
			const STE<SMP> rAp(deeproot::abs(ste.l), deeproot::abs(ste.r));
			if(rMaxAp.l < rAp.l)
			{
				rMaxAp.l = rAp.l;
			}
			if(rMaxAp.r < rAp.r)
			{
				rMaxAp.r = rAp.r;
			}
		}
		return rMaxAp;
	}

	template <class SMP>
	constexpr SMP extractMaxAP(const SMP& smp)
	{
		return deeproot::abs(smp);
	}

	template <class SMP>
	constexpr SMP extractMaxAP(const STE<SMP>& ste)
	{
		return deeproot::max(deeproot::abs(ste.l), deeproot::abs(ste.r));
	}

	template <class FRM>
	constexpr WAV<FRM> processNormalization(const WAV<FRM>& wav, bool forEachChl = false)
	{
		const FRM rMaxAp = extractMaxAPFRM(wav);
		if(forEachChl)
		{
			return wav / rMaxAp;
		}
		return wav / FRM(extractMaxAP(rMaxAp));
	}

	template <class FRM>
	constexpr WAV<FRM> processNormalization(WAV<FRM>&& wav, bool forEachChl = false)
	{
		const FRM rMaxAp = extractMaxAPFRM(wav);
		if(forEachChl)
		{
			return wav /= rMaxAp;
		}
		return wav /= FRM(extractMaxAP(rMaxAp));
	}
}