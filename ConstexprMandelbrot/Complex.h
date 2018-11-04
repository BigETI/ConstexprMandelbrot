#ifndef __COMPLEX_H__
#	define __COMPLEX_H__

/// <summary>
/// Complex number structure
/// </summary>
template <typename T>
struct Complex
{
	/// <summary>
	/// Real part
	/// </summary>
	T real;

	/// <summary>
	/// Imaginary part
	/// </summary>
	T imaginary;

	/// <summary>
	/// Get magnitude squared
	/// </summary>
	constexpr T GetMagnitudeSquared() const { return (real * real) + (imaginary * imaginary); };

	/// <summary>
	/// Add complex number
	/// </summary>
	/// <param name="complex">Complex number</param>
	/// <returns>Itself</returns>
	constexpr Complex<T> & operator += (const Complex<T> & complex)
	{
		real = real + complex.real;
		imaginary = imaginary + complex.imaginary;
		return (*this);
	}

	/// <summary>
	/// Multiply complex number
	/// </summary>
	/// <param name="complex">Complex number</param>
	/// <returns>Itself</returns>
	constexpr Complex<T> & operator *= (const Complex<T> & complex)
	{
		T real1(real);
		T imaginary1(imaginary);
		T real2(complex.real);
		T imaginary2(complex.imaginary);
		real = (real1 * real2) + (imaginary1 * imaginary2 * static_cast<T>(-1));
		imaginary = (real1 * imaginary2) + (real2 * imaginary1);
		return (*this);
	}
};

#endif