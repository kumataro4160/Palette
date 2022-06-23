export module palette.sgl.wavfx.fir_comb_filter;

export import palette.sgl.wav;
export import palette.sgl.fq;
import palette.interpolation;
import deeproot;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processFIRCombFilter(const WAV<FRM>& wav, FQ fq, value_t alpha, bool fixedLength = true)noexcept
	{
		const XTM xtm = 1.0 / fq;
		const NTM wavLength = wav.getLength() + static_cast<NTM>(deeproot::ceil(xtm));
		WAV<FRM> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = wav(t) + alpha * estimateBySincInterpolation(wav, t - xtm);
		}
		return ret;
	}
}