module;

#include <tuple>
#include <vector>

export module palette.sgl.wavfx.wav_io.riff_chunk_disassembler;

export import palette.sgl.wavfx.wav_io.riff_chunk;

export namespace palette
{
	constexpr int numBitsPerByte = 8;

	std::tuple<uint16_t, uint32_t, uint32_t, std::vector<uint8_t>> disassembleRIFFChunk(const RIFFChunk &riffChunk)
	{
		const uint16_t numCHLs = riffChunk.fmt_chunk.chl;
		const uint32_t smpRate = riffChunk.fmt_chunk.smps_per_sec;
		const uint16_t smpSize = riffChunk.fmt_chunk.bits_per_smp / numBitsPerByte;
		const uint32_t numSMPs = riffChunk.data_chunk.chunk_size / (numCHLs * smpSize);
		const std::vector<uint8_t> sglData = riffChunk.data_chunk.sglData;
		return {numCHLs, smpRate, numSMPs, sglData};
	}
}