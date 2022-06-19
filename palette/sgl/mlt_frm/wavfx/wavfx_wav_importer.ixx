module;

#include <tuple>
#include <vector>
#include <string>

export module palette.sgl.wavfx.wav_importer;

export import palette.sgl.wav;
import palette.sgl.wavfx.wav_io.binary;
import palette.sgl.wavfx.wav_io.riff_chunk_deserializer;
import palette.sgl.wavfx.wav_io.riff_chunk_disassembler;
import palette.sgl.wavfx.wav_io.sgl_deserializer;

export namespace palette
{
	template <class FRM>
	std::tuple<WAV<FRM>, uint32_t> importWavFloat64(std::string fileName)
	{
		Binary binary(fileName);
		const RIFFChunk &riffChunk = deserializeRIFFChunk(binary);
		auto [numCHLs, smpRate, numSMPs, sglData] = disassembleRIFFChunk(riffChunk);
		const WAV<FRM> &wav = deserializeWAV<FRM>(sglData);
		return {wav, smpRate};
	}
}