module;

#include <vector>

export module palette.sgl.wavfx.wav_io.riff_chunk_assembler;

export import palette.sgl.wavfx.wav_io.riff_chunk;

namespace palette
{
	constexpr int numBitsPerByte = 8;

	template <class SMP>
	constexpr FmtChunk assembleFormatChunk(uint16_t numCHLs, uint32_t smpRate)
	{
		FmtChunk ret;
		ret.chunk_ID = ' tmf';
		ret.chunk_size = 16;
		ret.wave_format_type = getWaveFormatType<SMP>();
		ret.chl = numCHLs;
		ret.smps_per_sec = smpRate;
		ret.bits_per_smp = sizeof(SMP) * numBitsPerByte;
		ret.block_size = ret.bits_per_smp * numCHLs / numBitsPerByte;
		ret.bytes_per_sec = ret.block_size * smpRate;
		return ret;
	}

	DataChunk assembleDataChunk(uint16_t numCHLs, uint32_t numSMPs, size_t smpSize, const std::vector<uint8_t> &sglData)
	{
		DataChunk ret;
		ret.chunk_ID = 'atad';
		ret.chunk_size = static_cast<uint32_t>(numCHLs * numSMPs * smpSize);
		ret.sglData = sglData;
		return ret;
	}

	DataChunk assembleDataChunk(uint16_t numCHLs, uint32_t numSMPs, size_t smpSize, std::vector<uint8_t> &&sglData)
	{
		DataChunk ret;
		ret.chunk_ID = 'atad';
		ret.chunk_size = static_cast<uint32_t>(numCHLs * numSMPs * smpSize);
		ret.sglData = std::move(sglData);
		return ret;
	}

	export template <class SMP>
	RIFFChunk assembleRIFFChunk(uint16_t numCHLs, uint32_t smpRate, uint32_t numSMPs, const std::vector<uint8_t> &data)
	{
		RIFFChunk ret;
		ret.chunk_ID = 'FFIR';
		ret.chunk_size = 36 + numCHLs * numSMPs * sizeof(SMP);
		ret.format_type = 'EVAW';
		ret.fmt_chunk = assembleFormatChunk<SMP>(numCHLs, smpRate);
		ret.data_chunk = assembleDataChunk(numCHLs, numSMPs, sizeof(SMP), data);
		return ret;
	}

	export template <class SMP>
	RIFFChunk assembleRIFFChunk(uint16_t numCHLs, uint32_t smpRate, uint32_t numSMPs, const std::vector<uint8_t> &&data)
	{
		RIFFChunk ret;
		ret.chunk_ID = 'FFIR';
		ret.chunk_size = 36 + numCHLs * numSMPs * sizeof(SMP);
		ret.format_type = 'EVAW';
		ret.fmt_chunk = assembleFormatChunk<SMP>(numCHLs, smpRate);
		ret.data_chunk = assembleDataChunk(numCHLs, numSMPs, sizeof(SMP), std::move(data));
		return ret;
	}
}