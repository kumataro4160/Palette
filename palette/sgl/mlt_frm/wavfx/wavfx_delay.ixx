export module palette.sgl.wavfx.delay;

export import palette.sgl.wav;
import palette.interpolation;
import deeproot;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processDelay(const WAV<FRM>& wav, XTM tm, bool fixedLength = true)noexcept
	{
		const NTM wavLength = wav.getLength() + static_cast<NTM>(deeproot::ceil(tm));
		WAV<FRM> ret(wavLength);
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = estimateBySincInterpolation(wav, t - tm);
		}
		return ret;
	}
}