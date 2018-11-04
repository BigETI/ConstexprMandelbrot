#define RUNTIME_MANDELBROT

#include <memory>
#include <vector>
#include <algorithm>
#include "Mandelbrot.h"
#include "lib/stb_image_write.h"

using namespace ConstexprMandelbrot;

/// <summary>
/// Float typed color type
/// </summary>
typedef RGBAColor<float> FloatColor;

/// <summary>
/// Byte typed color type
/// </summary>
typedef RGBAColor<uint8_t> ByteColor;

/// <summary>
/// Image width
/// </summary>
static constexpr size_t width = 1500;

/// <summary>
/// Image height
/// </summary>
static constexpr size_t height = 1000;

template <typename InputType, typename ResultType>
constexpr static ResultType & ConvertImage(const InputType & input, ResultType & result)
{
	for (size_t i(0); i != input.size(); i++)
	{
		const FloatColor & color(input[i]);
		ByteColor c;
		c.SetRed(static_cast<uint8_t>(std::clamp<Real>(color.GetRed(), 0.0, 1.0) * 255.0));
		c.SetGreen(static_cast<uint8_t>(std::clamp<Real>(color.GetGreen(), 0.0, 1.0) * 255.0));
		c.SetBlue(static_cast<uint8_t>(std::clamp<Real>(color.GetBlue(), 0.0, 1.0) * 255.0));
		c.SetAlpha(static_cast<uint8_t>(std::clamp<Real>(color.GetAlpha(), 0.0, 1.0) * 255.0));
		result[i] = c;
	}
	return result;
}

