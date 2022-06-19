module;

#include <numeric>

export module palette.sgl.wavfx.dc_removal;

export import palette.sgl.wav;
import palette.value_type;

namespace palette
{
	template <class FRM>
	constexpr FRM extractMean(const WAV<FRM>& wav)
	{
		return std::reduce(wav.begin(), wav.end(), FRM(0.0)) / static_cast<value_t>(wav.getLength());
	}

	template <class FRM>
	constexpr WAV<FRM> processDCRemoval(const WAV<FRM>& wav)
	{
		const FRM mean = extractMean(wav);
		return wav - mean;
	}

	template <class FRM>
	constexpr WAV<FRM> processDCRemoval(WAV<FRM>&& wav)
	{
		const FRM mean = extractMean(wav);
		return wav -= mean;
	}
}