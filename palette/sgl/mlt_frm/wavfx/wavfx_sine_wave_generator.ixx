export module palette.sgl.wavfx.sine_wave_generator;

export import palette.sgl.wav;
export import palette.sgl.ap;
export import palette.sgl.fq;
import palette.sgl.og;
import palette.sgl.th;
import deeproot;

export namespace palette
{
	constexpr WAV<AP> generateSineWav(FQ fq, NTM wavLength)
	{
		WAV<AP> ret(wavLength);
		const OG og = 2.0 * deeproot::pi * fq;
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = deeproot::sin(og * t);
		}
		return ret;
	}

	constexpr WAV<AP> generateSineWav(const WAV<FQ>& fq)
	{
		constexpr TH twoPi = 2.0 * deeproot::pi;
		const NTM wavLength = fq.getLength();
		WAV<AP> ret(wavLength);
		TH th = 0.0;
		for(ZTM t = 0; t < wavLength; ++t)
		{
			ret[t] = deeproot::sin(th);
			th += twoPi * fq(t);
			if(th >= twoPi)
			{
				th -= twoPi;
			}
		}
		return ret;
	}
}