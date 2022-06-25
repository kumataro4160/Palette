export module palette.sgl.wavfx.zero_order_hold;

export import palette.sgl.wav;
import deeproot;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> processZeroOrderHold(const WAV<FRM>& wav, NTM holdTm, bool fixedLength = true)noexcept
	{
		const NTM wavLength = wav.getLength() + (fixedLength ? 0 : (holdTm - 1));
		WAV<FRM> ret(wavLength);
		NTM holdCount = 0;
		FRM holdSmp = wav(0);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = holdSmp;
			++holdCount;
			if(holdCount >= holdTm)
			{
				holdSmp = wav(t);
				holdCount = 0;
			}
		}
		return ret;
	}

	template <class FRM>
	constexpr WAV<FRM> processZeroOrderHold(const WAV<FRM>& wav, const WAV<NTM>& holdTm, bool fixedLength = true)noexcept
	{
		const NTM operandLength = deeproot::max(wav.getLength(), holdTm.getLength());
		const NTM wavLength = wav.getLength() + fixedLength ? 0 : (holdTm(operandLength - 1) - 1);
		WAV<FRM> ret(wavLength);
		NTM holdCount = 0;
		FRM holdSmp = wav(0);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = holdSmp;
			++holdCount;
			if(holdCount >= holdTm(t))
			{
				holdSmp = wav(t);
				holdCount = 0;
			}
		}
		return ret;
	}
}