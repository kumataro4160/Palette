export module palette.sgl.wavfx.moving_average_filter;

export import palette.sgl.wav;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processMovingAverageFilter(const WAV<FRM>& wav, NTM N, bool fixedLength = true)
	{
		const NTM wavLength = wav.getLength() + (fixedLength ? 0 : N - 1);
		WAV<FRM> ret(wavLength);
		FRM out;
		for(ZTM t = 0; t < wavLength; ++t)
		{
			out += wav(t) - wav(t - N);
			ret[t] = out;
		}
		return ret;
	}
}