module;

#include <vector>

export module palette.sgl.wavfx.wav_io.riff_chunk;

export namespace palette
{
	struct FmtChunk
	{
		uint32_t chunk_ID;
		uint32_t chunk_size;
		uint16_t wave_format_type;
		uint16_t chl;
		uint32_t smps_per_sec;
		uint32_t bytes_per_sec;
		uint16_t block_size;
		uint16_t bits_per_smp;
	};

	struct DataChunk
	{
		uint32_t chunk_ID;
		uint32_t chunk_size;
		std::vector<uint8_t> sglData;
	};

	struct RIFFChunk
	{
		uint32_t chunk_ID;
		uint32_t chunk_size;
		uint32_t format_type;
		FmtChunk fmt_chunk;
		DataChunk data_chunk;
	};

	template <class SMP>
	constexpr uint16_t getWaveFormatType()
	{
		return 1;
	}

	template <>
	constexpr uint16_t getWaveFormatType<float>()
	{
		return 3;
	}

	template <>
	constexpr uint16_t getWaveFormatType<double>()
	{
		return 3;
	}
}