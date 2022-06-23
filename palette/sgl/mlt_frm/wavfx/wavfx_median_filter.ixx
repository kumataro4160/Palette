module;

#include <vector>
#include <algorithm>

export module palette.sgl.wavfx.median_filter;

export import palette.sgl.wav;
import deeproot;

export namespace palette
{
	constexpr value_t extractMedianSMP(const WAV<value_t>& wav, const deeproot::Range<ZTM>& range)
	{
		const NTM N = static_cast<NTM>(range.getSize());
		std::vector<value_t> frms(wav.begin() + range.getLower(), wav.end() + range.getUpper());
		std::sort(frms.begin(), frms.end());
		if(deeproot::isEven(N))
		{
			return (frms[N / 2 - 1] + frms[N / 2]) / 2.0;
		}
		return frms[N / 2];
	}

	constexpr WAV<value_t> processMedianFilter(const WAV<value_t>& wav, NTM N, bool fixedLength = true)
	{
		const NTM wavLength = wav.getLength() + (fixedLength ? 0 : N - 1);
		WAV<value_t> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = extractMedianSMP(wav, deeproot::Range<ZTM>(t, t + N));
		}
		return ret;
	}
}