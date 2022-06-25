export module palette.sgl.wavfx.terminator;

export import palette.sgl.wav;

export namespace palette
{
	template <class FRM>
	constexpr void terminate(WAV<FRM>&& wav)noexcept
	{
		wav.resize(0);
	}
}