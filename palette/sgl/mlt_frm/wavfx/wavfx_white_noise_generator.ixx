export module palette.sgl.wavfx.white_noise_generator;

export import palette.sgl.wav;
export import palette.sgl.ap;
import deeproot;

export namespace palette
{
	constexpr WAV<AP> generateWhiteNoise(NTM wavLength)
	{
		WAV<AP> ret(wavLength);
		deeproot::Xorshift64 xorshift64;
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = deeproot::distributeNormal(xorshift64);
		}
		return ret;
	}
}