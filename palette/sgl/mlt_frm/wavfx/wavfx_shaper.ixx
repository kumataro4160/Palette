export module palette.sgl.wavfx.shaper;

export import palette.sgl.wav;

namespace palette
{
	template <class FRM>
	using ShaperFunc = FRM(*)(FRM);

	template <class FRM>
	constexpr WAV<FRM> processShaper(const WAV<FRM>& wav, ShaperFunc<FRM> func)
	{
		const ZTM wavLength = wav.getLength();
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = func(wav(t));
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processShaper(WAV<FRM>&& wav, ShaperFunc<FRM> func)
	{
		const ZTM wavLength = wav.getLength();
		for(FRM& frm : wav)
		{
			frm = func(frm);
		}
		return wav;
	}
}