#ifndef __COLOR_H__
#	define __COLOR_H__

#include <array>

/// <summary>
/// Color structure
/// </summary>
template <typename T, size_t RedIndex, size_t GreenIndex, size_t BlueIndex, size_t AlphaIndex>
struct Color : std::array<T, 4>
{
	/// <summary>
	/// Transparent color
	/// </summary>
	/// <returns>Transparent color</returns>
	constexpr static const Color<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex> Transparent()
	{
		return Color<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex> { 0, 0, 0, 0 };
	}

	/// <summary>
	/// Black color
	/// </summary>
	/// <param name="maxValue">Maximal value</param>
	/// <returns>Black color</returns>
	constexpr static const Color<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex> Black(T maxValue)
	{
		Color<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex> ret{};
		ret.SetRed(static_cast<T>(0));
		ret.SetGreen(static_cast<T>(0));
		ret.SetBlue(static_cast<T>(0));
		ret.SetAlpha(maxValue);
		return ret;
	}

	/// <summary>
	/// Get red part
	/// </summary>
	constexpr T GetRed() const { return (*this)[RedIndex]; };

	/// <summary>
	/// Get green part
	/// </summary>
	constexpr T GetGreen() const { return (*this)[GreenIndex]; };

	/// <summary>
	/// Get blue part
	/// </summary>
	constexpr T GetBlue() const { return (*this)[BlueIndex]; };

	/// <summary>
	/// Get alpha part
	/// </summary>
	constexpr T GetAlpha() const { return (*this)[AlphaIndex]; };

	/// <summary>
	/// Set red part
	/// </summary>
	constexpr void SetRed(T val) { (*this)[RedIndex] = val; };

	/// <summary>
	/// Set green part
	/// </summary>
	constexpr void SetGreen(T val) { (*this)[GreenIndex] = val; };

	/// <summary>
	/// Set blue part
	/// </summary>
	constexpr void SetBlue(T val) { (*this)[BlueIndex] = val; };

	/// <summary>
	/// Set alpha part
	/// </summary>
	constexpr void SetAlpha(T val) { (*this)[AlphaIndex] = val; };

	/// <summary>
	/// Convert color inidices order
	/// </summary>
	template <size_t ConvertRedIndex, size_t ConvertGreenIndex, size_t ConvertBlueIndex, size_t ConvertAlphaIndex>
	constexpr Color<T, ConvertRedIndex, ConvertGreenIndex, ConvertBlueIndex, ConvertAlphaIndex> Convert()
	{
		Color<T, ConvertRedIndex, ConvertGreenIndex, ConvertBlueIndex, ConvertAlphaIndex> ret{};
		ret.SetRed(GetRed());
		ret.SetGreen(GetGreen());
		ret.SetBlue(GetBlue());
		ret.SetAlpha(GetAlpha());
		return ret;
	}

	/// <summary>
	/// Add color
	/// </summary>
	/// <param name="color">Color</param>
	/// <returns>Itself</returns>
	template <typename AnotherColorType, size_t AnotherRedIndex, size_t AnotherGreenIndex, size_t AnotherBlueIndex, size_t AnotherAlphaIndex>
	constexpr auto & operator += (const Color<AnotherColorType, AnotherRedIndex, AnotherGreenIndex, AnotherBlueIndex, AnotherAlphaIndex> & color)
	{
		SetRed(GetRed() + color.GetRed());
		SetGreen(GetGreen() + color.GetGreen());
		SetBlue(GetBlue() + color.GetBlue());
		SetAlpha(GetAlpha() + color.GetAlpha());
		return (*this);
	}

	/// <summary>
	/// Multiply color
	/// </summary>
	/// <param name="color">Color</param>
	/// <returns>Itself</returns>
	template <typename ValueType>
	constexpr auto & operator *= (const ValueType val)
	{
		SetRed(static_cast<T>(GetRed() * val));
		SetGreen(static_cast<T>(GetGreen() * val));
		SetBlue(static_cast<T>(GetBlue() * val));
		SetAlpha(static_cast<T>(GetAlpha() * val));
		return (*this);
	}

	/// <summary>
	/// Add color
	/// </summary>
	/// <param name="color">Color</param>
	/// <returns>Added color</returns>
	template <typename AnotherColorType, size_t AnotherRedIndex, size_t AnotherGreenIndex, size_t AnotherBlueIndex, size_t AnotherAlphaIndex>
	constexpr auto operator + (const Color<AnotherColorType, AnotherRedIndex, AnotherGreenIndex, AnotherBlueIndex, AnotherAlphaIndex> & color)
	{
		Color<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex> ret {};
		ret.SetRed(GetRed());
		ret.SetGreen(GetGreen());
		ret.SetBlue(GetBlue());
		ret.SetAlpha(GetAlpha());
		return ret += color;
	}

	/// <summary>
	/// Multiply color
	/// </summary>
	/// <param name="color">Color</param>
	/// <returns>Multiplied color</returns>
	template <typename ValueType>
	constexpr auto operator * (const ValueType val)
	{
		Color<T, RedIndex, GreenIndex, BlueIndex, AlphaIndex> ret {};
		ret.SetRed(GetRed());
		ret.SetGreen(GetGreen());
		ret.SetBlue(GetBlue());
		ret.SetAlpha(GetAlpha());
		return ret *= val;
	}
};

/// <summary>
/// RGBA color type
/// </summary>
template <typename T>
using RGBAColor = Color<T, 0, 1, 2, 3>;

/// <summary>
/// BGRA color type
/// </summary>
template <typename T>
using BGRAColor = Color<T, 2, 1, 0, 3>;

/// <summary>
/// ARGB color type
/// </summary>
template <typename T>
using ARGBColor = Color<T, 3, 0, 1, 2>;

/// <summary>
/// ABGR color type
/// </summary>
template <typename T>
using ABGRColor = Color<T, 3, 2, 1, 0>;

#endif