/// <summary>
/// Main entry point
/// </summary>
/// <param name="argc">Argument count</param>
/// <param name="argv">Arguments</param>
/// <returns></returns>
int main(int argc, char *argv[])
{
#ifdef RUNTIME_MANDELBROT
	std::vector<FloatColor> output;
	output.resize(width * height);
	Mandelbrot<width, height, float, 0, 1, 2, 3, 30>(FloatColor::Black(1.0f),
		std::array<FloatColor, 30>
	{
		FloatColor{ 0.1f, 0.0f, 0.9f, 1.0f },
			FloatColor{ 0.2f, 0.0f, 0.8f, 1.0f },
			FloatColor{ 0.3f, 0.0f, 0.7f, 1.0f },
			FloatColor{ 0.4f, 0.0f, 0.6f, 1.0f },
			FloatColor{ 0.5f, 0.0f, 0.5f, 1.0f },
			FloatColor{ 0.6f, 0.0f, 0.4f, 1.0f },
			FloatColor{ 0.7f, 0.0f, 0.3f, 1.0f },
			FloatColor{ 0.8f, 0.0f, 0.2f, 1.0f },
			FloatColor{ 0.9f, 0.0f, 0.1f, 1.0f },
			FloatColor{ 1.0f, 0.0f, 0.0f, 1.0f },
			FloatColor{ 0.9f, 0.1f, 0.0f, 1.0f },
			FloatColor{ 0.8f, 0.2f, 0.0f, 1.0f },
			FloatColor{ 0.7f, 0.3f, 0.0f, 1.0f },
			FloatColor{ 0.6f, 0.4f, 0.0f, 1.0f },
			FloatColor{ 0.5f, 0.5f, 0.0f, 1.0f },
			FloatColor{ 0.4f, 0.6f, 0.0f, 1.0f },
			FloatColor{ 0.3f, 0.7f, 0.0f, 1.0f },
			FloatColor{ 0.2f, 0.8f, 0.0f, 1.0f },
			FloatColor{ 0.1f, 0.9f, 0.0f, 1.0f },
			FloatColor{ 0.0f, 1.0f, 0.0f, 1.0f },
			FloatColor{ 0.0f, 0.9f, 0.1f, 1.0f },
			FloatColor{ 0.0f, 0.8f, 0.2f, 1.0f },
			FloatColor{ 0.0f, 0.7f, 0.3f, 1.0f },
			FloatColor{ 0.0f, 0.6f, 0.4f, 1.0f },
			FloatColor{ 0.0f, 0.5f, 0.5f, 1.0f },
			FloatColor{ 0.0f, 0.4f, 0.6f, 1.0f },
			FloatColor{ 0.0f, 0.3f, 0.7f, 1.0f },
			FloatColor{ 0.0f, 0.2f, 0.8f, 1.0f },
			FloatColor{ 0.0f, 0.1f, 0.9f, 1.0f },
			FloatColor{ 0.0f, 0.0f, 1.0f, 1.0f }
	}).Render(output);
	std::vector<ByteColor> result;
	result.resize(width * height);
	stbi_write_png("mandelbrot.png", width, height, 4, ConvertImage(output, result).data(), width * 4);
#else
	constexpr auto mandelbrot = []
	{
		Mandelbrot<width, height, float, 0, 1, 2, 3, 30> renderer(FloatColor::Black(1.0f),
			std::array<FloatColor, 30>
			{
				FloatColor{ 0.1f, 0.0f, 0.9f, 1.0f },
				FloatColor{ 0.2f, 0.0f, 0.8f, 1.0f },
				FloatColor{ 0.3f, 0.0f, 0.7f, 1.0f },
				FloatColor{ 0.4f, 0.0f, 0.6f, 1.0f },
				FloatColor{ 0.5f, 0.0f, 0.5f, 1.0f },
				FloatColor{ 0.6f, 0.0f, 0.4f, 1.0f },
				FloatColor{ 0.7f, 0.0f, 0.3f, 1.0f },
				FloatColor{ 0.8f, 0.0f, 0.2f, 1.0f },
				FloatColor{ 0.9f, 0.0f, 0.1f, 1.0f },
				FloatColor{ 1.0f, 0.0f, 0.0f, 1.0f },
				FloatColor{ 0.9f, 0.1f, 0.0f, 1.0f },
				FloatColor{ 0.8f, 0.2f, 0.0f, 1.0f },
				FloatColor{ 0.7f, 0.3f, 0.0f, 1.0f },
				FloatColor{ 0.6f, 0.4f, 0.0f, 1.0f },
				FloatColor{ 0.5f, 0.5f, 0.0f, 1.0f },
				FloatColor{ 0.4f, 0.6f, 0.0f, 1.0f },
				FloatColor{ 0.3f, 0.7f, 0.0f, 1.0f },
				FloatColor{ 0.2f, 0.8f, 0.0f, 1.0f },
				FloatColor{ 0.1f, 0.9f, 0.0f, 1.0f },
				FloatColor{ 0.0f, 1.0f, 0.0f, 1.0f },
				FloatColor{ 0.0f, 0.9f, 0.1f, 1.0f },
				FloatColor{ 0.0f, 0.8f, 0.2f, 1.0f },
				FloatColor{ 0.0f, 0.7f, 0.3f, 1.0f },
				FloatColor{ 0.0f, 0.6f, 0.4f, 1.0f },
				FloatColor{ 0.0f, 0.5f, 0.5f, 1.0f },
				FloatColor{ 0.0f, 0.4f, 0.6f, 1.0f },
				FloatColor{ 0.0f, 0.3f, 0.7f, 1.0f },
				FloatColor{ 0.0f, 0.2f, 0.8f, 1.0f },
				FloatColor{ 0.0f, 0.1f, 0.9f, 1.0f },
				FloatColor{ 0.0f, 0.0f, 1.0f, 1.0f }
			});
		std::array<FloatColor, width * height> output;
		std::array<ByteColor, width * height> result;
		renderer.Render(output);
		ConvertImage(output, result);
		return result;
	}();
	stbi_write_png("mandelbrot.png", width, height, 4, mandelbrot.data(), width * 4);
#endif
	return 0;
}