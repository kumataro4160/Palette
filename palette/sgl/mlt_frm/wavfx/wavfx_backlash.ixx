export module palette.sgl.wavfx.backlash;

export import palette.sgl.wav;
export import palette.sgl.ap;
import deeproot;

export namespace palette
{
	constexpr WAV<value_t> processBacklash(const WAV<value_t>& wav, AP deadBand)noexcept
	{
		const NTM wavLength = wav.getLength();
		WAV<value_t> ret(wavLength);
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = deeproot::min(deeproot::max(wav(t) - deadBand, ret(t - 1)), wav(t) + deadBand);
		}
		return ret;
	}
}