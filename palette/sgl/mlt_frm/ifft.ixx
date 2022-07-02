module;

#include <vector>

export module palette.sgl.ifft;

export import palette.sgl.wav;
export import palette.sgl.spc;
export import palette.value_type;
export import palette.sgl.ste;
export import deeproot.complex_rectangular;
import deeproot;

namespace palette
{
	inline std::vector<deeproot::complex_rectangular<value_t>> ifftCalculate(std::vector<deeproot::complex_rectangular<value_t>>& x, std::vector<deeproot::complex_rectangular<value_t>>& y, int n)
	{
		int strideWidth = 1;

		for(int nHalf = n / 2; nHalf >= 1; nHalf /= 2)
		{
			const value_t theta0 = deeproot::pi / nHalf;
			int i, j;
#pragma omp for private(i, j)
			for(i = 0; i < nHalf; ++i)
			{
				const value_t theta = i * theta0;
				const deeproot::complex_rectangular<value_t> w(deeproot::cos(theta), deeproot::sin(theta));
				for(j = 0; j < strideWidth; ++j)
				{
					y[strideWidth * i * 2 + j] = x[strideWidth * i + j] + x[strideWidth * (i + nHalf) + j];
					y[strideWidth * (i * 2 + 1) + j] = (x[strideWidth * i + j] - x[strideWidth * (i + nHalf) + j]) * w;
				}
			}
			strideWidth *= 2;
			std::swap(x, y);
		}
		return x;
	}

	inline std::vector<STE<deeproot::complex_rectangular<value_t>>> ifftCalculate(std::vector<STE<deeproot::complex_rectangular<value_t>>>& x, std::vector<STE<deeproot::complex_rectangular<value_t>>>& y, int n)
	{
		int strideWidth = 1;

		for(int nHalf = n / 2; nHalf >= 1; nHalf /= 2)
		{
			const value_t theta0 = deeproot::pi / nHalf;
			int i, j;
#pragma omp for private(i, j)
			for(i = 0; i < nHalf; ++i)
			{
				const value_t theta = i * theta0;
				const deeproot::complex_rectangular<value_t> w(deeproot::cos(theta), deeproot::sin(theta));
				for(j = 0; j < strideWidth; ++j)
				{
					y[strideWidth * i * 2 + j] = x[strideWidth * i + j] + x[strideWidth * (i + nHalf) + j];
					y[strideWidth * (i * 2 + 1) + j] = (x[strideWidth * i + j] - x[strideWidth * (i + nHalf) + j]);
					y[strideWidth * (i * 2 + 1) + j].l *= w;
					y[strideWidth * (i * 2 + 1) + j].r *= w;
				}
			}
			strideWidth *= 2;
			std::swap(x, y);
		}
		return x;
	}

	export WAV<deeproot::complex_rectangular<value_t>> ifft(const SPC<deeproot::complex_rectangular<value_t>>& spectrum)
	{
		const ZTM length = spectrum.getLength();
		if(length == 0 || length == 1 || !deeproot::isPowerOf2(length))
		{
			throw L"ifft : ’è‹`‚³‚ê‚Ä‚¢‚È‚¢“ü—Í";
		}
		std::vector<deeproot::complex_rectangular<value_t>> x(spectrum.begin(), spectrum.end());
		std::vector<deeproot::complex_rectangular<value_t>> y(length);
		return WAV(ifftCalculate(x, y, length));
	}

	export WAV<STE<deeproot::complex_rectangular<value_t>>> ifft(const SPC<STE<deeproot::complex_rectangular<value_t>>>& spectrum)
	{
		const ZTM length = spectrum.getLength();
		if(length == 0 || length == 1 || !deeproot::isPowerOf2(length))
		{
			throw L"ifft : ’è‹`‚³‚ê‚Ä‚¢‚È‚¢“ü—Í";
		}
		std::vector<STE<deeproot::complex_rectangular<value_t>>> x(spectrum.begin(), spectrum.end());
		std::vector<STE<deeproot::complex_rectangular<value_t>>> y(length);
		return WAV(ifftCalculate(x, y, length));
	}
}