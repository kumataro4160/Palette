export module palette.sgl.wavfx.differentiator;

export import palette.sgl.wav;

namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processDifferentiator(const WAV<FRM>& wav, bool fixedLength = true)
	{
		const ZTM wavLength = wav.getLength() + (fixedLength ? 0 : 1);
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = wav(t) - wav(t - 1);
		}
		return ret;
	}
}