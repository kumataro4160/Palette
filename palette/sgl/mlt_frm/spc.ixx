module;

#include <vector>

export module palette.sgl.spc;

export import palette.ztm;

export namespace palette
{
	template <class FRM>
	class SPC
	{
		std::vector<FRM> frms;

	public:
		constexpr SPC()noexcept
		{

		}
		constexpr explicit SPC(size_t length) :
			frms(length)
		{

		}
		constexpr explicit SPC(const std::vector<FRM> &spc) :
			frms(spc)
		{

		}
		constexpr explicit SPC(std::vector<FRM> &&spc)noexcept :
			frms(std::move(spc))
		{

		}
		constexpr FRM& operator[](ZTM n)noexcept
		{
			return frms[n];
		}
		constexpr const FRM& operator[](ZTM n)const noexcept
		{
			return frms[n];
		}
		constexpr FRM& at(ZTM n)
		{
			return frms.at(n);
		}
		constexpr const FRM& at(ZTM n)const
		{
			return frms.at(n);
		}
		constexpr FRM operator()(ZTM n)const noexcept
		{
			if(0 <= n && n < getLength())
			{
				return frms[n];
			}
			return FRM(0.0);
		}
		constexpr ZTM getLength()const noexcept
		{
			return static_cast<ZTM>(frms.size());
		}
		constexpr auto begin()noexcept
		{
			return frms.begin();
		}
		constexpr auto begin()const noexcept
		{
			return frms.begin();
		}
		constexpr auto end()noexcept
		{
			return frms.end();
		}
		constexpr auto end()const noexcept
		{
			return frms.end();
		}
	};
}