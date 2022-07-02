module;

#include <vector>

export module palette.sgl.fft;

export import palette.sgl.wav;
export import palette.sgl.spc;
export import palette.value_type;
export import palette.sgl.ste;
export import deeproot.complex_rectangular;
import deeproot;

namespace palette
{
	inline std::vector<deeproot::complex_rectangular<value_t>> fftCalculate(std::vector<deeproot::complex_rectangular<value_t>> &x, std::vector<deeproot::complex_rectangular<value_t>> &y, int n)
	{
		int strideWidth = 1;

		for(int nHalf = n / 2; nHalf >= 1; nHalf /= 2)
		{
			const value_t theta0 = -deeproot::pi / nHalf;
			int i, j;
#pragma omp for private(i, j)
			for(i = 0; i < nHalf; ++i)
			{
				const value_t theta = i * theta0;
				const deeproot::complex_rectangular<value_t> w(deeproot::cos(theta), deeproot::sin(theta));
				for(j = 0; j < strideWidth; ++j)
				{
					y[strideWidth * i * 2 + j] = (x[strideWidth * i + j] + x[strideWidth * (i + nHalf) + j]) / 2.0;
					y[strideWidth * (i * 2 + 1) + j] = (x[strideWidth * i + j] - x[strideWidth * (i + nHalf) + j]) / 2.0 * w;
				}
			}
			strideWidth *= 2;
			std::swap(x, y);
		}
		return x;
	}

	inline std::vector<STE<deeproot::complex_rectangular<value_t>>> fftCalculate(std::vector<STE<deeproot::complex_rectangular<value_t>>> &x, std::vector<STE<deeproot::complex_rectangular<value_t>>> &y, int n)
	{
		int strideWidth = 1;

		for(int nHalf = n / 2; nHalf >= 1; nHalf /= 2)
		{
			const value_t theta0 = -deeproot::pi / nHalf;
			int i, j;
#pragma omp for private(i, j)
			for(i = 0; i < nHalf; ++i)
			{
				const value_t theta = i * theta0;
				const deeproot::complex_rectangular<value_t> w(deeproot::cos(theta), deeproot::sin(theta));
				for(j = 0; j < strideWidth; ++j)
				{
					y[strideWidth * i * 2 + j] = (x[strideWidth * i + j] + x[strideWidth * (i + nHalf) + j]) / 2.0;
					y[strideWidth * (i * 2 + 1) + j] = (x[strideWidth * i + j] - x[strideWidth * (i + nHalf) + j]) / 2.0;
					y[strideWidth * (i * 2 + 1) + j].l *= w;
					y[strideWidth * (i * 2 + 1) + j].r *= w;
				}
			}
			strideWidth *= 2;
			std::swap(x, y);
		}
		return x;
	}

	export SPC<deeproot::complex_rectangular<value_t>> fft(const WAV<value_t> &wav)
	{
		const ZTM length = wav.getLength();
		if(length == 0 || length == 1 || !deeproot::isPowerOf2(length))
		{
			throw L"fft : 定義されていない入力";
		}
		std::vector<deeproot::complex_rectangular<value_t>> x(wav.begin(), wav.end());
		std::vector<deeproot::complex_rectangular<value_t>> y(length);
		return SPC(fftCalculate(x, y, length));
	}

	export SPC<STE<deeproot::complex_rectangular<value_t>>> fft(const WAV<STE<value_t>> &wav)
	{
		const ZTM length = wav.getLength();
		if(length == 0 || length == 1 || !deeproot::isPowerOf2(length))
		{
			throw L"fft : 定義されていない入力";
		}
		std::vector<STE<deeproot::complex_rectangular<value_t>>> x(wav.begin(), wav.end());
		std::vector<STE<deeproot::complex_rectangular<value_t>>> y(length);
		return SPC(fftCalculate(x, y, length));
	}
}