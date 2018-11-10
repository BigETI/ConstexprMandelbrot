#ifndef __CONSTEXPR_MANDELBROT_MANDELBROT_H__
#	define __CONSTEXPR_MANDELBROT_MANDELBROT_H__

#	include <array>
#	include <cstdint>
#	include <cmath>
#	include "Complex.h"
#	include "Color.h"

/// <summary>
/// constexpr mandelbrot namespace
/// </summary>
namespace ConstexprMandelbrot
{
	/// <summary>
	/// Real number type
	/// </summary>
	typedef long double Real;

	/// <summary>
	/// Mandelbrot class
	/// </summary>
	template <size_t Width, size_t Height, typename ColorType, size_t RedColorIndex, size_t GreenColorIndex, size_t BlueColorIndex, size_t AlphaColorIndex, size_t ColorsSize>
	class Mandelbrot
	{
	private:
		Color<ColorType, RedColorIndex, GreenColorIndex, BlueColorIndex, AlphaColorIndex> backgroundColor;
		std::array<Color<ColorType, RedColorIndex, GreenColorIndex, BlueColorIndex, AlphaColorIndex>, ColorsSize> colors;

		Mandelbrot() = delete;
		Mandelbrot(const Mandelbrot &) = delete;
		Mandelbrot(Mandelbrot &&) = delete;

		/// <summary>
		/// Get complex number from pixel
		/// </summary>
		/// <param name="x">X</param>
		/// <param name="y">Y</param>
		/// <param name="width">Width</param>
		/// <param name="height">Height</param>
		/// <returns>Complex number</returns>
		constexpr static Complex<Real> GetComplexFromPixel(Real x, Real y, size_t width, size_t height)
		{
			return Complex<Real>
			{
				((x / width) * static_cast<Real>(3.0)) - static_cast<Real>(2.0),
				((y / height) * static_cast<Real>(2.0)) - static_cast<Real>(1.0)
			};
		}

		/// <summary>
		/// Get mandelbrot point iterations
		/// </summary>
		/// <param name="x">X</param>
		/// <param name="y">Y</param>
		/// <param name="width">Width</param>
		/// <param name="height">Height</param>
		/// <param name="maxIterations">Maximal iterations</param>
		/// <returns>Number of iterations</returns>
		constexpr static size_t GetMandelbrotPointIterations(Real x, Real y, size_t width, size_t height, size_t maxIterations)
		{
			Complex<Real> c(GetComplexFromPixel(x, y, width, height));
			Complex<Real> z { 0.0, 0.0 };
			size_t i(0);
			for (; (i != maxIterations) && (z.GetMagnitudeSquared() < (1000.0 * 1000.0)); i++)
			{
				z *= z;
				z += c;
			}
			return i;
		}

	public:

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="backgroundColor">Background color</param>
		/// <param name="colors">Colors</param>
		constexpr Mandelbrot(const Color<ColorType, RedColorIndex, GreenColorIndex, BlueColorIndex, AlphaColorIndex> & backgroundColor, const std::array<Color<ColorType, RedColorIndex, GreenColorIndex, BlueColorIndex, AlphaColorIndex>, ColorsSize> & colors) : backgroundColor(backgroundColor), colors(colors)
		{
			// ...
		}

		/// <summary>
		/// Render mandelbrot
		/// </summary>
		/// <param name="result">Result</param>
		/// <param name="maxIterations">Maximal iterations</param>
		/// <param name="antiAliased">Anti aliased</param>
		template <typename ResultType>
		constexpr void Render(ResultType & result, size_t maxIterations = 128, bool antiAliased = true) const
		{
			const auto sin_phi_div_2(0.35355339059327376220042218105242);
			constexpr auto GetColor = [](size_t iterations, size_t maxIterations, const Color<ColorType, RedColorIndex, GreenColorIndex, BlueColorIndex, AlphaColorIndex> & backgroundColor, const std::array<Color<ColorType, RedColorIndex, GreenColorIndex, BlueColorIndex, AlphaColorIndex>, ColorsSize> & colors)
			{
				return ((iterations < maxIterations) ? colors[iterations % ColorsSize] : backgroundColor);
			};
			if (antiAliased)
			{
				for (int y(0), x(0); y < Height; y++)
				{
					for (x = 0; x < Width; x++)
					{
						result[x + (y * Width)] =
							(GetColor(GetMandelbrotPointIterations(static_cast<Real>(x), static_cast<Real>(y), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
							((
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x + 0.5), static_cast<Real>(y), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x - 0.5), static_cast<Real>(y), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x), static_cast<Real>(y + 0.5), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x), static_cast<Real>(y - 0.5), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x + sin_phi_div_2), static_cast<Real>(y + sin_phi_div_2), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x - sin_phi_div_2), static_cast<Real>(y + sin_phi_div_2), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x + sin_phi_div_2), static_cast<Real>(y - sin_phi_div_2), Width, Height, maxIterations), maxIterations, backgroundColor, colors) +
								GetColor(GetMandelbrotPointIterations(static_cast<Real>(x - sin_phi_div_2), static_cast<Real>(y - sin_phi_div_2), Width, Height, maxIterations), maxIterations, backgroundColor, colors)
								) * 0.125)) * 0.5;
					}
				}
			}
			else
			{
				for (int y(0), x(0); y < Height; y++)
				{
					for (x = 0; x < Width; x++)
					{
						result[x + (y * Width)] = GetColor(GetMandelbrotPointIterations(static_cast<Real>(x), static_cast<Real>(y), Width, Height, maxIterations), maxIterations, backgroundColor, colors);
					}
				}
			}
		}
	};
}

#endif