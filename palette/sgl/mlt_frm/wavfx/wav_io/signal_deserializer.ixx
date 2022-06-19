module;

#include <vector>

export module palette.sgl.wavfx.wav_io.sgl_deserializer;

import palette.value_type;
import palette.sgl.ste;
import palette.sgl.mns;
import palette.sgl.mlt;
import palette.sgl.wav;
import palette.sgl.spc;

namespace palette
{
	value_t deserializeSMP(const std::vector<uint8_t>::const_iterator &sglData)
	{
		return *(value_t *)(&sglData[0]);
	}

	template <class FRM>
	FRM deserializeFRM(const std::vector<uint8_t>::const_iterator &sglData)
	{
		throw "deserializeFRM : éwíËÇ≥ÇÍÇΩSGLÇ…ëŒâûÇµÇƒÇ¢Ç‹ÇπÇÒÅB";
	}

	template <>
	value_t deserializeFRM(const std::vector<uint8_t>::const_iterator &sglData)
	{
		return deserializeSMP(sglData);
	}

	template <>
	STE<value_t> deserializeFRM(const std::vector<uint8_t>::const_iterator &sglData)
	{
		STE<value_t> ret;
		ret.l = deserializeSMP(sglData);
		ret.r = deserializeSMP(sglData + sizeof(value_t));
		return ret;
	}

	template <>
	MNS<value_t> deserializeFRM(const std::vector<uint8_t>::const_iterator &sglData)
	{
		MNS<value_t> ret;
		ret.m = deserializeSMP(sglData);
		ret.s = deserializeSMP(sglData + sizeof(value_t));
		return ret;
	}

	template <size_t N>
	MLT<value_t, N> deserializeFRM(const std::vector<uint8_t>::const_iterator &sglData)
	{
		MLT<value_t, N> ret;
		for(size_t i = 0; i < N; ++i)
		{
			ret[i] = deserializeSMP(sglData + i * sizeof(value_t));
		}
		return ret;
	}

	export template <class FRM>
	WAV<FRM> deserializeWAV(const std::vector<uint8_t> &sglData)
	{
		const size_t length = sglData.size() / sizeof(FRM);
		WAV<FRM> ret(length);
		for(size_t i = 0; i < length; ++i)
		{
			ret[i] = deserializeFRM<FRM>(sglData.begin() + i * sizeof(FRM));
		}
		return ret;
	}

	export template <class FRM>
	SPC<FRM> deserializeSPC(const std::vector<uint8_t> &sglData)
	{
		const size_t length = sglData.size() / sizeof(FRM);
		SPC<FRM> ret(length);
		for(size_t i = 0; i < length; ++i)
		{
			ret[i] = deserializeFRM<FRM>(sglData.begin() + i * sizeof(FRM));
		}
		return ret;
	}
}