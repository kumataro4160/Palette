export module palette.sgl.wavfx.fir_comb_filter;

export import palette.sgl.wav;
export import palette.xfq;
import palette.interpolation;
import deeproot;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processFIRCombFilter(const WAV<FRM>& wav, XFQ fq, value_t alpha, bool fixedLength = true)
	{
		const XTM xtm = 1.0 / fq;
		const NTM wavLength = wav.getLength() + static_cast<NTM>(deeproot::ceil(xtm));
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = wav(t) + alpha * estimateBySincInterpolation(wav, t - xtm);
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processFIRCombFilter(const WAV<FRM>& wav, const WAV<XFQ>& fq, value_t alpha, bool fixedLength = true)
	{
		const NTM operandLength = deeproot::max(wav.getLength(), fq.getLength());
		const NTM wavLength = wav.getLength() + static_cast<NTM>(deeproot::ceil(1.9 / fq(operandLength - 1)));
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = wav(t) + alpha * estimateBySincInterpolation(wav, t - 1.0 / fq(t));
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processFIRCombFilter(const WAV<FRM>& wav, XFQ fq, const WAV<value_t>& alpha, bool fixedLength = true)
	{
		const XTM xtm = 1.0 / fq;
		const NTM wavLength = wav.getLength() + static_cast<NTM>(deeproot::ceil(xtm));
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = wav(t) + alpha(t) * estimateBySincInterpolation(wav, t - xtm);
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processFIRCombFilter(const WAV<FRM>& wav, const WAV<XFQ>& fq, const WAV<value_t>& alpha, bool fixedLength = true)
	{
		const NTM operandLength = deeproot::max(wav.getLength(), fq.getLength());
		const NTM wavLength = wav.getLength() + static_cast<NTM>(deeproot::ceil(1.9 / fq(operandLength - 1)));
		WAV<FRM> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = wav(t) + alpha(t) * estimateBySincInterpolation(wav, t - 1.0 / fq(t));
		}
		return ret;
	}
}