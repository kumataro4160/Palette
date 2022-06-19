module;

#include <vector>

export module palette.sgl.wavfx.wav_io.sgl_serializer;

import palette.value_type;
import palette.sgl.ste;
import palette.sgl.mns;
import palette.sgl.mlt;
import palette.sgl.wav;
import palette.sgl.spc;

namespace palette
{
	template <class SGL>
	void serializeFRM(const SGL &sgl, const std::vector<uint8_t>::iterator &sglData)
	{
		throw "serializeFRM : éwíËÇ≥ÇÍÇΩSGLÇ…ëŒâûÇµÇƒÇ¢Ç‹ÇπÇÒÅB";
	}

	template <>
	void serializeFRM(const value_t &smp, const std::vector<uint8_t>::iterator &sglData)
	{
		const size_t size = sizeof(value_t);
		union
		{
			value_t floatType;
			uint8_t binaryType[size];
		};
		floatType = smp;
		for(size_t i = 0; i < size; ++i)
		{
			sglData[i] = binaryType[i];
		}
	}

	template <>
	void serializeFRM(const STE<value_t> &steFRM, const std::vector<uint8_t>::iterator &sglData)
	{
		serializeFRM(steFRM.l, sglData);
		serializeFRM(steFRM.r, sglData + sizeof(value_t));
	}

	template <>
	void serializeFRM(const MNS<value_t> &msFRM, const std::vector<uint8_t>::iterator &sglData)
	{
		serializeFRM(msFRM.m, sglData);
		serializeFRM(msFRM.s, sglData + sizeof(value_t));
	}

	template <size_t N>
	void serializeFRM(const MLT<value_t, N> &mltFRM, const std::vector<uint8_t>::iterator &sglData)
	{
		for(size_t i = 0; i < N; ++i)
		{
			serializeFRM(mltFRM[i], sglData + i * sizeof(value_t));
		}
	}

	export template <class FRM>
	std::vector<uint8_t> serializeWAV(const WAV<FRM> &wav)
	{
		const size_t length = wav.getLength();
		std::vector<uint8_t> ret(length * sizeof(FRM));
		for(size_t i = 0; i < length; ++i)
		{
			serializeFRM(wav[i], ret.begin() + i * sizeof(FRM));
		}
		return ret;
	}

	export template <class FRM>
	std::vector<uint8_t> serializeSPC(const SPC<FRM> &spc)
	{
		const size_t length = spc.getLength();
		std::vector<uint8_t> ret(length * sizeof(FRM));
		for(size_t i = 0; i < length; ++i)
		{
			serializeFRM(spc[i], ret.begin() + i * sizeof(FRM));
		}
		return ret;
	}
}