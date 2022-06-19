module;

#include <vector>

export module palette.sgl.wavfx.wav_io.riff_chunk_serializer;

export import palette.sgl.wavfx.wav_io.binary;
export import palette.sgl.wavfx.wav_io.riff_chunk;

namespace palette
{
	Binary serializeFormatChunk(const FmtChunk &chunk)
	{
		Binary ret;
		ret.read(&chunk, sizeof(FmtChunk));
		return ret;
	}

	Binary serializeDataChunk(const DataChunk &chunk)
	{
		Binary ret;
		ret.read(&chunk.chunk_ID, sizeof(uint32_t));
		ret.read(&chunk.chunk_size, sizeof(uint32_t));
		ret.read(&chunk.sglData[0], chunk.sglData.size());
		return ret;
	}

	export Binary serializeRIFFChunk(const RIFFChunk &chunk)
	{
		Binary ret;
		ret.read(&chunk.chunk_ID, sizeof(uint32_t));
		ret.read(&chunk.chunk_size, sizeof(uint32_t));
		ret.read(&chunk.format_type, sizeof(uint32_t));
		ret.read(serializeFormatChunk(chunk.fmt_chunk));
		ret.read(serializeDataChunk(chunk.data_chunk));
		return ret;
	}
}