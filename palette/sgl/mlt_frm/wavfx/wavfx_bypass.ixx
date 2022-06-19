export module palette.sgl.wavfx.bypass;

export import palette.sgl.wav;

export namespace palette
{
	template <class FRM>
	constexpr WAV<FRM> bypass(const WAV<FRM>& wav)noexcept
	{
		return wav;
	}
}