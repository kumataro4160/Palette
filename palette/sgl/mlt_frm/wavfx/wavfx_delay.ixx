export module palette.sgl.wavfx.delay;

export import palette.sgl.wav;
import palette.interpolation;
import deeproot;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processDelay(const WAV<FRM>& wav, XTM tm, bool fixedLength = true)
	{
		const NTM wavLength = wav.getLength() + fixedLength ? 0 : static_cast<NTM>(deeproot::ceil(tm));
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = estimateBySincInterpolation(wav, t - tm);
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processDelay(const WAV<FRM>& wav, const WAV<XTM> &tm, bool fixedLength = true)
	{
		const NTM operandLength = deeproot::max(wav.getLength(), tm.getLength());
		const NTM wavLength = wav.getLength() + fixedLength ? 0 : static_cast<NTM>(deeproot::ceil(tm(operandLength - 1)));
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = estimateBySincInterpolation(wav, t - tm(t));
		}
		return ret;
	}
}