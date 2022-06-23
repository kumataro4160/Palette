export module palette.sgl.wavfx.zero_order_hold;

export import palette.sgl.wav;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processZeroOrderHold(const WAV<FRM>& wav, NTM holdTm, bool fixedLength = true)noexcept
	{
		const NTM wavLength = wav.getLength() + holdTm - 1;
		WAV<FRM> ret(wavLength);
		FRM holdSmp;
#pragma omp for
		for(ZTM t = 0; t < wavLength; ++t)
		{
			if(t % holdTm == 0)
			{
				holdSmp = wav(t);
			}
			ret[t] = holdSmp;
		}
		return ret;
	}
}