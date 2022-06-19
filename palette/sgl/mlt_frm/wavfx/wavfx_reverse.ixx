module;

#include <numeric>

export module palette.sgl.wavfx.reverse;

export import palette.sgl.wav;

namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processReverse(const WAV<FRM>& wav)
	{
		WAV<FRM> ret(wav);
		std::reverse(ret.begin(), ret.end());
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processReverse(WAV<FRM>&& wav)
	{
		std::reverse(wav.begin(), wav.end());
		return wav;
	}
}