export module palette.sgl.wavfx.slew_shaper;

export import palette.sgl.wav;

namespace palette
{
	template <class FRM>
	using SlewShaperFunc = FRM(*)(FRM);

	template <class FRM>
	constexpr WAV<FRM> processSlewShaper(const WAV<FRM>& wav, SlewShaperFunc<FRM> func)
	{
		const ZTM wavLength = wav.getLength();
		WAV<FRM> ret(wavLength);
		FRM prevOut = FRM(0.0);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = prevOut + func(wav(t) - prevOut);
			prevOut = ret[t];
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processSlewShaper(WAV<FRM>&& wav, SlewShaperFunc<FRM> func)
	{
		const ZTM wavLength = wav.getLength();
		FRM prevOut = FRM(0.0);
		for(FRM& frm : wav)
		{
			frm = prevOut + func(frm - prevOut);
			prevOut = frm;
		}
		return wav;
	}
}