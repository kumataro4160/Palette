module;

#include <string>

export module palette.sgl.wavfx.wav_exporter;

export import palette.sgl.wav;
import palette.sgl.wavfx.wav_io.sgl_serializer;
import palette.sgl.wavfx.wav_io.riff_chunk_assembler;
import palette.sgl.wavfx.wav_io.riff_chunk_serializer;
import palette.sgl.wavfx.wav_io.binary;
import palette.value_type;
import palette.sgl.mlt_chl;

namespace palette
{
	template <class FRM>
	uint16_t getNumSMPs()
	{
		throw "exportWAVAsWavFloat64 : FRMÇÃéwíËÇ™ñ≥å¯Ç≈Ç∑ÅB";
	}

	template <>
	constexpr uint16_t getNumSMPs<value_t>()
	{
		return 1;
	}

	template <>
	constexpr uint16_t getNumSMPs<STE<value_t>>()
	{
		return 2;
	}

	template <>
	constexpr uint16_t getNumSMPs<MNS<value_t>>()
	{
		return 2;
	}

	export template <class FRM>
	void exportWavFloat64(const WAV<FRM> &wav, uint32_t smpRate, std::string fileName)
	{
		std::vector<uint8_t> sglData = serializeWAV(wav);
		const RIFFChunk &riffChunk = assembleRIFFChunk<value_t>(getNumSMPs<FRM>(), smpRate, static_cast<uint32_t>(wav.getLength()), std::move(sglData));
		const Binary &binary = serializeRIFFChunk(riffChunk);
		binary.write(fileName);
	}

	export template <size_t N>
	void exportWavFloat64(const WAV<MLT<value_t, N>> &wav, uint32_t smpRate, std::string fileName)
	{
		std::vector<uint8_t> sglData = serializeWAV(wav);
		const RIFFChunk &riffChunk = assembleRIFFChunk<value_t>(N, smpRate, wav.getLength(), std::move(sglData));
		const Binary &binary = serializeRIFFChunk(riffChunk);
		binary.write(fileName);
	}
}